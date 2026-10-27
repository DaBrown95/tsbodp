# Grid cell properties and registration lifetime

Eight connected functions add 356 matching C bytes. Together with the two
previously accepted 24-byte property getters, they reconstruct the contiguous
404-byte cell API block at `0x3B8C0..0x3BA54`. The linked extents include all
original alignment. The larger [target selector](../src/frame/frame_find_target_cell.c)
at `0x3B75C` now matches all 356 bytes, retaining its documented original
unset-value failure paths. Neither this block nor whole-ROM equality establishes runtime behavior
or a complete code inventory.

| ROM offset | C function | Verified bytes |
| --- | --- | ---: |
| `0x3B8C0` | `frame_destroy_map_registration` | 44 |
| `0x3B904` | `frame_grid_add_occupancy` | 36 |
| `0x3B928` | `frame_grid_remove_occupancy` | 36 |
| `0x3B94C` | `frame_grid_clear_occupancy` | 24 |
| `0x3B97C` | `frame_grid_add_terrain` | 44 |
| `0x3B9A8` | `frame_grid_remove_terrain` | 40 |
| `0x3B9D0` | `frame_grid_clear_terrain` | 28 |
| `0x3B9EC` | `frame_probe_need_effect_position` | 104 |

## Cell fields and callers

The existing cell-pointer helper at `0x3BB80` returns a byte addressed by the
low two bytes of a packed cell. The getters, this writer family and the target
selector consistently split that byte into low two-bit `terrain` and upper
six-bit `occupied` fields. Those names remain provisional game interpretations;
the fields and masks themselves are observed. Each writer calls the same
helper and leaves storage alone when it returns null.

The occupancy operations OR a full-word mask into the upper field, clear mask
bits from that field, or assign it zero. They preserve the two low bits.
Terrain operations apply the corresponding OR, AND-NOT and zero assignment to
the low field while preserving occupancy. Ordinary packed unsigned bitfields
reproduce the original shifts, masks and stores without register constraints.
No additional bounds, mask validation or failed-lookup result is introduced.

The add/remove occupancy providers were previously called
`frame_register_bounds` and `frame_unregister_bounds`. Their bodies operate on
cell bits directly; geometric projection occurs in their callers. The canonical
names therefore identify the proved operation. Four existing callers use these
providers: object stepping (256 bytes), bounds refresh (92), need-effect
unregistration (336) and need-effect registration (964). Their observed masks
include 1, 2, 4, 8, 13, 16 and 61. The 1,648 bytes in those callers gain no new
coverage from the alias correction.

The unconverted point-to-cell provider at `0x48AF8` writes only the two low
coordinate bytes on success and leaves its output untouched on failure.
Bounds refresh, direction availability, need-effect configuration, route search
and attachment-neighbor search retain unchecked failed-projection paths that
can read unset local coordinates. Their sources now mark those paths with
`BUG` comments. Bounds refresh also transfers the unwritten upper half of its
local word when the cell changes. These are native write and local control-flow
findings; failure reachability during normal play remains unproved.

The retained static inventory records those direct callers and two cleanup
callers. It records no direct inbound call for the clear-occupancy helper,
terrain writer trio or temporary-position probe; an aligned whole-ROM search
also found no literal entry-pointer words for them. This is an inbound-evidence
limit, not proof of dead code or complete runtime reachability. They belong to
the same physical API block and use its established cell fields and context.

## Context lifetime and temporary registration

The destructor reuses the existing 20-byte `FrameMapRegistration` layout,
whose allocation and data pointer were already reconstructed. It clears exactly
one byte at the data pointer, frees the data, clears exactly 20 context bytes,
and frees the context. The single-byte clear is retained as observed; it is not
expanded to an inferred buffer length. The original has no null guard and
constructs no meaningful return value, so the C return type is void.

The registration probe first unregisters the object's need-effect pattern. It
then snapshots the complete fixed-point position and the linked byte at
`+0x83`, writes the two integer arguments shifted by 16, and calls the accepted
registration provider with commit zero. It restores the position, sets linked
to one, calls registration with commit one, restores the saved linked byte,
and returns the first call's byte result. The second result is discarded, as
in the original. This proves the order of calls and object-field restoration;
it does not establish transactional restoration of all registration effects.
An actual two-word point snapshot naturally produces the original stack and
register lifetimes. Unsigned word shifts preserve the original two-word
representation without adding coordinate clamps.

## Proof boundaries

Each new function has a full-address positive comparison and a compiled real
changed-source control that rejects. The occupancy and terrain controls alter
an operation or zero assignment; cleanup changes the one-byte clear to two;
the probe changes forced linked one to two. Necessary standalone assembly
contains only zero alignment directives. There are no copied instruction
bodies, output edits, masks or extra allocated source sections.

The first terrain-remove trial mistakenly compared 36 bytes. The next entry's
PUSH at `0x3B9D0` establishes a 40-byte extent, including the original two-byte
zero alignment. Both the raw reference extent and the entire linked 40-byte
candidate match. The initial short-extent failure remains retained, rather than
being reported as a successful comparison.

The final public header closure was recompiled for all 604 affected accepted
functions owned by this batch, covering 89,856 previously matching C bytes.
Every full-address positive and actual changed-source control passed under the
current public headers. This includes the four renamed occupancy callers and
adds no coverage for them. The two primary-scene callbacks were delegated to
their owner for fresh proofs after the coordinated scene aliases; the ten
scene-queue functions do not import the changed frame header.

Sources, raw expected/candidate bytes, actual controls, assembly, ELF files,
header receipts and static caller evidence remain under ignored
`reports/agents/vblank-wrapper/grid-cell-producers/`. No runtime or gameplay
claim is made. The next connected targets are the difficult target selector,
its owner-candidate lifecycle and upstream cell-data initialization.

## Conditional pattern write bounds

The registration provider now has a finite bound on its two append indices
for the fixed ROM patterns. The 149 pointer words before the separate appearance
records at `0x08062D78` contain 138 non-null patterns at 50 distinct addresses
and eleven null entries. Each backed pattern has two coordinate-offset bytes
and 25 action bytes in `0..5`. The largest pattern has twelve action-four
positions; the largest total for actions one, two, three and five is nine.
This physical prefix does not establish the complete table extent or valid
kind population.

The [registration scan](../src/frame/frame_register_need_effect.c) visits each
position once. Under stable ROM contents, intact state/frame backing and normal
provider returns, its candidate indices stay within `0..11` and target indices
within `0..8`, fitting the existing twelve- and ten-record banks. Rotation changes
coordinates, not append opportunities; unavailable cells and early returns
shorten the scan. Commit one first calls the target-writing commit-zero probe,
then clears the work area and scans again. Thus it can append eighteen target
records across the two scans while each scan uses at most nine slots. A failed
probe can leave partial target writes; no rollback is established.

The native registration index comes from an object byte. Interpreting all 256
possible index words gives 188 complete fixed-ROM images, including a GamePak
mirror, whose counts also fit those banks. Beyond the 149-word prefix these
include appearance, definition and instruction bytes; they are not additional
valid patterns or newly discovered execution. Other interpretations address
mutable IWRAM or palette storage, BIOS-prefetch or open-bus data. The fixed-ROM
bound does not cover those inputs. Neighbor lookup separately indexes by a
full state-kind word, so it does not inherit this byte-sized domain.

Capacity does not guarantee a usable candidate. With a cleared work bank and
the required cells available, a static coordinate model for kind zero with
direction three and anchor `(1,1)` appends eight candidates but puts `(0,0)` first.
The [native counter](../src/frame/frame_actor_owner_cell_count.c)
then reports zero because it stops at a zero low halfword. Moving the anchor to
`(2,2)` gives eight visible records in the same model. These are conditional
stored-value examples, not naturally reached gameplay observations. Valid
projection, terrain, live ownership, later writers and the target selector's
failure-path outputs remain open. No C coverage or runtime credit is added.

## Conditional scene-zero selector inputs

A fixed serialized setup now supplies a concrete geometric input for the
unconverted selector. Scene zero's base group contains constructors for actor
subtype 28 at `(1210,507)` and three kind-79 owners. Reusing the calibrated
decoder model for exactly its primary map and registration streams gives a
49 by 25 tile map and
a 99 by 99 registration grid. The model confirms initialized reads and bounded
writes throughout both decodes. The 9,804-byte registration output fits the
9,808-byte rounded allocation for the 9,801 logical cells. This is a static
resource observation, without a new gameplay trace.

The actor projects successfully to cell `(56,69)`. The last of those three
owners has direction five and snaps to `(1150,88)`, giving anchor `(80,40)`.
Its pattern has three target cells and three candidate cells:
`(79,40)`, `(79,39)` and `(79,38)`. All six initial cells have terrain two and
zero occupancy; all three candidate coordinates are nonzero. Successful
registration followed by an intact bank would therefore give mode-four count
three, avoiding the zero-coordinate sentinel example above. Initial cell data
does not prove registration succeeded after earlier objects or that later
occupancy writes preserve it.

Kind 79's actual search descriptor and choice callback expose action 49 despite
its serialized enabled byte being zero. Actor 28's schedule permits world zero
at hour ten on each weekday, including the fixed default clock, and its default
state can request that action after a successful random check. The actor-use
path reaches the selector directly through `frame_actor_route_to_target` at
`0x8CFC`; it does not establish the separate caller at `0x3BAC0`.
The retained natural route reaches scene six, without a scene-zero arrival or
same-live owner, bank, actor-projection and random-request observations. Those
history premises remain open. The separate
[terrain observations](RUNTIME_OBSERVATIONS.md#natural-scene-six-terrain-redirection)
explain two movement deflections during a finite approach to the first portal;
they do not establish arrival or add matching C coverage.
