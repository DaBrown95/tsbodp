"""Remove superseded successful build artifacts, retaining source/control receipts."""
import argparse, gzip, hashlib, json, os, re, shutil, time, zipfile
from pathlib import Path
ROOT = Path(__file__).resolve().parents[1]
BASE = Path('reports/us-eu/retention')
REFERENCE = '92ead9ff9467dbc23780e768278fe2e4bf7a0708447a0785770c129a5dbdb06e'
RUN = re.compile('\\d{8}T\\d{6}Z-[a-f0-9]{8}')

def sha(p):
    return hashlib.sha256(Path(p).read_bytes()).hexdigest()

def ordinary_tree(p):
    if p.is_symlink() or not p.is_dir() or p.resolve() != p or (not p.resolve().is_relative_to(ROOT / 'build')):
        raise ValueError('Unsafe build directory')
    for directory, dirs, files in os.walk(p, followlinks=False):
        for name in dirs + files:
            q = Path(directory, name)
            if q.is_symlink():
                raise ValueError('Linked artifact')

def retained_input_file(q):
    return (q.suffix == '.c' or q.name in ('header-snapshot.json', 'preprocessor.d', 'changed.s')
            or (q.name == 'source.s' and not (q.parent / 'source.c').exists() and not (q.parent / 'changed.c').exists())
            or (q.suffix == '.h' and any(part in q.parts for part in ('inline-glue-control', 'source-inputs'))))


def retained_inputs(p):
    return {q.relative_to(p).as_posix(): sha(q) for q in p.rglob('*') if q.is_file() and retained_input_file(q)}


def sync_directories(path):
    while path.is_relative_to(ROOT):
        descriptor = os.open(path, os.O_RDONLY)
        try:
            os.fsync(descriptor)
        finally:
            os.close(descriptor)
        if path == ROOT:
            break
        path = path.parent


def accepted(p):
    r = json.loads((p / 'report.json').read_text())
    if r.get('accepted') is not True or r.get('reference_sha256') != REFERENCE or r.get('run_id') != p.name:
        raise ValueError('Not a pinned successful run')
    return r

def current():
    return {kind: json.loads((ROOT / f'reports/us-eu/{kind}.json').read_text())['run_id'] for kind in ('pilot', 'build')}

def make_plan():
    now = current()
    latest = {}
    operations = []
    for kind, parent in [('pilot', ROOT / 'build/pilot/runs'), ('build', ROOT / 'build/us-eu/runs')]:
        valid = []
        for p in parent.iterdir():
            if not RUN.fullmatch(p.name) or not (p / 'report.json').is_file():
                continue
            try:
                accepted(p)
            except ValueError:
                continue
            valid.append(p)
        protected = {now[kind]} | {p.name for p in sorted(valid, key=lambda x: x.name)[-2:]}
        latest[kind] = sorted(protected)
        for p in valid:
            if p.name in protected:
                continue
            ordinary_tree(p)
            operations.append({'kind': kind, 'folder': p.relative_to(ROOT).as_posix(), 'report_sha256': sha(p / 'report.json'), 'retained_input_pins': retained_inputs(p)})
    return {'version': 1, 'helper_sha256': sha(__file__), 'current': now, 'protected_runs': latest, 'operations': operations, 'available_before': os.statvfs(ROOT).f_bavail * os.statvfs(ROOT).f_frsize}

def apply(plan):
    if plan.get('version') != 1 or plan['helper_sha256'] != sha(__file__) or plan['current'] != current():
        raise ValueError('Changed helper/current proof')
    if plan['protected_runs'] != make_plan()['protected_runs']:
        raise ValueError('Changed protection list')
    (ROOT / BASE).mkdir(parents=True, exist_ok=True)
    journal = ROOT / BASE / ('prune-' + str(time.time_ns()) + '.jsonl')
    if journal.exists():
        raise ValueError('Journal already exists')
    for i, item in enumerate(plan['operations']):
        p = ROOT / item['folder']
        expected_parent = ROOT / ('build/pilot/runs' if item['kind'] == 'pilot' else 'build/us-eu/runs')
        if p.parent != expected_parent or not RUN.fullmatch(p.name) or p.name in plan['protected_runs'][item['kind']]:
            raise ValueError('Invalid run selection')
        ordinary_tree(p)
        accepted(p)
        if sha(p / 'report.json') != item['report_sha256'] or retained_inputs(p) != item['retained_input_pins']:
            raise ValueError('Run report or source/control inputs changed')
        dest = ROOT / 'reports/pruned-build-runs' / item['kind'] / p.name
        if dest.exists():
            raise ValueError('Receipt destination exists')
        dest.mkdir(parents=True)
        report_data = (p / 'report.json').read_bytes()
        compressed = gzip.compress(report_data, mtime=0)
        assert gzip.decompress(compressed) == report_data
        (dest / 'report.json.gz').write_bytes(compressed)
        selected = []
        allocated = files = 0
        for directory, dirs, names in os.walk(p):
            for name in names:
                q = Path(directory, name)
                allocated += q.stat().st_blocks * 512
                files += 1
                if retained_input_file(q):
                    selected.append(q)
        archive = dest / 'sources-and-controls.zip'
        pins = {}
        with zipfile.ZipFile(archive, 'w', zipfile.ZIP_DEFLATED, compresslevel=6) as z:
            for q in selected:
                name = q.relative_to(p).as_posix()
                data = q.read_bytes()
                pins[name] = hashlib.sha256(data).hexdigest()
                z.writestr(name, data)
            z.writestr('_source_hashes.json', json.dumps(pins, sort_keys=True))
        with zipfile.ZipFile(archive) as z:
            assert set(z.namelist()) == set(pins) | {'_source_hashes.json'}
            for name, digest in pins.items():
                assert hashlib.sha256(z.read(name)).hexdigest() == digest
        assert hashlib.sha256(gzip.decompress((dest / 'report.json.gz').read_bytes())).hexdigest() == item['report_sha256']
        receipt = {**item, 'event': 'prepared', 'removed_files': files, 'removed_allocated_bytes': allocated, 'retained_sources_and_header_receipts': len(pins), 'archive_sha256': sha(archive), 'artifacts_pruned': True, 'report_file': 'report.json.gz', 'report_compressed_sha256': sha(dest / 'report.json.gz')}
        (dest / 'artifacts-pruned.json').write_text(json.dumps(receipt, indent=2) + '\n')
        for q in [archive, dest / 'report.json.gz', dest / 'artifacts-pruned.json']:
            with q.open('rb') as f:
                os.fsync(f.fileno())
        with journal.open('a') as f:
            f.write(json.dumps(receipt) + '\n')
            f.flush()
            os.fsync(f.fileno())
        sync_directories(dest)
        sync_directories(journal.parent)
        if plan['current'] != current() or sha(p / 'report.json') != item['report_sha256'] or retained_inputs(p) != item['retained_input_pins']:
            raise ValueError('Concurrent gate/input change detected')
        shutil.rmtree(p)
        with journal.open('a') as f:
            f.write(json.dumps({'event': 'completed', 'folder': item['folder']}) + '\n')
            f.flush()
            os.fsync(f.fileno())
        print('Pruned', i + 1, 'of', len(plan['operations']), item['folder'], flush=True)
    result = {'runs_removed': len(plan['operations']), 'protected_runs': plan['protected_runs'], 'retained': 'original run report and compressed C/control sources plus header hash receipts; current and previous full proofs retained intact', 'available_before': plan['available_before'], 'available_after': os.statvfs(ROOT).f_bavail * os.statvfs(ROOT).f_frsize}
    result['available_gain_bytes'] = result['available_after'] - result['available_before']
    (ROOT / BASE / 'latest-audit.json').write_text(json.dumps(result, indent=2) + '\n')
    print(json.dumps(result), flush=True)
if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--plan', type=Path, default=ROOT / BASE / 'plan.json')
    parser.add_argument('--apply', action='store_true')
    args = parser.parse_args()
    if args.apply:
        apply(json.loads(args.plan.read_text()))
    else:
        plan = make_plan()
        args.plan.parent.mkdir(parents=True, exist_ok=True)
        args.plan.write_text(json.dumps(plan, indent=2) + '\n')
        print(json.dumps({'operations': len(plan['operations']), 'protected_runs': plan['protected_runs']}))
