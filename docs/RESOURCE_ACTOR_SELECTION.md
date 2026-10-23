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
greater than two fails. The [kind scanner](RESOURCE_COLLECTION_KIND_SCAN.md)
selects result four; otherwise the original removal helper runs and the result
is two. Both success paths store one in the requested byte. The existing
byte-return selection
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
header import; their argument and result widths remain the same. The initial two-function cohort
checked all 103 matching importers with real changed-source
controls, along with the new functions and direct matching providers. Strict
declaration diagnostics also reject missing provider declarations that ordinary
C89 compilation can leave byte-identical. The matched source objects contain
only allocated text. The broader state-setter interface correction is separate;
these proofs use its final current headers.

Twenty-five bounded initialized Thumb fixtures check actual branch, argument,
return and write traces. Eleven cases distinguish the source controls. Provider
hooks supply explicit typed results and clobber caller-saved registers; they do
not execute the scanner, remover or count algorithm, or prove random
distribution. One negative relation yields a negative random upper argument;
the fixture checks that argument flow under an abstract return, without adding
a guard or establishing an interval-validity guarantee.

The [kind scanner at `0x0804573C`](RESOURCE_COLLECTION_KIND_SCAN.md) is recovered;
the [remover at `0x080454DC`](ACTOR_ENTRIES_RECONSTRUCTION.md#random-selectable-record-removal)
now has matching C source. The connected count
helper is recovered below. The scanner's collection pointer is
the canonical actor-context member at `0x03003A2C + 0x31C`, rather than a new
independent global. Its complete source and bounded verification are described
in the scanner notes. Arbitrary scene, actor, pointer, capacity, stage and
random-interval validity remain unchecked; these static and compiler findings
do not prove gameplay behavior.


## Selectable collection-entry count

The connected count provider owns the complete `0x45410..0x454DC` extent,
204 bytes including both literal-pool groups. The existing eligibility caller
now uses its canonical name at the same address; its body changes only that
identifier. The result remains a full word; `int` is a supported C model of
that return, without establishing the original signedness. No new credit is
assigned to the existing selection or eligibility bodies.

It obtains three signed word group IDs from the stage-dependent provider. The initialized stage-two, stage-three and stage-four outputs select
three, three and two collection groups respectively, with minus one marking
the end. The provider leaves the output unwritten for other stages;
this count source adds no initialization or stage guard. The count first sums
the actual byte group counts until the sentinel or three groups. If that sum
is zero it returns zero. Otherwise it scans the same groups, subtracting one
for each record rejected by the original kind predicate. The predicate's word
result is explicitly consumed as a low byte, as observed in the caller.
The matching stage and kind provider closure below now supplies those bodies.

The existing actor-context root is `0x03003A2C`. Its collection pointer field
at `+0x31C` explains the native `0x03003D48` literals without inventing a new
global. The canonical collection uses twelve-byte records beginning at offset
four and fifty four-byte group records beginning at `0x784`. Each group has a
byte start and count. The first sum loads its collection once; the second pass
retains each actual group pointer while reloading record storage and the group
count around predicate calls. The real next-group index is captured before
the inner loop. Capturing the collection field address in that live group
body recovers the original pool placement and control flow.

Three annotations apply only to actual values: the first sum's R0 group offset
and R4 group pointer are consumed in a call-free interval, and the second
pass's R5 entry index is held in a callee-saved register across the predicate
call. A fourth collection-pointer annotation was removed without changing
bytes. Removing the remaining annotations gives mismatches; unannotated
variants and raw comparisons remain private. The source has no embedded
instruction body, invented fields, additional reads or discarded initializer.
These annotations establish a supported source form, not the original spelling.

Current importer, caller and provider comparisons include real changed-source
controls. Separate strict declarations and pinned layout/type checks distinguish
actual field and ABI contracts from byte equality. The collection record and
group capacities, pointer validity, stage validity and arbitrary input lengths
remain unchecked. Bounded fixtures and static/compiler results do not establish
whole-game behavior.


## Stage and kind provider closure

Three connected providers now supply matching C for 320 bytes: the stage group
count at `0x456F4` (72 bytes), the three-word group-ID producer at `0x45794`
(96 bytes), and the kind predicate at `0x4565C` (152 bytes). The existing
same-address group-ID and kind declarations and all accepted caller spellings
stay unchanged. Earlier original-dependency descriptions for these three bodies
are superseded by this closure. The new isolated stage header declares the
count API used by the still-original random-removal path.

Both stage providers read the complete word at game root `0x03003950 + 0x440`.
The group count returns zero for stages zero, one and every value outside zero
through four; stages two and three return three, and stage four returns two.
The group-ID producer leaves all output words unchanged for stages zero, one
and the default path. For stages two, three and four it writes respectively
`23,25,24`, `46,48,47` and `39,40,-1`. An unchanged output is not an initialized
empty list. The accepted collection count still requires an initialized list;
no stage guard or fallback initialization has been added.

The kind predicate compares the full incoming word. It returns zero for kinds
118, 124, 127, 133, 134, 135, 140, 141, 144 and 146, and one for every other
word. For example, `0x10076` is accepted while 118 is rejected; narrowing the
input would change that behavior. The count helper and selection remover
consume the observed result's low byte. Full-word return declarations model the
native constants but do not uniquely establish the original C return widths
or signedness. The unsigned stage view is likewise a supported model of the
native word/range operations rather than proof of the original C spelling.

All three sources use ordinary switches without register annotations,
assembly statements, volatile accesses or extra reads. Their generated tables,
literal pools and complete boundaries are compared at the fixed original
addresses. The 72-byte count and 152-byte predicate use the existing pinned
historical assembler profile: their source-object text is 70 and 150 bytes,
and the unchanged linker supplies the original two zero bytes of word
alignment. No assembly output or alignment bytes are edited. The 96-byte
producer has a complete 96-byte source and linked extent.

Current accepted callers and the existing selection, collection-removal and
random providers are checked with real changed-source controls. Separate
strict declaration and layout/API failures enforce the chosen consistent word
and pointer contracts even where native return constants cannot determine the
original type spelling. Bounded instruction fixtures cover initialized and
nonwriting output paths and high-word inputs; they do not establish hardware
or gameplay behavior. Pointer validity, arbitrary output capacity and the
removal retry's stage/count validity remain unchecked. The
[scanner](RESOURCE_COLLECTION_KIND_SCAN.md) and
[complete random-removal body](ACTOR_ENTRIES_RECONSTRUCTION.md#random-selectable-record-removal)
now have matching C source.

## Row collection publication

The connected row-selection provider `condition_select_actor` now supplies a
complete matching 120-byte extent at `0x20B80`, ending before the separate
`0x20BF8` restore entry. The existing `condition_select_row` call view remains
`void(void *, unsigned int)`, forwarding the observed context root
`0x03003A2C` and the full row word. Its local declaration and metadata are
unchanged. The new isolated header supplies the same provider declaration.

Rows zero, one and every word outside zero through four make no publication
call. Row two publishes groups 16 and 17; row three publishes 24, 25 and 23;
row four publishes 46, 48 and 47, in those exact orders. These are collection
group identifiers, distinct from the caller's row and from the stage group-ID
producer above. No inferred fallback group, table capacity or row guard is
added. High-word row values take the default path without low-byte narrowing.
The unsigned word formal retains the existing consistent interface, without
claiming a unique original signedness spelling.

The source uses an ordinary switch and an internal context access view, with
no register bindings, assembly statements, volatile accesses or added reads.
The context value is held across the actual publication calls and each call
receives its original full-word group argument. The already recovered
publication provider, collection clear/add operations and row caller earn no
new C credit. Their actual controls and current literal headers are checked
with the new provider. The historical assembler emits the full 118-byte
function, including its generated table and literals; the unchanged linker
supplies the original two zero bytes to the complete 120-byte boundary.

Separate strict declarations and layout/API rejection cases check the
unchanged partial context and group views. Native equality alone cannot
establish those types because this selector forwards the context without
reading its fields. Fifty-one finite call-trace fixtures cover full-word
dispatch, ordered group operands and caller-saved register clobbering; two
distinguish the changed-source group control. They abstract the publication
provider's effects and do not execute the collection bodies. Null contexts
are used only on no-call paths. Context validity, complete storage and the
providers' arbitrary count/capacity domains remain unchecked. These findings
do not establish hardware or gameplay behavior.
