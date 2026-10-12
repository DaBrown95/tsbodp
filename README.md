# The Sims: Bustin' Out

A work-in-progress matching decompilation of *The Sims: Bustin' Out* for the
Game Boy Advance, initially targeting the multilingual USA/Europe release.

This is deliberately an **almost entirely AI-driven experiment**. Virtually
all project analysis, reconstructed code, custom tooling and documentation
are produced by AI coding agents. The owner sets the direction and uses the
project to explore what these tools can achieve. Compilation and exact byte comparison
check the results; AI-generated explanations remain subject to verification.

## Status

19 C functions match exactly, covering 676 bytes including literal pools and
alignment. The complete 16 MiB ROM matches the reference, with the remaining
regions retained as explicitly unconverted inputs. Full source reconstruction
is incomplete.

See [RAM and interrupts](docs/RAM_AND_INTERRUPTS.md) for the current milestone.

## Building

Supply your own USA/Europe ROM. Expected SHA-1:
`fb5662172fadebf4577f6f6f163741fc041c11e6`.

Follow [build setup and verification](docs/BUILD.md) to place the ROM and
configure the pinned toolchain. Setup is currently verified on the project's
macOS environment. With the tools configured:

```sh
make audit
make build
make compare
```

## About

Results are shared for inspection and reproducibility. External contributions,
pull requests, issues and support requests are not accepted.

ROMs, extracted assets and generated game binaries stay local. Original game
and third-party rights remain with their respective owners.
