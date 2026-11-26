# Double conversion runtime

The four routines below convert between doubles and integers and compare two
doubles. They are adapted from
[`libgcc/fp-bit-base.c` and `libgcc/libgcc2.c`](https://github.com/pret/agbcc/tree/da598c1d918402c42c0c0d7128ba14567f3175e9/libgcc)
at the pinned agbcc revision. The original copyright notices, GPL terms and
linking exceptions stay in the adapted sources. The complete GPL text is in
`licenses/GCC-GPL-2.0.txt`, and these files keep their upstream licence.

| Entry | ROM offset | Complete extent |
| --- | --- | --- |
| `__fixunsdfsi` | `0x4CDC4` | 68 |
| `__gedf2` | `0x4DB44` | 76 |
| `__floatsidf` | `0x4DC28` | 124 |
| `__fixdfsi` | `0x4DCA4` | 116 |

The four extents total 384 bytes. They are built with the separately pinned
old Thumb backend and the `-O2` that the upstream Makefile uses, in both the
normal and strict-declaration builds. Each extent, including literal pools and
alignment, matches the reference at its original address, and each
changed-source control is rejected in both modes. Alignment is written
explicitly, as in the upstream libgcc Makefile. No instruction bodies, output
patches or instruction glue are used. That the upstream source and compiler
produce these bytes does not identify the game's own toolchain.

`__fixdfsi` is 116 bytes because it includes the original two-byte zero tail
up to `0x4DD18`.

`runtime_conversion.h` declares only these four exports and uses the existing
runtime types; the floating-point and integer headers are unchanged. Checks
with the target compiler cover sixteen facts about mode, width, alignment and
offset, and the four function definitions. Five incompatible input or result
declarations are rejected. Leaving out the real unpack declaration keeps the
signed conversion's bytes identical but makes strict compilation fail, so
byte equality alone does not show an API is valid.

Doubles are passed and returned in the old mixed-word convention: high word in
R0, low word in R1. Signed and unsigned integer results are 32 bits. The
unpacked record and integer helpers follow
[RUNTIME_FLOATING_POINT.md](RUNTIME_FLOATING_POINT.md). No host floating-point
layout is assumed.

## Differences from upstream and input domains

`__floatsidf` and `__fixdfsi` keep the selected upstream bodies. `__gedf2`
returns a signed comparison result, including -1 for unordered input, not a
Boolean. `__fixdfsi` returns zero for zero and NaN, saturates infinities and
large exponents, and otherwise truncates using the unpacked fraction.

`__fixunsdfsi` keeps its branch condition, signed casts and low branch. Only
the final bias subtraction in the high branch is unsigned: the upstream signed
subtraction overflows for the upper part of the unsigned range, while the
unsigned expression compiles to the same bytes and is defined modular
arithmetic.

For `__fixunsdfsi` to be well defined, its double-to-signed cast must have a
representable truncated integral part. That includes some negative fractions
just below INT_MIN: -2147483648.5 truncates to INT_MIN, but -2147483649 does
not. A negative low-branch input such as -1.5 returns `0xFFFFFFFF`, not zero.
Behaviour outside the cast's domain (infinities, NaN, out-of-range values) was
only seen in the original code, not defined by the source.

In `__floatsidf`, a zero input leaves the unpacked fraction unwritten before
the packer reads it. This is the original behaviour, and no initialisation or
guard has been added. INT_MIN takes an explicit constant-return path. Other
non-zero inputs initialise and normalise the fraction.

## Checks run

A source model checks 649 cases: 628 where the source defines the result and
21 that only the original code reaches. Three of the defined cases are at the
negative cast edge. The original and compiled bodies each run with three stack
seeds, for 3,894 runs. Each of the four changed-source controls diverges on
defined cases (334 in total), plus four more in the original-only cases.
Eight deliberately wrong models are rejected.

Twelve further sequences call the actual entries in turn (eleven defined
non-zero cases and one zero case that only the original reaches), for 216
entry executions, counted separately from the 649 base cases. Seven existing
runtime routines are supplied, and six of them are called by these sequences.
The checks run the nested bodies with no stand-in helpers, and reject
truncated literal pools, missing providers, wrong return words, callee-save or
stack errors, and mislabelled domains.

The four definitions import eight provider symbols. Five existing callers
bind ten times to the integer-to-double and double-to-unsigned conversions;
their extents total 2,372 bytes. This is a count of those bindings, not a
complete list of callers.

Matching bytes, the source model, whole-ROM equality and correct gameplay
behaviour are separate claims, and only the first three are checked here.
