# Secondary menu consequences

`display_menu_resolve_selected_kind` at `0x08040978` and
`display_menu_show_change` at `0x080408A8` add two matching Thumb functions and
524 C bytes. The dispatcher occupies 316 bytes and the indicator producer 208. The dispatcher extent ends at `0x08040AB4`, after its
return at `0x08040AB2`, and includes its intervening literal pools. Its accepted
source is [menu_resolve_selected_kind.c](../src/display/menu_resolve_selected_kind.c)
and its guarded role views are in
[display_menu_effects.h](../include/display_menu_effects.h).

The unconverted secondary menu at `0x0803F908` supplies the first selected
actor-entry kind and the number of selected entries after updating those
entries through the published `condition_update_actor`. That caller also
selects the success/failure background and coordinates text, cues, relation
changes and indicators. Its semantic C candidate has the correct 1,112-byte
extent but differs substantially and receives no coverage. These links are
static call/access evidence, not tested UI or gameplay behavior.

The matching dispatcher connects selected kinds to existing game-value and
condition operations:

| Kind | Observed operation |
| --- | --- |
| 143 | Add parameter 2 multiplied by twenty times quantity, plus 30 |
| 144 | On first incomplete condition (3,1,2), add 5000, mark the triple and decrement quantity; then add parameter 2 multiplied by fifty times the remaining quantity |
| 129 | Count the first 24 bits of the shared once mask; more than nine marks triple (2,3,3) |
| 118 | Mark triple (2,4,3) |
| 125 | If state byte `+E5` is 255 and capacity lookup finds no kind 125, clear the byte and mark (1,0,0) |
| 142 / 130 / 140 | Mark (0,0,1), (1,3,1) or (3,0,1), respectively |
| 119 through 123 | Add quantity to state byte `+E6`; its narrowed result above two marks (2,2,2) |

The parameter source is the existing view at `0x030039E8`. Game-value updates
use the published `frame_add_game_value` and retain its ignored integer return.
Completion, triple setting and capacity lookup also use their established
canonical APIs; this batch does not reconstruct replacement copies of them.
Quantity is a complete signed word. The code does not validate zero or negative
quantities, avoid arithmetic wrapping, or clamp the byte counter beyond the
original narrowing behavior.

The once-mask word is at `0x03003A2C`. The state access view at `0x03003950`
shares its base with the catalog/game-state views, observes bytes `+E5/+E6` and
the actor-entry pointer at `+F0`, and establishes no complete storage or entry
count. The names `staged`, `group_count`, `once_mask` and `award` describe this
bounded path and remain inferred; the numeric condition triples have no
unproven quest labels.

The indicator producer connects the same secondary menu to the published
72-byte `FrameTransientEffect` lifecycle. Kinds 6 and 7 select definition groups
5 and 6, place the effect at fixed-point (208,32), set flag 8 and rate 0x8000.
Kinds 4 and 5 select groups 7 and 8, play cues 17 and 18, obtain x/y through the
existing bounded-random API with inputs 240 and 100, and set rate zero. Other
kinds create no effect. The call inputs and resulting assignments do not prove
random endpoint semantics or the visual meaning of those groups.

The common initialized fields are phase 3, flags OR 0x2182, height 60, enabled
1, countdown 1, unknown halfword `+34` zero, direction zero and offsets (5,20).
Owner is the published menu hint-object slot at `0x030043B0 + 8`. The existing
transient record layout is reused without change. Branch-specific fields are
written before the common nonzero-pointer guard; the reconstruction adds no
allocation check or alternate failure path. The extent includes its final
pool through `0x08040977` and ends at the dispatcher entry `0x08040978`.
A semantic inline placement helper shares the first two branches without
creating an additional separately credited function.

All 316 dispatcher bytes and 208 indicator bytes match, and changing the bit-count threshold
from `total > 9` to `total > 8` rejects with one differing byte. The indicator height mutation from 60 to 59 also rejects with one differing
byte. Both sources use ordinary C with no register bindings. Separate semantic multiplier locals
preserve the parameter/quantity calculation, while a pointer captured before
the one-bit local preserves the mask-read lifetime. The first dispatcher same-size attempt with twenty differing bytes and the
later four-byte attempt remain intact. The indicator's first 204-byte attempt
with an incomplete flags inference also remains excluded and intact.
Full source snapshots, expected/candidate bytes, commands and the actual
compiled control are retained in the ignored catalog-presentation reports;
`menu-secondary-ready.json` contains the ready metadata.

The marker producer's canonical source is
[menu_show_change.c](../src/display/menu_show_change.c).

The 168-byte choice initializer now matches; see its
[acceptance and remaining domains](DISPLAY_MENU_CHOICE.md#choice-initializer).
The relation lifecycle now has its own exact connected batch described in
[DISPLAY_MENU_RELATION.md](DISPLAY_MENU_RELATION.md). The secondary menu and
its remaining gauge/resource consumers remain useful connected targets. Whole-ROM matching is independently gated by the publisher and is not
proof that these unconverted paths have been reconstructed or exercised.
