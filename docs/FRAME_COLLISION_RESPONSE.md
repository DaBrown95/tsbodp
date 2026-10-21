# Default collision response

Two ordinary C functions cover a connected 776-byte response path. The copied
collision dispatcher calls the default C8 callback, which gates on point
distance and calls the directional resolver. Names and access views remain
provisional. Byte equality, static calling evidence and bounded model execution
are separate results; this does not establish complete game behaviour.

| Function | ROM offset | Complete C extent |
| --- | --- | --- |
| `frame_resolve_actor_contact` | `0x10DAC` | 720 bytes |
| `frame_scene_player_collision` | `0x1123C` | 56 bytes |

The resolver ends at `0x1107C`. Its complete source symbol and allocated text
include the 32-byte eight-way table and four-byte table-base literal. The next
304-byte unrooted collider-overlap predicate is separately source-owned,
including its two-byte alignment tail; the accepted callbacks at `0x111AC` and
`0x111F8` remain separate. Its proof does not extend the bounded runtime/model
claims for this response path. An early private 1,168-byte span hypothesis was
rejected and preserved before source acceptance. Both new source symbols own
their full declared extents; there is no additional source-tail or low-level
glue credit in this path.

The callback receives two `CollisionObject` pointers in receiver/other order.
It reads the receiver radius byte at `+0xAE`, compares the accepted distance
calculation on both next positions, and, within that distance, clears the
other object's velocity, restores its next position and calls the resolver.
The two observed literal installations are in the scene-player constructor and
the still-private activity-zero constructor. This aligned literal scan and the
mapped direct-call evidence do not form a complete dynamic caller inventory.

The existing copied ARM dispatcher is 640 bytes of already accepted C, located
at ROM `0xB0E8` and executed at `0x03002A20`. Its two indirect transfers pass the
two concrete object pointers in both orders through C8/CC callback slots. No
new C or glue credit is assigned to that dispatcher. The exact existing
`frame_scene_player.h` correction changes the default symbol declaration and
C8 field to its established `CollisionObject*` pair contract. All 43 current
literal importers retain their original source, metadata, controls and compiler
profiles. The broader one-argument `FrameActorObject.on_interact` view at CC
remains separate and unchanged.

The resolver uses signed integer positions derived from next-position fixed
coordinates, signed response bounds at `+0xBC..+0xBF`, and the signed one-bit
horizontal mirror field at D3 bit four. Those response bounds differ from the
dispatcher's registered bounds at B0/B6. Two direction-specific edge samples
test inclusive containment. Odd directions restore individual position axes;
even directions apply positive or negative speed divided by eight through the
accepted point-add provider. If neither sample is contained but the rectangles
overlap, it restores the other position, clears velocity and sets contact bit
one at `+0xAC`.

The fixed compiler establishes `FrameObject` 312/align4 and `FramePoint`
8/align4. Isolated partial views expose direction at 18 and word speed at 20
(24/align4), contact halfword at 172 (176/align4), and radius byte at 174
(176/align4). The rounded sizes include uninterpreted trailing storage and do
not establish allocation capacity. Member-width assertions are independent of
size/alignment/offset: a genuine wrong speed-halfword diagnostic initially
passed those three coarse checks, so that verification gap and its raw evidence
were retained before direct width/sign assertions were added. The signed mirror
probe returns target words zero or minus one; an unsigned declaration is
rejected in the actual source and separately produces zero/one in the native
field-value diagnostic.

The ordinary-C equivalence domain requires the sampled *other* object's
direction to be 0..7, initialized aligned accessed fields and representable
signed arithmetic. The native above-seven branch leaves sample coordinates
unwritten. No default initializers, invented incoming formals or direction
filter have been added. The dispatcher supplies no universal direction gate.
An extended-direction receiver alone does not violate this input condition,
because the other object is sampled; multiple extended-mode players remain a
possible high-direction producer, without proof of an executed invalid pair.
Global reachability of that native path is unresolved and is outside the
defined-C fixture claim. Negative right shifts use the pinned target compiler's
arithmetic-shift behaviour.

All 48 current normal pairs and three strict diagnostic pairs preserve genuine
changed-source controls. The 46 accepted context functions include all 43
changed-header importers plus actual distance, point-add and copied-dispatcher
providers. An omitted point-add declaration still produces the original 720
bytes under the legacy profile and is rejected by the strict declaration
diagnostic; byte identity alone therefore does not establish that interface.
The 824 initialized source/original/compiled cases execute all four actual
response/distance/point-add bodies with no opaque hooks, and 147 cases diverge
under their genuine source controls. Five input/interpreter failure guards are
retained. The source model abstracts helper stack addresses while checking the
ordered object writes, nested calls and complete object-memory result. It does
not execute the copied ARM dispatcher, scheduler or resource engine and is not
a gameplay test.

The [activity-zero controller](SCENE_CONTACT_ACTIVITY_ZERO.md#movement-worker)
at `0x24720` now has its own complete 472-byte C match and genuine source
controls. That compiler proof does not extend the finite collision qualification
above or establish complete activity gameplay.

## Nearby unrooted interaction bodies

Two adjacent C bodies cover another 132 bytes:
`frame_propagate_layer_three_unrooted_114d8` at `0x114D8` (72) and
`frame_obstacle_turn_unrooted_11520` at `0x11520` (60). Their names and incoming
interfaces remain provisional; no caller or callback installation is established by
this ownership work.

The first reads both object pointers and sets both display-layer fields to three
when either field is already three and the first object's signed position Y is less
than the second's. It preserves the other display bits. The second uses incoming R1
and leaves R0 unread; its first `void*` parameter records that unused argument slot
without identifying its content. Unless the actor's variant is thirteen, it replaces
the direction using the existing obstacle-direction table at twice the old
direction, calls the accepted variant setter with thirteen, stores timer twenty and
sets pending bits `0x12`. There is no additional direction guard.

Both complete extents match under the normal and strict declaration checks, and
genuine changed-source controls are rejected. The second extent includes its
four-byte table-address literal; neither adds glue credit. Separate checks
retain the actual variant setter in its original source context and reject wrong
contracts and field layouts. Valid initialized object backing, a valid reached
table index and the existing partial-view compatibility assumptions remain
preconditions. Byte equality does not establish incoming callers, table capacity
or gameplay reachability. The separately source-owned overlap predicate at
`0x1107C` remains unrooted and outside this pair.

## Unrooted collider-overlap predicate

The [overlap predicate](../src/frame/frame_bounds_overlap_unrooted_1107c.c) at
`0x0801107C` owns 304 C extent bytes: 302 instruction bytes and two terminal
alignment bytes. It compares the second object's aggregate bounds with each
active collider of the first and returns one when any pair overlaps, otherwise
zero. Edge contact counts as overlap. The incoming two-pointer view and name
remain provisional; no caller or callback installation is established.

Both inputs use the existing `FrameAnimationObject` access view. Animation
refresh, tick and part-collider writers already own its count byte at `0xAF` and
two packed six-byte records at `0xB0`. This predicate interprets physical record
bytes zero through three as signed left, right, top and bottom offsets. Existing
member names `x`, `y`, `width` and `height` are provisional slot names here; the
record does not compute right as `x + width` or bottom as `y + height`. Byte
four is the signed nonzero activity kind. The second object's aggregate offsets
occupy `0xBC..0xBF`. Signed fixed-point upper halves and the signed horizontal
mirror bit reproduce the native geometry.

The chosen C domain requires live compatible initialized object/record backing
and a collider count no greater than two. Reached serialized counts and the
complete incoming object population are not proved to satisfy that domain, and
no count clamp is added. Adding or subtracting a signed byte from a signed upper
half stays within the target integer range. The function makes no calls or
object writes; that static effect comparison is not runtime or gameplay
observation.

Normal and strict builds match every extent byte, and genuine edge-comparison
controls reject by one byte. Separate actual refresh and tick source contexts
retain their canonical declarations and 25 layout/sign facts; wrong contracts,
offsets, record stride and kind sign are rejected. Their unchanged
full-body/control proofs are reused. Deriving the current record address from
the actual index lets the pinned optimizer create the native cursor after the
initial count guard and advance it before the byte offset and index. The earlier
source attempts remain useful failures; no register binding or header change was
needed. This independently bounded function replaces a 302-byte estimated
backlog row. Its two alignment bytes are newly mapped; it adds no newly
discovered instruction extent or glue credit.
