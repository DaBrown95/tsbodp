# Resource actor selection

The provider at `0x0804559C` and its eligibility helper at `0x080457F4` match
their complete 112- and 96-byte extents in ordinary C without register bindings.
The first extent includes literal pools at `0x080455E8`, `0x080455EC` and
`0x08045600`, returns at `0x0804560A`, and ends before the distinct entry at
`0x0804560C`. The helper includes its two pool words at `0x08045844` and
`0x08045848`, returns at `0x08045852`, and ends before `0x08045854`.

Eligibility reads the complete unsigned stage word at game offset `0x440`.
It then tests condition group `(4,4)`, the requested byte at `0x747`, incoming
word comparisons `scene <= 14` and `actor > 14`, selected-row membership and
an original collection-count helper. These tests short circuit in that order.
The matching condition-group provider returns a word, consumed here through
the original low-byte cast. The selected-row provider's actual guarded interface
returns a byte. A provisional private word declaration for the latter could
retain the same caller bytes with a cast; it was superseded before publication
and is rejected by a compiler type-assignment diagnostic.

Selection returns zero when eligibility or the random test fails. Otherwise it
reads signed relation entry 13, treats the `-128` sentinel as zero, and passes
`(relation + 100) / 2` to the matching signed random-range provider. A result
greater than two fails. The original kind scanner selects result four;
otherwise the original removal helper runs and the result is two. Both success
paths store one in the requested byte. The existing byte-return selection
interface remains unchanged, and all native exits return zero, two or four.
Neither the inferred selection name nor those values establish actor-ID or
gameplay meanings.

The two new views overlap physical game storage. The world root is
`0x03003950`; the relation root is `0x03003980`, or world plus `0x30`.
Their requested offsets `0x747` and `0x717` identify the same byte. Pinned
compiler checks establish observed prefix sizes/alignment `0x748/4` and
`0x718/4`, the unsigned word stage, byte flags, and the existing signed-byte
relation record stride four. These prefixes describe accessed offsets and do
not establish complete game storage or capacity. Actual wrong widths, offsets,
packing, provider-return types and signedness fail separate diagnostics.

Only the two old selection declarations were replaced with a guarded role
header import; their argument and result widths remain the same. All 103
current matching importers were freshly checked with real changed-source
controls, along with the new functions and direct matching providers. Strict
declaration diagnostics also reject missing provider declarations that ordinary
C89 compilation can leave byte-identical. The matched source objects contain
only allocated text. The broader state-setter interface correction is separate;
these proofs use its final current headers.

Twenty-five bounded initialized Thumb fixtures check actual branch, argument,
return and write traces. Eleven cases distinguish the source controls. Provider
hooks supply explicit typed results and clobber caller-saved registers; they do
not execute the original scanner, remover or count algorithm, or prove random
distribution. One negative relation yields a negative random upper argument;
the fixture checks that argument flow under an abstract return, without adding
a guard or establishing an interval-validity guarantee.

The kind scanner at `0x0804573C`, remover at `0x080454DC` and count helper at
`0x08045410` remain explicitly original. The scanner's collection pointer is
the canonical actor-context member at `0x03003A2C + 0x31C`, rather than a new
independent global. Its incomplete C trials are not credited. Arbitrary scene,
actor, pointer, capacity, stage and random-interval validity remain unchecked;
these static and compiler findings do not prove gameplay behavior.
