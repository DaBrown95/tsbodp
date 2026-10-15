# Double conversion runtime source evidence

This connected conversion path is adapted from
[`libgcc/fp-bit-base.c` and `libgcc/libgcc2.c`](https://github.com/pret/agbcc/tree/da598c1d918402c42c0c0d7128ba14567f3175e9/libgcc)
at the pinned agbcc revision. The original copyright notices, GPL terms and
linking exceptions remain in the adapted sources. The complete GPL text is in
`licenses/GCC-GPL-2.0.txt`; these borrowed files retain their upstream licence.

| Entry | ROM offset | Complete extent |
| --- | --- | --- |
| `__fixunsdfsi` | `0x4CDC4` | 68 |
| `__gedf2` | `0x4DB44` | 76 |
| `__floatsidf` | `0x4DC28` | 124 |
| `__fixdfsi` | `0x4DCA4` | 116 |

The four extents total 384 bytes. Both normal and strict-declaration builds use
the separately pinned old Thumb backend and the upstream Makefile's `-O2`.
Every complete extent, including literal pools and alignment, matches the fixed
reference at its original address; all four actual changed-source controls
reject in both modes. The signed conversion's 116-byte extent includes the
original two-byte zero tail through `0x4DD18`. The shorter 114-byte inventory
entry omitted that tail. Explicit zero alignment follows the upstream libgcc
Makefile; no instruction bodies, output patches or instruction glue are added.
This source/compiler correspondence does not uniquely identify the game's
historical toolchain.

The new `runtime_conversion.h` declares only these four exports and imports the
existing runtime types. The existing floating-point and integer headers are
unchanged. Actual target-compiler checks cover sixteen mode, width, alignment
and offset facts and the four complete function definitions. Five incompatible
input/result declarations reject. Omitting the real unpack declaration leaves
the legacy signed-conversion bytes identical but causes strict compilation to
reject, demonstrating that byte equality alone does not establish a valid API.

DF arguments and returns use the old mixed-word ABI: the high word is in R0
and the low word in R1. Signed and unsigned integer results are 32 bits. The
unpacked record and integer helper conventions remain those described in
`RUNTIME_FLOATING_POINT.md`; no host floating-point layout is assumed.

## Source adaptations and domains

The signed conversion and greater-or-equal wrapper retain the selected upstream
function bodies and their class checks. The wrapper returns a signed comparison
result, including -1 for unordered input; it is not a Boolean result. The
double-to-signed routine returns zero for zero and NaN, saturates infinities or
large exponents, and otherwise truncates using the unpacked fraction.

The unsigned conversion retains its branch condition, signed casts and low
branch. Only its final high-branch bias subtraction is unsigned. The upstream
signed subtraction overflows for the intended upper unsigned range; the
unsigned expression has identical native bytes and performs defined modular
subtraction. The unchanged upstream predecessor and its raw matching output
remain separate evidence.

For an ordinary defined-source unsigned-conversion case, the relevant DF-to-SI
cast must have a representable truncated integral part. This includes some
negative fractions just below INT_MIN: -2147483648.5 truncates to INT_MIN,
whereas -2147483649 does not. A negative low-branch input such as -1.5 returns
unsigned `0xFFFFFFFF`, rather than a zero clamp. Nonfinite and out-of-cast-domain
unsigned-conversion observations remain native-only diagnostics.

The integer-to-double zero branch leaves the unpacked fraction unwritten before
calling the existing packer, whose source reads that field before class
dispatch. Zero therefore remains a seeded native-only case. No initialization
or guards have been invented. INT_MIN takes the explicit constant-return path;
other nonzero signed inputs initialize and normalize the required fraction.

## Bounded verification

The source model checks 649 base cases: 628 defined-source cases and 21 separate
native-only cases. Three defined cases exercise the negative cast-formal edge.
Original and compiled bodies execute with three stack seeds, giving 3,894
base executions. All four actual source controls have defined witnesses, with
334 defined-case divergences; four additional unsigned-control differences
belong only to the native-only domain. Eight deliberately wrong models reject.

Twelve separate sequential actual-entry compositions include eleven defined
nonzero cases and one native-only zero case, with 216 entry executions. These
are not added to the base-case count. Seven existing runtime providers are
supplied statically; six are actually called by the retained cases. The checks
execute nested bodies without opaque helper hooks or external-ROM pool rescue.
They reject executed truncated literal pools, missing actual providers,
incorrect DF return words, callee-save/stack failures and domain relabeling.

The four new definitions have eight provider-symbol imports. Five existing
consumer definitions have ten metadata bindings to integer-to-double and
double-to-unsigned conversion; their accepted extents total 2,372 bytes. Those
counts describe this bounded binding audit, not a complete runtime caller
inventory. Other comparison wrappers, single-precision arithmetic and remaining
runtime entries stay original. Matching bytes, bounded source-model execution,
whole-ROM equality and gameplay correctness remain separate claims.
