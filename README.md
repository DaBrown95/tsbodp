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

The current build is verified on macOS with the local tool profile in
[`config/pilot-toolchain.json`](config/pilot-toolchain.json). It requires
Python 3.13, Git, Make and Xcode's compiler tools. ROM auditing and the
synthetic safeguard tests need only Python 3.10 or later.

A fresh checkout does not yet provision the toolchain automatically. The
runner checks the compiler source revision, native tool hashes and complete
Apple Clang version against the profile. Builds on another host need reviewed
tool pins and a fresh matching run; portable setup is still in progress.

<details>
<summary>Set up the local toolchain</summary>

Run these commands from the repository root. First create the Python environment:

```sh
python3.13 -m venv toolchains/analysis-venv
toolchains/analysis-venv/bin/python -m pip install -r config/analysis-requirements.txt
```

Build the matching Thumb compiler from its pinned public source:

```sh
git clone https://github.com/pret/agbcc.git toolchains/agbcc
git -C toolchains/agbcc checkout da598c1d918402c42c0c0d7128ba14567f3175e9
make -C toolchains/agbcc/gcc -j1
```

Build GNU binutils 2.43.1 into `toolchains/binutils/`. Verify the source archive
before extracting it:

```sh
curl --fail --location --output toolchains/binutils-2.43.1.tar.xz \
  https://ftp.gnu.org/gnu/binutils/binutils-2.43.1.tar.xz
printf '%s  %s\n' \
  13f74202a3c4c51118b797a39ea4200d3f6cfbe224da6d1d95bb938480132dfd \
  toolchains/binutils-2.43.1.tar.xz | shasum -a 256 -c -
tar -xf toolchains/binutils-2.43.1.tar.xz -C toolchains
```

Use a separate build directory. From the repository root:

```sh
project_root="$PWD"
mkdir -p toolchains/binutils-build-host
cd toolchains/binutils-build-host
CFLAGS='-O2 -std=gnu11' ../binutils-2.43.1/configure \
  --target=arm-none-eabi --prefix="$project_root/toolchains/binutils" \
  --disable-nls --disable-werror --disable-gdb --disable-gdbserver \
  --disable-gprofng --disable-sim --disable-gold --without-zstd \
  --with-system-zlib
make -j6 MAKEINFO=true all-binutils all-gas all-ld
make MAKEINFO=true install-binutils install-gas install-ld
cd "$project_root"
```

Only the Thumb compiler and binutils are required for the current matching
functions; the complete agbcc runtime libraries are not built. Rebuilding on
another host can change native binary hashes. Those changes require review
and matching verification before updating the local profile.

</details>

Supply your own original USA/Europe ROM at:

```text
baseroms/Sims, The - Bustin' Out (USA, Europe) (En,Fr,De,Es,It,Nl).gba
```

Expected size: **16,777,216 bytes**. Expected SHA-1:
`fb5662172fadebf4577f6f6f163741fc041c11e6`.
USA revision 1 is a separate comparison reference, not the current build target.

With the local toolchain configured:

```sh
make audit
make doctor
make build
make compare
```

The output is `build/us-eu/bustin-out.gba`. Every byte must match the reference;
there are no masks, ignored differences or output repairs. The build also
requires changed-source negative controls to fail comparison.

Other commands:

| Command | Purpose |
| --- | --- |
| `make test` | Test identity, layout, comparison and progress safeguards without a ROM. |
| `make pilot` | Compile and compare the accepted C functions independently. |
| `make ram-map` | Verify copied RAM regions and export local analysis images. |
| `make analyze` | Reproduce the bounded startup analysis. |
| `make audit-all` | Also audit USA revision 1, when its separate dump is present. |
| `make inventory` | Audit the ROM and refresh the full static entry and extent map. |
| `make progress` | Refresh the treemap from current inventory and verified build evidence. |

Use `make test PYTHON=toolchains/analysis-venv/bin/python` to also run the
scanner controls; plain `make test` skips them when Capstone is unavailable.

Rendering the treemap additionally needs Pillow:

```sh
toolchains/analysis-venv/bin/python -m pip install -r config/progress-requirements.txt
make inventory
make progress
```

Run `make build` again after source or build-helper changes before refreshing
progress. Run `make inventory` again after changes to the scanner or its map
inputs. The renderer rejects stale evidence. The public snapshot contains
addresses, sizes and verification metadata, without ROM bytes or local paths.

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
