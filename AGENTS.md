# Project guidance

This is an owner-run, AI-driven matching decompilation of *The Sims: Bustin' Out*
for Game Boy Advance. There are two targets, `rev0` (USA/Europe) and `rev1`
(USA revision 1), built from shared sources. Each has its own `config/<target>/`
folder with its pinned identity, build manifest and RAM map; `rev0` also keeps
the ROM map and its static evidence there. Neither is generated from the other. Follow the user's instructions over this file.

## Matching

- Keep the reference ROM and expected hashes fixed. Investigate mismatches;
  never change the reference to make a candidate pass.
- Accepted replacements must compile and link to identical bytes at the original
  addresses, including literal pools and alignment. No output patches, masks,
  fabricated code or embedded original instruction bodies in claimed matches.
- Keep unconverted ROM regions explicit and local. Whole-ROM equality does not
  mean the whole game has been decompiled.
- Format project-owned C with the committed `.clang-format`; borrowed code keeps
  its upstream style. Reformatting must keep each changed-source control applicable.
- Treat inferred names, types and function boundaries as provisional. Distinguish
  static findings, compiler matches and runtime/gameplay evidence.
- Matching C may retain an original bug when the function reliably matches with
  the pinned compiler and flags, without unrelated setup outside the function.
  Mark it with a short `// BUG:` comment naming the unset value and failing path.
- Work in small connected batches. Keep one latest verified full-build proof,
  including its changed-source negative controls, and a bounded set of useful
  failure evidence for active work. Preserve unique source attempts and concise
  findings; delete obsolete generated payloads and record their retirement.
  An old hash ledger alone does not require permanent artifact retention.

## Verification and progress

- Use `make pilot` for the matching C loop and `make build` for full-ROM matching;
  add `TARGET=rev1` for revision 1, or run `make build-all`. Code that differs
  between revisions goes under `#if TSBO_REVISION`; fixed addresses go in
  `include/revision.h`. `make port` proposes carrying new matches across.
  Preserve the changed-source negative controls.
- Run `make test` for changes to analysis, build or verification tools. Add tests
  for meaningful failure cases rather than mirroring the implementation.
- Before publishing source or map changes, run `make build-all`, then
  `make inventory` to refresh the `rev0` ROM map, and commit the updated map
  with the corresponding work. The ROM map needs per-target static evidence,
  which only `rev0` has so far.
- Run `make prune` after a verified build; it keeps only each target's latest
  verified pilot and link run. Keep local disk use small.
- Documentation-only edits need link and diff checks, not a ROM rebuild.
- Report verified function/byte counts. Keep source coverage, mapped extents and
  whole-ROM equality separate; never colour an unverified candidate green.

## Publication and privacy

- Never commit ROMs, extracted game assets, game binaries, proprietary tools,
  credentials or personal machine paths. Keep local inputs and outputs under
  the ignored `baseroms/`, `analysis/`, `extracted/`, `build/`, `reports/` and
  `toolchains/` directories. `baseroms/.gitkeep` is the only tracked ROM-directory file.
- Stage explicit files and inspect their contents and outgoing history before
  pushing. Ignore rules do not protect a file that is already tracked.
- Preserve third-party licences and notices when borrowing code; record its
  source, revision and changes. Attribution alone is not permission.
- Keep issues, pull requests and other contribution features disabled. Do not
  solicit contributions or contact other projects unless the user asks.
- Commit small verified milestones. Push when publication is authorised; never
  force-push or rewrite published history without an explicit user request.

## Repository and communication

Keep source in `src/`, shared headers in `include/`, per-target pins and maps
in `config/<target>/`, tool pins in `config/toolchains/`,
and tooling in `tools/`. `docs/` holds only provenance records that sources
cite (borrowed runtime code, assembly-origin and runtime evidence); licence
texts live in `licenses/`.
Keep working notes and failed attempts out of the repository, under the
ignored `analysis/`. Reader-facing instructions belong in the README.

Keep the README lean, retain the AI experiment disclosure and no-contributions
policy, and describe results plainly without inflated progress claims.
