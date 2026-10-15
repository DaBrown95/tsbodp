"""Static byte unions from pre-weak snapshots; no I/O, decoding or credit."""
from collections import Counter, defaultdict


STRONG_EVIDENCE = frozenset((
    'startup', 'startup main pointer', 'bounded audit', 'audited RAM entry',
    'audited dispatch entry', 'direct call', 'resolved literal transfer',
))

CLASSIFICATION_PROFILES = {
    'strong_rooted_instruction': dict(
        confidence='high_static_instruction_provenance',
        evidence_basis='ARM/Thumb CFG observation from corroborated roots; not runtime or function ownership.'),
    'instruction_and_referenced_data_dual_use': dict(
        confidence='high_static_mixed_role',
        evidence_basis='Qualified instruction and data-reference observations with reviewed dual-use evidence.'),
    'strong_rooted_referenced_data': dict(
        confidence='high_referenced_data_role_execution_exclusion_provisional',
        evidence_basis='Strong-rooted literal/table references; role does not prove bytes can never execute.'),
    'known_data': dict(
        confidence='moderate_static_data_role',
        evidence_basis='Independently supplied data region or explicit data-only source/glue extent.'),
    'owned_extent_unclassified': dict(
        confidence='high_owned_boundary_unknown_role',
        evidence_basis='Independent source/glue extent, without a qualified instruction or data role here.'),
    'estimated_envelope_unclassified': dict(
        confidence='low_estimated_boundary',
        evidence_basis='Provisional discovery envelope only; neither byte role nor function boundary is established.'),
    'unresolved': dict(
        confidence='unknown',
        evidence_basis='No supplied strong instruction/data observation or owned/estimated extent.'),
    'ambiguous_mode_conflict': dict(
        confidence='ambiguous',
        evidence_basis='Both ARM and Thumb instruction observations; no mode is selected as confirmed.'),
    'ambiguous_instruction_known_data': dict(
        confidence='ambiguous',
        evidence_basis='Qualified instruction overlaps an independently supplied data role.'),
    'ambiguous_instruction_data_overlap': dict(
        confidence='ambiguous',
        evidence_basis='Instruction and referenced-data observations overlap without reviewed dual-use evidence.'),
    'contingent_unqualified_observation': dict(
        confidence='ambiguous_contingent_execution',
        evidence_basis='Raw CFG instruction observation excluded by reviewed context-specific evidence; alternative retained.'),
}


def _integer(value, label):
    if type(value) is not int:
        raise ValueError(label + ' must be an integer')
    return value


def _ranges(values, size):
    spans = []
    for value in values:
        if not isinstance(value, (list, tuple)) or len(value) != 2:
            raise ValueError('Expected half-open physical range')
        a, b = (_integer(v, 'Range endpoint') for v in value)
        if not 0 <= a < b <= size:
            raise ValueError('Physical range outside ROM')
        spans.append((a, b))
    out = []
    for a, b in sorted(spans):
        if out and a <= out[-1][1]:
            out[-1] = (out[-1][0], max(b, out[-1][1]))
        else:
            out.append((a, b))
    return out


def _length(spans):
    return sum(b-a for a, b in spans)


def _intersection(left, right):
    out, i, j = [], 0, 0
    while i < len(left) and j < len(right):
        a, b = max(left[i][0], right[j][0]), min(left[i][1], right[j][1])
        if a < b:
            out.append((a, b))
        if left[i][1] < right[j][1]:
            i += 1
        else:
            j += 1
    return out


def _subtract(spans, cuts):
    out, j = [], 0
    for a, b in spans:
        while j < len(cuts) and cuts[j][1] <= a:
            j += 1
        k, cursor = j, a
        while k < len(cuts) and cuts[k][0] < b:
            c, d = cuts[k]
            if cursor < c:
                out.append((cursor, min(c, b)))
            cursor = max(cursor, d)
            k += 1
        if cursor < b:
            out.append((cursor, b))
    return out


def _points(values, size):
    return _ranges(((v, v+1) for v in values), size)


def _extent(row, size):
    a = _integer(row['rom_offset'], 'Extent offset')
    n = _integer(row['size'], 'Extent size')
    return _ranges(((a, a+n),), size)[0]


def _physical(scanner, address, length, size):
    if type(address) is not int or type(length) is not int or length <= 0:
        raise ValueError('Invalid instruction address or length')
    a = scanner.physical(address)
    if a is None or not 0 <= a < a+length <= size:
        raise ValueError('Instruction lacks ROM backing')
    if any(scanner.physical(address+i) != a+i for i in range(length)):
        raise ValueError('Instruction crosses copy boundary')
    return a, a+length


def _annotation_evidence(row):
    if (not isinstance(row.get('reason'), str) or not row['reason'].strip()
            or not isinstance(row.get('evidence'), list) or not row['evidence']
            or any(not isinstance(e, str) or not e.strip() for e in row['evidence'])):
        raise ValueError('Quality annotation needs reason and evidence')


def _classification(active):
    if active['ARM'] and active['Thumb']:
        return 'ambiguous_mode_conflict'
    if active['instruction'] and active['known_data']:
        return 'ambiguous_instruction_known_data'
    if active['instruction'] and active['referenced_data']:
        return ('instruction_and_referenced_data_dual_use' if active['approved_dual_use']
                else 'ambiguous_instruction_data_overlap')
    if active['instruction']:
        return 'strong_rooted_instruction'
    if active['referenced_data']:
        return 'strong_rooted_referenced_data'
    if active['raw_instruction']:
        return 'contingent_unqualified_observation'
    if active['known_data']:
        return 'known_data'
    if active['source_owned']:
        return 'owned_extent_unclassified'
    if active['estimated_envelope']:
        return 'estimated_envelope_unclassified'
    return 'unresolved'


def _partition(roles, size):
    events = defaultdict(Counter)
    for role, spans in roles.items():
        for a, b in spans:
            events[a][role] += 1
            events[b][role] -= 1
    events[0]; events[size]
    active, result, counts = Counter(), [], Counter()
    points = sorted(events)
    for a, b in zip(points, points[1:]):
        active.update(events[a])
        name = _classification(active)
        present = sorted(k for k, v in active.items() if v > 0)
        counts[name] += b-a
        if result and result[-1]['classification'] == name and result[-1]['roles'] == present:
            result[-1]['size'] += b-a
        else:
            result.append(dict(rom_offset=a, size=b-a, classification=name, roles=present,
                               **CLASSIFICATION_PROFILES[name]))
    return result, counts


def _summaries(partition, size):
    result = []
    for a in range(0, size, 65536):
        b, totals = min(a+65536, size), Counter()
        for row in partition:
            n = min(b, row['rom_offset']+row['size'])-max(a, row['rom_offset'])
            if n > 0:
                totals[row['classification']] += n
        result.append(dict(rom_offset=a, size=b-a, classification_bytes=dict(sorted(totals.items())),
                           classification_profiles=sorted(totals)))
    return result


def _counts(roles, counts, raw_literals):
    return dict(
        raw_instruction_union_bytes=_length(roles['raw_instruction']),
        qualified_observed_instruction_union_bytes=_length(roles['instruction']),
        nonconflicting_qualified_instruction_bytes=counts['strong_rooted_instruction']+counts['instruction_and_referenced_data_dual_use'],
        raw_referenced_data_union_bytes=_length(raw_literals),
        qualified_referenced_data_union_bytes=_length(roles['referenced_data']),
        source_glue_owned_extent_bytes=_length(roles['source_owned']),
        estimated_envelope_union_bytes=_length(roles['estimated_envelope']),
        classification_bytes=dict(sorted(counts.items())))


def _copy_accounting(copies, size):
    rows, spans = [], []
    for row in copies:
        a, b = _extent(row, size)
        ram = _integer(row['ram_address'], 'RAM address')
        if not 0 <= ram < ram+(b-a) <= 2**32:
            raise ValueError('RAM copy address outside word address space')
        spans.append((a, b))
        rows.append(dict(name=row.get('name'), rom_offset=a, size=b-a,
                         ram_address=ram))
    overlaps = []
    for i, left in enumerate(rows):
        for right in rows[i+1:]:
            a = max(left['rom_offset'], right['rom_offset'])
            b = min(left['rom_offset']+left['size'], right['rom_offset']+right['size'])
            if a < b:
                overlaps.append(dict(names=[left['name'], right['name']],
                                     rom_offset=a, size=b-a))
    union = _ranges(spans, size)
    return dict(installations=rows, physical_source_union=union,
                installed_byte_sum=sum(r['size'] for r in rows),
                unique_physical_source_bytes=_length(union),
                repeated_physical_source_bytes=sum(r['size'] for r in rows)-_length(union),
                pairwise_source_overlaps=overlaps,
                limitation='A copy is not an execution claim.')


def census(scanner, strong_entries, strong_results, rows=(), data_regions=(),
           source_code=(), quality_annotations=()):
    """Pure partition. Physical-range annotations require reason/evidence.

    exclude_observation: entry, mode, instruction_ranges, optional literal_ranges;
    dual_use: ranges. Context exclusions preserve other roots and raw alternatives.
    Owned/estimated extents never seed instructions.
    """
    quality_annotations, source_code = tuple(quality_annotations), tuple(source_code)
    size = len(scanner.data)
    if not size or set(strong_entries) != set(strong_results):
        raise ValueError('Strong entry/result snapshots differ or ROM is empty')
    observations, all_instructions, all_literals = {}, [], []
    for key in sorted(strong_results):
        address, mode = key
        evidence = set(strong_entries[key].get('evidence', ()))
        if not evidence or not evidence <= STRONG_EVIDENCE:
            raise ValueError('Weak/unknown entry cannot enter census')
        if (type(address) is not int or mode not in ('ARM', 'Thumb')
                or address % (4 if mode == 'ARM' else 2) or scanner.physical(address) is None):
            raise ValueError('Unaligned or unknown execution mode')
        result = strong_results[key]
        instructions = []
        for pc, length in result['instructions'].items():
            if pc % (4 if mode == 'ARM' else 2) or length not in ((4,) if mode == 'ARM' else (2, 4)):
                raise ValueError('Invalid instruction alignment or width')
            instructions.append(_physical(scanner, pc, length, size))
        instructions = _ranges(instructions, size)
        literals = _points(result.get('literals', ()), size)
        observations[key] = dict(instructions=instructions, literals=literals,
                                 excluded_instructions=[], excluded_literals=[])
        all_instructions.extend(instructions)
        all_literals.extend(literals)
    raw_instructions = _ranges(all_instructions, size)
    raw_literals = _ranges(all_literals, size)
    dual = []
    for annotation in quality_annotations:
        _annotation_evidence(annotation)
        kind = annotation.get('kind')
        if kind == 'exclude_observation':
            key = annotation.get('entry'), annotation.get('mode')
            if key not in observations:
                raise ValueError('Exclusion names no strong entry')
            obs = observations[key]
            count = 0
            for role in ('instruction', 'literal'):
                cuts = _ranges(annotation.get(role+'_ranges', ()), size)
                if _subtract(cuts, obs[role+'s']):
                    raise ValueError('Quality exclusion invents unobserved bytes')
                if role == 'instruction':
                    unit = 4 if key[1] == 'ARM' else 2
                    if any(a % unit or b % unit for a, b in cuts):
                        raise ValueError('Quality exclusion splits an instruction unit')
                    # A Thumb BL occupies two units; do not cut either half.
                    for pc, length in strong_results[key]['instructions'].items():
                        span = [_physical(scanner, pc, length, size)]
                        overlap = _intersection(span, cuts)
                        if overlap and _length(overlap) != length:
                            raise ValueError('Quality exclusion splits an instruction')
                obs['excluded_'+role+'s'].extend(cuts)
                count += _length(cuts)
            if not count:
                raise ValueError('Empty quality exclusion')
        elif kind == 'dual_use':
            spans = _ranges(annotation.get('ranges', ()), size)
            if not spans:
                raise ValueError('Empty dual-use annotation')
            dual.extend(spans)
        else:
            raise ValueError('Unknown quality annotation kind')
    by_mode = dict(ARM=[], Thumb=[])
    literals, excluded_instructions, excluded_literals, boundaries = [], [], [], []
    for key, obs in observations.items():
        address, mode = key
        cuts = _ranges(obs['excluded_instructions'], size)
        litcuts = _ranges(obs['excluded_literals'], size)
        instructions = _subtract(obs['instructions'], cuts)
        refs = _subtract(obs['literals'], litcuts)
        by_mode[mode].extend(instructions)
        literals.extend(refs)
        excluded_instructions.extend(cuts)
        excluded_literals.extend(litcuts)
        result = strong_results[key]
        boundaries.append(dict(
            execution_address=address, entry_rom_offset=scanner.physical(address),
            mode=mode, name=strong_entries[key].get('name'),
            evidence=sorted(strong_entries[key]['evidence']),
            raw_instruction_intervals=obs['instructions'],
            qualified_instruction_intervals=instructions,
            referenced_data_intervals=refs, excluded_instruction_intervals=cuts,
            excluded_literal_intervals=litcuts,
            return_sites=sorted(result.get('return_sites', ())),
            issues=sorted(result.get('issues', ())),
            unresolved_transfer_sites=sorted(result.get('unresolved_transfers', ())),
            terminal_observed=bool(result.get('terminal', False)),
            boundary_basis='entry reach, not function ownership',
            compiler_ownership_established=False, runtime_reachability_established=False))
    by_mode = {m: _ranges(v, size) for m, v in by_mode.items()}
    instructions = _ranges(by_mode['ARM']+by_mode['Thumb'], size)
    literals = _ranges(literals, size)
    modes = _intersection(by_mode['ARM'], by_mode['Thumb'])
    dual = _ranges(dual, size)
    if (_subtract(dual, _intersection(instructions, literals))
            or _intersection(dual, modes)):
        raise ValueError('Invalid dual-use roles or mode conflict')
    ownership, owner_rows = [], []
    for row in source_code:
        a, b = _extent(row, size)
        ownership.append((a, b))
        owner_rows.append(dict(name=row.get('name'), rom_offset=a, size=b-a,
                               source=row.get('source'), mode=row.get('mode'),
                               kind=row.get('source_kind', 'source_or_glue'),
                               instruction_bytes_in_extent=_length(_intersection([(a, b)], instructions)),
                               referenced_data_bytes_in_extent=_length(_intersection([(a, b)], literals))))
    owned = _ranges(ownership, size)
    if _length(owned) != sum(b-a for a, b in ownership):
        raise ValueError('Source/glue extents overlap')
    known = _ranges([_extent(r, size) for r in data_regions]+[_extent(r, size) for r in source_code if r.get('mode') == 'data'], size)
    estimated = _ranges((_extent(r, size) for r in rows), size)
    excluded_instructions = _ranges(excluded_instructions, size)
    excluded_literals = _ranges(excluded_literals, size)
    roles = dict(instruction=instructions, ARM=by_mode['ARM'], Thumb=by_mode['Thumb'],
                 referenced_data=literals, known_data=known, source_owned=owned,
                 estimated_envelope=estimated, raw_instruction=raw_instructions,
                 excluded_observation=excluded_instructions, approved_dual_use=dual)
    partition, counts = _partition(roles, size)
    summaries = _summaries(partition, size)
    return dict(
        schema_version=1, rom_bytes=size, complete_physical_partition=True,
        complete_code_inventory=False, recovered_source_credit_changed=False,
        single_code_denominator_established=False, runtime_observations=0,
        basis='Pre-weak strong snapshots; physical aliases counted once.',
        confidence='Static roots; boundaries, open targets and gaps remain qualified.',
        classification_definitions={k: dict(v) for k, v in CLASSIFICATION_PROFILES.items()},
        limitations=[
            'CFG unions do not prove function ownership or runtime reachability; table prefixes may be incomplete.',
            'Owned extents include pools/alignment. Weak seeds, linked-only tags and copies cannot establish code.',
            'Unresolved bytes may contain code; no whole-code denominator is inferred.'],
        strong_execution_entries=len(observations),
        unique_physical_entries=len({scanner.physical(k[0]) for k in observations}),
        counts=_counts(roles, counts, raw_literals),
        physical_unions={k: v for k, v in roles.items()},
        excluded_literal_observations=excluded_literals,
        quality_annotations=list(quality_annotations), partition=partition,
        regions_64KiB=summaries, entry_boundary_observations=boundaries,
        source_extent_ownership=owner_rows,
        copy_accounting=_copy_accounting(scanner.copies, size))


def verify_census(data, size):
    """Check serialized accounting; caller separately pins live scanner provenance."""
    if (type(size) is not int or size <= 0 or data['rom_bytes'] != size
            or data['schema_version'] != 1 or data['complete_physical_partition'] is not True
            or data['complete_code_inventory'] is not False
            or data['single_code_denominator_established'] is not False
            or data['recovered_source_credit_changed'] is not False
            or data['runtime_observations'] != 0
            or data['classification_definitions'] != CLASSIFICATION_PROFILES):
        raise ValueError('Invalid census identity/credit/completeness')
    names = {'instruction', 'ARM', 'Thumb', 'referenced_data', 'known_data',
             'source_owned', 'estimated_envelope', 'raw_instruction',
             'excluded_observation', 'approved_dual_use'}
    if set(data['physical_unions']) != names:
        raise ValueError('Census physical roles differ')
    roles = {k: _ranges(v, size) for k, v in data['physical_unions'].items()}
    if any([list(x) for x in roles[k]] != [list(x) for x in v]
           for k, v in data['physical_unions'].items()):
        raise ValueError('Physical union ranges are not normalized')
    if (_ranges(roles['ARM']+roles['Thumb'], size) != roles['instruction']
            or _subtract(roles['instruction'], roles['raw_instruction'])
            or _subtract(roles['excluded_observation'], roles['raw_instruction'])
            or _subtract(roles['approved_dual_use'], _intersection(roles['instruction'], roles['referenced_data']))
            or _intersection(roles['approved_dual_use'], _intersection(roles['ARM'], roles['Thumb']))):
        raise ValueError('Physical union role relationships differ')
    expected, counts = _partition(roles, size)
    if data['partition'] != expected or data['regions_64KiB'] != _summaries(expected, size):
        raise ValueError('Invalid census partition or summaries')
    raw_refs = _ranges(roles['referenced_data']+_ranges(data['excluded_literal_observations'], size), size)
    expected_counts = _counts(roles, counts, raw_refs)
    if data['counts'] != expected_counts:
        raise ValueError('Census counts differ from physical unions')
    owners = [_extent(r, size) for r in data['source_extent_ownership']]
    if (_ranges(owners, size) != roles['source_owned']
            or sum(b-a for a, b in owners) != _length(roles['source_owned'])):
        raise ValueError('Source/glue ownership differs or overlaps')
    raw, qualified, refs, cuts, litcuts, entries, physical_entries = [], [], [], [], [], set(), set()
    modes = dict(ARM=[], Thumb=[])
    for row in data['entry_boundary_observations']:
        key = row['execution_address'], row['mode']
        if (key in entries or key[1] not in ('ARM', 'Thumb')
                or not set(row['evidence']) or not set(row['evidence']) <= STRONG_EVIDENCE
                or row['compiler_ownership_established'] is not False
                or row['runtime_reachability_established'] is not False):
            raise ValueError('Invalid entry evidence/ownership')
        entries.add(key)
        physical_entries.add(row['entry_rom_offset'])
        a, b = _ranges(row['raw_instruction_intervals'], size), _ranges(row['excluded_instruction_intervals'], size)
        if _subtract(b, a) or _subtract(a, b) != _ranges(row['qualified_instruction_intervals'], size):
            raise ValueError('Entry exclusion differs')
        raw.extend(a); cuts.extend(b)
        qualified.extend(row['qualified_instruction_intervals'])
        modes[key[1]].extend(row['qualified_instruction_intervals'])
        refs.extend(row['referenced_data_intervals'])
        litcuts.extend(row['excluded_literal_intervals'])
    if (len(entries) != data['strong_execution_entries']
            or len(physical_entries) != data['unique_physical_entries']
            or _ranges(raw, size) != roles['raw_instruction']
            or _ranges(qualified, size) != roles['instruction']
            or _ranges(refs, size) != roles['referenced_data']
            or _ranges(cuts, size) != roles['excluded_observation']
            or _ranges(litcuts, size) != _ranges(data['excluded_literal_observations'], size)
            or any(_ranges(v, size) != roles[m] for m, v in modes.items())):
        raise ValueError('Entry union accounting differs')
    copy = _copy_accounting(data['copy_accounting']['installations'], size)
    # JSON turns interval tuples into arrays.
    copy['physical_source_union'] = [list(s) for s in copy['physical_source_union']]
    actual = dict(data['copy_accounting'])
    actual['physical_source_union'] = [list(s) for s in actual['physical_source_union']]
    if copy != actual:
        raise ValueError('ROM-copy alias accounting differs')
    return True
