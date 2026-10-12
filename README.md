# The Sims: Bustin' Out

A work-in-progress matching decompilation of *The Sims: Bustin' Out* for the
Game Boy Advance, initially targeting the multilingual USA/Europe release.

This is deliberately an **almost entirely AI-driven experiment**. Virtually
all project analysis, reconstructed code, custom tooling and documentation
are produced by AI coding agents. The owner sets the direction and uses the
project to explore what these tools can achieve. Compilation and exact byte
comparison check the results; AI-generated explanations remain subject to
verification.

## Progress

![Matching progress treemap](assets/progress.png)

The code treemap comes from a ROM-wide static scan, including code copied
into RAM. Tiles show discovered entries and candidates, weighted by estimated
extents; they are not yet a proven function census. Darker tiles are candidates.
The main code banks and startup/audio panels use separate scales. The strip
below accounts for every byte of the ROM, including unresolved code, data and
padding. Green means verified matching C, including its literal pools
and alignment. Unconverted regions never count as reconstructed source.

The [full inventory](assets/rom-inventory.json) records addresses, discovery
evidence, body bounds, calls and indirect transfers. Guarded switch tables are
checked before their case blocks join the containing body; weak interior labels
are folded back into that body. Copied RAM code is counted once at its ROM
location, with ARM and Thumb mode conflicts recorded explicitly.

A bounded code body has closed static control flow. Its alignment, literal-pool
ownership, stack balance and runtime reachability may still need review.
Callback call sites and shared dispatch stubs are counted separately; observed
IRQ/audio tables do not establish every possible runtime target. These checks
strengthen the map without awarding matching-source credit.

## Building

On macOS, install Python 3.10 or later and Xcode's command line tools, then run
from the repository root:

```sh
make setup
```

Setup downloads and builds the pinned public compiler tools and installs the
Python dependencies. It only needs to run once; rerunning it checks and reuses
an existing setup. Other operating systems are not yet supported by this helper.

Put your own USA/Europe ROM here:

```text
baseroms/Sims, The - Bustin' Out (USA, Europe) (En,Fr,De,Es,It,Nl).gba
```

Expected SHA-1: `fb5662172fadebf4577f6f6f163741fc041c11e6` (16 MiB).
Then build:

```sh
make build
```

The result is `build/us-eu/bustin-out.gba`. The build checks the ROM identity,
recompiles the accepted C functions and requires an exact whole-ROM match,
including changed-source failure controls. Unconverted regions still come
from your ROM and do not count as reconstructed source.

| Command | Purpose |
| --- | --- |
| `make test` | Run the verification safeguards; no ROM needed. |
| `make progress` | Rebuild, refresh the full map and render the treemap. |
| `make audit-all` | Also check a separate USA revision 1 dump, if present. |

Public source versions stay pinned in `config/pilot-toolchain.json`. Setup
records native tool fingerprints locally; builds reject changed tools.

## Repository

```text
.
├── README.md       Project overview and build instructions
├── Makefile        Build and verification commands
├── assets/         Progress treemap and its verified snapshot
├── config/         ROM identities, tool pins and mapped extents
├── include/        Reconstructed types and hardware contracts
├── src/            Reconstructed game source
├── pilot/          Compiler matching manifest and initial candidates
├── tools/          Build, audit, analysis and progress tools
├── tests/          Verification safeguards
└── docs/           Internal AI scratch notes; not reader documentation
```

ROMs, toolchains, extracted assets, analysis databases, reports and game builds
stay in ignored local directories. `docs/` is the agents' working scratch area;
reader instructions belong in this README.

## About

Results are shared for inspection and reproducibility. External contributions,
pull requests, issues and support requests are not accepted.

ROMs, extracted assets and generated game binaries are not distributed.
Original game and third-party rights remain with their respective owners.
