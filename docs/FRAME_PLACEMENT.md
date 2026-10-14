# Placement session

This path connects actor selector 22 to a need-effect preview, grid registration,
route validation, display choice and commit/cancel handoff. Ten complete
source extents are contiguous from ROM offset `0x2F4EC` through `0x2FAD0`; the
connected 92-byte view provider at `0xE9E8` brings this batch to eleven functions
and 1,600 bytes.
Names and role views are inferred from their callers and accesses. Exact
compiler/linker equality establishes those bytes; it does not establish complete
placement behavior for every game state or complete source coverage.

| Function | ROM offset | Complete bytes |
| --- | ---: | ---: |
| `frame_placement_begin` | `0x2F4EC` | 348 |
| `frame_placement_cancel` | `0x2F648` | 104 |
| `frame_placement_rotate` | `0x2F6B0` | 116 |
| `frame_placement_move` | `0x2F724` | 220 |
| `frame_placement_confirm` | `0x2F800` | 152 |
| `frame_placement_reset_parameter` | `0x2F898` | 100 |
| `frame_placement_validate` | `0x2F8FC` | 192 |
| `frame_placement_update_graphic` | `0x2F9BC` | 164 |
| `frame_placement_set_valid_palette` | `0x2FA60` | 48 |
| `frame_placement_create_preview` | `0x2FA90` | 64 |
| `transition_configure_view` | `0xE9E8` | 92 |

The placement run contributes 1,508 bytes; its view provider contributes 92.
The total 1,600 bytes includes all literal pools and alignment. Rotation,
parameter reset and preview creation have two trailing zero alignment bytes each;
the source's section-alignment directive preserves those original boundaries.
The following `0x2FAD0` entry is the separately reconstructed primary scene actor
factory. No interior label or incomplete mapped extent is counted as a function.

## Session and object roles

The session root is `0x03005870`. Observed fields are a grid pointer at `+0x00`,
effect/actor/preview pointers at `+0x04/+0x08/+0x0C`, a two-word original position
at `+0x10`, selected and original four-byte cells at `+0x18/+0x1C`, and original
direction at `+0x20`. These accesses establish 33 bytes; the aligned 32-bit C
view occupies 36 bytes. They do not establish the complete allocation or that
all consumers use this role. Cancel clears four pointer words and only the two
low coordinate bytes of each cell. Saved position/direction and cell upper bytes
persist.

Actor mode `+0x68` agrees with the existing selector-22 work view. The existing
need-effect object view supplies direction `+0x12`, position `+0x18/+0x1C`, kind
byte `+0x4C`, state pointer `+0x64`, linked byte `+0x83`, and OAM flip bit. These
access views do not replace the generic callback types or claim the complete
layout of every actor or effect.

Begin saves the effect state, creates and hides its preview, projects the actor's
cell, selects an initial cell, validates it and installs a 30-by-30 view. Mode 1
uses pattern dimensions and actor facing to offset the initial candidate; the
other path projects the existing preview position. Create-preview copies
position/direction from a newly spawned effect, enables it and clears its linked
byte. Cancel restores the actor view and removes the preview; in mode 1 it also
removes the effect, while the other path re-enables it.

Rotate preserves direction for subtype 141; the other path indexes the original
rotation table. Move maps its word direction through the existing direction
table, wraps the two coordinate bytes and checks signed byte-distance magnitudes
against 20 before projection and validation. The local packed record assigns
only its two coordinate fields before a complete word transfer. Its upper 16
bits are unwritten, matching the original stack traffic; no zero/default or
valid upper-bit invariant is inferred. Signed fixed-point shifts and packed
bitfield accesses use the pinned compiler/hardware model, without claiming
portable behavior for arbitrary ISO C inputs.

Confirm commits only when validation returns 1. It restores the actor view,
unregisters the old effect for mode 0, transfers the preview position/direction,
configures and updates the effect, enables effect and preview flags, clears the
preview pointer and disables primary-object flags `0x01000000`. Parameter reset
uses the original kind/optional tests: selected kinds receive zero, and kinds
106–108 receive 512 when the optional byte is not 1.

## Validation and the grid return ABI

Validation temporarily registers the preview with mode 1. After successful
registration it scans at most twelve four-byte records at state `+0x74`; both
low coordinate bytes zero terminate the scan. Every nonzero search result is
accepted. It unregisters after the scan and sets palette slot 6 for success,
slot 1 for failure. The upper two record bytes are copied without an inferred
meaning. Registration failure does not enter this scan/unregister path.

The original validation call compares the complete returned word. The existing
720-byte grid provider has explicit status returns 0, 1 and 2, including 2 for
same-cell success. Its canonical return model is therefore an unsigned word.
The existing route caller consumes the low byte and retains its observed
explicit narrowing. This changes no original provider bytes or cell/state
layout. The provider, route caller, selector-22 aliases and every accepted
importer of the changed declarations require fresh positive and actual
changed-source controls together.

The matched failure-first loop places the real failed-search increment/copy
before the successful-search break. This preserves the original algorithm and
memory accesses while allowing the pinned compiler to choose the intended loop
exit. In the compiler's `expand_end_loop`, a bounded 30-instruction scan had
otherwise selected the successful-search break and moved the call into the loop
test, preventing initial-test duplication. A named record byte offset computed
before the record-root pointer then preserves the original address order. Both
`index * sizeof(record)` and the corresponding scaled-offset form match. There
are no register constraints, synthetic reads, discarded initializers or compiler
changes in these eleven functions.

## Display resources and limits

Graphic selection indexes the original resource pointer table by
`width + 5 * height`. Directions 1/7 and 3/5 select resource offsets 16 and 48;
the retained direction controls horizontal OAM flip. The unsigned address guard
compares the resource-table root plus `kind * 20` against zero. It is the
observed 32-bit address calculation, not an invented null check of the selected
resource. Kind is loaded as a byte. The table capacity, geometry domain and
original declaration of this guard remain uncertain.

Rotation, movement, command and resource tables remain original data. The
existing two-word view configuration at `0x08053504` is reused as a position/size
access view instead of introducing a conflicting global name. The point-to-cell converter at `0x48AF8` remains an original, unconverted
provider at this boundary. No runtime or
complete-game inventory claim follows from these static interpretations.

The batch retains eleven complete positive/control pairs, native
object/linked-section evidence, current header snapshots and full-ROM matching
integration, alongside fresh proofs and actual controls for all 31 existing
importers (6,184 bytes). The changed controls alter real palette/radius/scan-cap/flag/kind/
view-size/spawn parameters; unchanged successful builds are not controls.

## View configuration provider

The 92-byte provider has the existing object/point-by-value/byte-index ABI. It
explicitly narrows the index at entry, stores the tracked object into the
48-byte motion record rooted at `0x030017D8`, and stores the two configuration
words into an indexed eight-byte record rooted at `0x03001898`. It then copies
object position to both current motion position and motion target. Chained
field assignments preserve the observed repeated stores without new memory
traffic or register constraints.

The configuration root lies four motion strides after the motion root. That
adjacency and the observed eight-byte indexing do not prove a four-element
capacity or the complete RAM allocation. The new role header retains a bounded
two-word access view, while the previously inferred view-context layout is not
used to address this provider. Its two literal pools and the independent next
entry at `0xEA44` establish the complete `0xE9E8..0xEA44` extent. Its actual
control changes the stored second configuration word by one and must reject.
