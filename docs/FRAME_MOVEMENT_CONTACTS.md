# Frame movement contacts

Nine matching Thumb functions reconstruct 1,200 C bytes of the frame update's
movement-contact and offset-probe path. These matches include their complete
literal pools and alignment. The names and access views are inferred from
calls and memory accesses, and do not establish runtime or gameplay behavior.

| Entry | Extent bytes | Observed role |
| --- | ---: | --- |
| `0x08002C30` | 104 | Clear contact state, query moving objects and enqueue dispatcher candidates |
| `0x0802B204` | 88 | Reset the shared filter, query bounds and update display layer/contact state |
| `0x0802AC6C` | 176 | Construct a movement rectangle and query one or two edges |
| `0x0802AD1C` | 220 | Apply the selected contact response and refresh terrain state |
| `0x08001C78` | 20 | Test whether all requested object flags are present |
| `0x0802B430` | 4 | Return the contact argument unchanged |
| `0x0802AF14` | 240 | Try an offset, restore a rejected position or mark an accepted displacement |
| `0x0802B434` | 68 | Select the offset sign using the velocity dot product |
| `0x0802B004` | 280 | Sample four rectangle edges and retain classified terrain/contact words |

The accepted [frame_step_object.c](../src/frame/frame_step_object.c) calls the
104-byte front end after velocity integration and bounds updating. Its earlier
provisional name `frame_collect_render_order` is corrected to
`frame_collect_movement_contacts`: the body clears the contact halfword at
object `+0xAC`, conditionally queries movement contacts, and queues objects for
the copied ARM collision dispatcher. It does not perform the separate renderer
finalizer's ordering operation. The caller's bytes and changed-source control
are reverified after this source and metadata rename.

The front end caches flags before its helper calls. When either velocity word
is nonzero, flags `0x10040` enable the original three-cell probe and flag
`0x200` enables the rectangle/layer query. Flags masked by 6 equal to 4 append
the object to the dispatcher scratch pointer array at `0x03002500`, using the
count at `0x030024F8`. These are the existing dispatcher globals; this path
does not infer a new allocation capacity or overflow check.

The shared filter is a two-word view at `0x03001DF0`. The rectangle refresh
writes its first word to 255, calls the bounds query, obtains signed integer
coordinates from the high halfwords of next position, updates the existing
display-layer bitfield through `frame_layer_at_position`, and applies contact
state. Object flag `0x01000000` bypasses this work. The matching edge scanner observes and fills both filter words.

The bounds query snapshots the next-position pair and direction byte at
object `+0x12` before calling the flag predicate. Flag `0x8000` chooses the
four-word offsets at `0x08059B0C`, giving x offsets -12/12 and y offsets -15/15;
otherwise the table at `0x08059B1C` gives -4/4 and -3/3. The bounds array is
ordered x0, x1, y0, y1. Flag `0x20000000` selects a mask of 3 and halves the
cached direction; otherwise the mask is 1 and the cached direction is used
directly. A fresh direction read selects either one edge or an even edge
followed by the next edge when the first contact lies outside 2 through 35.
The final forwarder ignores its object argument and returns the complete word
contact argument. The observed normal direction domain explains the four-even
edge interface; arbitrary direction-byte validity is not proven here.

The contact response is a byte at object `+0x84`. For contact words 2 through
35, response 1 restores next position and requests variant state 2; response 2
looks up the direction at `0x08059B04`, sets pending-update bit 16, negates
velocity and restores next position; response 3 restores next position and
calls the original redirection body; response 4 restores next position and
requests variant state 5. Other responses do none of these assignments. The
reverse table is distinct from the existing actor reverse table at
`0x08052858`; the aliases are kept separate. Every contact, including words
outside that range, queries terrain at next position, stores its low byte at
`+0x85`, and sets or clears object flag `0x4000` according to terrain bit 1.
The response, terrain and pending-byte views in
[frame_movement.h](../include/frame_movement.h) preserve all unspecified bytes.

The offset probe receives an object in R0 and a two-word displacement in R1/R2.
Its C interface uses the existing `FramePoint` by value. It snapshots next
position, adds the displacement, and queries contact bounds. If a registration
context exists, it converts the resulting integer coordinates to a packed cell.
A failed conversion rejects the offset. A changed low cell halfword triggers
the matching occupancy and terrain queries; object flag `0x40` with occupancy
mask `0x3D`, or flag `0x10000` with terrain bit 2 clear, rejects it. Contact
words 2 through 35 also reject it. Rejection restores both saved coordinates
and returns 1; acceptance leaves the new position, ORs contact bit 2 and
returns 0. No registration context skips the cell tests. Only the packed
cell's initialized low halfword is compared; unknown upper bytes are not
interpreted as an integer value.

The direction probe computes the dot product of velocity and the incoming
displacement. A positive product tests displacement scaled by `0x4000`; a
negative product tests its negation. A zero product returns 1 without trying
an offset. The source multiplication preserves the meaningful signed scaling
operation without a negative signed left shift. These bodies establish the
observed call convention and return polarity; original source type names and
arbitrary overflow-domain behavior remain unknown.

The 280-byte edge scanner at `0x0802B004` now has a matching ordinary-C reconstruction, including its complete pools and explicit zero tail alignment. It uses the shared four-word bounds order x0, x1, y0, y1 and recognizes even directions 0, 2, 4 and 6. Each case selects a starting corner, the opposite corner of that edge, a cardinal unit increment and the signed edge length. The sampling loop advances by eight coordinate units, retaining each nonzero terrain-classification word and stopping for contact classes 2 through 35. If the retained word lies outside that range, it queries the endpoint and keeps a nonzero result. The shared sentinel 255 initializes the filter first from the endpoint and then from the starting point. Names, coordinate units and terrain-class meanings remain inferred from these calls and accesses.

The source separates each case's initial coordinates from its moving `FramePoint`, and copies the endpoint as a complete aggregate before the by-value terrain call. These ordinary C lifetimes recover the original working-coordinate and step registers, and the endpoint's two stack words; no register variables or instruction assembly are needed. The failed member-copy and independent-scalar attempts are retained privately. The sole assembly declaration expresses zero tail alignment and does not contain the original instruction body.

The switch's original default sets only the length. It still reaches endpoint-dependent work, without initializing the corresponding point locals. The C source preserves that behavior and therefore relies on the inferred valid even-direction caller domain; arbitrary direction values and arbitrary coordinate-overflow domains are not claimed to have defined C behavior. The normal bounds-query call path selects these four edges, but byte equality does not prove all runtime caller inputs or gameplay behavior.

The fresh canonical shared-header proof matches all 280 bytes; its changed-source control changes the step from eight to nine and is rejected with one differing byte. Source, complete header-closure snapshots, commands, expected/candidate bytes and useful failed attempts remain private under movement-edge reports. The ready index is `movement-edge-batch-manifest.json`. The original terrain classifier, three-cell probe and redirection body remain explicit until their own complete C matches are accepted; the edge scanner does not claim their source coverage.

Eight sources use ordinary C without register bindings. The bounds query uses
one scoped R1 binding for its contact result, assigned after each external call;
no call-clobbered value is kept across a call. An aggregate next-position
snapshot recovers the required x/y register pair. Likewise, using a two-word
displacement argument and a local scaled pair recovers both offset probes;
the earlier independent-scalar parameter candidates remain excluded.

All nine fresh canonical extent proofs and actual changed-source controls
pass. The controls alter the cleared contact, filter sentinel, requested flag,
pending bit, predicate result, forwarded contact, accepted contact bit or zero
dot-product result; the edge control changes its step from eight to nine. Eight
reject with one differing byte and the requested-flag
control rejects with two. Commands, source/header snapshots, expected and
candidate bytes, controls and useful failed attempts remain in ignored local
movement reports; `frame-movement-ready.json` indexes the accepted batch.

The three-cell probe at `0x0802AA78` (312 bytes), terrain classifier at
`0x0802ABB0` (188), and redirection body at `0x0802ADF8` (284) remain original
explicit regions. The grid point converter
at `0x08048AF8` remains another unconverted dependency. The renderer and its
finalizer also remain unaccepted. These connected targets receive no C credit
from the nine matches; byte-identical full-ROM integration is checked
separately and does not imply their source reconstruction or runtime execution.
