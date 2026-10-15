"""Private process prototype: bounded independent pilot workers, deterministic result order.

Native profile/tool verification and final report publication stay in pilot.main.
No cache: every C/glue source, source control, inline-glue control and requested
optimization matrix member is compiled into a fresh independent directory.
"""
from concurrent.futures import ThreadPoolExecutor, ProcessPoolExecutor, as_completed
import multiprocessing
import copy
import hashlib
from pathlib import Path
import re
from types import SimpleNamespace
from project import ROOT, compare_bytes
from source_controls import mutate, require_negative_controls, verified_comparison
from source_addresses import execution_address
from source_coverage import byte_counts, inline_glue
from toolchain import compiler_selection, assembler_selection, optimization_flags

MAX_JOBS = 8


def validate_jobs(jobs):
    if type(jobs) is not int or not 1 <= jobs <= MAX_JOBS:
        raise ValueError('jobs must be an integer from 1 to 8')
    return jobs


def _file_digest(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def _inputs(functions, extra_inputs):
    headers = sorted((ROOT / 'include').rglob('*.h'))
    paths = {Path(__file__).resolve(), *(path.resolve() for path in headers)}
    paths.update((ROOT / f['source']).resolve() for f in functions)
    paths.update(Path(path).resolve() for path in extra_inputs)
    if any(not path.is_file() for path in paths):
        raise ValueError('pilot batch input is not a regular file')
    return {str(path): _file_digest(path) for path in sorted(paths)}, {str(path.resolve()) for path in headers}


def _verify_inputs(pins, header_inventory):
    if {str(path.resolve()) for path in (ROOT / 'include').rglob('*.h')} != header_inventory:
        raise ValueError('pilot batch header inventory changed')
    for path, digest in pins.items():
        if not Path(path).is_file() or _file_digest(path) != digest:
            raise ValueError('pilot batch input changed: ' + path)


def run_ordered(items, worker, jobs):
    """Bounded workers; no partial result list escapes after any failure."""
    validate_jobs(jobs)
    if jobs == 1:
        return [worker(item) for item in items]
    results = [None] * len(items)
    with ThreadPoolExecutor(max_workers=jobs, thread_name_prefix='pilot') as executor:
        futures = {executor.submit(worker, item): index for index, item in enumerate(items)}
        try:
            for future in as_completed(futures):
                results[futures[future]] = future.result()
        except BaseException:
            for future in futures:
                future.cancel()
            # Context exit waits for in-flight native processes/worker checks.
            # The coordinator receives the exception and cannot publish success.
            raise
    return results


def compile_candidate(function, run_folder, flags, rom, copies, *, negative_control, matrix, compile_c, assemble_low_level):
    """Original pilot per-function body, with only ordered publication moved out."""
    manifest = {'compiler_flags': flags}
    args = SimpleNamespace(negative_control=negative_control, matrix=matrix)
    compile_function = compile_c
    assemble_glue = assemble_low_level
    name = function["name"]
    source = ROOT / function["source"]
    folder = run_folder / name
    folder.mkdir(parents=True, exist_ok=True)
    snapshot = folder / "source.c"
    snapshot.write_bytes(source.read_bytes())
    is_c = function.get('kind', 'compiled_c') == 'compiled_c'
    data, compile_commands = (compile_function(function, snapshot, folder, manifest["compiler_flags"])
                              if is_c else assemble_glue(function, snapshot, folder))
    expected = rom[function["rom_offset"]:function["rom_offset"] + function["size"]]
    (folder / 'expected.bin').write_bytes(expected)
    (folder / 'candidate.bin').write_bytes(data)
    result = compare_bytes(expected, data)
    result['compiled_c_bytes'], result['assembly_glue_bytes'] = byte_counts(function)
    address = execution_address(function, copies) if is_c else 0x08000000 + function['rom_offset']
    result.update({**function, "address": f"{address:#010x}",
                   'rom_address': f"{0x08000000 + function['rom_offset']:#010x}",
                   "source_sha256": hashlib.sha256(snapshot.read_bytes()).hexdigest(),
                   "commands": compile_commands, "expected_sha256": hashlib.sha256(expected).hexdigest()})
    if is_c:
        selection = compiler_selection(function, manifest['compiler_flags'])
        result.update({'compiler_id': selection['compiler_id'], 'compiler_flags': selection['flags']})
        result['assembler_id'] = assembler_selection(function)['assembler_id']
    if args.matrix and is_c:
        result["optimization_trials"] = []
        for flag in ("-O0", "-O1", "-O2", "-O3", "-Os"):
            trial_flags = optimization_flags(selection['flags'], flag)
            trial_function = {**function, 'compiler_flags': trial_flags}
            trial_data, trial_commands = compile_function(
                trial_function, snapshot, folder / flag[1:], trial_flags)
            trial = compare_bytes(expected, trial_data)
            trial.update({"flags": trial_flags, "commands": trial_commands})
            result["optimization_trials"].append(trial)
    if args.negative_control and 'negative_control' in function:
        control_folder = folder / 'negative-control'
        control_folder.mkdir()
        changed = control_folder / ('changed.c' if is_c else 'changed.s')
        changed.write_text(mutate(snapshot.read_text(), function['negative_control']))
        control_data, control_commands = (compile_function(function, changed, control_folder, manifest['compiler_flags'])
                                         if is_c else assemble_glue(function, changed, control_folder))
        (control_folder / 'candidate.bin').write_bytes(control_data)
        control = compare_bytes(expected, control_data)
        control.update({'rejected': not control['identical'], 'commands': control_commands,
                        'source_edit': function['negative_control'],
                        'source_sha256': hashlib.sha256(changed.read_bytes()).hexdigest()})
        result['negative_control'] = control
    if args.negative_control and function.get('inline_glue'):
        spec = function['inline_glue']
        control_folder = folder / 'inline-glue-control'
        control_folder.mkdir()
        header_name = Path(spec['source']).relative_to('include').as_posix()
        original_header = (folder / 'include' / header_name).read_text()
        changed_header = mutate(original_header, spec['negative_control'])
        control_data, control_commands = compile_function(
            function, snapshot, control_folder, manifest['compiler_flags'],
            header_overrides={header_name: changed_header})
        (control_folder / 'candidate.bin').write_bytes(control_data)
        control = compare_bytes(expected, control_data)
        control.update({'rejected': not control['identical'], 'commands': control_commands,
                        'source_edit': spec['negative_control'],
                        'header': spec['source'],
                        'source_sha256': hashlib.sha256(changed_header.encode()).hexdigest()})
        result['inline_glue_control'] = control
    verified = verified_comparison(result, controls_compiled=args.negative_control)
    result['source_reconstruction_verified'] = verified and is_c
    result['assembly_glue_verified'] = verified and not is_c
    result['inline_glue_verified'] = verified and bool(inline_glue(function))

    return result


# Spawn context belongs only to this module's private worker process. ROM16MiB
# and immutable batch parameters are transferred once per worker, not per task.
_PROCESS_CONTEXT = None


def _initialize_process(context):
    global _PROCESS_CONTEXT
    _PROCESS_CONTEXT = context


def _process_candidate(function):
    c = _PROCESS_CONTEXT
    source = (ROOT / function['source']).resolve()
    if _file_digest(source) != c['source_pins'][str(source)]:
        raise ValueError('pilot source changed before worker')
    result = compile_candidate(function, c['run_folder'], c['flags'], c['rom'], c['copies'],
                               negative_control=c['negative_control'], matrix=c['matrix'],
                               compile_c=c['compile_c'], assemble_low_level=c['assemble_low_level'])
    if _file_digest(source) != c['source_pins'][str(source)]:
        raise ValueError('pilot source changed during worker')
    return result


def _process_results(functions, context, jobs):
    results = [None] * len(functions)
    with ProcessPoolExecutor(max_workers=jobs, mp_context=multiprocessing.get_context('spawn'),
                             initializer=_initialize_process, initargs=(context,)) as executor:
        futures = {executor.submit(_process_candidate, function): index
                   for index, function in enumerate(functions)}
        try:
            for future in as_completed(futures):
                results[futures[future]] = future.result()
        except BaseException:
            for future in futures:
                future.cancel()
            raise
    return results


def compile_candidates(functions, run_folder, flags, rom, copies, *, negative_control,
                       matrix, jobs=1, compile_c, assemble_low_level, extra_inputs=()):
    """Fresh private/coordinator API. Caller publishes only the complete result."""
    validate_jobs(jobs)
    functions = copy.deepcopy(list(functions))
    if not functions:
        raise ValueError('pilot cohort cannot be empty')
    names = [f['name'] for f in functions]
    if any(not isinstance(name, str) or re.fullmatch(r'[A-Za-z_][A-Za-z0-9_]*', name) is None for name in names):
        raise ValueError('unsafe pilot output name')
    if len(set(name.casefold() for name in names)) != len(names):
        raise ValueError('duplicate pilot output names')
    require_negative_controls(functions)
    pins, header_inventory = _inputs(functions, extra_inputs)
    _verify_inputs(pins, header_inventory)
    run_folder = Path(run_folder)
    if run_folder.exists():
        raise ValueError('pilot output must be a fresh directory')
    run_folder.mkdir(parents=True)

    def worker(function):
        source = (ROOT / function['source']).resolve()
        if _file_digest(source) != pins[str(source)]:
            raise ValueError('pilot source changed before worker')
        result = compile_candidate(function, run_folder, flags, rom, copies,
                                   negative_control=negative_control, matrix=matrix,
                                   compile_c=compile_c, assemble_low_level=assemble_low_level)
        if _file_digest(source) != pins[str(source)]:
            raise ValueError('pilot source changed during worker')
        return result

    if jobs == 1:
        results = run_ordered(functions, worker, 1)
    else:
        context = dict(run_folder=run_folder, flags=flags, rom=rom, copies=copies,
                       negative_control=negative_control, matrix=matrix,
                       compile_c=compile_c, assemble_low_level=assemble_low_level,
                       source_pins={str((ROOT / f['source']).resolve()): pins[str((ROOT / f['source']).resolve())]
                                    for f in functions})
        results = _process_results(functions, context, jobs)
    _verify_inputs(pins, header_inventory)
    return results
