"""Synthetic failure tests for private scheduling, separate from native byte proofs."""
from pathlib import Path
import ast
import copy
import importlib.util
import json
import sys
import tempfile
import threading
import time
import unittest
from unittest.mock import patch
from concurrent.futures import ThreadPoolExecutor

sys.path.insert(0,'tools')
MODULE=Path(__file__).resolve().parents[1]/'tools/pilot_parallel_process.py'


class ParallelPilotTests(unittest.TestCase):
    def setUp(self):
        spec=importlib.util.spec_from_file_location('private_parallel_under_test',MODULE)
        self.module=importlib.util.module_from_spec(spec)
        spec.loader.exec_module(self.module)
        self.temporary=tempfile.TemporaryDirectory(prefix='private-parallel-pilot-')
        self.addCleanup(self.temporary.cleanup)
        self.root=Path(self.temporary.name)
        self.module.ROOT=self.root
        (self.root/'include').mkdir()
        (self.root/'include/test.h').write_text('original header\n')
        (self.root/'src').mkdir()
        (self.root/'src/fixture.c').write_text('unsigned fixture(void) { return 7; }\n')
        self.function=dict(name='fixture',source='src/fixture.c',rom_offset=0,size=4,symbols={},negative_control=dict(before='return 7;',after='return 8;'))
        self.rom=b'ABCD1234'

    def compile(self,fn,source,folder,flags,header_overrides=None):
        folder.mkdir(parents=True,exist_ok=True)
        (folder/'include').mkdir(exist_ok=True)
        (folder/'include/bios.h').write_text('.byte 0\n')
        changed='return 8;'in source.read_text()or bool(header_overrides)
        raw=self.rom[:fn['size']]
        return (b'X'+raw[1:]if changed else raw),[['synthetic-compiler',*fn.get('compiler_flags',flags)]]

    def batch(self,**changes):
        args=dict(functions=[self.function],run_folder=self.root/'proof',flags=['-O2','-mthumb-interwork'],rom=self.rom,copies=[],negative_control=True,matrix=False,jobs=1,compile_c=self.compile,assemble_low_level=lambda fn,src,folder:self.compile(fn,src,folder,[]))
        args.update(changes)
        return self.module.compile_candidates(**args)

    def test_invalid_jobs_fail_before_any_output(self):
        for jobs in[0,-1,9,True,False,1.5,'2',None]:
            with self.subTest(jobs=jobs),self.assertRaisesRegex(ValueError,'jobs'):
                self.batch(jobs=jobs)
        self.assertFalse((self.root/'proof').exists())

    def test_duplicate_casefold_or_unsafe_names_fail_before_workers(self):
        for name in['fixture','FIXTURE','../escape','a/b','bad-name','']:
            other=dict(self.function,name=name)
            with self.subTest(name=name),self.assertRaisesRegex(ValueError,'duplicate|unsafe'):
                self.batch(functions=[self.function,other])
        self.assertFalse((self.root/'proof').exists())

    def test_existing_outputs_and_empty_cohort_reject(self):
        with self.assertRaisesRegex(ValueError,'empty'):
            self.batch(functions=[])
        (self.root/'proof').mkdir()
        with self.assertRaisesRegex(ValueError,'fresh'):
            self.batch()

    def test_missing_changed_source_control_rejects(self):
        fn=dict(self.function)
        fn.pop('negative_control')
        with self.assertRaisesRegex(ValueError,'Required control'):
            self.batch(functions=[fn])

    def scheduled(self, items, worker, jobs):
        # Exercise the actual process coordinator with deterministic in-process
        # workers. Real spawned/native success and failure receipts are separate.
        contexts = []
        def executor(**kwargs):
            contexts.append(kwargs.pop('mp_context').get_start_method())
            return ThreadPoolExecutor(**kwargs)
        with patch.object(self.module, 'ProcessPoolExecutor', executor), \
             patch.object(self.module, '_process_candidate', worker):
            result = self.module._process_results(items, {}, jobs)
        self.assertEqual(contexts, ['spawn'])
        return result

    def test_completion_order_never_changes_manifest_order(self):
        completed=[]
        def worker(value):
            time.sleep((6-value)*0.002)
            completed.append(value)
            return value*3
        self.assertEqual(self.scheduled(list(range(6)),worker,3),[x*3 for x in range(6)])
        self.assertNotEqual(completed,list(range(6)))

    def test_active_workers_never_exceed_jobs(self):
        lock=threading.Lock();barrier=threading.Barrier(3);active=maximum=0
        def worker(value):
            nonlocal active,maximum
            with lock:
                active+=1;maximum=max(maximum,active)
            if value<3:barrier.wait(timeout=2)
            time.sleep(.002)
            with lock:active-=1
            return value
        self.assertEqual(self.scheduled(list(range(12)),worker,3),list(range(12)))
        self.assertEqual(maximum,3)

    def test_worker_error_drains_running_work_and_cannot_publish_partial(self):
        started=threading.Event();released=threading.Event();finished=threading.Event();published=[]
        def worker(value):
            if value==0:
                self.assertTrue(started.wait(2));released.set();raise RuntimeError('actual worker failure')
            if value==1:
                started.set();self.assertTrue(released.wait(2));time.sleep(.01);finished.set()
            return value
        with self.assertRaisesRegex(RuntimeError,'actual worker failure'):
            published.extend(self.scheduled(list(range(12)),worker,2))
        self.assertEqual(published,[])
        self.assertTrue(finished.is_set())

    def test_source_changed_during_worker_fails_closed(self):
        def compiler(*args,**kwargs):
            result=self.compile(*args,**kwargs)
            (self.root/'src/fixture.c').write_text('changed live source\n')
            return result
        with self.assertRaisesRegex(ValueError,'source changed'):
            self.batch(compile_c=compiler)

    def test_project_header_or_inventory_change_fails_closed(self):
        for change in['contents','new-header']:
            with self.subTest(change=change):
                def compiler(*args,**kwargs):
                    result=self.compile(*args,**kwargs)
                    path=self.root/('include/test.h'if change=='contents'else'include/new.h')
                    path.write_text('changed header\n')
                    return result
                with self.assertRaisesRegex(ValueError,'batch input changed|inventory changed'):
                    self.batch(compile_c=compiler,run_folder=self.root/change)

    def test_extra_pinned_input_changed_fails_closed(self):
        extra=self.root/'pinned.json';extra.write_text('{}')
        def compiler(*args,**kwargs):
            result=self.compile(*args,**kwargs);extra.write_text('{"changed":true}');return result
        with self.assertRaisesRegex(ValueError,'batch input changed'):
            self.batch(compile_c=compiler,extra_inputs=[extra])

    def test_optional_store_default_preserves_existing_compiler_signature(self):
        self.assertTrue(self.batch()[0]['source_reconstruction_verified'])

    def test_per_run_store_reaches_compiler_and_spawn_context(self):
        output = self.root.resolve() / 'stored-proof'
        store = output / '.project-header-content'
        observed = []
        def compiler(*args, project_header_store=None, **kwargs):
            observed.append(project_header_store)
            return self.compile(*args, **kwargs)
        def processes(functions, context, jobs):
            self.assertEqual(jobs, 4)
            self.assertEqual(context['project_header_store'], store)
            self.module._initialize_process(context)
            return [self.module._process_candidate(f) for f in functions]
        with patch.object(self.module, '_process_results', side_effect=processes):
            results = self.batch(run_folder=output, project_header_store=store,
                                 compile_c=compiler, jobs=4)
        self.assertTrue(results[0]['source_reconstruction_verified'])
        self.assertEqual(observed, [store, store])

    def test_shared_global_wrong_named_or_existing_store_is_rejected(self):
        output = self.root.resolve() / 'proof'
        for store in [self.root.resolve() / 'global-cache', output / 'fixture',
                      output / 'nested/.project-header-content']:
            with self.subTest(store=store), self.assertRaisesRegex(ValueError, 'fresh per-run'):
                self.batch(run_folder=output, project_header_store=store)
        self.assertFalse(output.exists())
        outside = self.root.resolve() / 'outside'
        outside.mkdir()
        output.mkdir()
        (output / '.project-header-content').symlink_to(outside, target_is_directory=True)
        with self.assertRaisesRegex(ValueError, 'fresh per-run'):
            self.batch(run_folder=output, project_header_store=output / '.project-header-content')

    def test_actual_controls_and_split_glue_classification_preserved(self):
        results=self.batch()
        self.assertTrue(results[0]['source_reconstruction_verified'])
        self.assertFalse(results[0]['assembly_glue_verified'])
        self.assertTrue(results[0]['negative_control']['rejected'])
        fn=dict(self.function,kind='assembly_glue')
        results=self.batch(functions=[fn],run_folder=self.root/'glue')
        self.assertFalse(results[0]['source_reconstruction_verified'])
        self.assertTrue(results[0]['assembly_glue_verified'])
        self.assertEqual(results[0]['compiled_c_bytes'],0)

    def test_matrix_retains_nondefault_mode_and_cpu_flags(self):
        fn=dict(self.function,compiler_id='gcc302',mode='ARM',compiler_flags=['-O3','-marm','-mthumb-interwork','-mcpu=arm7tdmi'])
        row=self.batch(functions=[fn],matrix=True)[0]
        self.assertEqual([x['flags'][0]for x in row['optimization_trials']],['-O0','-O1','-O2','-O3','-Os'])
        self.assertTrue(all(x['flags'][1:]==fn['compiler_flags'][1:]for x in row['optimization_trials']))

    def test_inline_glue_control_and_credit_remain_separate(self):
        fn=dict(self.function,size=8,inline_glue=dict(source='include/bios.h',begin_prefix='__tsbodp_glue_bios_begin_',end_prefix='__tsbodp_glue_bios_end_',spans=[dict(offset=4,size=4)],negative_control=dict(before='.byte 0',after='.byte 1')))
        row=self.batch(functions=[fn])[0]
        self.assertTrue(row['inline_glue_control']['rejected'])
        self.assertTrue(row['inline_glue_verified'])
        self.assertEqual((row['compiled_c_bytes'],row['assembly_glue_bytes']),(4,4))



if __name__=='__main__':unittest.main(verbosity=2)
