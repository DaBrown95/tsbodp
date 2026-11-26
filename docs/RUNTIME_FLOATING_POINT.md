# Floating-point runtime

The game's double-precision arithmetic and comparison routines, and a few
64-bit integer helpers, are adapted from the public
[`libgcc/fp-bit-base.c`, `libgcc/libgcc2.c` and `libgcc/longlong.h`](https://github.com/pret/agbcc/tree/da598c1d918402c42c0c0d7128ba14567f3175e9/libgcc)
at the pinned agbcc revision. Original copyright notices and linking
exceptions stay in each adapted file, and the complete GPL text is in
`licenses/GCC-GPL-2.0.txt`. These files keep their upstream licence, not the
licence of this project's own work.

The upstream libgcc Makefile compiles these files with the old Thumb compiler
and `-O2`. The separately pinned `agbcc_old` backend reproduces that selection
from an independent copy of the 130 tracked compiler inputs; the default Thumb
backend is a separate profile. That this backend matches does not identify the
game's own toolchain.

## Arithmetic functions

| Entry | ROM offset | Full extent |
| --- | --- | --- |
| `__pack_d` | `0x4D010` | 328 |
| `__unpack_d` | `0x4D158` | 216 |
| `_fpadd_parts` | `0x4D230` | 620 |
| `__adddf3` | `0x4D49C` | 48 |
| `__subdf3` | `0x4D4CC` | 56 |
| `__muldf3` | `0x4D504` | 680 |
| `__divdf3` | `0x4D7AC` | 392 |
| `__fpcmp_parts_d` | `0x4D934` | 256 |
| `__lshrdi3` | `0x4E6F8` | 52 |
| `__muldi3` | `0x4E72C` | 112 |
| `__negdi2` | `0x4E79C` | 24 |

The eleven functions total 2,784 bytes. Each full extent, including literal
pools and alignment, matches at its original address in both the normal and
strict-declaration builds. Each changed-source control is rejected, and the
full ROM is byte-identical to the reference. The comparator has 254
instruction bytes and a two-byte zero tail; the shift and negation helpers
have 50 and 22 instruction bytes, each with a two-byte zero tail. Alignment is
written explicitly, as in the upstream libgcc Makefile. The sources contain no
original instruction bodies and no instruction-level assembly.

Five accepted functions call the add, subtract and multiply routines: actor
state 42, actor input velocity, the proportional scene counter, actor state 27
and menu scrolling text. Their eight bindings agree with the entries above,
and their extents total 2,372 bytes. This is a count of those bindings, not a
complete list of callers. The double-to-integer conversions are in
[RUNTIME_CONVERSIONS.md](RUNTIME_CONVERSIONS.md).

## Types and calling convention

Checked with the old target compiler, the unpacked record is 20 bytes,
four-aligned: class at 0, sign at 4, signed normal exponent at 8 and the
unsigned 64-bit fraction at 12, low word first. Doubles use the old
mixed-word convention: the high word is passed and returned in R0 and the low
word in R1. The pack and unpack sources swap the two words around their
packed IEEE bitfield view. The 64-bit integer helpers take the low word in R0
and the high word in R1. No host double layout is assumed.

The upstream add-parts helper is `static`. Here it is exported so that it can
live in its own translation unit, with its meaning and three-pointer call
unchanged. The upstream NaN helper's static record is an access view of RAM
at `0x030024C0`, taken from the literals in the compiled code. It has no
initialiser and is not treated as an allocated data object. Pack and unpack
never use that helper, so the allocation does not appear in their translation
units.

The game's memory initialiser clears the double and single NaN records to
zero during startup, with a fixed-source DMA fill of `0x030015B0..0x03007D00`.
That is where their startup contents come from; it does not rule out later
writes through other aliases.

The negation routine does both word subtractions as unsigned arithmetic, which
avoids signed overflow in the upstream expression. The conversion from
unsigned to signed words keeps the two's-complement bits, and the generated
extent is unchanged. The other types, class values, guard constants and
partial-product expressions follow the pinned source, and the headers leave
out unrelated upstream conditional features.

## Input domains

The union layout and the unsigned-to-signed conversions depend on the pinned
compiler's behaviour. The shift helper needs a count from 0 to 63. The
arithmetic routines need unpacked inputs with valid class, sign, exponent and
fraction values; they are not portable C for arbitrary malformed input.

The original unpacker leaves the exponent and fraction unwritten on some zero,
infinity and NaN paths, and pack reads its input fraction before checking the
class. The source keeps these behaviours; no initialisation or guards have
been added. Underflow packing shifts and truncates, and must not be replaced
with host IEEE rounding.

## Checks run

An integer source model runs 1,979 initialised cases that the source defines,
plus 40 special-value cases that only the original code reaches. Original and
compiled bodies each run with three stack seeds, with no stand-in helpers and
no fallback to ROM data. All eleven changed-source controls diverge on defined
cases (884 differences), plus nine more in the original-only cases. Eleven
deliberately wrong models are rejected. The checks also include 17
interpreter and input guards, 450 arithmetic primitive checks, 112 carry and
flag branch cases and 15 validator corruption controls. A run with a missing
literal pool is rejected even when the original ROM is available.

The compiler-profile tooling passes 246 tests, including stale and altered
inputs and rejection of a parallel bootstrap recipe. A fresh serial bootstrap
reproduces all eleven extents.

These checks do not cover every caller precondition, hardware floating point,
full IEEE conformance or correct gameplay behaviour.

## Double-comparison wrappers

Six ordinary C wrappers, with the existing `__gedf2`, make up the comparison
family. All six bodies come from the pinned `fp-bit-base.c`, built with the
same `agbcc_old -O2` recipe.

| Entry | ROM offset | Complete extent |
| --- | --- | ---: |
| `__cmpdf2` | `0x4DA34` | 44 |
| `__eqdf2` | `0x4DA60` | 76 |
| `__nedf2` | `0x4DAAC` | 76 |
| `__gtdf2` | `0x4DAF8` | 76 |
| `__gedf2` (see [RUNTIME_CONVERSIONS.md](RUNTIME_CONVERSIONS.md)) | `0x4DB44` | 76 |
| `__ltdf2` | `0x4DB90` | 76 |
| `__ledf2` | `0x4DBDC` | 76 |

The six wrappers add 424 bytes, and with `__gedf2` the seven total 500 bytes
across `0x4DA34..0x4DC28`. Each unpacks both doubles into 20-byte records and
calls `__fpcmp_parts_d`. They return signed comparison words, not Booleans.
The EQ, NE, LT and LE wrappers return positive one if either input is NaN;
GT and GE return negative one. The generic comparator passes the NaN result
through from the parts comparator. The caller applies the test that suits its
operation.

The names follow the upstream order and the result conventions. Wrappers that
share a result convention cannot be told apart by what they do, so the
historical symbol names and exact toolchain release are not recovered. Among
the accepted C, only `__fixunsdfsi` calls any of these (the GE wrapper); none
of the six new wrappers is called directly.

Only the selected upstream wrappers are expanded. The full copyright,
authorship, GPL and linking-exception notices stay; trailing whitespace is
trimmed. The six use the existing mixed-word convention, target types and
unpacked-record declarations, and their prototypes were added to `runtime_fp.h`
without changing any existing declaration. A strict old-target compilation of
all seven definitions with the conversion header checks the signed 32-bit
result, the 64-bit double, the 20-byte record and function-pointer
compatibility.

Each full extent matches and rejects a source change that adds one to the
comparator's return value. For equal finite inputs such as one and one, both
parts records are initialised and the result is zero, while the changed source
returns one. Five of the changed sources keep their size; GT's grows from 76
to 80 bytes and is rejected as a whole. The six spans hold 414 instruction
bytes and ten trailing zero alignment bytes, with no literal pools and no
assembly in the C. Alignment follows the upstream Makefile. No runtime model
or gameplay test covers the wrappers, and the model counts above are for the
arithmetic functions only. The limits on input domains still apply, and
matching and the strict API check do not show IEEE conformance or that the
wrappers are reached at runtime.
