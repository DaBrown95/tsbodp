# The Sims: Bustin' Out

A matching decompilation of *The Sims: Bustin' Out* for the Game Boy Advance,
targeting the multilingual USA/Europe release.

This is an **AI-driven experiment** to see what coding agents can do.
Almost all code, analysis and tooling are AI-generated.

## Progress

![Matching progress treemap](assets/progress.png)

Green tiles are matching C. Function boundaries in the
[ROM map](assets/rom-inventory.json) are provisional.
The build matches the original ROM, but most regions are still copied from
the original dump.

## Building

Requires macOS, Python 3.10+ and Xcode's command line tools.

Run once from the repository root:

```sh
make setup
```

Put your USA/Europe ROM here:

```text
baseroms/Sims, The - Bustin' Out (USA, Europe) (En,Fr,De,Es,It,Nl).gba
```

SHA-1: `fb5662172fadebf4577f6f6f163741fc041c11e6` (16 MiB).

```sh
make build
```

Output: `build/us-eu/bustin-out.gba`. The build fails if any byte differs.

| Command | Purpose |
| --- | --- |
| `make test` | Run tests; no ROM needed. |
| `make progress` | Rebuild and update the treemap. |
| `make audit-all` | Check both the USA/Europe and USA revision 1 dumps. |

## Repository

```text
.
├── Makefile        Build commands
├── assets/         Progress image and ROM map
├── config/         ROM hashes, tool versions and mapped regions
├── include/        C headers
├── src/            Decompiled C
├── tools/          Build and analysis scripts
├── tests/          Tests
└── docs/           Internal AI scratch notes
```

## About

This project does not accept contributions, pull requests, issues or support
requests. ROMs, extracted assets and game binaries are not included.

## Licence and credits

### Project licence

The [MIT licence](LICENSE.md) covers project-authored tools, documentation and
original contributions to reconstructed source, to the extent that the project
holds rights in that material. It grants no rights in the original game or in
third-party material. Reconstruction does not transfer the original game's
copyright to this project.

Almost all code, analysis and tooling are AI-generated as an intentional
experiment. This disclosure is not a claim that every output has copyright
protection or is free of third-party rights.

### Original game

*The Sims: Bustin' Out* for Game Boy Advance was developed by Griptonite Games
with EA's Maxis studio and published by Electronic Arts. Credit belongs to the
original development team; see the [GBA credits](https://www.mobygames.com/game/11215/the-sims-bustin-out/credits/gameboy-advance/).

The original game code, graphics, audio, text and trademarks remain the property
of their respective rights holders. Nintendo's ROM header logo is also excluded
from the project licence. This is an unofficial project with no affiliation or
endorsement from the original developers, publisher or Nintendo.

ROMs, extracted game assets and rebuilt game binaries are not distributed here.
Building requires a separately supplied ROM dump.

### Tools and dependencies

These dependencies are installed separately and retain their own licences.
The table lists their main licences; upstream notices cover bundled components.
Pinned versions are recorded in [config/](config/).

| Dependency | Use | Licence |
| --- | --- | --- |
| [pret/agbcc](https://github.com/pret/agbcc/tree/da598c1d918402c42c0c0d7128ba14567f3175e9), based on GNU GCC | Matching C compiler | GPL-2.0-or-later for the compiler; separate notices for other components |
| [GNU Binutils](https://www.gnu.org/software/binutils/) 2.43.1 | Assembler, linker and binary conversion | GPL-3.0-or-later for the tools used here; separate notices for other components |
| [Capstone](https://www.capstone-engine.org/) 5.0.7, by Nguyen Anh Quynh and contributors | Disassembly | BSD-3-Clause; component notices also apply |
| [pyelftools](https://github.com/eliben/pyelftools) 0.32, by Eli Bendersky and contributors | ELF inspection | Unlicense/public-domain dedication; bundled Construct has its own licence |
| [Pillow](https://python-pillow.github.io/) 12.3.0, by Alex Clark and contributors, based on PIL | Progress images | MIT-CMU; bundled libraries have their own licences |

Python and Apple's Xcode command line tools are also required. Their own terms
apply. The build currently uses agbcc as a compiler without linking its bundled
runtime libraries.

### References and inspiration

- [Tonc](https://gbadev.net/tonc/), by Jasper Vijn and contributors, for GBA hardware documentation, including interrupts.
- [No-Intro](https://no-intro.org/), via [libretro's database](https://github.com/libretro/libretro-database/blob/master/metadat/no-intro/Nintendo%20-%20Game%20Boy%20Advance.dat), for ROM identity checks.
- [TsilaAllaoui/warioland4](https://github.com/TsilaAllaoui/warioland4) and [722rsr/gtadv3-decomp](https://github.com/722rsr/gtadv3-decomp).

When third-party code is copied or adapted, its source, revision and changes
must be recorded, and its copyright and licence notices retained with it.
Credit alone does not grant permission to reuse code.
