# The Sims: Bustin' Out

A matching decompilation of *The Sims: Bustin' Out* for the Game Boy Advance.
One set of C sources builds two releases byte for byte: the multilingual
USA/Europe release (`rev0`) and its USA revision 1 (`rev1`).

This is an **AI-driven experiment** to see what coding agents can do.
Almost all code, analysis and tooling are AI-generated.

## Status

Both ROMs rebuild byte for byte. Every routine we have found has a matching
source, apart from one in `rev0`, explained
[below](#the-case-of-the-missing-store).

| | `rev0` USA/Europe | `rev1` USA revision 1 |
| --- | ---: | ---: |
| Matching C functions | 2,559 | 2,560 |
| C bytes (with literal pools and alignment) | 322,324 | 322,576 |
| Known routines still without C | 1 (124 bytes) | none |
| Whole ROM identical | yes | yes |

Both builds also contain 4,068 bytes of assembly, counted separately from C:
hardware glue and library routines that were written in assembly to begin
with. Most of each ROM is data copied from the original dump: graphics, sound,
text and tables.

Function names, types and boundaries are our inferences, not the original
developers'. The `rev0` [ROM map](assets/rev0/rom-inventory.json) records the
evidence behind them.

We also looked for code the map might have missed, and a second, independent
pass checked our work. In both ROMs every byte of the main code area is C or
assembly, apart from the cartridge header, two data words and `rev0`'s
master-volume routine. Every call lands on a known function, every jump into
RAM lands in a known copy, and the data contains no function endings beyond
what random bytes would produce. Code reached only through pointers built at
run time could still hide from checks like these; only a trace of the running
game could rule it out.

## The case of the missing store

Exactly one mapped routine has no source owner: the 124-byte audio
master-volume function at `0x08049968`. Our best C matches 122 of its bytes.
The other two are a single instruction, and we are fairly sure no C source
ever produced it. Here is the detective story.

**The suspect.** The function is `kramSetMasterVol` from
[Krawall](https://github.com/sebknzl/krawall/tree/8d338581bf0ed0afad15b66bf5979ad4c4d15ed0),
Sebastian Kienzl's sound library, which the game uses for its audio. It fills
a clipping table centred on its base address: indices −1023 to 1023 in a loop,
then one last byte at index −1024.

**The compiler trips.** Write that last store as `table[-1024] = ...` and
[GCC 3.0.2](https://ftp.gnu.org/gnu/gcc/gcc-3.0.2/) falls over, but only when
the compiler itself runs on a 32-bit machine. The bit offset −8192 gets
[treated as unsigned](https://github.com/gcc-mirror/gcc/blob/releases/gcc-3.0.2/gcc/expmed.c#L233)
before being divided by eight, so −1024 comes out as `0x1FFFFC00`. The store
would land at `0x22000E38`, which is nowhere near the table, or near anything
else. Our [pinned compiler](config/toolchains/gcc302-hwi32.json) reproduces
the bug, and the same bad constant is sitting in the original ROM's literal
pool. So far, so explicable.

**The store vanishes.** The original code loads the table address, loads the
bad constant, adds them, works out the value to write... and then does
nothing at all:

| Address | Original ROM | Our C |
| --- | --- | --- |
| `0x080499B0` | `mov r8, r8` | `strb r2, [r1]` |

That is not how compilers behave. An optimiser that drops a store also drops
the sums feeding it; it does not carefully compute an address and a value and
then shrug. We went through the tools looking for anything that could plant
that no-op. GCC 3.0.2 has
[one no-op emitter](https://github.com/gcc-mirror/gcc/blob/releases/gcc-3.0.2/gcc/stmt.c#L653-L664),
and it only fires in unoptimised builds. The
[`nop` pattern](https://github.com/gcc-mirror/gcc/blob/releases/gcc-3.0.2/gcc/config/arm/arm.md#L6920-L6926)
is where the `mov r8, r8` spelling comes from, but nothing optimised reaches
it. The [assembler](https://ftp.gnu.org/gnu/binutils/) emits that encoding
only for a literal `nop`, and the linker only inside interworking stubs.

**The confession, sort of.** The public Krawall source
[writes the statement as `table[-i]`](https://github.com/sebknzl/krawall/blob/8d338581bf0ed0afad15b66bf5979ad4c4d15ed0/lib/mixer.c#L106-L107),
where `i` happens to be 1024 once the loop ends, under a comment noting that
`[-1024]` "makes GCC 3.0.2 generate an invalid constant". The
[USA revision 1 ROM](config/rev1/target.json) ships that version: 116
bytes at `0x08049A4C`, no bad constant, a real store. Compile the `[-i]` form
with our pinned compiler and flags and all 116 bytes drop out.

**Our theory.** Someone spotted the stray write and, as a stopgap, blanked
out that one instruction in the already-compiled library. The source got its
proper fix later, in time for revision 1. The compiler bug, the no-op and the
revision 1 match are established. Who removed the store, and how, is our
inference: no build artefact from the time shows it, and a post-processing
script would fit just as well.

So the routine stays without a C owner.
We could make the bytes match by patching the compiler's output, but then it
would not be a decompilation.

## Building

Requires macOS, Python 3.10+ and Xcode's command line tools. Run once from the
repository root:

```sh
make setup
```

Then put one or both ROMs in `baseroms/` under these names:

| Target | File | SHA-1 |
| --- | --- | --- |
| `rev0` | `Sims, The - Bustin' Out (USA, Europe) (En,Fr,De,Es,It,Nl).gba` | `fb5662172fadebf4577f6f6f163741fc041c11e6` |
| `rev1` | `Sims, The - Bustin' Out (USA) (En,Fr,De,Es,It,Nl) (Rev 1).gba` | `7038fa0e4cb8aeac9e48a0b45574db66cba39e73` |

```sh
make build              # rev0
make build TARGET=rev1  # rev1
make build-all          # both
```

Output goes to `build/<target>/bustin-out.gba`. The build fails if any byte
differs from the original.

| Command | Purpose |
| --- | --- |
| `make test` | Run the tool tests; no ROM needed. |
| `make audit-all` | Check that both ROM dumps are the expected ones. |
| `make inventory` | Refresh the `rev0` ROM map. |
| `make port TARGET=rev1` | Add new `rev0` matches to the `rev1` manifest. |
| `make prune` | Delete old local build runs. |

### How the two revisions fit together

Revision 1 is mostly a relink of revision 0: the same functions, shifted by a
few bytes, plus a handful of bug fixes. So both targets compile the same files
in [src/](src/). Code that changed between revisions sits under
`#if TSBO_REVISION`, and fixed addresses that moved live in
[include/revision.h](include/revision.h).

Each target has its own folder in [config/](config/) holding its ROM identity
(`target.json`), the list of functions with their addresses (`build.json`) and
the code copied into RAM at boot (`ram-map.json`). Neither target is generated
from the other. When a function is matched for one revision, `make port` looks
for the same compiled bytes in the other ROM. If it finds them, differing only
in addresses, it adds the function there. The full build then has to confirm
the result like any other change.

## Repository

```text
.
├── Makefile            Build commands
├── src/                Matching C and justified assembly, shared by both targets
├── include/            C headers, including revision.h
├── config/
│   ├── rev0/           USA/Europe: identity, manifest, RAM map, ROM-map evidence
│   ├── rev1/           USA revision 1: identity, manifest, RAM map
│   ├── toolchains/     Pinned compiler and assembler sources
│   └── python-requirements.txt
├── assets/rev0/        ROM map
├── tools/              Build and analysis scripts
├── tests/              Tool tests
└── docs/               Provenance notes for borrowed and assembly-origin code
```

## About

This project does not accept contributions, pull requests, issues or support
requests. ROMs, extracted assets and game binaries are not included.

## Licence and credits

The [MIT licence](LICENSE.md) covers our own contributions to the source, tools
and documentation. It does not cover original game code, assets or trademarks,
Nintendo's ROM header logo, or third-party material.

### Original game

*The Sims: Bustin' Out* for Game Boy Advance was developed by Griptonite Games
with EA's Maxis studio and published by Electronic Arts. See the
[GBA credits](https://www.mobygames.com/game/11215/the-sims-bustin-out/credits/gameboy-advance/) for the original development team.

This is an unofficial project, unaffiliated with the original developers,
publisher or Nintendo.

### Tools and dependencies

Dependencies are installed separately under their own licences. The table lists
their main licences; bundled components retain their upstream notices.
Pinned versions are recorded in [config/toolchains/](config/toolchains/) and [config/python-requirements.txt](config/python-requirements.txt).
The adapted audio routines, assembly-origin mixer primitives, hardware timer IRQ
and BIOS division wrapper retain their [Krawall licence](licenses/Krawall-LGPL-2.1.txt)
and source notices.
The selected floating-point, integer and register-call runtime sources retain their GNU GCC
notices and [GPL licence](licenses/GCC-GPL-2.0.txt), including the exceptions
printed in those source files.
The adapted Newlib string providers retain their [upstream notices](licenses/Newlib-COPYING.txt).
They include software developed by the University of California, Berkeley.
The independently reconstructed background decoder has documented
[assembly-origin evidence and version limits](docs/RESOURCE_BACKGROUND_DECODER.md).

| Dependency | Use | Licence |
| --- | --- | --- |
| [pret/agbcc](https://github.com/pret/agbcc/tree/da598c1d918402c42c0c0d7128ba14567f3175e9), based on GNU GCC | Matching C compiler | GPL-2.0-or-later |
| [GNU GCC](https://ftp.gnu.org/gnu/gcc/gcc-3.0.2/) 3.0.2 | Selected ARM/Thumb matching C compiler | GPL-2.0-or-later |
| [GNU Binutils](https://www.gnu.org/software/binutils/) 2.43.1 | Assembler, linker and binary conversion | GPL-3.0-or-later |
| [GNU Binutils](https://ftp.gnu.org/gnu/binutils/) 2.10.1 | Selected assembler for earlier alignment behavior | GPL-2.0-or-later |
| [Capstone](https://www.capstone-engine.org/) 5.0.7, by Nguyen Anh Quynh and contributors | Disassembly | BSD-3-Clause |
| [pyelftools](https://github.com/eliben/pyelftools) 0.32, by Eli Bendersky and contributors | ELF inspection | Unlicense/public-domain dedication |
| [Krawall](https://github.com/sebknzl/krawall/tree/8d338581bf0ed0afad15b66bf5979ad4c4d15ed0), by Sebastian Kienzl | Selected audio routines and BIOS division wrapper | LGPL-2.1-or-later |
| [mGBA](https://github.com/mgba-emu/mgba/tree/26b7884bc25a5933960f3cdcd98bac1ae14d42e2) 0.10.5 | Optional bounded runtime observations | MPL-2.0 and bundled notices |

The selected historical tools use documented [host compatibility patches](tools/patches/README.md)
under their respective upstream licences. Their selection does not establish
the historical game's toolchain.

### References and inspiration

- [Tonc](https://gbadev.net/tonc/), by Jasper Vijn and contributors, for GBA hardware documentation, including interrupts.
- [No-Intro](https://no-intro.org/), via [libretro's database](https://github.com/libretro/libretro-database/blob/master/metadat/no-intro/Nintendo%20-%20Game%20Boy%20Advance.dat), for ROM identity checks.
- [TsilaAllaoui/warioland4](https://github.com/TsilaAllaoui/warioland4) and [722rsr/gtadv3-decomp](https://github.com/722rsr/gtadv3-decomp).
