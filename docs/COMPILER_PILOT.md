> Internal AI scratch notes. Historical compiler-pilot plan; current build instructions are in the root README.

# Audit and compiler pilot

## Initial five-function result (historical)

The first pilot passes five linked function comparisons, covering 124 bytes
including their pools and padding. At the initial pilot milestone, `make pilot`
checked all 19 accepted functions; `make pilot-matrix` adds optimisation trials. The tested
`-O2 -mthumb-interwork` configuration passes all five; `-O3` and `-Os` also pass.
`-O0` fails all five, and `-O1` fails the conditional bit update. These results
support the agbcc backend without uniquely identifying historical options.

The indexed table setter uses a declared external array and a linker-defined
RAM address. A hard-coded pointer candidate had a different instruction order;
the failed run and its source snapshot remain local. No output bytes were
patched. The negative control changes the setter's C to store `value + 1` and
is rejected after real compilation and linking.

Tool source pins, native binary hashes and host preprocessor identity are in
`config/pilot-toolchain.json`. The runner checks those pins and clean compiler
source before compiling. It records hashes of the runner, verifier, manifests,
sources and tools with every run. The current integration milestone is documented in
[RAM and interrupts](RAM_AND_INTERRUPTS.md): 19 accepted C functions
and an all-byte matching partial reconstruction of the complete ROM.

## Local tool setup used for this pilot

The analysis environment uses Python 3.13 and the packages pinned in
`config/analysis-requirements.txt`. The native compiler was built from the pinned
pret/agbcc commit with `make -C toolchains/agbcc/gcc -j1`, without changing its
source. That initial setup built the Thumb compiler, not agbcc's complete runtime libraries.

GNU binutils 2.43.1 was built from the official source archive whose SHA-256 is
recorded in the toolchain pin. Use a separate build directory, the documented
configure options in that pin, and a project-local installation prefix of
`toolchains/binutils`. `--with-system-zlib` and GNU C11 host flags avoid an
incompatibility between bundled zlib and the current Apple toolchain.
`MAKEINFO=true` skips optional manual generation; the assembler and linker are
built normally. Build commands and logs are under `reports/toolchains/`.

This manual setup has been superseded by `make setup`, which records native
fingerprints locally. Public source pins stay fixed and fresh builds check matching.

## Copied ARM source support

The tile allocator at ROM offset `0xB77C` executes at `0x03007390` after a
200-byte BIOS word copy. Its matching C extent is 196 bytes; the final copied
word belongs to the following frame-copy source and remains separately owned.
The accepted allocator uses `-O2 -mthumb-interwork -fomit-frame-pointer` and four
explicit C register constraints. They influence allocation without embedding
instructions or changing compiled output. The byte bitmap, run search and
failure value are expressed as C operations.

`config/arm-toolchain.json` pins agbcc's ARM backend from the same unchanged
source revision as Thumb. `make setup` provisions it when the build manifest
contains ARM C; `make setup-arm` verifies or provisions it directly. Its native
host profile is separate from the existing Thumb profile. Existing changed
binaries are rejected rather than silently enrolled.

Copied functions declare both a ROM storage offset and a RAM execution address,
with the named installation map in `config/ram-map-us-eu.json`. The pilot checks
mode, alignment, copy containment, installation literals and overlapping virtual
extents. The full linker uses the RAM address for relocations and the original
ROM address for storage, then checks both in the final ELF. Binary conversion
uses those load addresses; no bytes are moved or repaired after conversion.
Tests include an authored ARM branch whose encoding depends on its RAM address,
incorrect copy/address/mode declarations, overlapping extents, unexpected
allocated source data and an independently invalidated ARM compiler profile.

Copied C receives coverage only after its complete linked extent matches and
its changed-source control rejects. The interrupt dispatcher remains explicitly
separate assembly glue. Other copied regions remain unconverted.

## 1. Establish the reference

Run `make audit`. Stop on a mismatch and identify the dump rather than changing
the expected hash to make it pass. Record the audit's SHA-256 as the locally
verified identity. The fixed reference remains immutable throughout the work.

## 2. Map enough code to select pilot functions

Inspect startup, ARM/Thumb transitions, runtime helpers, interrupt handling and
any code copied into RAM. Record ROM offsets and runtime addresses separately.
Distinguish instructions from literal pools, tables and padding. Preserve
uncertain boundaries as uncertain, and validate them using cross-references and
runtime observation where needed.

Useful references:

- [GhidraGBA](https://github.com/SiD3W4y/GhidraGBA)
- [gbadisasm](https://github.com/camthesaxman/gbadisasm)
- [mGBA](https://github.com/mgba-emu/mgba)
- [Tonc](https://gbadev.net/tonc/)

Investigate the reported Krawall audio engine independently. The extractor
author reports an older western format without its signature. Do not infer
absence from a failed string search, or assume that current Krawall source is
the exact revision in the game.

- [Author's Bustin' Out report](https://gbatemp.net/threads/unkrawertergba-a-tool-to-rip-krawall-engine-music-from-gba-games.570236/)
- [UnkrawerterGBA](https://github.com/MCJack123/UnkrawerterGBA)
- [Krawall](https://github.com/sebknzl/krawall)

## 3. Identify and pin a compiler

Treat [agbcc](https://github.com/pret/agbcc) as a candidate, not a finding.
Use code generation and runtime helper evidence to narrow the compiler family.
Check other contemporary ARM toolchains if that evidence contradicts agbcc.
Do not install a full toolchain until the candidates and host requirements have
been inspected. Pin compiler, assembler, linker, libraries, host tools and
effective options when chosen; different units may need different settings.

## 4. Match representative functions

Select several small functions with established boundaries: simple arithmetic,
a branch/loop, structure access, and a call or switch where available. Avoid
assuming that a trivial leaf function uniquely identifies a compiler.

For each function record:

- Reference SHA-256, offset, address, ARM/Thumb mode and byte extent.
- Literal-pool ownership, surrounding alignment and known external symbols.
- Candidate source, types, compiler identity, full commands and flags.
- Raw differences, resolved calls/pointers and final exact-match result.

[objdiff](https://github.com/encounter/objdiff) can compare relocatable objects
once suitable reference objects and relocations have been reconstructed. The
final authority is linked bytes at the target addresses, including pools and
padding; relocation-normalised instruction similarity alone is insufficient.

Do not patch output, embed the original instruction body in candidate source,
mask differences, or count placeholders as recovered source. Preserve failed
candidates and useful observations locally, with authored conclusions in notes.

## 5. Integrate a source-driven exact reconstruction

Create explicit section layout and link order. Unresolved locally extracted
regions may support an intermediate reconstruction, but report them separately
as unconverted. Replace them incrementally with verified assembly or source.
Every accepted source replacement must keep whole-ROM equality. Also track
source coverage and later behavioural understanding as distinct measures.

The pilot succeeds when representative functions match under a reproducibly
pinned toolchain and the integration method preserves their final bytes. A
full-game decompilation remains a separate, subsequent milestone.

## Standalone trial headers

The pilot snapshots the source's literal include closure in each trial directory,
including both sides of conditional includes. Macro includes, `include_next`,
missing headers and source-local dependencies conservatively retain all project
headers for the real preprocessor to resolve. Reused trial directories lose stale
header snapshots before copying; a hash receipt records the retained inputs.
All project headers still participate in the full gate's freshness fingerprint.

Eight benchmark compilations (four positive candidates and their changed-source
controls) produced identical outputs with the old and new snapshot methods.
Header copies fell from 344 to 48. Measured compilation time stayed approximately
0.39 seconds in both cases; the established benefit is reduced file/disk growth,
not faster compilation. Tests cover unresolved includes, relative cycles, inactive
branches, comments, line splicing, deleted headers and snapshot independence.
