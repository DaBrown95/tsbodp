# Floating-point runtime source evidence

This connected double-precision path is adapted from the public
[`libgcc/fp-bit-base.c`, `libgcc/libgcc2.c` and `libgcc/longlong.h`](https://github.com/pret/agbcc/tree/da598c1d918402c42c0c0d7128ba14567f3175e9/libgcc)
at the existing pinned agbcc revision. Original copyright notices and linking
exceptions remain in each adapted file; the complete GPL text is in
`licenses/GCC-GPL-2.0.txt`. These files retain their upstream licence, rather
than the licence for this project's own work.

The upstream libgcc Makefile explicitly uses the old Thumb compiler and `-O2`.
The separately pinned `agbcc_old` backend builds that exact upstream
`OLD_COMPILER` selection in an independent copy of the 130 tracked compiler
inputs. The default Thumb backend remains a separate profile. Selecting this
backend does not identify the game's historical toolchain uniquely.

## Connected source ownership

| Entry | ROM offset | Full candidate extent |
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

The eleven functions total 2,784 verified matching C bytes. Each complete extent
matches at its original address, including literal pools and alignment, in both
normal and strict-declaration builds. Each changed-source negative control
rejects, and the integrated full ROM is byte-identical to the fixed reference.
The comparator has 254 instruction bytes and a two-byte zero tail;
the shift and negation helpers have 50/22 instruction bytes and two-byte zero
tails. Explicit source alignment follows the upstream libgcc Makefile. It
contains no original instruction bodies and adds no low-level instruction glue.

The five existing direct consumers are actor state 42, actor input velocity,
the proportional scene counter, actor state 27 and menu scrolling text. Their
eight current bindings to add/subtract/multiply all agree with these entries;
the five accepted consumer extents total 2,372 bytes. This finite binding audit
is not a complete runtime caller inventory. The remaining double-comparison
wrappers are covered below; single-precision
arithmetic and other remaining runtime entries stay original. The connected
conversion subset is documented in [RUNTIME_CONVERSIONS.md](RUNTIME_CONVERSIONS.md).

## Types and ABI

The actual old target compiler checks the 20-byte, four-aligned unpacked record:
class at 0, sign at 4, signed normal exponent at 8, and the unsigned 64-bit
fraction at 12. The fraction's two 32-bit words use low word first. DF values
use the distinct old mixed-word convention: the high word is passed/returned
in R0 and the low word in R1. The pack/unpack source explicitly swaps the two
words around its packed IEEE bitfield view. No host double layout is assumed.
The integer helpers use low word in R0 and high word in R1.

The upstream static add-parts helper is exposed only to permit separate
translation-unit ownership. Its source meaning and actual three-pointer call
contract are retained. The upstream NaN helper's static record is an external
RAM access view at `0x030024C0`, established by the actual core literals. No
initializer, complete allocation ownership or new data credit is assigned to
that storage. Pack and unpack never consume that helper, so its unused static
allocation is absent from those translation units.

The negation adaptation performs both word subtractions as unsigned arithmetic,
avoiding signed word-negation overflow in the upstream expression. The target's
unsigned-to-signed word conversion preserves the resulting two's-complement
bits; the full generated extent remains identical. Other required types,
class values, guard constants and partial-product expressions follow the pinned
source. The headers omit unrelated upstream conditional features.

## Verification boundaries

The target union representation and unsigned-to-signed conversions rely on the
pinned compiler's implementation. The shift helper requires a count in 0..63.
Unpacked arithmetic inputs require the established class/sign/exponent/fraction
representations and bounded signed arithmetic; arbitrary malformed parts are
not a portable-C contract.

The original unpacker leaves exponent/fraction fields unwritten on some zero,
infinity and NaN paths. Pack reads its input fraction before dispatching on
class. Those source-domain limits remain explicit: no invented initialization
or guards have been added. The bounded checks keep defined-source cases and
seeded native transport diagnostics in separate domains.
Underflow packing shifts and truncates; it must not be replaced by an assumed
host IEEE rounding result. Static byte equality, finite execution checks,
whole-ROM equality and gameplay remain separate claims.

The integer source model checks 1,979 initialized, defined-source cases and
40 separate native-only special-value wrapper cases. Original and compiled
bodies execute with three stack seeds, without helper hooks or external ROM
data fallback. All eleven actual source controls have defined-case witnesses:
884 differences belong to that domain; nine additional differences are
native-only diagnostics. Eleven deliberately wrong models also reject.
The checks include 17 interpreter/input guards, 450 arithmetic primitive checks,
112 decoded carry/flag branch cases and 15 validator corruption controls.
An executed missing-literal-pool case rejects even with the original ROM
available. Independent review and a writer-trapped full replay passed.

The compiler-profile tooling passes 246 tests, including stale and altered
inputs and rejection of a parallel bootstrap recipe. An actual fresh serial
bootstrap reproduces all eleven extents. These finite checks do not establish
all caller preconditions, every unknown stack representation, hardware
floating-point behavior, universal IEEE conformance or gameplay correctness.

## Double-comparison wrapper closure

Six further ordinary-C wrappers add 424 complete extent bytes around the
existing unpacker and parts comparator. The same pinned `fp-bit-base.c` supplies
all six bodies, and the established `agbcc_old -O2` recipe matches each on its
first source-backed reconstruction. Existing providers and the already-owned
`__gedf2` add no new coverage.

| Entry | ROM offset | Complete extent |
| --- | --- | ---: |
| `__cmpdf2` | `0x4DA34` | 44 |
| `__eqdf2` | `0x4DA60` | 76 |
| `__nedf2` | `0x4DAAC` | 76 |
| `__gtdf2` | `0x4DAF8` | 76 |
| Existing `__gedf2` | `0x4DB44` | 76 |
| `__ltdf2` | `0x4DB90` | 76 |
| `__ledf2` | `0x4DBDC` | 76 |

The seven wrappers account for the connected `0x4DA34..0x4DC28` interval, with
500 C extent bytes in total. Each unpacks both DF inputs into the existing
20-byte records and calls `__fpcmp_parts_d`. These functions return signed
comparison words, not Boolean values. The EQ, NE, LT and LE wrappers return
positive one when either input is NaN; GT and existing GE return negative one.
The generic comparator delegates its NaN result to the parts comparator. The
caller applies the comparison appropriate to its operation.

Names follow the pinned upstream order and compatible native result protocols.
Wrappers sharing a result protocol cannot be distinguished by their operations
alone, so this does not uniquely recover historical symbol names or identify
the precise original toolchain release. The current accepted-C import audit
finds `__fixunsdfsi` calling the already-owned GE wrapper; it finds no direct
import of the six newly owned wrappers. Their reconstruction closes a coherent
runtime family without implying gameplay use or a complete caller inventory.

Only the selected upstream symbol wrappers are expanded. The complete original
copyright, authorship, GPL and linking-exception notices remain; trailing
whitespace is trimmed. All six use the existing mixed-word DF ABI, target
representation and unpacked-record declarations. Their six new prototypes in
`runtime_fp.h` leave every existing type and provider signature unchanged.
A strict old-target compilation includes all seven actual definitions together
with the conversion header, checks the signed 32-bit result, 64-bit DF and
20-byte record, and checks compatible function pointers. The existing GE body
also remains exact with its own rejected source control.

Every new full extent matches and rejects a real source mutation that adds one
to the existing comparator return. Equal finite inputs such as one and one
initialize both parts records and produce zero, while the mutation returns one.
Five controls retain their extents; GT's grows from 76 to 80 bytes and rejects
in full. The six positive spans contain 414 instruction bytes and ten trailing
zero alignment bytes, with no literal pools or assembly instructions in the C.
The alignment directives follow the upstream Makefile. No new runtime model or
gameplay test was run, and the earlier bounded model counts are unchanged.
Existing target-representation and provider-domain limits still apply; matching
and the strict API check do not prove universal IEEE behavior or runtime reachability.
