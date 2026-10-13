"""Retain bounded source bundles and their project-header dependencies."""

import hashlib
import json
import os
from pathlib import Path
import re
import shutil


_TOKENS = re.compile(r'/\*[\s\S]*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'')
_INCLUDE = re.compile(r'^\s*#\s*(include(?:_next)?)\b([^\n]*)', re.MULTILINE)
_LITERAL = re.compile(r'^\s*(?:"([^"\n]+)"|<([^>\n]+)>)\s*$')
MAX_LOCAL_HEADERS = 256
MAX_LOCAL_BYTES = 4 * 1024 * 1024
MAX_LOCAL_DIRECTORIES = 256


def _directives(text):
    # Translation-phase line splicing precedes comments. Preserve strings so a
    # comment marker inside a string cannot hide a later include directive.
    text = text.replace('\\\n', '')
    text = _TOKENS.sub(lambda match: re.sub(r'[^\n]', ' ', match[0])
                       if match[0].startswith(('/*', '//')) else match[0], text)
    return _INCLUDE.findall(text)


def _inside(path, root):
    return path == root or root in path.parents


def _normal(path):
    return Path(os.path.abspath(path))


def _safe_file(path, root):
    path = _normal(path)
    if not _inside(path, root) or path.resolve() != path:
        raise ValueError('Header input escapes its retained root or uses a symlink')
    if not path.is_file():
        raise ValueError('Header input is not a regular file')
    return path


def _digest(data):
    return hashlib.sha256(data).hexdigest()


def snapshot_headers(source, destination, include_root):
    """Retain a source/local-header bundle plus the project include closure.

    Both conditional branches are scanned. Macro includes, include_next and
    missing literals retain all project headers and a bounded local .h set.
    The real preprocessor resolves those directives; its dependency file must
    subsequently prove that every input was retained. Unknown local extensions
    therefore cannot silently fall back to a live, unpinned input.
    """
    source = Path(source).resolve()
    destination = _normal(destination)
    if destination.resolve() != destination:
        raise ValueError('Snapshot destination uses a symlink')
    include_root = Path(include_root).resolve()
    proof_root, local_root = destination.parent, source.parent
    bundle_root = proof_root / 'source-inputs'
    generated = (destination, bundle_root)
    if (any(_inside(output, include_root) or _inside(include_root, output)
            for output in generated)
            or any(_inside(source, root) for root in generated)):
        raise ValueError('Snapshot output overlaps a source input root')
    source_data = source.read_bytes()
    if len(source_data) > MAX_LOCAL_BYTES:
        raise ValueError('Source bundle exceeds its byte limit')
    project = {_safe_file(path, include_root): path.read_bytes()
               for path in include_root.rglob('*.h')}
    # Resolve only after clearing generated inputs. A reused folder must never
    # consume a deleted live header through its previous retained copy.
    for root in generated:
        if root.exists():
            shutil.rmtree(root)
        root.mkdir(parents=True)
    local, selected, visited = {}, set(), set()
    pending = [(source, source_data)]
    fallback, expanded_fallback = False, False

    def add_local(path):
        if path not in local:
            data = path.read_bytes()
            if (len(local) + 1 > MAX_LOCAL_HEADERS
                    or len(source_data) + sum(map(len, local.values())) + len(data) > MAX_LOCAL_BYTES):
                raise ValueError('Source-local header bundle exceeds its file or byte limit')
            local[path] = data
        pending.append((path, local[path]))

    def resolve(path, name, quoted):
        if Path(name).is_absolute():
            raise ValueError('Absolute include escapes the retained snapshot')
        if quoted:
            root = include_root if _inside(path, include_root) else local_root
            candidate = _normal(path.parent / name)
            if (not _inside(candidate, root)
                    or any(_inside(candidate, output) for output in generated)):
                raise ValueError('Quoted include escapes its retained input root')
            if candidate.exists() or candidate.is_symlink():
                return _safe_file(candidate, root)
        candidate = _normal(include_root / name)
        if not _inside(candidate, include_root):
            raise ValueError('Project include escapes its retained input root')
        if candidate.exists() or candidate.is_symlink():
            return _safe_file(candidate, include_root)
        return None

    def fallback_locals():
        directories = 0
        excluded = (*generated, include_root)
        if proof_root != local_root and _inside(proof_root, local_root):
            excluded += (proof_root,)
        for directory, children, names in os.walk(local_root):
            directory = Path(directory)
            children[:] = [name for name in children
                           if not any(_inside(_normal(directory / name), root)
                                      for root in excluded)]
            directories += 1
            if directories > MAX_LOCAL_DIRECTORIES:
                raise ValueError('Source-local fallback exceeds its directory limit')
            for name in children:
                if (directory / name).is_symlink():
                    raise ValueError('Source-local fallback contains a symlink directory')
            for name in names:
                if name.endswith('.h'):
                    path = _safe_file(directory / name, local_root)
                    add_local(path)

    while pending or (fallback and not expanded_fallback):
        if not pending:
            expanded_fallback = True
            selected.update(project)
            pending.extend(project.items())
            fallback_locals()
        path, data = pending.pop()
        if path in visited:
            continue
        visited.add(path)
        for directive, arguments in _directives(data.decode('utf-8')):
            literal = _LITERAL.fullmatch(arguments)
            if directive != 'include' or literal is None:
                fallback = True
                continue
            dependency = resolve(path, literal[1] or literal[2], bool(literal[1]))
            if dependency is None:
                fallback = True
            elif _inside(dependency, include_root):
                if dependency not in project:
                    project[dependency] = dependency.read_bytes()
                selected.add(dependency)
                pending.append((dependency, project[dependency]))
            else:
                add_local(dependency)
    digests = {}
    for path in sorted(selected):
        relative = path.relative_to(include_root)
        output = destination / relative
        output.parent.mkdir(parents=True, exist_ok=True)
        output.write_bytes(project[path])
        digests[relative.as_posix()] = _digest(project[path])
    saved_source = bundle_root / source.name
    saved_source.write_bytes(source_data)
    local_digests = {}
    for path, data in sorted(local.items()):
        relative = path.relative_to(local_root)
        output = bundle_root / relative
        output.parent.mkdir(parents=True, exist_ok=True)
        output.write_bytes(data)
        local_digests[relative.as_posix()] = _digest(data)
    receipt = {'selection': 'all project headers' if fallback else 'literal include closure',
               'headers': digests,
               'source_bundle': {'directory': bundle_root.name,
                                 'source': source.name, 'source_sha256': _digest(source_data),
                                 'source_local_headers': local_digests,
                                 'original_source': os.path.relpath(source, proof_root)}}
    (proof_root / 'header-snapshot.json').write_text(json.dumps(receipt, indent=2) + '\n')
    verify_snapshot_inputs(receipt, destination)
    return receipt


def retained_source(receipt, destination):
    destination = Path(destination).resolve()
    bundle = receipt['source_bundle']
    root = _normal(destination.parent / bundle['directory'])
    if not _inside(root, destination.parent) or root == destination.parent:
        raise ValueError('Source bundle path escapes the proof folder')
    return _safe_file(root / bundle['source'], root)


def verify_snapshot_inputs(receipt, destination):
    """Reject changed retained inputs and changed original source/local headers."""
    destination = Path(destination).resolve()
    bundle = receipt['source_bundle']
    source = retained_source(receipt, destination)
    original = _normal(destination.parent / bundle['original_source'])
    local_root, bundle_root = original.parent, source.parent
    checks = [(source, bundle_root, bundle['source_sha256']),
              (original, local_root, bundle['source_sha256'])]
    for name, digest in bundle['source_local_headers'].items():
        checks.extend(((bundle_root / name, bundle_root, digest),
                       (local_root / name, local_root, digest)))
    checks.extend((destination / name, destination, digest)
                  for name, digest in receipt['headers'].items())
    for path, root, digest in checks:
        if _digest(_safe_file(path, root).read_bytes()) != digest:
            raise ValueError('Source or header input changed during compilation')


def verify_preprocessor_dependencies(receipt, destination, dependency_file):
    """Check actual macro/include_next inputs against the retained snapshot."""
    text = Path(dependency_file).read_text().replace('\\\n', '')
    if not text.startswith('snapshot:'):
        raise ValueError('Preprocessor dependency receipt has an unexpected target')
    words, current, escape = [], [], False
    for character in text[len('snapshot:'):]:
        if escape:
            current.append(character)
            escape = False
        elif character == '\\':
            escape = True
        elif character.isspace():
            if current:
                words.append(''.join(current).replace('$$', '$'))
                current = []
        else:
            current.append(character)
    if escape:
        raise ValueError('Incomplete escape in preprocessor dependency receipt')
    if current:
        words.append(''.join(current).replace('$$', '$'))
    destination = Path(destination).resolve()
    source = retained_source(receipt, destination)
    allowed = {source, *(source.parent / name for name in receipt['source_bundle']['source_local_headers']),
               *(destination / name for name in receipt['headers'])}
    # macOS may spell the same temporary directory as /var or /private/var.
    # Compare the actual file identities with our canonical retained roots.
    dependencies = {_normal(word).resolve() for word in words}
    if source not in dependencies or dependencies - allowed:
        raise ValueError('Preprocessor consumed an input outside the retained snapshot')
    return sorted(os.path.relpath(path, destination.parent) for path in dependencies)
