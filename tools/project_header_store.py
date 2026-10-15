"""Verified per-run project-header bytes behind ordinary proof paths.

Only the same project-relative header name and content may share an inode.
Sources and source-local bundles remain independent copies. This store never
reuses preprocessed source, compiler output, comparisons or acceptance results.
"""

import hashlib
import os
from pathlib import Path, PurePosixPath
import stat
import uuid


def _normal(path):
    return Path(os.path.abspath(path))


def _inside(path, root):
    return path == root or root in path.parents


def _identity(info):
    return info.st_dev, info.st_ino


def _safe_directory(path):
    path = _normal(path)
    if path.resolve() != path:
        raise ValueError('Header-store directory uses a symlink')
    path.mkdir(parents=True, exist_ok=True)
    if not stat.S_ISDIR(path.lstat().st_mode) or path.resolve() != path:
        raise ValueError('Header-store directory is not a plain directory')
    return path


def _fsync_directory(path):
    descriptor = os.open(path, os.O_RDONLY | getattr(os, 'O_DIRECTORY', 0) |
                         getattr(os, 'O_NOFOLLOW', 0))
    try:
        os.fsync(descriptor)
    finally:
        os.close(descriptor)


def object_key(relative_path, data):
    """Preserve CPP file identity and relative-sibling lookup semantics."""
    if (not isinstance(relative_path, str) or not relative_path or
            '\\' in relative_path or '\0' in relative_path):
        raise ValueError('Invalid project-relative header identity')
    relative = PurePosixPath(relative_path)
    if (relative.is_absolute() or '..' in relative.parts or
            relative.as_posix() != relative_path or not relative_path.endswith('.h')):
        raise ValueError('Invalid project-relative header identity')
    content = hashlib.sha256(data).hexdigest().encode('ascii')
    return hashlib.sha256(b'project-header-path-and-content-v2\0' +
                          relative_path.encode('utf-8') + b'\0' + content).hexdigest()


class ProjectHeaderStore:
    """One run owns this directory; every reuse rechecks regular immutable bytes.

    Read-only mode is an accidental-write safeguard, not an owner-privilege
    security boundary. Existing snapshot checks must still run before and after
    preprocessing, compilation and assembly.
    """

    def __init__(self, root, include_root, header_root, source_inputs):
        self.root = _normal(root)
        self.include_root = _normal(include_root)
        self.header_root = _normal(header_root)
        for path in (self.include_root, self.header_root):
            if path.resolve() != path:
                raise ValueError('Header-store input root uses a symlink')
            if _inside(self.root, path) or _inside(path, self.root):
                raise ValueError('Header-store directory overlaps live inputs')
        if (_inside(self.header_root, self.include_root) or
                _inside(self.include_root, self.header_root)):
            raise ValueError('Header proof root overlaps live project headers')
        inputs = [*self.include_root.rglob('*.h'), *map(_normal, source_inputs)]
        self.forbidden_identities = set()
        for path in inputs:
            if path.resolve() != path or not stat.S_ISREG(path.lstat().st_mode):
                raise ValueError('Live project or source input is not a regular non-symlink file')
            if _inside(path, self.root):
                raise ValueError('Header-store directory contains a live input')
            self.forbidden_identities.add(_identity(path.stat()))
        self.root = _safe_directory(self.root)
        self.root_identity = _identity(self.root.lstat())
        self.seen_inode_keys = {}

    def _open_verified(self, path, expected, size):
        try:
            descriptor = os.open(path, os.O_RDONLY | getattr(os, 'O_NOFOLLOW', 0))
        except OSError as error:
            raise ValueError('Unreadable or symlink header-store object') from error
        try:
            before = os.fstat(descriptor)
            if not stat.S_ISREG(before.st_mode) or before.st_mode & 0o222:
                raise ValueError('Header-store object must be regular and read-only')
            if _identity(before) in self.forbidden_identities:
                raise ValueError('Header-store object aliases a live project or source input')
            if before.st_size != size:
                raise ValueError('Header-store object size mismatch')
            digest = hashlib.sha256()
            while block := os.read(descriptor, 131072):
                digest.update(block)
            after, current = os.fstat(descriptor), path.lstat()
            if (_identity(before) != _identity(after) or
                    _identity(current) != _identity(after) or
                    not stat.S_ISREG(current.st_mode) or
                    before.st_size != after.st_size or
                    before.st_mtime_ns != after.st_mtime_ns or after.st_mode & 0o222):
                raise ValueError('Header-store object changed while verifying')
            if digest.hexdigest() != expected:
                raise ValueError('Poisoned header-store object')
            return descriptor, after
        except BaseException:
            os.close(descriptor)
            raise

    def retain(self, data, destination, relative_path):
        if not isinstance(data, bytes):
            raise TypeError('Project header bytes required')
        if (self.root.resolve() != self.root or
                _identity(self.root.lstat()) != self.root_identity):
            raise ValueError('Header-store directory changed')
        destination = _normal(destination)
        if not _inside(destination, self.header_root) or destination == self.header_root:
            raise ValueError('Header proof destination is outside its retained project-header root')
        if destination.relative_to(self.header_root).as_posix() != relative_path:
            raise ValueError('Header proof path does not match its project-relative identity')
        if destination.parent.resolve() != destination.parent:
            raise ValueError('Header proof destination uses a symlink')
        if destination.exists() or destination.is_symlink():
            raise ValueError('Header proof destination already exists')
        if _inside(destination, self.root) or _inside(destination, self.include_root):
            raise ValueError('Unsafe header proof destination')
        expected = hashlib.sha256(data).hexdigest()
        key = object_key(relative_path, data)
        obj = self.root / (key + '.h')
        temporary = self.root / ('.pending-' + uuid.uuid4().hex)
        if not (obj.exists() or obj.is_symlink()):
            descriptor = os.open(temporary, os.O_WRONLY | os.O_CREAT | os.O_EXCL |
                                 getattr(os, 'O_NOFOLLOW', 0), 0o600)
            try:
                try:
                    remaining = memoryview(data)
                    while remaining:
                        count = os.write(descriptor, remaining)
                        if count <= 0:
                            raise OSError('Short header-store write')
                        remaining = remaining[count:]
                    os.fchmod(descriptor, 0o444)
                    os.fsync(descriptor)
                finally:
                    os.close(descriptor)
                checked, _ = self._open_verified(temporary, expected, len(data))
                os.close(checked)
            except BaseException:
                temporary.unlink()
                raise
            try:
                try:
                    os.link(temporary, obj, follow_symlinks=False)
                except FileExistsError:
                    pass  # A racing creator won; independently verify its bytes.
            finally:
                temporary.unlink()
            _fsync_directory(self.root)
        descriptor, info = self._open_verified(obj, expected, len(data))
        previous_key = self.seen_inode_keys.setdefault(_identity(info), key)
        if previous_key != key:
            os.close(descriptor)
            raise ValueError('Distinct project-relative header identities alias one store inode')
        try:
            os.link(obj, destination, follow_symlinks=False)
            try:
                linked, current = destination.lstat(), obj.lstat()
                if (not stat.S_ISREG(linked.st_mode) or
                        _identity(linked) != _identity(info) or
                        _identity(current) != _identity(info)):
                    raise ValueError('Header-store object changed before hardlink')
                os.lseek(descriptor, 0, os.SEEK_SET)
                digest = hashlib.sha256()
                while block := os.read(descriptor, 131072):
                    digest.update(block)
                if digest.hexdigest() != expected:
                    raise ValueError('Header-store object changed after hardlink')
            except BaseException:
                destination.unlink()
                raise
        finally:
            os.close(descriptor)


def write_header_override(path, text):
    """Atomically detach the proof inode before changing a retained header."""
    path = _normal(path)
    if path.resolve() != path or not stat.S_ISREG(path.lstat().st_mode):
        raise ValueError('Header override target must be a plain retained file')
    temporary = path.parent / ('.override-' + uuid.uuid4().hex)
    descriptor = os.open(temporary, os.O_WRONLY | os.O_CREAT | os.O_EXCL |
                         getattr(os, 'O_NOFOLLOW', 0), 0o600)
    try:
        try:
            remaining = memoryview(text.encode('utf-8'))
            while remaining:
                count = os.write(descriptor, remaining)
                if count <= 0:
                    raise OSError('Short header override write')
                remaining = remaining[count:]
            os.fchmod(descriptor, 0o644)
            os.fsync(descriptor)
        finally:
            os.close(descriptor)
        os.replace(temporary, path)
    finally:
        if temporary.exists():
            temporary.unlink()
    _fsync_directory(path.parent)
