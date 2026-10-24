# Transient-effect emission

Five connected replacements add 1,792 matching C bytes to the 72-byte transient
effect lifecycle. They connect its published factory and destructor to the
separate 84-byte render-effect family. Together those seven bodies cover 1,980
bytes; the shared pool and random helpers have their own coverage. Complete
extent matching includes literal pools and alignment. Names and record views
follow static calls and accesses, and do not establish runtime or gameplay
behavior.

| Entry | Function | Extent bytes |
| --- | --- | ---: |
| `0x080307FC` | `frame_step_transient_effect` | 204 |
| `0x080308C8` | `frame_emit_transient_render_effect` | 1,372 |
| `0x0803105C` | `frame_clear_transient_effects` | 60 |
| `0x080310C4` | `frame_step_transient_effects` | 80 |
| `0x0803140C` | `frame_step_owner_transient_effects` | 76 |

The existing 72-byte factory at `0x0803054C` and destructor at `0x08031038`
use the free pool at `0x03001EDC`, active head at `0x030059E0`, count at
`0x03001EE6` and maximum at `0x03001EE8`. The emitter instead allocates an
84-byte record from `0x03001ED8`, links it through `0x030059E4`, and updates
the count and maximum at `0x03001EE2` and `0x03001EE4`. These distinct lists
explain why the neighboring collector and updater use a different flag offset
and record size. The layouts remain separate in `frame_transient_effect.h`
and `frame_render_effect.h`; the emission header imports both without changing
their fields.

The transient updater removes its node when an owner has flag 2, or when
transient flag 2 enables a halfword countdown whose decrement becomes 65535.
Otherwise flag `0x8000` suppresses cadence processing. Halfword `+0x36` advances
against the threshold at `+0x28`; a reached threshold resets that counter and
attempts the number of emissions specified by byte `+0x3C`. Each attempt
requires render count at most 62, a clear pending byte at `0x03001EE0`, a clear
transient flag `0x40`, and either owner flag `0x40000000` or transient flag
`0x200`. These gates and the original owner dereferences are retained without
adding a null-owner fallback.

The emitter chooses an integer origin from the owner's OAM coordinates,
two interpolated attachments, a selected attachment, the transient's signed
position halves, or the owner's signed next-position halves. Flags and motion
mode choose those branches. Failed attachment reads release the newly
allocated 84-byte node and decrement its count. The halfword view in
`frame_transient_emission.h` models the observed signed high-halfword loads;
it does not replace the complete coordinate type.

The emitter calls `frame_random_secondary_range` at `0x08035404`, which uses
the separate generator at `0x080355AC`, masks its value to 15 bits, scales it
by `last - first + 1` and adds the first endpoint. This 40-byte range body
differs from the published `frame_random_range` at `0x080353D8`: the latter
uses the primary generator and bypasses it for equal endpoints. The secondary
range and generator remain unconverted dependencies in this batch.

For two-attachment interpolation, the source reflects attachment X around the
owner position when the facing exceeds a limit of four or eight, selected by
owner flag `0x20000000`. It adds the owner's Y position, interpolates both
components using one random fixed-point weight, and converts the resulting
pair to integer coordinates. The halfword at transient `+0x34` supplies the
origin radius. Independent random offsets within that radius become fixed
coordinates in the render record's origin pair.

The render record receives the transient's lifetime at `+0x2A`, flags, resource,
palette byte, tile index, index array, motion mode, amplitude and phase step.
OAM layer either uses a fixed value or copies/adjusts the owner's layer, with
the observed field truncation. Animation delay is three for flag 4, otherwise
one or the signed lifetime divided by the resource sequence's frame count.
The compiler emits the signed division helper at `0x0804CD2C`; both the signed
countdown and positive halfword frame count promote to signed `int`. Nonzero
frame count and consistent owner, resource and pool state remain caller
preconditions inferred from the original body.

Six motion modes either leave velocity zero, select a mapped direction, choose
a random direction, or copy the requested direction and switch to mapped mode.
The three direction-map roots are `0x08052854`, `0x08052858` and `0x08052860`.
The middle one reuses the existing actor reverse-direction alias. Velocity
tables at `0x0804EAE0`, `0x0804EB00` and `0x0804EB80` contain consecutive X/Y
word pairs, with an eight-byte direction stride. The source preserves the
table roots and observed indexing rather than claiming table bounds for every
possible direction byte.

The updater matches ordinary C by separating the loaded flags, lifetime mask
and retained flags snapshot. In the emitter, a saved first-multiply rate and
a two-component table traversal recover the observed value lifetimes. Its
only fixed-register declaration binds the address of the render direction
byte to call-preserved R5 across the two multiply calls. The earlier allocation
R3 constraint was removed while preserving equality. The remaining binding
is a compiler constraint, not instruction assembly or runtime evidence.
Explicit zero tail alignment is kept separate from the C body.

The y-component traversal computes the byte offset before advancing the table
pointer by one word, then forms the observed 32-bit address with the offset
first. This is source-level address arithmetic on the pinned target; arbitrary
host pointer widths, direction values and overflowing coordinate domains are
not claimed to have equivalent behavior. Failed independent-scalar, coordinate
pair, component-order and constraint-removal attempts retain complete raw
comparisons in ignored local reports.

Fresh canonical source and current-header proofs match all 204 and 1,372 bytes.
Their real controls change the render-count gate from 62 to 61 and the
four-direction reflection limit from four to three; each is rejected with one
differing byte. The lifecycle helpers have their own changed-source controls
and header proofs. `transient-update-batch-manifest.json` and
`transient-lifecycle-ready.json` index the private receipts, including sources,
header closures, commands and expected/candidate bytes. Whole-ROM integration
and runtime behavior remain separate claims.

## Definition tile cleanup

Three further connected bodies cover 248 bytes, including their pools and
alignment: `frame_release_transient_definition_tiles` at `0x08030FB4` (132),
`frame_release_scene_transient_tiles` at `0x08026C14` (52), and
`frame_clear_scene_effects` at `0x08029970` (64). These ordinary C replacements
use no register constraints. They connect the separate transient/render lists
to the existing tile-release helper rather than claiming new effect gameplay.

The definition table has a 40-byte entry stride and eight entries per group.
The resource pointer at `+0x00` leads to the existing sequence pointer at resource
`+0x04`. The release loop reads the sequence's halfword frame count at `+0x06`
and halfword offsets beginning at `+0x0C`. It resolves each frame relative to
that offset-table base and adds the product of the width and height bytes at
frame `+0x02` and `+0x03` into a halfword accumulator. Both accumulation and
the byte iterator retain the original narrowing; no frame-count bound or
additional guard is inferred. The definition's halfword tile index at `+0x24`
and accumulated area are passed to `display_release_tile_bytes_immediately`
at `0x08047904` with flag zero. That existing helper shifts its size argument
right by six in this mode; the release loop alone does not establish the
resource's pixel encoding or its runtime allocation preconditions.

The 52-byte scene wrapper releases group-zero entries three, six, and seven,
plus entry two when the unsigned scene word at `0x03004334` is at most fourteen.
The 64-byte wrapper first clears the primary object list and both distinct
effect families. It then releases entries one and zero only when the shared
scene view at `0x030043F4` has scene byte `+0x12` equal to zero and flag `0x20`
in byte `+0x15`. The existing countdown-state view supplies those same offsets;
using it does not establish the surrounding scene storage or explain the flag.

Canonical public-source proofs and changed-source controls are indexed by
`definition-release-ready.json` in ignored local reports. Changing the area
calculation rejects 53 bytes; changing the scene threshold and flag rejects
one byte each. The ten existing direct transient/emission-header consumers
also retain fresh positive and negative-control proofs. Names and cleanup
roles follow these static calls and field accesses; runtime behavior remains
unverified by this batch.

## Definition producers and tile replacement

Three connected ordinary C bodies add 412 matching bytes, including literal
pools and alignment. They supply the definition table consumed by the published
transient factory and emitter, and connect its tile contents to the release path
above. The selected sources use no fixed-register declarations.

| Entry | Function | Extent bytes |
| --- | --- | ---: |
| `0x080303D8` | `frame_initialize_transient_definition` | 184 |
| `0x08030490` | `frame_reload_transient_definition` | 188 |
| `0x08047944` | `display_recopy_tile_bytes` | 40 |

Both producers use the resource's sequence pointer at `+0x04`, halfword frame
count at sequence `+0x06`, and halfword offset table at `+0x0C`. Each selected
frame contributes the product of its width and height bytes to a halfword
accumulator. The initializer stores each preceding accumulated value shifted
right by six; the reload stores the preceding accumulated value directly.
Those indexed halfword stores establish the definition's offset view as sixteen
halfwords at `+0x04`, replacing the earlier 32-byte view without changing its
storage. Sixteen describes the space before the index at `+0x24`; neither body
checks that the resource count fits that space. The byte iterator, halfword
accumulation and unchecked source count retain the original narrowing and caller
preconditions. No count guard or resource-format limit is inferred.

The observed table root is `0x030058A0`, with 40-byte slots and eight slots per
320-byte group. The initializer calls the existing byte allocator at
`0x080477B8` with flag zero. It stores the low byte of the returned allocation
at `+0x26`, narrows the source frame count into `+0x27`, installs the resource
pointer, then copies the byte at `+0x26` into the halfword index at `+0x24`.
The reload writes the same resource and frame-count fields, but stores the low
byte of accumulated area at `+0x26` and retains the existing index. These two
different writes justify splitting the old two-byte tail into a neutral
`unknown26` byte and a `frame_count` byte; they do not establish one broader role
for the neutral byte.

The reload calls `display_recopy_tile_bytes` with the resource, complete area,
flag zero and existing index. That helper narrows its flag to a byte and its
index to a halfword. A nonnull resource causes either flag branch to call the
same existing tile-copy routine at `0x0804766C`; the area argument is unused in
this body. It returns the narrowed index without allocating or releasing tiles.
The source preserves both branches. These accesses establish the local transfer
contract, not the pixel encoding or valid runtime allocation domains.

The source resolves each frame from its serialized offset and forms the
definition address from the observed slot and group strides. A named table
address after the allocation preserves the initializer's observed lifetime.
Earlier byte-array casts, pointer-first address expressions and alternative
scopes remain in ignored reports with their raw mismatches. The final matches
contain semantic C and explicit zero tail alignment, with no instruction-body
transcription or output modification.

The canonical initializer control changes the shift from six to seven and
rejects one byte; the reload control adds one to each frame height and rejects
89 bytes; the replacement control changes the returned index by one and rejects
one byte. `transient-definition-ready.json` indexes the three fresh public-source
proofs, retained source/header inputs, compiler commands and raw expected and
candidate bytes. A separate fresh closure proof verifies all thirteen existing
transient/emission consumers, totaling 2,644 bytes, with every real control
rejected. That total includes the three cleanup functions once and includes the
1,372-byte emitter. These are source and static-call findings; full-ROM
integration and runtime behavior remain separate claims.

## Unrooted definition-index reset

[`frame_reset_effect_lists_unrooted_30f70`](../src/frame/frame_reset_effect_lists_unrooted.c)
at `0x08030F70` adds 68 matching C bytes: 60 instruction bytes and eight literal
bytes, with no alignment bytes. This source addition changes no other C
implementation.

The function reads and writes the eight index halfwords in group zero of
`g_frame_transient_definitions`, setting each to `0xFFFF`. The canonical
[`FrameTransientDefinition`](../include/frame_transient_effect.h) has a
40-byte stride and its index at byte 36, so these accesses are
`0x030058C4 + 40 * slot` for slots zero through seven. It then calls
`frame_clear_transient_effects` at `0x0803105C`, followed by
`frame_clear_render_effects` at `0x08031098`.

The source separates the real R0 address-arithmetic phase from the halfword
value loaded, ORed with the R4 halfword mask, and stored. Their lifetimes do
not overlap; the constrained phases finish before the cleanup calls. The
first-field address in R5 is also consumed by the loop. No fabricated
consumer, copied instruction body or output modification is used.

Normal and strict compilation both match all 68 bytes with zero differences.
Changing the loop's remaining count from seven to six removes one record
update and rejects with one differing byte in each profile. Actual-definition
interface and target-layout checks also pass. Incoming callers remain unknown:
this entry remains unrooted, and the match establishes no runtime execution,
complete table backing, global writer closure or cleanup validity for arbitrary
list state.
