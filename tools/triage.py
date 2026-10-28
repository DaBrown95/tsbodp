"""Inventory-driven remaining-C queue. Diagnostic receipts never grant C credit."""
import argparse
from collections import Counter
import hashlib
import json
import os
from pathlib import Path, PurePosixPath
import re
import tempfile

from toolchain import compiler_selection

ROOT = Path(__file__).resolve().parents[1]
OUTPUT = 'config/triage-us-eu.json'
MARKDOWN = 'docs/TRIAGE.md'
PRIORITY = (0x3D788, 0xB840, 0xF034, 0x180D4, 0x38B90, 0x48A14, 0x23E8)
FAR_OFF = {0x3DC48, 0x3248, 0x1AA78, 0x19640, 0xB564, 0x1510C, 0x1B300}
SKIP = {'normal', 'strict', 'header-store', 'include', 'source-inputs', 'build',
        'gcc', 'gcc_arm', 'node_modules', '__pycache__', 'qualification'}
MAX_JSON = 4_000_000
MAX_METADATA = 5000
REJECT = re.compile(r'(?:SEMANTIC.*REJECT|REJECT.*(?:SEMANTIC|INHERITED)|'
                    r'COLLISION|INVALID_C|UNQUALIFIED|STALE)', re.I)
STATUS_KEYS = {'status', 'validity_status', 'source_status', 'semantic_status',
               'classification', 'source_validity'}
CLOSED = {
    0x49968: 'Reachable native NOP remains unexplained; suspected non-C origin.',
    0xA0A4: 'Inventory290; retained full comparison292. Rejected cursor/header models excluded.',
    0x48AF8: 'Inventory126; retained full comparison128 includes trailing alignment.',
    0x48BF8: 'Inventory86; retained full comparison88 includes trailing alignment.',
    0x42964: 'Matching 656-byte C owner accepted; earlier request/ordinal binding collision excluded.',
    0x19D80: 'Historical volatile368/121 is unqualified; use ordinary-state evidence.',
    0x1510C: 'Rejected induction-register collision excluded.',
}


def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def relative(value):
    """Accept only publication-safe repository paths, never machine paths."""
    if not isinstance(value, str) or not value or '\\' in value or '\x00' in value:
        raise ValueError('Invalid relative evidence path')
    p = PurePosixPath(value)
    if p.is_absolute() or '..' in p.parts or ':' in value or str(p) != value:
        raise ValueError('Unsafe relative evidence path')
    if any(ord(c) < 32 for c in value):
        raise ValueError('Control character in evidence path')
    return value


def local(root, value):
    p = root / relative(value)
    if any(x.is_symlink() for x in (p, *p.parents) if x != root and root in x.parents):
        raise ValueError('Symlink in evidence or output path')
    if not p.resolve().is_relative_to(root.resolve()):
        raise ValueError('Path escapes repository')
    return p


def read_json(path, limit=MAX_JSON):
    if path.stat().st_size > limit:
        raise ValueError('Evidence JSON exceeds bounded size')
    try:
        return json.loads(path.read_text())
    except (UnicodeError, json.JSONDecodeError) as exc:
        raise ValueError('Malformed evidence JSON') from exc


def integer(value, minimum=0):
    return isinstance(value, int) and not isinstance(value, bool) and value >= minimum


def inventory_rows(progress, inventory):
    if progress.get('target') != 'us-eu' or inventory.get('target') != 'us-eu':
        raise ValueError('Unsupported or conflicting inventory target')
    if progress.get('reference_sha256') != inventory.get('reference_sha256'):
        raise ValueError('Conflicting fixed-reference identities')
    indexed = {}
    for row in inventory.get('rows', []):
        off = row.get('rom_offset')
        if not integer(off) or off in indexed:
            raise ValueError('Malformed or duplicate inventory row')
        indexed[off] = row
    rows, seen = [], set()
    for row in progress.get('rows', []):
        if row.get('status') not in ('mapped_code', 'candidate'):
            continue
        off = row.get('rom_offset')
        if (not integer(off) or off in seen or not integer(row.get('size'), 1)
                or not isinstance(row.get('name'), str)
                or not re.fullmatch(r'[A-Za-z_][A-Za-z0-9_]*', row['name'])):
            raise ValueError('Malformed or duplicate unowned progress row')
        native = indexed.get(off, {})
        if native.get('size') != row['size'] or native.get('mode') not in ('ARM', 'Thumb'):
            raise ValueError('Progress/inventory extent or mode disagreement')
        addresses = native.get('runtime_addresses', [])
        if not addresses or any(not integer(a) for a in addresses):
            raise ValueError('Missing or malformed execution address')
        seen.add(off)
        rows.append({**row, 'mode': native['mode'], 'runtime_addresses': addresses})
    return sorted(rows, key=lambda row: row['rom_offset'])


def walk_records(value):
    if isinstance(value, dict):
        yield value
        for child in value.values():
            yield from walk_records(child)
    elif isinstance(value, list):
        for child in value:
            yield from walk_records(child)


def comparison(value):
    """Require an explicitly complete byte-comparison schema, not a local score."""
    choices = []
    for item in walk_records(value):
        fields = ('reference_size', 'candidate_size', 'differing_bytes_including_missing_or_extra')
        if all(integer(item.get(k)) for k in fields):
            extent, size, diff = (item[k] for k in fields)
            if extent <= 0 or size <= 0 or diff > max(extent, size) or diff < abs(extent-size):
                raise ValueError('Impossible full comparison')
            choices.append((extent, size, diff, item))
    if len({x[:3] for x in choices}) != 1:
        raise ValueError('Missing or ambiguous full comparison')
    return choices[0]


def rejected(value, source_hash, name):
    for record in walk_records(value):
        matches = (record is value or record.get('name') == name or record.get('trial') == name
                   or record.get('source_sha256') == source_hash)
        if not matches:
            continue
        if record.get('invalid_C') is True or record.get('source_valid_under_recorded_premises') is False:
            return True
        if any(isinstance(record.get(k), str) and REJECT.search(record[k]) for k in STATUS_KEYS):
            return True
    return False


def bounded_metadata(root):
    found = []
    for prefix in ('analysis', 'reports/current-goal'):
        start = root / prefix
        if not start.exists() or start.is_symlink():
            continue
        for folder, dirs, files in os.walk(start, followlinks=False):
            p = Path(folder)
            depth = len(p.relative_to(start).parts)
            dirs[:] = sorted(d for d in dirs if depth < 3 and d not in SKIP
                             and not d.startswith('.') and not (p / d).is_symlink()
                             and not any(s in d for s in ('host-feasibility', 'toolchain', 'compiler-build')))
            if 'metadata.json' in files:
                found.append(p / 'metadata.json')
    if len(found) > MAX_METADATA:
        raise ValueError('Bounded metadata scan limit exceeded')
    return sorted(found)


def evidence_documents(folder, root, cache):
    result = []
    for parent in (folder, folder.parent):
        if parent == root / 'analysis':
            continue
        for name in ('final-assessment.json', 'assessment.json', 'plan.json', 'peer-source-review.json'):
            p = parent / name
            if p.is_file() and not p.is_symlink():
                if p not in cache:
                    cache[p] = read_json(p)
                result.append((p, cache[p]))
    return result


def private_header_hashes(documents, root):
    hashes = {}
    def visit(value, context=''):
        if isinstance(value, dict):
            path, digest = value.get('path'), value.get('sha256')
            if (isinstance(path, str) and path.endswith('.h') and isinstance(digest, str)
                    and ('private' in context.lower() or 'override' in context.lower()
                         or 'private' in path.lower() or 'override' in path.lower())):
                try:
                    if sha(local(root, path)) == digest:
                        hashes[digest] = path
                except (OSError, ValueError):
                    pass
            for key, child in value.items():
                visit(child, context + '/' + key)
        elif isinstance(value, list):
            for child in value:
                visit(child, context)
    for _, value in documents:
        visit(value)
    return hashes


def candidate(root, metadata_path, metadata, row, cache):
    folder = metadata_path.parent
    source_name = relative(metadata.get('source'))
    if not source_name.startswith(('analysis/', 'src/')) or not source_name.endswith('.c'):
        raise ValueError('Unsupported candidate source location')
    source = local(root, source_name)
    source_hash = sha(source)
    # This named historical line was explicitly disqualified by the later
    # ordinary-state review; a low score is not a source qualification.
    if row['rom_offset'] == 0x19D80 and (re.search(r'\bvolatile\s+int\s+current_x\b', source.read_text())
                                         or 'position_storage' in source.read_text()):
        raise ValueError('Explicitly unqualified historical workspace model')
    receipt = folder / 'result.json'
    result = read_json(receipt)
    extent, size, diff, full = comparison(result)
    if metadata.get('size') != extent or metadata.get('mode', 'Thumb') != row['mode']:
        raise ValueError('Metadata/comparison extent or mode disagreement')
    selection = compiler_selection(metadata, ['-O2', '-mthumb-interwork'])
    if any(not re.fullmatch(r'-[A-Za-z0-9_=+.,-]+', flag) for flag in selection['flags']):
        raise ValueError('Unsafe or nonportable compiler flags')
    expected_backend = 'agbcc_arm' if row['mode'] == 'ARM' else 'gcc302' if row['rom_offset'] == 0x49968 else 'agbcc'
    if selection['compiler_id'] != expected_backend:
        raise ValueError('Different experimental compiler backend')
    docs = evidence_documents(folder, root, cache)
    assessments = [(p, x) for p, x in docs if p.name in ('assessment.json', 'final-assessment.json')]
    if not assessments:
        raise ValueError('No retained assessment')
    if rejected(result, source_hash, folder.name) or any(rejected(x, source_hash, folder.name) for _, x in assessments):
        raise ValueError('Explicit semantic rejection or unqualified source')
    normal = folder / 'normal'
    snapshot = read_json(normal / 'header-snapshot.json')
    bundle = snapshot.get('source_bundle', {})
    if bundle.get('source_sha256') != source_hash:
        raise ValueError('Stale source snapshot')
    if sha(normal / 'source-inputs' / bundle.get('source', 'source.c')) != source_hash:
        raise ValueError('Stale retained source')
    recorded_hash = result.get('source_sha256')
    if recorded_hash is not None and recorded_hash != source_hash:
        raise ValueError('Stale comparison source')
    headers = snapshot.get('headers')
    if not isinstance(headers, dict) or not headers:
        raise ValueError('Missing header closure')
    private_hashes = private_header_hashes(docs, root)
    overrides = {}
    for name, digest in sorted(headers.items()):
        relative(name)
        if sha(normal / 'include' / name) != digest:
            raise ValueError('Stale retained header')
        public = root / 'include' / name
        if not public.is_file() or sha(public) != digest:
            if digest not in private_hashes:
                raise ValueError('Stale or unqualified private header')
            overrides[name] = {'path': private_hashes[digest], 'sha256': digest}
    locals_ = bundle.get('source_local_headers', {})
    for name, digest in locals_.items():
        relative(name)
        if sha(normal / 'source-inputs' / name) != digest:
            raise ValueError('Stale source-local header')
    raw = normal / 'candidate.bin'
    expected_hash = result.get('raw_sha256', full.get('candidate_hashes', {}).get('sha256'))
    if not isinstance(expected_hash, str):
        expected_hash = result.get('raw', {}).get('sha256') if isinstance(result.get('raw'), dict) else None
    if not isinstance(expected_hash, str) or raw.stat().st_size != size or sha(raw) != expected_hash:
        raise ValueError('Missing or stale complete candidate bytes')
    if not (normal / 'linked.elf').is_file():
        raise ValueError('Retained linked ELF unavailable')
    return dict(source=source_name, source_sha256=source_hash,
                metadata=metadata_path.relative_to(root).as_posix(), metadata_sha256=sha(metadata_path),
                receipt=receipt.relative_to(root).as_posix(), receipt_sha256=sha(receipt),
                assessment=assessments[0][0].relative_to(root).as_posix(),
                assessment_sha256=sha(assessments[0][0]), candidate_bytes=size,
                comparison_extent_bytes=extent, full_byte_differences=diff,
                candidate_sha256=expected_hash, evidence_state='retained-inputs-revalidated',
                private_header_qualification='private-provisional' if overrides or locals_ else 'canonical-current',
                header_overrides=overrides, private_headers=sorted(overrides), source_local_headers=sorted(locals_),
                compiler_id=selection['compiler_id'], compiler_flags=selection['flags'],
                qualification='Diagnostic only; source/backing/API premises and full acceptance gates remain.')


def portable_best(root, previous, row):
    old = previous.get(row['rom_offset'], {})
    best = old.get('best_candidate')
    if not isinstance(best, dict) or old.get('mode') != row['mode']:
        return None
    required = ('source', 'metadata', 'receipt', 'assessment')
    try:
        paths = [local(root, best[k]) for k in required]
        if any(p.exists() for p in paths):
            return None  # A changed or stale local attempt must not be rescued.
        for key in required:
            if not re.fullmatch('[0-9a-f]{64}', best[key + '_sha256']):
                return None
        size, extent, diff = (best[k] for k in ('candidate_bytes', 'comparison_extent_bytes', 'full_byte_differences'))
        if not all(integer(v, 1 if i < 2 else 0) for i, v in enumerate((size, extent, diff))):
            return None
        if not abs(size-extent) <= diff <= max(size, extent):
            return None
        compiler_selection({'mode': row['mode'], 'compiler_id': best['compiler_id'],
                            'compiler_flags': best['compiler_flags']}, [])
        if (best.get('private_header_qualification') not in ('private-provisional', 'canonical-current')
                or not re.fullmatch('[0-9a-f]{64}', best['candidate_sha256'])
                or any(not re.fullmatch(r'-[A-Za-z0-9_=+.,-]+', f) for f in best['compiler_flags'])):
            return None
        for name in best.get('private_headers', []) + best.get('source_local_headers', []):
            relative(name)
        for name, item in best.get('header_overrides', {}).items():
            relative(name)
            relative(item['path'])
            if not re.fullmatch('[0-9a-f]{64}', item['sha256']):
                return None
    except (KeyError, TypeError, ValueError):
        return None
    # Copy only this tool's published schema, never arbitrary input keys/text.
    keys = ('source', 'source_sha256', 'metadata', 'metadata_sha256', 'receipt', 'receipt_sha256',
            'assessment', 'assessment_sha256', 'candidate_bytes', 'comparison_extent_bytes',
            'full_byte_differences', 'candidate_sha256', 'private_header_qualification',
            'private_headers', 'source_local_headers', 'header_overrides', 'compiler_id', 'compiler_flags')
    result = {k: best[k] for k in keys if k in best}
    result['evidence_state'] = 'recorded-not-revalidated'
    result['qualification'] = 'Recorded diagnostic only; private inputs unavailable for current revalidation.'
    return result


def search_time_records(root, offsets):
    """Keep explicit log measurements separate; do not infer or sum overlaps."""
    records = {offset: [] for offset in offsets}
    count = 0
    start = root / 'reports/current-goal'
    if not start.exists() or start.is_symlink():
        return records, count
    for folder, dirs, files in os.walk(start, followlinks=False):
        p = Path(folder)
        depth = len(p.relative_to(start).parts)
        dirs[:] = sorted(d for d in dirs if depth < 2 and d not in SKIP
                         and not d.startswith('.') and not(p / d).is_symlink())
        for name in sorted(set(files) & {'continuation.json', 'search-ledger.json', 'ledger.json'}):
            path = p / name
            if path.is_symlink() or path.stat().st_size > MAX_JSON:
                continue
            try:
                data = read_json(path)
            except ValueError:
                continue
            count += 1
            for record in walk_records(data):
                off, seconds = record.get('rom_offset'), record.get('search_wall_seconds')
                if off in records and isinstance(seconds, (int, float)) and not isinstance(seconds, bool) and 0 <= seconds < 1e9:
                    item = {'receipt': path.relative_to(root).as_posix(), 'receipt_sha256': sha(path),
                            'search_wall_seconds': seconds}
                    if item not in records[off]:
                        records[off].append(item)
    return records, count


def validated_searches(root, rows, reference_sha256):
    """Read fresh adapter comparisons, never upstream scores as byte equality."""
    found = {off: [] for off in rows}
    rejected_count = 0
    base = root / 'analysis/permuter'
    if not base.is_dir() or base.is_symlink():
        return found, rejected_count
    paths = sorted(base.glob('*/validation-*/result.json'))
    if len(paths) > 5000:
        raise ValueError('Bounded search-validation limit exceeded')
    for path in paths:
        try:
            local(root, path.relative_to(root).as_posix())
            result = read_json(path)
            if result.get('status') not in ('NONMATCH', 'FULL_BYTES_MATCH_REVIEW_REQUIRED'):
                raise ValueError('Unsupported search validation')
            manifest, source_record = result['job_manifest'], result['candidate_source']
            job_path = local(root, manifest['path'])
            source = local(root, source_record['path'])
            if sha(job_path) != manifest['sha256'] or sha(source) != source_record['sha256']:
                raise ValueError('Stale search input')
            if rejected(result, source_record['sha256'], path.parent.name):
                raise ValueError('Explicit semantic rejection or unqualified search source')
            job = read_json(job_path)
            function = job['function']
            off = function['rom_offset']
            if off not in rows:
                continue
            if (job.get('reference_rom_sha256') != reference_sha256 or not job.get('safe_weights_reviewed')
                    or not job.get('full_byte_validation_required') or job.get('mode') != rows[off]['mode']
                    or job.get('execution_address') not in rows[off]['runtime_addresses']):
                raise ValueError('Search target/context disagreement')
            selected = compiler_selection(function, ['-O2', '-mthumb-interwork'])
            if any(not re.fullmatch(r'-[A-Za-z0-9_=+.,-]+', f) for f in selected['flags']):
                raise ValueError('Unsafe search flags')
            extent, size, diff, full = comparison(result)
            if extent != function['size']:
                raise ValueError('Search comparison extent disagreement')
            folder = path.parent
            raw = folder / 'candidate.bin'
            if (raw.stat().st_size != size or sha(raw) != full['candidate_hashes']['sha256']
                    or sha(folder / 'source.c') != source_record['sha256']
                    or not (folder / 'linked.elf').is_file()):
                raise ValueError('Stale search validation artifacts')
            immutable = {relative(x['path']): x['sha256'] for x in job['immutable_inputs']}
            snapshot_path = job_path.parent / 'context/header-snapshot.json'
            if immutable.get(snapshot_path.relative_to(root).as_posix()) != sha(snapshot_path):
                raise ValueError('Stale search header snapshot')
            snapshot = read_json(snapshot_path)
            private = bool(snapshot.get('source_bundle', {}).get('source_local_headers'))
            for name, digest in snapshot['headers'].items():
                relative(name)
                if sha(snapshot_path.parent / 'include' / name) != digest:
                    raise ValueError('Stale search retained header')
                public_name = 'include/' + name
                if public_name in immutable:
                    if sha(local(root, public_name)) != immutable[public_name] or immutable[public_name] != digest:
                        raise ValueError('Stale search public header')
                else:
                    private = True
            found[off].append(dict(source=source_record['path'], source_sha256=source_record['sha256'],
                                  receipt=path.relative_to(root).as_posix(), receipt_sha256=sha(path),
                                  job_manifest=manifest['path'], job_manifest_sha256=manifest['sha256'],
                                  candidate_bytes=size, comparison_extent_bytes=extent,
                                  full_byte_differences=diff, candidate_sha256=sha(raw),
                                  source_review='pending', source_credit=0,
                                  private_header_qualification='private-provisional' if private else 'canonical-current',
                                  compiler_id=selected['compiler_id'], compiler_flags=selected['flags']))
        except (OSError, ValueError, KeyError, TypeError):
            rejected_count += 1
    return found, rejected_count


def build(root, previous=None):
    root = root.resolve()
    inputs = ('assets/progress.json', 'assets/rom-inventory.json', 'docs/COMPLETION_BLOCKERS.md')
    progress, inventory = (read_json(root / p, 64_000_000) for p in inputs[:2])
    if progress.get('input_sha256', {}).get(inputs[1]) != sha(root / inputs[1]):
        raise ValueError('Progress references a stale inventory')
    rows = inventory_rows(progress, inventory)
    by_offset = {r['rom_offset']: r for r in rows}
    old = {}
    for r in (previous or {}).get('rows', []):
        if not isinstance(r, dict) or not integer(r.get('rom_offset')) or r['rom_offset'] in old:
            raise ValueError('Malformed or duplicate prior triage row')
        old[r['rom_offset']] = r
    candidates = {off: [] for off in by_offset}
    drafts = {off: set() for off in by_offset}
    attempts, exclusions, cache = Counter(), {off: Counter() for off in by_offset}, {}
    paths = bounded_metadata(root)
    malformed = 0
    for path in paths:
        off = None
        try:
            metadata = read_json(path)
            if not isinstance(metadata, dict):
                continue
            off = metadata.get('rom_offset')
            if off not in by_offset:
                continue
            attempts[off] += 1
            source = local(root, metadata.get('source'))
            if source.is_file() and source.suffix == '.c':
                drafts[off].add(source.relative_to(root).as_posix())
            candidates[off].append(candidate(root, path, metadata, by_offset[off], cache))
        except (OSError, ValueError, KeyError, TypeError) as exc:
            if off in by_offset:
                reason = str(exc) if isinstance(exc, ValueError) else 'Missing or malformed retained input'
                exclusions[off][reason] += 1
            else:
                malformed += 1
    time_records, receipt_count = search_time_records(root, by_offset)
    searches, rejected_searches = validated_searches(root, by_offset, progress['reference_sha256'])
    output = []
    for row in rows:
        off = row['rom_offset']
        eligible = candidates[off]
        best = min(eligible, key=lambda c: (c['full_byte_differences'],
                   abs(c['candidate_bytes']-c['comparison_extent_bytes']),
                   c['private_header_qualification'] != 'canonical-current', c['source'])) if eligible else portable_best(root, old, row)
        was_attempted = attempts[off] > 0 or bool(drafts[off]) or old.get(off, {}).get('status') in ('attempted', 'near-miss')
        near = best is not None and best['candidate_bytes'] == best['comparison_extent_bytes'] and best['full_byte_differences'] <= 32
        status = 'suspected-not-C' if off == 0x49968 else 'near-miss' if near else 'attempted' if was_attempted else 'untouched'
        mode = row['mode']
        compiler_id = 'gcc302' if off == 0x49968 else 'agbcc_arm' if mode == 'ARM' else 'agbcc'
        flags = ['-O2', '-mthumb'] if off == 0x49968 else ['-O2', '-mthumb-interwork']
        if best and best['compiler_id'] == compiler_id:
            flags = best['compiler_flags']
        selected = compiler_selection({'mode': mode, 'compiler_id': compiler_id}, flags)
        source = best['source'] if best else min(drafts[off]) if drafts[off] else None
        search_best = min(searches[off], key=lambda c: (c['full_byte_differences'],
                          abs(c['candidate_bytes']-c['comparison_extent_bytes']), c['source'])) if searches[off] else None
        output.append(dict(name=row['name'], rom_offset=off, inventory_bytes=row['size'],
                           mode=mode, compiler_id=selected['compiler_id'], compiler_flags=selected['flags'],
                           runtime_addresses=row['runtime_addresses'], status=status,
                           user_priority=PRIORITY.index(off)+1 if off in PRIORITY else None,
                           user_far_off=off in FAR_OFF, c_draft=source,
                           historical_active_effort_seconds=None, effort_status='unrecorded',
                           active_effort_seconds=None,
                           search_wall_seconds=time_records[off][0]['search_wall_seconds'] if len(time_records[off]) == 1 else None,
                           search_wall_time_records=time_records[off], best_candidate=best, search_best=search_best,
                           retained_attempt_contexts=attempts[off], eligible_diagnostic_contexts=len(eligible),
                           excluded_contexts=dict(sorted(exclusions[off].items())),
                           closed_note=CLOSED.get(off, 'No retained attempt found in the bounded scan.' if status == 'untouched' else 'Prior bounded source experiments remain nonmatches.')))
    text = (root / inputs[2]).read_text()
    match = re.search(r'(\d+) unowned rows\s*/\s*([\d,]+)\s+(?:estimated\s+)?bytes', text)
    documented = {'rows': int(match[1]), 'bytes': int(match[2].replace(',', ''))} if match else None
    totals = dict(rows=len(rows), inventory_bytes=sum(r['size'] for r in rows),
                  statuses={s: sum(r['status'] == s for r in output) for s in ('near-miss', 'attempted', 'untouched', 'suspected-not-C')},
                  status_inventory_bytes={s: sum(r['inventory_bytes'] for r in output if r['status'] == s)
                                          for s in ('near-miss', 'attempted', 'untouched', 'suspected-not-C')})
    return dict(schema_version=1, target='us-eu', totals=totals, rows=output,
                scope='Diagnostic queue only; no C ownership or runtime credit. Inventory bytes and proven comparison extents are separate.',
                inputs={p: sha(root / p) for p in inputs},
                documented_inventory=documented,
                documentation_count_current=documented == {'rows': totals['rows'], 'bytes': totals['inventory_bytes']},
                scan=dict(roots=['analysis', 'reports/current-goal'], maximum_directory_depth=3,
                          metadata_files=len(paths), malformed_metadata=malformed,
                          current_goal_receipts=receipt_count,
                          rejected_search_validations=rejected_searches,
                          private_files_required_for_fresh_revalidation=True,
                          historical_effort='Not inferred from file timestamps or first/last activity.',
                          search_wall_time='Separate from active effort; no retrospective time inferred.'))


def resolve_row(root, name):
    """Return a checked local adapter input or explain what must be restored."""
    root = Path(root).resolve()
    report = read_json(local(root, OUTPUT))
    matches = [r for r in report['rows'] if r['name'] == name or f"0x{r['rom_offset']:X}".lower() == str(name).lower()]
    if len(matches) != 1:
        raise ValueError('Triage row name or hexadecimal ROM offset must identify one row')
    row = matches[0]
    best = row.get('best_candidate')
    if not best:
        raise ValueError('Triage row has no qualified retained candidate; supply a reviewed explicit context')
    if best.get('evidence_state') != 'retained-inputs-revalidated':
        raise ValueError('Restore the recorded private inputs and regenerate triage before setup')
    for key in ('source', 'metadata', 'receipt', 'assessment'):
        path = local(root, best[key])
        if not path.is_file() or sha(path) != best[key + '_sha256']:
            raise ValueError('Triage candidate changed; regenerate triage before setup')
    overrides = {}
    for name, record in best.get('header_overrides', {}).items():
        path = local(root, record['path'])
        if not path.is_file() or sha(path) != record['sha256']:
            raise ValueError('Restore the private header override and regenerate triage')
        overrides[name] = path
    meta = read_json(local(root, best['metadata']))
    if meta.get('rom_offset') != row['rom_offset'] or meta.get('size') != best['comparison_extent_bytes']:
        raise ValueError('Triage metadata no longer describes the selected extent')
    return dict(row=row, function=meta['name'], source=local(root, best['source']),
                metadata=local(root, best['metadata']), header_overrides=overrides)


def markdown(report):
    lines = ['# Remaining C triage', '',
             f"{report['totals']['rows']} unowned inventory rows / {report['totals']['inventory_bytes']:,} bytes. "
             'Scores compare complete retained extents, including missing or extra bytes; they grant no source credit.', '',
             'Regenerate with `python3 tools/triage.py`; check with `python3 tools/triage.py --check`. '
             'Private evidence may be unavailable on another checkout; recorded rows then say so. '
             'Historical active effort and search wall time are unrecorded, not zero.', '',
             '| ROM | Name | Inventory | Best bytes / differences | Compared extent | Status | Priority | Context |',
             '| --- | --- | ---: | ---: | ---: | --- | ---: | --- |']
    for row in report['rows']:
        best = row['best_candidate']
        score = f"{best['candidate_bytes']} / {best['full_byte_differences']}" if best else 'unqualified/unavailable'
        extent = str(best['comparison_extent_bytes']) if best else '—'
        context = best['private_header_qualification'] if best else '—'
        if best and best['evidence_state'] == 'recorded-not-revalidated':
            context += '; recorded'
        lines.append(f"| `0x{row['rom_offset']:05X}` | `{row['name']}` | {row['inventory_bytes']} | {score} | {extent} | {row['status']} | {row['user_priority'] or '—'} | {context} |")
    searched = [row for row in report['rows'] if row.get('search_best')]
    if searched:
        lines += ['', 'Fresh search comparisons awaiting source review:']
        for row in searched:
            best = row['search_best']
            lines.append(f"- `0x{row['rom_offset']:05X}`: {best['candidate_bytes']} bytes / {best['full_byte_differences']} differences over {best['comparison_extent_bytes']} bytes; no source credit.")
    lines += ['', 'Priority1–7 follows the requested near-miss order; other full-size candidates with at most32 differing bytes also enter the near-miss queue. '
              'Existing attempts override the older “untouched” list. Private types and backing/API premises still require acceptance review.', '',
              'Closed notes: ' + ' '.join(f"`0x{off:05X}`: {note}" for off, note in sorted(CLOSED.items())), '']
    return '\n'.join(lines)


def write_outputs(root, report, check=False, output=OUTPUT, document=MARKDOWN):
    if output != OUTPUT or document != MARKDOWN:
        raise ValueError('Only the two owned generated outputs may be written')
    payloads = [(local(root, output), json.dumps(report, indent=2) + '\n'),
                (local(root, document), markdown(report))]
    if check:
        return all(p.is_file() and p.read_text() == text for p, text in payloads)
    for path, text in payloads:
        path.parent.mkdir(parents=True, exist_ok=True)
        with tempfile.NamedTemporaryFile('w', dir=path.parent, prefix='.triage-', delete=False) as handle:
            temporary = Path(handle.name)
            handle.write(text)
        try:
            os.replace(temporary, path)
        finally:
            temporary.unlink(missing_ok=True)
    return True


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--check', action='store_true')
    parser.add_argument('--root', type=Path, default=ROOT)
    args = parser.parse_args(argv)
    root = args.root.resolve()
    previous_path = local(root, OUTPUT)
    previous = read_json(previous_path) if previous_path.exists() else None
    report = build(root, previous)
    if not write_outputs(root, report, args.check):
        parser.exit(1, 'Triage outputs are stale; run python3 tools/triage.py.\n')
    print(json.dumps(report['totals'], sort_keys=True))


if __name__ == '__main__':
    main()
