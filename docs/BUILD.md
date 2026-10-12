# Build and verification

The build is currently verified on the project's macOS environment. A fresh
checkout does not provision the toolchain automatically. The runner checks
local binary hashes and the complete Apple Clang version against
[`config/pilot-toolchain.json`](../config/pilot-toolchain.json); adopting a
new host requires reviewed tool pins and a fresh exact matching run.

See [local tool setup](../pilot/README.md#local-tool-setup-used-for-this-pilot)
for the source revisions and build procedure. The analysis environment uses
Python 3.13 with the dependencies in
[`config/analysis-requirements.txt`](../config/analysis-requirements.txt),
installed under `toolchains/analysis-venv/`. Build tools also live under
`toolchains/`. Auditing the ROM and running the synthetic safeguard tests need
only Python 3.10 or later.

## Reference ROM

Place your own USA/Europe dump at the configured repository-relative path:

```text
baseroms/Sims, The - Bustin' Out (USA, Europe) (En,Fr,De,Es,It,Nl).gba
```

Then run from this project directory:

```sh
make audit
make doctor
```

Python 3.10 or later is sufficient for these commands. The audit checks the
entire file against the target's catalogue SHA-1 and size, records SHA-256,
and checks the GBA game code, revision, fixed header byte and header checksum.
SHA-256 is now pinned to the verified dump; MD5 and CRC32 are also checked
against the catalogue values. `make audit-all` additionally verifies USA
revision 1 when that separate dump is present.
It writes local metadata to `reports/us-eu/audit.json` and exits unsuccessfully
on a mismatch. It never patches, trims or rewrites the input.

Expected size: **16,777,216 bytes**. Expected SHA-1:
`fb5662172fadebf4577f6f6f163741fc041c11e6`.

Identity source: [No-Intro metadata mirrored by libretro](https://github.com/libretro/libretro-database/blob/master/metadat/no-intro/Nintendo%20-%20Game%20Boy%20Advance.dat).
The filename and cartridge label alone do not establish this identity. USA
revision 1 is an audited comparison reference; Japan remains a future target.

## Exact-match acceptance

`make build` produces `build/us-eu/bustin-out.gba`.
Run `make compare` to audit the reference again and compare every output byte.
There is no ignored region, masked difference or automatic header repair.
Comparison writes `reports/us-eu/compare.json` and fails on any difference.

Whole-ROM equality is separate from source reconstruction progress. Original
bytes retained during analysis, assembly placeholders, and copied data do not
count as matching C/C++. The current build links 19 matching C functions
(676 bytes including pools and alignment) with explicitly unconverted regions
extracted locally from the reference. Those regions contain 16,776,540 bytes and do not count as recovered
source. The complete linked ROM matches; full source reconstruction remains
incomplete. A same-size changed-source control must fail whole-ROM comparison.

Original intentional assembly can remain assembly when supported by evidence.
Track recovered game code, library code, assembly and assets separately; do not
use total ROM size as the denominator for a code decompilation percentage.

## Next work

`make analyze` reproduces the bounded startup map using the isolated analysis
environment. `make pilot` compiles the 19 accepted C candidates, links each at its
original address, checks its entire text extent, and compiles a changed-source
negative control that must fail comparison. `make pilot-matrix` also compares
optimisation levels. Each run retains source snapshots, intermediate files,
commands and a report in a separate ignored directory under `build/pilot/runs/`.
The latest summary is `reports/us-eu/pilot.json`.

Follow [the audit and compiler pilot](../pilot/README.md) and the
[RAM map and interrupt milestone](RAM_AND_INTERRUPTS.md). `make ram-map`
verifies the three copied regions and exports local RAM images for analysis.
`make doctor` reports local tools and evidence status. `make test` checks the
audit and comparison safeguards using synthetic data, without a game ROM.

The project uses one shared source tree with target-specific configuration,
symbols, layouts and reports. Add other releases only after independently
identifying their ROMs and comparing their differences.

## Local content

`baseroms/`, `build/`, `reports/`, `extracted/`, `analysis/` and `toolchains/`
are ignored. Keep original ROMs, extracted assets, private disassembly databases,
save files and proprietary tools local. Source control should contain authored
source, extraction/build scripts, configuration and research notes with evidence.
