# Grid cell properties and registration lifetime

Eight connected functions add 356 matching C bytes. Together with the two
previously accepted 24-byte property getters, they reconstruct the contiguous
404-byte cell API block at `0x3B8C0..0x3BA54`. The linked extents include all
original alignment. The larger target selector at `0x3B75C` remains an
unconverted 356-byte function; its closest retained candidate differs in 26
bytes. Neither this block nor whole-ROM equality establishes runtime behavior
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
