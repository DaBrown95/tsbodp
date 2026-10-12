# Project guidance

This is an owner-run, AI-driven matching decompilation of *The Sims: Bustin' Out*
for Game Boy Advance. The current target is USA/Europe revision 0; identities
are pinned in `config/targets/`. Follow the user's instructions over this file.

## Matching

- Keep the reference ROM and expected hashes fixed. Investigate mismatches;
  never change the reference to make a candidate pass.
- Accepted replacements must compile and link to identical bytes at the original
  addresses, including literal pools and alignment. No output patches, masks,
  fabricated code or embedded original instruction bodies in claimed matches.
- Keep unconverted ROM regions explicit and local. Whole-ROM equality does not
  mean the whole game has been decompiled.
- Treat inferred names, types and function boundaries as provisional. Distinguish
  static findings, compiler matches and runtime/gameplay evidence.
- Work in small connected batches. Preserve useful failed attempts and raw
  comparison evidence in ignored local reports.

## Verification and progress

- Use `make pilot` for the matching C loop and `make build` for full-ROM matching.
  Preserve the changed-source negative controls.
- Run `make test` for changes to analysis, build or verification tools. Add tests
  for meaningful failure cases rather than mirroring the implementation.
- Before publishing source or map progress, run `make progress`. It rebuilds,
  verifies, refreshes the inventory and generates the public treemap. Commit the
  updated progress files with the corresponding work.
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

Keep source in `src/`, shared headers in `include/`, pins and maps in `config/`,
and tooling in `tools/`. `docs/` is internal AI scratch space. Reader-facing
instructions belong in the README.

Keep the README lean, retain the AI experiment disclosure and no-contributions
policy, and describe results plainly without inflated progress claims.
