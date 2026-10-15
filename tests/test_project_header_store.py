"""Project-header inode sharing must preserve CPP identity and verification."""
from pathlib import Path
import errno, hashlib, json, multiprocessing, os, shutil, stat, sys, tempfile, unittest, subprocess
from unittest.mock import patch
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
import project_header_store as p
import header_snapshots as base
import pilot_parallel_process as parallel

def race_worker(root, index, barrier, queue):
    try:
        root = Path(root)
        barrier.wait(timeout=20)
        records = []
        for trial in range(10):
            out = root / 'proofs' / str(index) / str(trial) / 'include'
            r = base.snapshot_headers(root / 'inputs/source.c', out, root / 'include', project_header_store=root / 'cache')
            base.verify_snapshot_inputs(r, out)
            records.append((out / 'one.h').stat().st_ino)
        queue.put(dict(index=index, inodes=records))
    except BaseException as ex:
        queue.put(dict(index=index, error=repr(ex)))
        raise

class StoreTests(unittest.TestCase):

    def setUp(self):
        self.temp = tempfile.TemporaryDirectory(prefix='project-header-store-')
        self.root = Path(self.temp.name).resolve()
        self.inc = self.root / 'include'
        self.src = self.root / 'inputs'
        self.inc.mkdir()
        self.src.mkdir()
        self.cache = self.root / 'cache'
        self.source = self.src / 'source.c'
        self.source.write_text('#include "local.h"\n#include "one.h"\nint result(void){return ONE;}\n')
        (self.src / 'local.h').write_text('/* ordinary local copy */\n')
        (self.inc / 'one.h').write_text('#define ONE 1\n')
        self.out = self.root / 'proof/include'

    def tearDown(self):
        self.temp.cleanup()

    def snapshot(self, out=None):
        return base.snapshot_headers(self.source, out or self.out, self.inc, project_header_store=self.cache)

    def store(self):
        return p.ProjectHeaderStore(self.cache, self.inc, self.out,
                                    [self.source, self.src / 'local.h'])

    def obj(self, data=None):
        return self.cache / (p.object_key('one.h', data or (self.inc / 'one.h').read_bytes()) + '.h')

    def test_identical_receipt_and_retained_bytes(self):
        r = self.snapshot()
        other = self.root / 'copy/include'
        q = base.snapshot_headers(self.source, other, self.inc)
        self.assertEqual(r, q)
        self.assertEqual((self.out / 'one.h').read_bytes(), (other / 'one.h').read_bytes())
        base.verify_snapshot_inputs(r, self.out)

    def test_project_paths_share_objects_but_never_live_inputs(self):
        self.snapshot()
        other = self.root / 'second/include'
        self.snapshot(other)
        a = (self.out / 'one.h').stat()
        self.assertEqual(a.st_ino, (other / 'one.h').stat().st_ino)
        self.assertEqual(a.st_ino, self.obj().stat().st_ino)
        self.assertNotEqual(a.st_ino, (self.inc / 'one.h').stat().st_ino)
        self.assertEqual(stat.S_IMODE(a.st_mode), 292)

    def test_source_and_local_bundle_stay_independent_even_on_content_collision(self):
        content = (self.inc / 'one.h').read_bytes()
        (self.src / 'local.h').write_bytes(content)
        self.snapshot()
        obj = self.obj().stat().st_ino
        self.assertNotEqual(obj, (self.out.parent / 'source-inputs/local.h').stat().st_ino)
        self.assertNotEqual(self.source.stat().st_ino, (self.out.parent / 'source-inputs/source.c').stat().st_ino)

    def test_fresh_changed_header_gets_new_object_and_keeps_old_proof(self):
        first = self.snapshot()
        old = (self.out / 'one.h').read_bytes()
        (self.inc / 'one.h').write_text('#define ONE 2\n')
        other = self.root / 'second/include'
        second = self.snapshot(other)
        self.assertNotEqual(first['headers'], second['headers'])
        self.assertEqual((self.out / 'one.h').read_bytes(), old)
        self.assertEqual(len(list(self.cache.glob('*.h'))), 2)

    def test_deleted_header_does_not_survive_reused_output(self):
        self.snapshot()
        (self.inc / 'one.h').unlink()
        r = self.snapshot()
        self.assertNotIn('one.h', r['headers'])
        self.assertFalse((self.out / 'one.h').exists())
        self.assertEqual(r['selection'], 'all project headers')

    def test_changed_source_local_header_is_rejected(self):
        r = self.snapshot()
        (self.src / 'local.h').write_text('changed\n')
        with self.assertRaises(ValueError):
            base.verify_snapshot_inputs(r, self.out)

    def test_preexisting_poison_is_not_trusted_by_filename(self):
        store = self.store()
        obj = self.obj()
        obj.write_bytes(b'poisoned bytes!\n')
        obj.chmod(292)
        self.out.mkdir(parents=True)
        with self.assertRaisesRegex(ValueError, 'size mismatch|[Pp]oisoned'):
            store.retain((self.inc / 'one.h').read_bytes(), self.out / 'one.h', relative_path='one.h')
        self.assertFalse((self.out / 'one.h').exists())
        self.assertEqual(obj.read_bytes(), b'poisoned bytes!\n')

    def test_same_length_poison_rejected_by_digest(self):
        data = (self.inc / 'one.h').read_bytes()
        store = self.store()
        obj = self.obj()
        obj.write_bytes(b'X' * len(data))
        obj.chmod(292)
        self.out.mkdir(parents=True)
        with self.assertRaisesRegex(ValueError, '[Pp]oisoned'):
            store.retain(data, self.out / 'one.h', relative_path='one.h')

    def test_writable_existing_object_refused_not_repaired(self):
        store = self.store()
        obj = self.obj()
        obj.write_bytes((self.inc / 'one.h').read_bytes())
        self.out.mkdir(parents=True)
        with self.assertRaisesRegex(ValueError, 'read-only'):
            store.retain(obj.read_bytes(), self.out / 'one.h', relative_path='one.h')
        self.assertTrue(obj.stat().st_mode & 146)

    def test_symlink_object_refused(self):
        store = self.store()
        self.obj().symlink_to(self.inc / 'one.h')
        self.out.mkdir(parents=True)
        with self.assertRaises(ValueError):
            store.retain((self.inc / 'one.h').read_bytes(), self.out / 'one.h', relative_path='one.h')

    def test_symlink_cache_directory_refused(self):
        real = self.root / 'real'
        real.mkdir()
        self.cache.symlink_to(real, target_is_directory=True)
        with self.assertRaises(ValueError):
            self.snapshot()

    def test_cache_root_replaced_after_open_refused(self):
        store = self.store()
        self.cache.rename(self.root / 'old-cache')
        self.cache.symlink_to(self.root / 'old-cache', target_is_directory=True)
        self.out.mkdir(parents=True)
        with self.assertRaisesRegex(ValueError, 'directory changed'):
            store.retain(b'data', self.out / 'one.h', relative_path='one.h')

    def test_cache_cannot_be_a_live_header_hardlink(self):
        store = self.store()
        live = self.inc / 'one.h'
        live.chmod(292)
        os.link(live, self.obj())
        self.out.mkdir(parents=True)
        with self.assertRaisesRegex(ValueError, 'aliases a live'):
            store.retain(live.read_bytes(), self.out / 'one.h', relative_path='one.h')

    def test_cache_cannot_alias_another_same_content_live_header(self):
        other = self.inc / 'two.h'
        other.write_bytes((self.inc / 'one.h').read_bytes())
        other.chmod(292)
        store = self.store()
        os.link(other, self.obj())
        self.out.mkdir(parents=True)
        with self.assertRaisesRegex(ValueError, 'aliases a live'):
            store.retain(other.read_bytes(), self.out / 'one.h', relative_path='one.h')

    def test_existing_destination_is_not_overwritten(self):
        store = self.store()
        self.out.mkdir(parents=True)
        dest = self.out / 'one.h'
        dest.write_bytes(b'old proof')
        with self.assertRaisesRegex(ValueError, 'already exists'):
            store.retain(b'new data', dest, relative_path='one.h')
        self.assertEqual(dest.read_bytes(), b'old proof')

    def test_override_detaches_before_editing_shared_bytes(self):
        self.snapshot()
        other = self.root / 'second/include'
        self.snapshot(other)
        obj = self.obj()
        inode = obj.stat().st_ino
        old = obj.read_bytes()
        p.write_header_override(self.out / 'one.h', '#define ONE 9\n')
        self.assertNotEqual(inode, (self.out / 'one.h').stat().st_ino)
        self.assertEqual((other / 'one.h').read_bytes(), old)
        self.assertEqual(obj.read_bytes(), old)

    def test_symlink_override_is_refused(self):
        self.out.mkdir(parents=True)
        q = self.out / 'one.h'
        q.symlink_to(self.inc / 'one.h')
        with self.assertRaises(ValueError):
            p.write_header_override(q, 'broken\n')

    def test_late_shared_object_change_is_caught_by_existing_verifier(self):
        r = self.snapshot()
        obj = self.obj()
        obj.chmod(420)
        obj.write_bytes(b'X' * obj.stat().st_size)
        obj.chmod(292)
        with self.assertRaises(ValueError):
            base.verify_snapshot_inputs(r, self.out)

    def test_late_live_header_changes_caught_at_parallel_batch_boundary(self):
        f = {'name': 'result', 'source': 'inputs/source.c'}
        for kind in ['changed', 'deleted', 'added']:
            (self.inc / 'one.h').write_text('#define ONE 1\n')
            with patch.object(parallel, 'ROOT', self.root):
                pins, inventory = parallel._inputs([f], [])
                if kind == 'changed':
                    (self.inc / 'one.h').write_text('#define ONE 2\n')
                elif kind == 'deleted':
                    (self.inc / 'one.h').unlink()
                else:
                    (self.inc / 'added.h').write_text('new\n')
                with self.assertRaises(ValueError):
                    parallel._verify_inputs(pins, inventory)
            if (self.inc / 'added.h').exists():
                (self.inc / 'added.h').unlink()

    def test_cross_filesystem_or_link_failure_fails_without_copy_fallback(self):
        store = self.store()
        self.out.mkdir(parents=True)
        with patch.object(p.os, 'link', side_effect=OSError(errno.EXDEV, 'injected cross-device')):
            with self.assertRaises(OSError):
                store.retain(b'abc', self.out / 'one.h', relative_path='one.h')
        self.assertFalse((self.out / 'one.h').exists())
        self.assertEqual(list(self.cache.iterdir()), [])

    def test_short_write_never_publishes_a_content_object(self):
        store = self.store()
        self.out.mkdir(parents=True)
        with patch.object(p.os, 'write', return_value=0):
            with self.assertRaisesRegex(OSError, '[Ss]hort header-store write'):
                store.retain(b'abc', self.out / 'one.h', relative_path='one.h')
        self.assertEqual(list(self.cache.iterdir()), [])

    def test_symlink_proof_parent_is_rejected_without_touching_target(self):
        store = self.store()
        protected = self.root / 'protected'
        protected.mkdir()
        saved = protected / 'saved.h'
        saved.write_text('saved proof\n')
        alias = self.root / 'alias'
        alias.symlink_to(protected, target_is_directory=True)
        with self.assertRaisesRegex(ValueError, 'outside its retained'):
            store.retain(b'new header', alias / 'new.h', 'one.h')
        self.assertEqual(saved.read_text(), 'saved proof\n')
        self.assertFalse((protected / 'new.h').exists())

    def test_outside_proof_and_source_bundle_destinations_are_rejected(self):
        store = self.store()
        outside = self.root / 'outside'
        source_bundle = self.out.parent / 'source-inputs'
        outside.mkdir()
        source_bundle.mkdir(parents=True)
        for destination in [outside / 'one.h', source_bundle / 'one.h']:
            with self.subTest(destination=destination), self.assertRaisesRegex(
                    ValueError, 'outside its retained project-header root'):
                store.retain(b'header bytes', destination, 'one.h')
            self.assertFalse(destination.exists())
        self.assertEqual(list(self.cache.iterdir()), [])

    def test_symlink_parent_inside_allowed_header_root_is_rejected(self):
        store = self.store()
        self.out.mkdir(parents=True)
        protected = self.root / 'protected'
        protected.mkdir()
        (self.out / 'alias').symlink_to(protected, target_is_directory=True)
        with self.assertRaisesRegex(ValueError, 'destination uses a symlink'):
            store.retain(b'header bytes', self.out / 'alias/one.h', 'alias/one.h')
        self.assertFalse((protected / 'one.h').exists())

    def test_destination_name_must_match_the_project_relative_identity(self):
        store = self.store()
        self.out.mkdir(parents=True)
        with self.assertRaisesRegex(ValueError, 'does not match'):
            store.retain(b'header bytes', self.out / 'two.h', 'one.h')
        self.assertFalse((self.out / 'two.h').exists())
        self.assertEqual(list(self.cache.iterdir()), [])

    def test_read_only_source_and_local_hardlink_objects_are_rejected(self):
        data = (self.inc / 'one.h').read_bytes()
        for target in [self.source, self.src / 'local.h']:
            with self.subTest(target=target):
                target.write_bytes(data)
                target.chmod(0o444)
                store = self.store()
                obj = self.obj(data)
                os.link(target, obj)
                self.out.mkdir(parents=True, exist_ok=True)
                with self.assertRaisesRegex(ValueError, 'aliases a live project or source input'):
                    store.retain(data, self.out / 'one.h', 'one.h')
                self.assertFalse((self.out / 'one.h').exists())
                self.assertEqual(target.read_bytes(), data)
                obj.unlink()
                target.chmod(0o644)

    def test_selected_local_identity_is_passed_after_closure_resolution(self):
        # The source is still genuine C text. A same-content project/local pair
        # would otherwise let a read-only local inode impersonate a cache object.
        data = (self.inc / 'one.h').read_bytes()
        local = self.src / 'local.h'
        local.write_bytes(data)
        local.chmod(0o444)
        self.cache.mkdir()
        os.link(local, self.obj(data))
        with self.assertRaisesRegex(ValueError, 'aliases a live project or source input'):
            self.snapshot()
        self.assertEqual(local.read_bytes(), data)
        self.assertFalse((self.out / 'one.h').exists())

    def test_store_overlapping_generated_inputs_rejects_before_clearing(self):
        self.out.mkdir(parents=True)
        saved = self.out / 'saved.h'
        saved.write_text('saved proof\n')
        with self.assertRaisesRegex(ValueError, 'overlaps generated'):
            base.snapshot_headers(self.source, self.out, self.inc,
                                  project_header_store=self.out / '.objects')
        self.assertEqual(saved.read_text(), 'saved proof\n')

    def test_short_override_write_preserves_shared_proofs_and_leaves_no_temporary(self):
        self.snapshot()
        other = self.root / 'other/include'
        self.snapshot(other)
        old = self.obj().read_bytes()
        with patch.object(p.os, 'write', return_value=0):
            with self.assertRaisesRegex(OSError, 'Short header override write'):
                p.write_header_override(self.out / 'one.h', 'changed\n')
        self.assertEqual((self.out / 'one.h').read_bytes(), old)
        self.assertEqual((other / 'one.h').read_bytes(), old)
        self.assertEqual(self.obj().read_bytes(), old)
        self.assertEqual(list(self.out.glob('.override-*')), [])

    def test_four_process_creation_and_link_race(self):
        # Same bytes at two project-relative paths must retain two identities,
        # while each identity is shared by all forty independent snapshots.
        (self.inc/'two.h').write_bytes((self.inc/'one.h').read_bytes())
        self.source.write_text(self.source.read_text()+'#include "two.h"\n')
        ctx = multiprocessing.get_context('spawn')
        barrier = ctx.Barrier(4)
        queue = ctx.Queue()
        workers = [ctx.Process(target=race_worker, args=(str(self.root), i, barrier, queue)) for i in range(4)]
        for w in workers:
            w.start()
        rows = [queue.get(timeout=40) for w in workers]
        for w in workers:
            w.join(timeout=40)
            self.assertEqual(w.exitcode, 0)
        self.assertTrue(all(('error' not in r for r in rows)), rows)
        self.assertEqual(len({v for r in rows for v in r['inodes']}), 1)
        self.assertEqual(len(list(self.cache.glob('*.h'))), 2)
        self.assertEqual(len(list((self.root / 'proofs').rglob('one.h'))), 40)
        self.assertEqual(self.obj().stat().st_nlink, 41)
        other=self.cache/(p.object_key('two.h',(self.inc/'two.h').read_bytes())+'.h')
        self.assertEqual(other.stat().st_nlink,41)
        self.assertNotEqual(other.stat().st_ino,self.obj().stat().st_ino)

    def test_same_content_paths_remain_distinct_across_two_snapshots(self):
        content=b'#pragma once\n'
        (self.inc/'one.h').write_bytes(content);(self.inc/'two.h').write_bytes(content)
        self.source.write_text('#include "one.h"\n#include "two.h"\n')
        self.snapshot();other=self.root/'second/include';self.snapshot(other)
        self.assertNotEqual((self.out/'one.h').stat().st_ino,(self.out/'two.h').stat().st_ino)
        for name in ['one.h','two.h']:
            self.assertEqual((self.out/name).stat().st_ino,(other/name).stat().st_ino)

    def test_noncanonical_project_identity_is_rejected(self):
        for name in ['', '/one.h', '../one.h', 'a/../one.h', 'a//one.h', './one.h', 'a\\one.h', 'one.h/', 'one.c', 'one\0.h']:
            with self.subTest(name=name),self.assertRaises(ValueError):p.object_key(name,b'valid bytes')

    def test_two_path_keys_poisoned_to_same_inode_are_rejected(self):
        data=b'#pragma once\n'
        (self.inc/'one.h').write_bytes(data);(self.inc/'two.h').write_bytes(data)
        self.source.write_text('#include "one.h"\n#include "two.h"\n')
        self.cache.mkdir();a=self.cache/(p.object_key('one.h',data)+'.h');a.write_bytes(data);a.chmod(0o444)
        os.link(a,self.cache/(p.object_key('two.h',data)+'.h'))
        with self.assertRaisesRegex(ValueError,'[Dd]istinct project-relative'):self.snapshot()

    @unittest.skipUnless(shutil.which('xcrun'), 'Host preprocessor is not installed')
    def test_actual_CPP_pragma_once_relative_siblings_match_ordinary_copies(self):
        for name,macro in [('a','LEFT'),('b','RIGHT')]:
            d=self.inc/name;d.mkdir();(d/'role.h').write_text('#pragma once\n#include "value.h"\n');(d/'value.h').write_text('#define '+macro+' 7\n')
        self.source.write_text('#include "a/role.h"\n#include "b/role.h"\nint result=LEFT+RIGHT;\n')
        ordinary=self.root/'ordinary/include';q=base.snapshot_headers(self.source,ordinary,self.inc);r=self.snapshot();outputs=[]
        for root,receipt in [(ordinary,q),(self.out,r)]:
            out=root.parent/'source.i';deps=root.parent/'deps.d'
            cmd=['xcrun','clang','--target=arm-none-eabi','-E','-P','-undef','-nostdinc','-std=gnu89','-MD','-MF',str(deps),'-MT','snapshot','-I',str(root),str(base.retained_source(receipt,root)),'-o',str(out)]
            run=subprocess.run(cmd,capture_output=True,text=True);self.assertEqual(run.returncode,0,run.stderr);consumed=base.verify_preprocessor_dependencies(receipt,root,deps)
            self.assertTrue(all('include/'+name in consumed for name in ['a/role.h','a/value.h','b/role.h','b/value.h']))
            outputs.append(out.read_bytes())
        self.assertEqual(outputs[0],outputs[1]);self.assertIn(b'int result=7 +7;',outputs[1])

    def test_macro_fallback_and_local_copy_semantics_unchanged(self):
        self.source.write_text('#define X "one.h"\n#include X\n#include "local.h"\n')
        (self.inc / 'unused.h').write_text('/* still retained by fallback */\n')
        r = self.snapshot()
        q = base.snapshot_headers(self.source, self.root / 'plain/include', self.inc)
        self.assertEqual(r, q)
        self.assertEqual(r['selection'], 'all project headers')
        self.assertEqual(set(r['headers']), {'one.h', 'unused.h'})
if __name__ == '__main__':
    unittest.main(verbosity=2)
