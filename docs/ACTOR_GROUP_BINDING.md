# Actor group resources and palette composition

Fifteen connected C functions reconstruct 2,168 bytes, including literal pools and
alignment. They close the resource and palette dependencies of the accepted
actor factory, actor-part updater and scene-player factory. Names describe the
observed part indices and transfers; this is static/compiler evidence, without
a runtime or gameplay experiment.

| Entry | Function | Complete extent |
| --- | --- | ---: |
| `0x08001400` | `frame_clear_part_variants` | 24 |
| `0x08001450` | `frame_set_part_variants` | 40 |
| `0x080140CC` | `frame_create_palette_menu_actors` | 396 |
| `0x08014258` | `frame_update_palette_menu_actor` | 232 |
| `0x08014340` | `frame_step_palette_menu_choices` | 168 |
| `0x080143E8` | `frame_draw_palette_menu_row` | 228 |
| `0x080144CC` | `frame_step_palette_menu` | 184 |
| `0x080161AC` | `frame_load_actor_palette_pair` | 32 |
| `0x080256A4` | `frame_create_palette_scene_actor` | 248 |
| `0x0803AD64` | `frame_bind_actor_group` | 164 |
| `0x0803AE08` | `frame_compose_actor_group_palette` | 116 |
| `0x0803AE7C` | `frame_compose_actor_group_alternate_palette` | 76 |
| `0x0803AEC8` | `frame_load_actor_group_palette` | 144 |
| `0x0803AF58` | `frame_load_actor_group_alternate_palette` | 96 |
| `0x08045328` | `display_text_set_object_string` | 20 |

The existing 12-byte animation-part record starts at object `+0x104`. The setter
writes its variants pointer at part `+8` and palette byte at `+1`; the clearer
only clears the pointer. Their incoming part index narrows to a byte. No part
count validation, flags update or tile allocation is added.

The binder reads definition byte zero to index the pointer tables rooted at
`0x08D72028`, `0x08D72038` and `0x08D72030`. The first supplies part zero's
variants, and the second additionally indexes by definition byte two for part
one. Both retain the object's OAM palette nibble. The third table supplies part
two's variants; its entry for the signed animation byte at object `+0x103`
controls whether the part is installed or its pointer cleared. The palette
lookup at `0x0806A250` uses that same signed index. A result of 254 selects the
game-state palette byte at `+0x42D`, otherwise the looked-up byte is used.
These table accesses do not establish valid mode, variant or negative-animation
domains. The source preserves the unchecked indexing and fallback.

The packed signed-eight-bit access view reproduces the observed byte load and
sign extension without changing the shared actor layout. Short register roles
retain the palette-table address and animation value during the lookup, then
reuse r0 for the variants offset. No value in a caller-clobbered register is
needed across an intervening call. Explicit 32-bit address arithmetic preserves
the observed add-operand order; pointer-first variants differed in one or two
bytes. These are compiler findings, not evidence for the original source spelling.

The palette composer builds 16 halfwords on the stack from the ROM root at
`0x080CCFFC`. First and last halfwords come from the common row. The intervening
ranges are selected independently from 32-byte rows:

| Definition byte | Destination/source byte offset | Bytes copied |
| ---: | ---: | ---: |
| 1 | 2 | 6 |
| 4 | 8 | 6 |
| 5 | 14 | 6 |
| 3 | 20 | 6 |
| 6 | 26 | 4 |

The existing `heap_copy` supplies each range, then the existing alternate
palette loader transfers all 16 halfwords beginning at slot shifted four.
The callee retains a full-word slot argument, without incoming byte narrowing;
the shared provisional prototype is corrected accordingly. The already accepted
callers continue to supply their observed palette nibble or zero. Palette-slot
bounds and visual meaning of individual color ranges remain unproven.

A view containing first/last halfwords around the 28-byte middle preserves the
observed stack-address lifetime. Its declaration after the row address closes
the remaining two-instruction scheduling difference naturally, without register
bindings in this body. Earlier plain-array, pointer-binding and compiler-profile
failures retain their complete raw comparisons under ignored actor-group reports.

Canonical sources, positive proofs and changed-source controls are
retained under `reports/audio-root/actor-group-canonical/`. The four new controls
change the fallback selector, transfer count, stored palette and cleared pointer.
The fresh current-header closure covers 232 existing functions; none is counted
again as new coverage. The ready manifest records their complete extents, source
and header snapshots, compiler/link commands and raw positive/control bytes.
Whole-ROM integration is verified separately at publication; the unconverted
renderer, sorter and other actor resource operations remain explicit.

The next four functions add 320 bytes to this resource path. The first composer
performs the same five range copies and common first/last-halfword writes into a
caller-supplied 32-byte palette. The alternate composer and transfer wrapper use
a second ROM row root at `0x080CD1FC`, also with 32-byte rows. They write the common
first halfword, then select these ranges:

| Definition byte | Destination/source byte offset | Bytes copied |
| ---: | ---: | ---: |
| 1 | 2 | 12 |
| 3 | 14 | 12 |
| 4 | 26 | 6 |

The final six-byte copy supplies the last halfword as part of its selected row.
The transfer wrapper composes into its own 32-byte stack buffer and calls the
same accepted palette loader with a full-word slot shifted four and count 16.
All three compile as ordinary C without register bindings; complete extents
include the observed literal word and two-byte zero alignment before it.

Fresh canonical proofs under `reports/audio-root/actor-palette-canonical/`
preserve four changed-source controls: change the final row selector in each
composer, the transfer count in the wrapper and the second palette-pair slot.
All reject, and the four earlier
direct consumers of the shared actor-group header are recompiled with their
controls after the declaration additions. Those rechecks add no coverage.

The incomplete static inventory records alternate-wrapper calls from
`0x080140CC`, `0x08014258`, `0x080161AC` and `0x080256A4`. The 32-byte caller at
`0x080161AC` is now reconstructed: it loads the common definition at
`0x03003970` through the ordinary wrapper into slot 1, then through the alternate
wrapper into slot 2. This base is the existing scene-player group and overlaps
game-state `+0x20`; the declaration is an access view, without establishing a new
allocation or definition-array bound. The other callers are reconstructed below
as the scene actor factory and palette-menu constructor/updater.
The inventory records no calls to either standalone composer. These are shared
palette operations connected through the same row layouts and accepted copy and
display-transfer dependencies; the standalone composers' active uses, row-index
domains, output alignment and visual effects remain uncertain.

The 248-byte scene actor factory tests one byte from the resource pointer at
`0x03001DB4`, offset four plus the selection word at `0x03004350 + 0xC`. A value
of one allocates an object with allocator argument zero and stores its pointer
at `0x030043B0`. The position argument indexes signed-halfword coordinate pairs
at `0x08056324`; conversion to an unsigned word before shifting preserves the
observed 16.16 positions without a signed-left-shift assumption. The factory
stores flags 25, direction four and OAM palette two, selects its definition,
loads the ordinary/alternate palettes into slots two/three, enables parts and
requests animation zero. Part zero selects a variants table by definition byte
zero at `0x08D70CE8`. Part one additionally selects by byte two at `0x08D70D40`.
Their palette bytes are two/three. The factory then sets the animation variant
from the signed animation byte and direction table, and part zero's order to
four. It adds no allocation-failure or index-validation behavior.

The definition base `0x03005DC4` is the accepted save state `0x03005D90 + 0x34`:
the first decoded record's `+0x20` tail. Its 40-byte stride selects each record's
two pair bytes followed by six nibble bytes. The new access view exposes those
eight selectors, then 32 bytes solely to express the observed stride; those
following bytes overlap later record/state fields and are not read by this
factory. This connects the record decoder to actor parts and palette ranges
without claiming a separate allocation or a complete appearance format. The
selection word also overlaps the accepted scene-request parameter field, and
the stored object pointer overlaps the first scene-object slot. Names and valid
index domains remain provisional.

The factory matches in ordinary C without register bindings. Naming the actual
resource base, then the scene-selection pointer, then advancing the base by
four closes a two-instruction scheduling difference. Earlier folded-offset
candidates and the four-byte mismatch retain raw evidence. The current header
and complete 248-byte extent, including all literal words, are verified under
`reports/audio-root/actor-palette-scene-canonical/`; changing flags 25 to 17
produces one differing byte. The incomplete inventory records direct callers
at `0x08024E18` and `0x08025038`, both still unconverted. No runtime visibility,
animation or save-to-scene round-trip experiment has been performed.

Three further functions add 648 bytes and close the menu constructor/update
path through the already accepted text renderer. The 396-byte constructor
allocates a primary object and stores it in slot zero of the existing scene
object array. Its signed-halfword position comes from `0x08051FB0`; it sets
direction four, palette one and flags 17. The current definition at
`0x03003970` supplies the same two variants-table selections, palette transfers
to slots one/two, animation request zero and part-zero order four as the other
actor factories. It then creates these scene objects through the accepted
four-word interface, preserving the observed creation order:

| Stored slot | ID | Subtype | Palette | Layer |
| ---: | ---: | ---: | ---: | ---: |
| 1 | 10 | 0 | 3 | 1 |
| 2 | 0 | 4 | 10 | 1 |
| 3 | 16 | 7 | 4 | 1 |
| 6 | 11 | 1 | 7 | 0 |
| 4 | 23 | 7 | 5 | 1 |
| 5 | 21 | 6 | 9 | 1 |
| 8 | 8 | 234 | 8 | 1 |
| 9 | 31 | 235 | 8 | 1 |

These are observed IDs and arguments, without assigning names to their visual
content. A retained ROM palette at `0x080DA6A0` is transferred at halfword 96
with count 16. The constructor copies the game-state text prefix at `+0x10`
to text field zero, selects font `(1, 0, 0)`, looks up token `0x184F`, creates
label ID nine into slot seven and requests state fourteen. The background
control word is read from `0x08051F60`. Explicit unsigned address subtraction
recovers the text prefix from the retained definition address; it is an access
to the same game-state storage, not a separate text allocation.

The 232-byte updater compares the old selector byte at game `+0x20` with the
full choice word at `0x03001918`. On a difference it selects the same font,
updates slot seven's text and restores the background control. It then copies
the low bytes of seven choice words into game `+0x20..+0x26`, leaving the eighth
selector untouched. Both palettes and part-zero/part-one variant pointers are
refreshed, followed by the signed animation and direction variant. The initial
comparison does not narrow the choice word, even though the later store does;
no choice, object-slot, string-termination or table bounds are added.

Named current-selector and selected-variant values preserve the observed load
and pointer setup order. Stores through the game-state fields preserve the
retained base and byte-pointer lifetimes; an earlier compact pointer form was
212 bytes and differed by 178, and a later 232-byte form still differed by six.
The final source matches in ordinary C without register bindings. The
constructor includes its literal words and zero alignment; the updater includes
its 32-byte literal pool and two-byte zero alignment.

The 20-byte string wrapper stores its string argument on the stack and passes
that pointer's address to the accepted 304-byte `display_text_update`. Its
18-byte instruction body has two zero alignment bytes before the next entry.
This closes the observed single-string to string-pointer handoff into text
sizing, drawing and tile transfers; those previously accepted bytes are not
counted again. The provider's declaration is retained without a new provisional
library alias.

Fresh canonical proofs under `reports/audio-root/palette-menu-canonical/`
include controls for flags 17 to 25, the final selector's source word and an
advanced string pointer. All three reject actual source changes. The incomplete
inventory records constructor callers `0x08015CB8`/`0x08015DE8`, still
unconverted. The updater caller `0x08014340` is reconstructed below. Static
connectivity, full-ROM byte equality and runtime menu behavior remain separate
claims.


The connected input, redraw and outer button handlers add 580 bytes. The input
handler passes the scene-request word at `0x03004358` to the accepted local
vertical helper with bounds 0 through 7 and wrapping enabled. It repeats while
the row is disabled in the byte table at `0x08051FA0`, then uses the horizontal
helper on that row's word at `0x03001918`, bounded by the count byte at
`0x08051F70` minus one. Changed rows or choices play cue zero; changing choice
zero redraws row five before refreshing actor palettes. The unchecked loop and
count subtraction are preserved; no fallback for an all-disabled table or zero
count is added. This is source behavior, without a runtime validation claim.

The redraw reads a four-byte coordinate row at `0x08051F80`, with byte x/y
fields, selects font three and a color from the enabled byte, looks up token
row plus 24, then invokes the accepted text-block drawer at tile row times 40
plus one. Row five clears its background rectangle and conditionally uses token
32. Redrawing row zero can also refresh row five with token 32 or 29 according
to choice zero when the saved byte at game-state `+0x20` differs. Both literal
pools are compiled in their original positions, including the pool between the
conditional text selection branches. Its complete 228-byte extent ends at the
next entry `0x080144CC`; an initial trial's 232-byte metadata was an arithmetic
error and supplied no accepted coverage.

The outer handler reads the local player's pressed halfword at `0x03004228`.
Button masks one/two write transition words eight and thirty at request `+0x10`
and `+0x14`, select parameter nine/zero and play cue twelve. Direction bits
`0xF0` call the input handler; a changed row redraws the old and new rows,
updates object slot two's ID, sets variant state 58, then selects resource index
five for row seven or four otherwise and invokes the accepted item refresher.
The request view is shared through `scene_request.h`; its first four words
retain the previous layout, and the two following words are already observed
in the display scene-request view. These declarations describe overlapping
state at `0x03004350`, not separate allocations or an established global size.

All three match in ordinary C without register bindings. Reusing one previous
selection word across the input phases closes the input handler's register
lifetimes; expressing the directional mask as a word initialized to `0xF0`
and then ANDed closes the outer handler's final two operand-register bytes.
The redraw's explicit enabled-byte load followed by its color decision closes
its seven-byte scheduling difference. Their complete extents include all
literal pools and zero alignment. Fresh canonical proofs under
`reports/audio-root/palette-menu-control-canonical/` preserve controls changing
a captured choice value, text token and transition parameter; all reject.
Affected earlier scene/menu consumers are recompiled with their existing
controls and add no new coverage.
