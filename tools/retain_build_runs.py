"""Retire duplicate successful build outputs; hold unique source attempts."""
import argparse, hashlib, json, os, re, shutil, time
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
    return (q.suffix in ('.c', '.h') or q.name == 'changed.s'
            or (q.name == 'source.s' and not (q.parent / 'source.c').exists() and not (q.parent / 'changed.c').exists())
            )


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

def current_inputs(now):
    if now['pilot'] != now['build']:
        raise ValueError('Current pilot/build proof is not paired; finish the full build before retirement')
    pins = {}
    for kind, parent in [('pilot', 'build/pilot/runs'), ('build', 'build/us-eu/runs')]:
        if not RUN.fullmatch(now[kind]):
            raise ValueError('Invalid current run')
        p = ROOT / parent / now[kind]
        ordinary_tree(p)
        accepted(p)
        pins[kind] = {'report_sha256': sha(p / 'report.json'), 'inputs': retained_inputs(p)}
    return pins

def input_identities(pins):
    return {(Path(name).suffix, digest) for proof in pins.values()
            for name, digest in proof['inputs'].items()}

def unique_inputs(pins, known):
    return [name for name, digest in pins.items() if (Path(name).suffix, digest) not in known]

def make_plan():
    now = current()
    proof_inputs = current_inputs(now)
    known = input_identities(proof_inputs)
    latest = {}
    operations, held = [], []
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
        protected = {now[kind]}
        latest[kind] = sorted(protected)
        for p in valid:
            if p.name in protected:
                continue
            ordinary_tree(p)
            inputs = retained_inputs(p)
            unique = unique_inputs(inputs, known)
            item = {'kind': kind, 'folder': p.relative_to(ROOT).as_posix(), 'report_sha256': sha(p / 'report.json'), 'retained_input_pins': inputs}
            if unique:
                held.append({**item, 'unique_inputs': unique, 'reason': 'Unique source/control/header input; deliberate review required'})
            else:
                operations.append(item)
    return {'version': 2, 'helper_sha256': sha(__file__), 'current': now, 'current_proof_pins': proof_inputs, 'protected_runs': latest, 'operations': operations, 'held_runs': held, 'available_before': os.statvfs(ROOT).f_bavail * os.statvfs(ROOT).f_frsize}

def apply(plan):
    if plan.get('version') != 2 or plan['helper_sha256'] != sha(__file__) or plan['current'] != current():
        raise ValueError('Changed helper/current proof')
    fresh = make_plan()
    if plan['protected_runs'] != fresh['protected_runs']:
        raise ValueError('Changed protection list')
    if plan['current_proof_pins'] != fresh['current_proof_pins']:
        raise ValueError('Changed current proof inputs')
    known = input_identities(plan['current_proof_pins'])
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
        report = accepted(p)
        if sha(p / 'report.json') != item['report_sha256'] or retained_inputs(p) != item['retained_input_pins']:
            raise ValueError('Run report or source/control inputs changed')
        if unique_inputs(item['retained_input_pins'], known):
            raise ValueError('Unique source/control/header input cannot be removed')
        allocated = files = 0
        for directory, dirs, names in os.walk(p):
            for name in names:
                q = Path(directory, name)
                allocated += q.stat().st_blocks * 512
                files += 1
        receipt = {key: value for key, value in item.items() if key != 'retained_input_pins'}
        receipt.update({'event': 'prepared', 'removed_files': files, 'removed_allocated_bytes': allocated,
                   'retained_input_count': len(item['retained_input_pins']),
                   'retained_input_pins_sha256': hashlib.sha256(json.dumps(item['retained_input_pins'], sort_keys=True, separators=(',', ':')).encode()).hexdigest(),
                   'artifacts_pruned': True, 'inputs_duplicated_in_current_proof': True,
                   'compiled_c_functions': report.get('compiled_c_functions'),
                   'compiled_c_bytes_including_pools_and_alignment': report.get('compiled_c_bytes_including_pools_and_alignment')})
        with journal.open('a') as f:
            f.write(json.dumps(receipt) + '\n')
            f.flush()
            os.fsync(f.fileno())
        sync_directories(journal.parent)
        if (plan['current'] != current() or current_inputs(plan['current']) != plan['current_proof_pins']
                or sha(p / 'report.json') != item['report_sha256'] or retained_inputs(p) != item['retained_input_pins']):
            raise ValueError('Concurrent gate/input change detected')
        shutil.rmtree(p)
        with journal.open('a') as f:
            f.write(json.dumps({'event': 'completed', 'folder': item['folder']}) + '\n')
            f.flush()
            os.fsync(f.fileno())
        print('Pruned', i + 1, 'of', len(plan['operations']), item['folder'], flush=True)
    result = {'runs_removed': len(plan['operations']), 'held_runs': len(plan['held_runs']), 'protected_runs': plan['protected_runs'], 'retained': 'current proof intact; unique source/control/header attempts and failed runs held; duplicate generated runs retired without archives', 'available_before': plan['available_before'], 'available_after': os.statvfs(ROOT).f_bavail * os.statvfs(ROOT).f_frsize}
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
        print(json.dumps({'operations': len(plan['operations']), 'held_runs': len(plan['held_runs']), 'protected_runs': plan['protected_runs']}))
