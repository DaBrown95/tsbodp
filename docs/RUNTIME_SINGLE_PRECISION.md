# Single-precision providers and connected conversions

The pinned [`fp-bit-base.c`](https://github.com/pret/agbcc/blob/da598c1d918402c42c0c0d7128ba14567f3175e9/libgcc/fp-bit-base.c) now supplies the complete 23-function runtime
interval `0x4DD18..0x4E6F8`: 2,528 matching C extent bytes, including 2,442
instruction bytes, 56 literal-pool bytes and 30 zero alignment bytes. The
seven-function double/single conversion subset accounts for 524 bytes; the
remaining sixteen SF arithmetic, comparison and signed-conversion entries
account for 2,004. These are source ownership counts for this interval, not
whole-game completeness.


| Entry | ROM offset | C extent bytes |
| --- | --- | ---: |
| `__negdf2` | `0x4DD18` | 40 |
| `__make_dp` | `0x4DD40` | 40 |
| `__truncdfsf2` | `0x4DD68` | 68 |
| `__pack_f` | `0x4DDAC` | 184 |
| `__unpack_f` | `0x4DE64` | 124 |
| `_fpadd_parts_f` | `0x4DEE0` | 380 |
| `__addsf3` | `0x4E05C` | 44 |
| `__subsf3` | `0x4E088` | 52 |
| `__mulsf3` | `0x4E0BC` | 356 |
| `__divsf3` | `0x4E220` | 236 |
| `__fpcmp_parts_f` | `0x4E30C` | 228 |
| `__cmpsf2` | `0x4E3F0` | 40 |
| `__eqsf2` | `0x4E418` | 72 |
| `__nesf2` | `0x4E460` | 72 |
| `__gtsf2` | `0x4E4A8` | 72 |
| `__gesf2` | `0x4E4F0` | 72 |
| `__ltsf2` | `0x4E538` | 72 |
| `__lesf2` | `0x4E580` | 72 |
| `__floatsisf` | `0x4E5C8` | 96 |
| `__fixsfsi` | `0x4E628` | 104 |
| `__negsf2` | `0x4E690` | 36 |
| `__make_fp` | `0x4E6B4` | 24 |
| `__extendsfdf2` | `0x4E6CC` | 44 |

The original notices and linking exceptions remain in every adapted file.
The existing pinned old Thumb `-O2` recipe matches every selected body on its
first source-backed comparison. This does not uniquely identify the game's
historical compiler. Only symbol wrappers, distinct SF identifiers, separate
translation-unit helper visibility and source-backed alignment are adapted.
The inline multiply/divide helpers retain their source operations. There are
no assembly instruction bodies or binary patches in these replacements.

The SF parts record is 16 bytes, four-aligned, with class/sign/exponent/fraction
at offsets 0/4/8/12. It shares the upstream class enum and target mode types with
the existing 20-byte DF view. All 23 actual definitions compile together under
the old target compiler with warnings as errors and typed function pointers;
widths, field offsets and alignment are checked. The DF conversion interface
retains its high-word-first floating-value ABI and actual fifth argument word
on the stack for `__make_dp`.

The SF NaN helper is an external access view at `0x030024D8`, established by
three actual original/matching literal references. It adds no allocation,
initializer or static-data ownership. The original special-value field limits
remain: unpack can leave exponent/fraction unwritten on zero/infinity and
exponent unwritten on NaN; pack reads fraction before class dispatch. Arbitrary
malformed parts remain outside the stated source domain. The accepted startup
DMA clear zeros the full SF and DF records in `0x030015B0..0x03007D00`
before later game initialization, establishing their initial class, sign,
exponent and fraction as zero. Later arbitrary aliases/writes remain open.
No invented initialization changes original generation.

Every full extent rejects its actual changed-source control, including controls
that change output size. Twenty-three initialized finite cases across three
stack seeds also give 69 observable control differences, with original and
compiled bodies agreeing in all 69 cases. These checks reuse the unchanged
bounded Thumb interpreter and actual compiled providers, without hooks or ROM
fallback for missing instruction bodies/pools. The above-midpoint truncation
case specifically needs the discarded-bit sticky mark. An executed removed
literal pool rejects even with the reference ROM available.

These finite witnesses establish neither universal IEEE behavior nor complete
incoming transfers, caller domains or gameplay reachability. The earlier
floating-point model counts remain unchanged.
