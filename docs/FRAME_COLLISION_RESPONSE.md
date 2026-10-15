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
304-byte function remains original, including its two-byte alignment tail;
the already accepted callbacks at `0x111AC` and `0x111F8` are separate. An early
private 1,168-byte span hypothesis was rejected and preserved before source
acceptance. Both new source symbols own their full declared extents; there is
no additional source-tail or low-level glue credit in this path.

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

The remaining activity-zero controller at `0x24720` is still original: the
current private source has ten differing bytes in its switch tree. Its other
private matching functions remain held with that connected activity path.
