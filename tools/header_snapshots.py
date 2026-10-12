"""Retain a standalone header snapshot without duplicating unrelated headers."""

import hashlib
import json
from pathlib import Path
import re


_TOKENS = re.compile(r'/\*[\s\S]*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'')
_INCLUDE = re.compile(r'^\s*#\s*(include(?:_next)?)\b([^\n]*)', re.MULTILINE)
_LITERAL = re.compile(r'^\s*(?:"([^"\n]+)"|<([^>\n]+)>)\s*$')


def _directives(text):
    # Translation-phase line splicing precedes comments. Preserve strings so a
    # comment marker inside a string cannot hide a later include directive.
    text = text.replace('\\\n', '')
    text = _TOKENS.sub(lambda match: re.sub(r'[^\n]', ' ', match[0])
                       if match[0].startswith(('/*', '//')) else match[0], text)
    return _INCLUDE.findall(text)


def snapshot_headers(source, destination, include_root):
    """Copy the literal include closure, falling back for unresolved directives.

    Conditional directives are deliberately not evaluated here: both literal
    branches are retained. Macro includes, include_next, missing literals and
    source-local headers retain the complete project-header set so the real
    preprocessor, rather than this scanner, decides their meaning.
    """
    source, destination, include_root = map(Path, (source, destination, include_root))
    include_root = include_root.resolve()
    headers = {path.resolve(): path.read_bytes() for path in include_root.rglob('*.h')}
    selected, visited = set(), set()
    pending = [(source.resolve(), source.read_text())]
    fallback = False
    while pending and not fallback:
        path, text = pending.pop()
        if path in visited:
            continue
        visited.add(path)
        for directive, arguments in _directives(text):
            literal = _LITERAL.fullmatch(arguments)
            if directive != 'include' or literal is None:
                fallback = True
                break
            name = literal[1] or literal[2]
            candidates = ([path.parent / name] if literal[1] else []) + [include_root / name]
            dependency = next((candidate.resolve() for candidate in candidates
                               if candidate.exists()), None)
            if dependency not in headers:
                fallback = True
                break
            selected.add(dependency)
            pending.append((dependency, headers[dependency].decode('utf-8')))
    if fallback:
        selected = set(headers)
    destination.mkdir(parents=True, exist_ok=True)
    # A caller reusing a trial folder must never consume a deleted live header
    # through a stale snapshot left by the preceding candidate.
    for stale in destination.rglob('*.h'):
        stale.unlink()
    digests = {}
    for path in sorted(selected):
        relative = path.relative_to(include_root)
        output = destination / relative
        output.parent.mkdir(parents=True, exist_ok=True)
        output.write_bytes(headers[path])
        digests[relative.as_posix()] = hashlib.sha256(headers[path]).hexdigest()
    receipt = {'selection': 'all project headers' if fallback else 'literal include closure',
               'headers': digests}
    (destination.parent / 'header-snapshot.json').write_text(json.dumps(receipt, indent=2) + '\n')
    return receipt
