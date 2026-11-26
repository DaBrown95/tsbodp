#!/usr/bin/env python3
"""Delete local pilot and ROM-link runs except each target's latest verified one.

A full pilot run is several hundred megabytes, so old runs add up quickly. The
run named by reports/<target>/pilot.json and build.json is kept so `make
progress` can still check it; everything else under build/<target>/pilot and
build/<target>/rom is removed. Nothing tracked is touched.
"""
import argparse
import json
import shutil
import sys

from project import TARGETS, target_paths


def kept_runs(paths):
    """Run ids named by the target's latest reports; none if it has not been built."""
    kept = set()
    for name in ('pilot', 'build'):
        report = paths.reports / f'{name}.json'
        if report.is_file():
            kept.add(json.loads(report.read_text())['run_id'])
    return kept


def stale_runs(paths):
    kept = kept_runs(paths)
    return sorted(run for folder in (paths.pilot_runs, paths.rom_runs) if folder.is_dir()
                  for run in folder.iterdir() if run.is_dir() and run.name not in kept)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--dry-run', action='store_true')
    args = parser.parse_args()
    for target in TARGETS:
        for run in stale_runs(target_paths(target)):
            print(('Would delete ' if args.dry_run else 'Deleting ') + str(run))
            if not args.dry_run:
                shutil.rmtree(run)
    return 0


if __name__ == '__main__':
    sys.exit(main())
