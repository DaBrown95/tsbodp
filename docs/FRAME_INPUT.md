# Internal AI scratch: frame queue and input evidence

These reconstructed names are descriptions supported by static original-image
accesses and compiler matches. They are not recovered original identifiers.
No runtime or gameplay validation is claimed here.

`frame_update` at ROM `0x8A0` is installed as the IRQ context VBlank callback by
`irq_init`. It runs only when the halfword at context offset `0x38` equals one.
The context is now the shared interrupt-module `IrqContext`: its
`transfer_ready` halfword is the handoff flag at `+0x38`. A value of one permits
transfer work; the scheduler observes the same field. The name describes its
producer/consumer role rather than a recovered original identifier. The writable queue at `0x030015B8` has an 8-bit
count at `+8` and object pointers from `+12`. Flag `2` requests allocation
release; flag `0x80` updates the ten-bit field at object `+0xD4` from the
halfword at `+0xFE`. The queue count is cleared and the deferred allocation
bitmap is flushed via ROM `0x4796C`.

`frame_release_display` at `0xF74` declines flag `0x100` objects. The low two
bits of the byte at object `+0x101` select shared allocation handling. Bit zero
selects shared slot zero; otherwise the slot comes from `+0xDA`. The group
comes from `+0x102` and addresses a 52-byte record through `0x030017C8`.
Record halfword allocation indices start at `+8`; reference counters start at
`+32`. A counter reaching zero schedules the range release through `0x47924`.
The object allocation index and byte count at `+0xFE` and `+0xFC` are cleared.
In the unshared path, bit `0x40` at `+0x101` selects four more 12-byte records
starting at `+0x108`. Object bit five at `+0xD1` controls the byte-to-tile shift
used by the range-release helper. The physical allocation interpretation is
supported by that helper's `>>5` / `>>6` conversion and bitmap dependency;
precise original type names remain uncertain.

`input_poll` at `0x1F168` and `input_clear` at `0x1F0E4` reconstruct an independent
connected input path. Input uses four-entry halfword arrays. Current state at
`0x03004220`, previous state at `0x03004270`, pressed at `0x03004228` and released
at `0x03004230` are paired with local-only arrays at `0x03004238`, `0x03004248`,
`0x03004250` and `0x03004218`. Config bytes at `0x03004110` and `0x03004111`
select participant count and local participant. When the count exceeds one,
current participant input comes from the mutable receive array at
`0x03004268`; the local-only state still reads GBA KEYINPUT at `0x04000130` and
XORs the ten active-low key bits with `0x3FF`. The single-participant path updates
both state sets from KEYINPUT. Idle-frame count at `0x03004240` increments only
when the selected participant has no key bits set. Only the first disable
halfword at `0x03004258` is read by the polling entry; the enable and disable
helpers write all four slots. Writes and bounds should not be broadened on the
basis of inferred intent.

The connected direction helpers use ROM table `0x53548` and left/right masks
`0x20` / `0x10`. Their 16-value rotation returns sentinel 16 when neither key
is held. Seven selection helpers consume held, pressed or local pressed state,
move a bounded unsigned value, and optionally wrap. These helpers are included
for the complete recovered input path, not as an isolated-function byte target.
Input callers and the producer of the receive array remain further targets.

The frame scheduler at ROM `0x618` is a matched 648-byte bridge from object
updates into render work and the VBlank queue. Its reverse traversal follows
`FrameObject.previous` at `+4` from the primary list's `last` pointer at `+4`.
The recycle helper at `0x24D84` calls the doubly linked unlink helper `0x24DD8`
and head insertion helper `0x24DC0`; this supports the direction of the inferred
links and replaces the earlier ambiguous active-list names. The scheduler calls
the copied ARM dispatcher at `0x03002A20`, constructs object work, invokes the
copied sort entry at `0x03002900`, applies updates, prepares render entries and
coordinates display completion. Numeric typed function pointers keep these
RAM calls explicit and preserve the original interworking thunks. The copied
collision dispatcher now has a verified 640-byte semantic ARM C replacement;
the [sorter](../src/frame/frame_sort_display_objects.c) now owns all 284 ARM bytes
at ROM `0xB840`, linked for copied address `0x03002900`. It orders the prefix
before the first excluded object by layer, priority flags and signed pixel Y,
using gaps 21, 7, 3 and 1. Pinned normal/strict builds and changed-gap controls pass.

`frame_install_runtime` at `0x109C` now matches its complete 108-byte C extent:
72 instruction bytes and 36 literal bytes. It allocates 40,960 zeroed bytes for
128 object slots at a 320-byte stride, then allocates 572 zeroed shared-display
bytes. The canonical `FrameObject` is a 312-byte partial C view, not a claim
that these slots allocate only 312 bytes. The shared allocation size does not
establish complete runtime record or index bounds. Neither allocation has an
original null check before the subsequent pool initialization.

The installer copies ROM `0xB840` to RAM `0x03002900`, 71 words / 284 bytes, and
ROM `0xB0E8` to RAM `0x03002A20`, 160 words / 640 bytes. Both calls use SWI `0B`
(`CpuSet`), with bit `0x04000000` selecting 32-bit copy units and the low bits
holding the word count. It then clears the shared rounding word at
`0x030017D0`. These addresses and transfer sizes retain the existing RAM map.

The changed-source control reduces the first transfer from 71 to 70 words;
it still compiles to 108 bytes and rejects by one byte. Source/header snapshots,
linked bytes and comparisons are retained under ignored
`analysis/frame-install-runtime/`. This reconstructs the installer and its
allocation/copy operations. It does not establish observed execution, complete
callback domains, or valid object-array and count populations.

`frame_initialize_effect_pools` at `0x30338` matches its complete 160-byte
extent: 112 Thumb instruction bytes and 48 literal bytes. It allocates and
initializes 64 render-effect slots at an 84-byte stride and 15 transient-effect
slots at a 72-byte stride, then allocates four 256-byte layer-pointer lists.
It clears both active heads, their halfword counts/maxima and the pending byte.
Typed free-head words at `0x03001ED8` / `0x03001EDC` share storage with the
existing pool-address views; those consumer declarations stay intact.
The source uses the existing record layouts and pool API. Reducing the layer
loop from four iterations to three retains the 160-byte extent and rejects by
one byte. The initializer supplies the existing effect consumers; allocation
success and complete later index/callback domains remain separate preconditions.

`frame_step_object` at `0x1CCC` is a matched 256-byte object update coordinator.
It branches between removal, visibility, callbacks, animation, affine updates,
velocity, bounds and render ordering. `frame_remove_object` at `0x928` is a
matched 140-byte removal path: it handles the remove callback, callback cleanup,
conditional owner release and affine teardown before the doubly linked recycle
operation. `frame_check_visibility` at `0x9B4` is a matched 300-byte projection
and 240 by 160 viewport test. Bounds are signed bytes at `+0xBC` through `+0xBF`,
and visible participants and the selected local participant set separate object
flags. Forced visibility and fixed-screen placement remain distinct branches.

Three further connected dependencies match: `frame_prepare_animation` at
`0x31E4` (100 bytes) copies the source object's next position and display layer,
with one-pixel vertical offsets selected by shared-display flags; the 104-byte
`frame_advance_position` at `0x34D8` adds sine/cosine motion using 16-bit phases,
signed rates and signed amplitudes; `frame_integrate_velocity` at `0x23C8`
(32 bytes) adds acceleration and combines velocity with current position.
The last name replaces the earlier unsupported pending-flags description.

All 25 accepted extents in this path compile and link to their complete original
bytes, including literal pools and zero alignment: 4,176 bytes (2,824 frame,
1,352 input). Function-specific changed-source controls were rejected for every
extent. Raw source snapshots, compiler output, linked objects, expected and
candidate bytes, useful failed attempts and comparison reports remain under
ignored `reports/agents/frame-input/`. Pool-free helpers declare zero alignment
explicitly; no original instructions are embedded in C.

`frame_draw_sequence` at `0x2960` matches all 720 bytes, including its literal
pools and padding. It is a substantive shared renderer dependency: a selected
frame locates packed four-byte sprite parts after six-byte collider records and
two-byte attachment records. Those part bitfields are signed nine-bit x and y,
two-bit size, two-bit shape and ten-bit tile displacement, in that order. The
OAM view carries GBA attribute bits; the local OAM copy uses word-sized bitfield
operations, while the object's stored hardware view exposes byte and halfword
fields. Affine modes transform the part center using object scale at `+0xE8`
and `+0xEC`, the rounding bias at `0x030017D0`, and signed/unsigned fixed-point
rounding. Normal modes mirror offsets by sprite dimensions. Flag two requests
vertical mirroring plus the queue's deferred layer at `+0x20C`. Only screen y
positions from -64 through 192 are appended; options masked by three trigger
the associated channel marker after the append. The marker argument is an
integer: the original channel-minus-one call is not truncated to eight bits.
These are static access and exact compiler findings, not runtime validation.

`frame_update_bounds` at `0x33A4` matches 92 bytes. For objects with flag
`0x10000000`, it derives signed integer coordinates from the high halves of
current position, requests a four-byte registration key through `0x48AF8` and
compares its low halfword with object `+0xC4`. A changed key causes unregister
and register calls at `0x3B928` / `0x3B904`, with argument 16, followed by a
four-byte key update. The two-word union captures the independently evidenced
comparison width and copied key width; the meaning of each key half remains
uncertain.

The 1,400-byte renderer at `0x23E8` is an active semantic C candidate and remains
unverified. Its multipart packed records, object hardware OAM view and nested
frame-selection behavior are being resolved against static accesses. Animation
tick and bounds, affine, render-order and display allocation dependencies are
further connected targets. Compiler equality does not establish gameplay.

The object animation path now includes three additional exact replacements:
`frame_decode_animation_commands` at `0x0800201C` (388 bytes),
`frame_refresh_animation_bounds` at `0x080021A0` (248 bytes), and
`frame_refresh_part_colliders` at `0x08002298` (304 bytes). These 940 bytes
bring this local batch to 28 functions and 5,116 matching C bytes.
Changed-source controls alter the command threshold, dirty flag and part collider
flag respectively; all fail the full extent comparison. The frame tick caller
at `0x08001DCC` also matches its full 592-byte extent. It brings this local
batch to 29 functions and 5,708 matching C bytes. A changed-source control
reverses its delay decrement and is rejected.

The command reader gives static evidence for the animation state at object
`+0xD8`: delay, reset delay, previous frame and current frame occupy four bytes;
resource, current command and command start pointers follow. Commands are two
bytes. Values through `0xF2` choose a frame and delay; `0xFD` jumps relative to
the command start, `0xFE` waits one tick and `0xFF` marks completion. Movement
commands use signed byte offsets, with mirroring read from display byte
`+0xD3`; velocity commands scale unsigned byte magnitudes and then apply the
mirror sign. `0xF6` calls `0x08040FFC`, provisionally named `audio_play_animation_cue`.
The callee checks audio enable byte `0x03005D98`, selects a four-byte cue
descriptor at `0x08D73B9C`, then resolves either a direct sample or a random
variant. It calls the copied RAM audio start and pitch wrappers at
`0x0804C878` and `0x0804C88C`, followed by coordination at `0x08041534`.
The static return value is retained as an unsigned handle; this caller ignores
it. These are static call and data findings, not runtime observations.
The random branch calls `0x0803542C` and may request animation 2 or 3 using
object byte `+0x103`, flags `0x10` and pending-update byte `+0x4F` bit 2.
The otherwise undefined command cases retain the observed repeat behavior.

A frame header contains two halfword bounds at bytes 6 and 8. They are copied
into byte bounds at object `+0xBC` through `+0xBF`, with width and height added
for the opposite endpoints. Attachment entries use two bytes each; collider
entries follow and use six bytes: x, y, width, height, kind and one unknown byte.
The object collider array begins at `+0xB0` and its count is at `+0xAF`.
The array view has two slots because the clearing loop stops after slot 1; the
copy loop trusts the sequence count, so this does not prove all data is bounded
to two entries. Part flag 2 supplies collider overrides, while flags 4 and 8
select the previous frame with wrap or clamp. The header bounds for an override
come from sequence bytes 2 through 5. Signed kind tests and unsigned variant
indices are preserved. Names and the independent `frame_animation.h` view are
provisional static interpretations; no rebuilt gameplay claim is made.

The frame tick decrements its nonzero delay only when flag `0x10` is set.
It advances a plain frame index with wrap and completion flag `0x400000`, or
advances the two-byte command cursor and invokes the command decoder. Both
branches inline the same bounds/collider refresh algorithm. The accepted
source keeps that algorithm as a semantic C inline helper. The independent
`frame_tick.h` record view groups the eight-byte core at `+0xD8` separately
from the command pointers; all offsets agree with `frame_animation.h`. Its
direct byte fields and explicit resource-field pointer preserve the observed
compiler aliasing and address reuse. Useful failed field-grouping candidates
and their complete raw comparisons remain in ignored local reports.

The affine display continuation adds ten matching C replacements, 632 bytes:
scale setup (`0x35C8`, 136), destruction (`0x3650`, 64), transition setup
(`0x3690`, 60), frame update (`0x36CC`, 72), slot acquisition (`0x3714`, 60),
slot extraction (`0x2CF64`, 12), slot insertion (`0x2CF70`, 20), allocation
(`0x2CF84`, 68), release (`0x2CFC8`, 72), and double-buffer matrix commit
(`0x2D010`, 68). This follows the already matching frame step, removal and
scheduler calls into a complete scale/slot/commit path. Together the local
frame/input batch has 39 exact replacements covering 6,340 bytes; this is a
batch subtotal, not a game inventory or a runtime validation claim.

`frame_affine.h` gives the display at object `+0xD0` the same OAM layout used
by the sequence renderer. Modes 1 and 3 already own an affine slot; acquisition
otherwise allocates one and writes it into bits 9 through 13 of the OAM X
halfword. These bits overlap the ordinary sprite flip fields. The existing
three-bit `affine_index` renderer name remains provisional; the slot accessors
prove a five-bit hardware field for this path. The 32 slot-use bytes begin at
RAM `0x03004D30`; the byte at `0x03005860` records the high-water count.
Allocation scans exactly 32 entries and returns 32 when every entry is used.
Acquisition preserves the original lack of an explicit failure check. Release
clears a slot and trims trailing unused entries. These are static observations
of the original code, not assurances that every caller safely handles exhaustion.

Scale setup stores signed X/Y values at `+0xE8` and `+0xEC`, a narrowed
16-bit angle at `+0xF8`, and reciprocal values computed by signed division
of `0x1000000` by each scale. A reciprocal that narrows to zero becomes one.
The eight-byte records at `0x03004410` contain the two reciprocals and angle.
The transition helper computes signed per-frame steps at `+0xF0` and `+0xF4`
when its duration is nonzero; the duration is narrowed to the halfword at
`+0xFA`. The frame helper decrements this halfword, accumulates both steps,
and passes the scales shifted right by eight to scale setup. The signed
halfword load of the angle establishes that the caller transfers its signed
value before the setup function narrows it. The inferred public argument type
is `int`, with that explicit narrowing retained in the source.

Matrix commit calls the original Thumb helper at `0x4C8E0` (a software
interrupt 15 wrapper) twice. It uses the parameter array and count above and
writes at byte 6 in each of the two OAM banks selected by the pointer at
`0x03004D20`, with an eight-byte destination stride. This is connected to
`frame_prepare_oam_transfer`, which disables unused entries in both banks and
sets the interrupt transfer-ready byte. The getter and frame update retain
explicit zero alignment directives; no original instruction body is embedded.
All ten final linked extents and their changed-source negative controls are
preserved under the ignored `reports/agents/frame-input/affine-final/` and
`negative-controls/` directories. Alternative field views, loop layouts and
compiler padding failures remain under the local affine report directories.

The allocation/upload continuation now includes two further exact C readers:
`frame_part_dimensions` (`0xD94`, 152 bytes) and `frame_part_pixels`
(`0xE2C`, 144 bytes). The local frame/input subtotal is 41 functions and 6,636
bytes. Both select a part's variant record, then use the object's current frame
or the preceding frame. Part flag 4 wraps a preceding frame below zero to the
sequence's last frame; flag 8 clamps that case to frame zero. The dimension
reader sign-extends the object group and variant bytes at `+0x134` and `+0x135`,
while the pixel reader zero-extends them. This difference is retained explicitly.

The 16-byte variant record exposes pixel data at `+0`, a sequence pointer at
`+4`, an optional palette pointer at `+8`, and a frame delay byte at `+12` in
other local readers. The pixel reader proves that the halfword at frame `+4`
is a pixel-data offset. Earlier `tile_bytes`/`bytes` names for this halfword in
the provisional render/animation views should therefore be read as unresolved
labels, not a demonstrated size. The frame allocation code derives upload byte
counts from width times height. The dimension and pixel matches retain raw
comparisons in `part-access-matrix/` and final `parts-final/` local reports, and
their changed-source controls reject. The direct frame-switch routine at
`0xC6C` remains unconverted: its current C candidate matches the bounds and
collider operations, but still differs in the final flag-clear instruction and
literal pool. It receives no coverage credit.

The direct frame switch and its resource/variant setters now close the manual
animation setup path with three more exact C functions: `frame_set_animation_frame`
(`0xC6C`, 296 bytes), `frame_set_animation_resource` (`0x1478`, 36), and
`frame_set_animation_variant` (`0xBE8`, 132). The local subtotal is 44 functions
and 7,100 bytes. All final extents match and all corresponding changed-source
controls reject. The previous frame-switch candidate's final mask was decoded
incorrectly during analysis: the raw little-endian pool word is `0xFFBFFFFF`,
so the operation clears the already established animation-complete flag
`0x400000`. Correcting that semantic reading resolves the entire match; compiler
padding and mask-synthesis alternatives remain preserved as failed evidence.

The frame switch refreshes only when the requested frame differs or flag
`0x80` is set. It stores the frame and copies the frame-delay byte into the
countdown, then conditionally rebuilds primary bounds and colliders and the
multipart collider contribution. It clears animation completion even when the
frame and bounds do not change. The typed `FrameTickObject` view retains the
same direct delay/frame fields used by the matched tick function. Resource
assignment compares the pointer at `+0xDC`, marks flag `0x80` on change, and
selects frame zero through this setter.

Variant selection uses signed indices for its two-dimensional variant table,
while storing the original byte arguments at object `+0x134` and `+0x135`.
It copies the selected record's frame delay and assigns that record as the
animation resource. An optional palette pointer at record `+8` transfers 16
entries to the object's OAM palette bank: frame flag `0x10` selects the alternate
immediate loader at `0x11708`, otherwise the queue producer at `0x11718` is used.
These destinations are distinguished by the connected palette code, not by an
assumption that both calls upload immediately. Final proofs are retained under
`setters-final/`; the accepted list contains only the exact replacements.

The scheduler's display-update stage is now reconstructed as exact C:
`frame_apply_update` (`0x2C98`, 1,356 bytes). This brings the local frame/input
subtotal to 45 functions and 8,456 verified bytes. The routine connects the
already matched scheduler, animation-frame readers, tile allocator, release
queue and raw/compressed upload wrappers. Its complete extent and changed-source
control are retained under `apply-final/` and `negative-controls/`; useful failed
variants remain under `apply-*` report directories. No runtime claim is added.

The update requires argument 1, visible flag `0x40000000`, neither blocking flag
`0x100` nor removal flag 2, and either dirty flag `0x80` or an unallocated tile
index. It obtains width and height from the selected frame and retains their
product as a 16-bit byte count. Sharing mode 1 maintains one resource/frame tile
entry, reusing the entry when its resource, reference count and frame match, or
when its epoch equals the current allocation epoch. Sharing mode 2 indexes 12
tile/reference-count entries by frame, acquires the current entry and releases
the preceding frame when its final reference disappears. The shared record is
52 bytes: resource at `+4`, 12 halfword indices at `+8`, 12 byte counts at `+32`,
frame at `+44`, and epoch at `+48`. These offsets corroborate the earlier release
path's shared-layout view; the epoch's broader lifecycle is still unconverted.

For private allocation, sharing bit `0x40` adds four independently sized parts.
Failed allocation writes index `0xFFFF` and zero bytes, and a failed primary
allocation suppresses upload. Newly allocated parts upload the current frame,
or the preceding frame with flag-4 wrapping or flag-8 clamping. The primary
index is also narrowed into OAM's ten-bit tile field. Dirty flag `0x80` is set
only when this update stage runs; the preceding-frame byte is updated even when
it does not. The direct `FrameApplyObject` view and its ordinary part fields
preserve the observed compiler lifetimes without imposing experimental volatile
fields from the unresolved renderer. The scheduler's pointer cast is a type
clarification and revalidates to its original bytes. A separate integer address
base with the reconstructed record's `sizeof` reproduces both shared-table
address calculations; no original instruction body or output adjustment is used.

Seven connected readers and setup routines add 548 exact C bytes, bringing this
local subtotal to 52 functions and 9,004 bytes: `frame_object_dimensions`
(`0x16F0`, 36), `frame_read_sequence_attachment` (`0x1C8C`, 64),
`frame_read_attachment` (`0x1724`, 72), `frame_attachment_position`
(`0x176C`, 100), `frame_part_attachment_position` (`0x17D0`, 156),
`frame_set_animation_commands` (`0x15BC`, 56), and
`frame_set_animation_program` (`0x15F4`, 64). Final extents and all prior frame
replacements revalidate under `attachment-final/`; changed-source controls reject.

The primary dimension reader follows resource `+4`, then the sequence's current
frame offset, and reads width and height at frame `+2/+3`. Attachment count is
sequence `+10`; each attachment occupies two signed coordinate bytes beginning
at frame `+10`. Both raw readers reject attachment indices at or above this
count. Their world-position wrappers scale the signed values by 16 bits and add
the object's world position, reflecting the x contribution for direction byte
`+0x12` above 4, or above 8 when object flag `0x20000000` is set. The multipart
wrapper selects the part resource using signed requested-animation `+0x103` and
variant `+0x135` indices. That choice differs from the group-index reader at
`+0x134` and is retained explicitly rather than merged into one assumed role.

The command setter writes both command pointers at `+0xE4/+0xE0`, advances them
by twice its byte argument, and decodes commands and refreshes bounds only for a
non-null program. The combined resource/program setter always runs those two
stages; when its resource changes, it sets both frame bytes `+0xDA/+0xDB` to
`0xFF` before decoding. These functions demonstrate that the skip argument is
measured in two-byte command units. Names and the direction flag's wider meaning
remain provisional, and these compiler matches do not establish gameplay tests.

Four frame command targets add 252 verified bytes: `frame_stop_motion`
(`0x1548`, 12), `frame_request_animation` (`0x1B5C`, 120),
`frame_set_variant_state` (`0x1BE0`, 36), and `frame_find_objects`
(`0x1A8C`, 84). The local subtotal is 56 functions and 9,256 bytes. These close
calls from the connected animation command table; final comparisons are under
`commands-final/` and their controls reject.

Stopping motion clears both acceleration and velocity components. Variant-state
assignment changes byte `+0x4E` and marks pending-update bit 2 only on change.
The animation request compares its byte argument against signed byte `+0x103`,
preserves a request for animation 1 when object id is 0 or 7 and the old request
is 2 or 3, otherwise stores the request, marks flag `0x10` and pending-update
bit 4, and clears animation completion `0x400000`. Object id 7 with subtype at
most 31 delegates to `0x2C004`, whose actor-specific behavior remains unconverted.
The direct typed command-object view is an observed layout, not a complete game
object type. Object search preserves the next pointer before writing its output
array, matches both 16-bit ids against byte arguments, and stops at the byte
capacity. The original completion mask is again retained as `0xFFBFFFFF`.

The actor-specific animation branch now closes with two more exact C extents:
`frame_request_actor_animation` (`0x2C004`, 1,128 bytes) and
`frame_set_animation_record` (`0x132C`, 88). The local subtotal is 58 functions
and 10,472 bytes. Final proofs are under `actor-final/`, including the switch
jump table generated by the compiler from semantic C cases. The initial generic
object-view attempt and its raw mismatch are retained under `actor-animation/`.
Changed-source controls reject, including a changed world-condition value.

The actor routine follows the generic request helper's id-7/subtype-at-most-31
handoff. It skips an unchanged request unless pending-update bit `0x10` marks a
direction change. It chooses one of seven 8-byte records per subtype at
`0x0805C2F8`; each record contains a directional variant-table pointer and an
animation-command pointer. The case table spans animation ids 1 through 102 and
also has a default selecting record 1. Cases 19 and 20 only accept subtypes 22,
26, 28 or 19. Animation 6 chooses record 2 for subtype 31 when byte
`0x03002EDC` equals 1 and word `0x03004334` equals 28, otherwise record 0.
The special-event/world labels are provisional interpretations of these checks,
not established gameplay meanings or a complete table inventory.

After selecting a record, the routine uses direction byte `+0x12` through the
byte mapping at `0x0804F1B0` to choose a 16-byte variant resource. The resource
setter copies its delay byte, invokes the exact frame-zero resource setter and
routes its optional 16-entry palette through the immediate or queued palette
path. The actor then starts the selected commands at offset zero, stores the
request, marks flag `0x10` and pending bit 4, and clears completion. All of these
calls now reach matching C except for the original data tables themselves,
which remain explicit unconverted ROM regions.

Five connected actor lifecycle routines add 1,116 exact C bytes:
`frame_create_actor` (`0x2BDAC`, 600), `frame_actor_tick` (`0x2C46C`, 172),
`frame_update_actor_parts` (`0x2C518`, 256), `frame_update_actor_animation`
(`0x2C77C`, 76), and `frame_actor_remove` (`0x2C7C8`, 12). The local subtotal is
63 functions and 11,588 bytes. All previous local extents revalidate under
`actor-runtime-final/`; the cleaned table indexing remains exact under
`actor-runtime-clean/`. Their changed-source controls reject. The earlier factory
size estimate was corrected by subtracting its actual adjacent boundaries:
`0x2C004 - 0x2BDAC = 600`, rather than the initial 856-byte estimate.

The factory acquires a frame object, sets id 7, subtype, actor byte `+0x4C`,
direction, position, speed and flags, and installs the known before-step and actor
callbacks. Subtypes above 31 use multipart resource definitions; the remaining
subtypes use one of the previously reconstructed seven-record animation sets.
Subtype 25 adds sharing bit `0x20`. Factory and update callers prove that the
variant setter's arguments are signed bytes; refining that setter's definition
from unsigned to signed byte preserves its entire 132-byte extent. The direction
mapping is also read as signed at these callers. The same bytes remain unsigned
indices in the single-resource actor request, so both table views are explicit.

The eight-byte multipart definitions start at `0x0805A680` and use subtype minus
32. Their first byte selects between two command tables. The compiler folds the
subtraction into the earlier literal `0x0805A580` for the group-binding call, then
recovers the actual table base for the kind read. Treating those literals as two
independent assets initially produced an extra load; the connected access pattern
resolves them to one table without an output patch or fabricated body.

Actor tick delegates state handling, updates single or multipart animation,
maintains an optional indicator pointer at `+0x90`, reflects OAM x according to
direction and clears the pending-update byte before refreshing actor state.
Multipart update uses pending mask `0x16`; selected variant states request moving
animation 6 and recompute velocity, while three other states request animation 1
and stop motion. Pending mask `0x14` rebinds directional parts and starts the
appropriate command table. The single-resource update restarts an animation on
direction changes and either recomputes or clears motion. Removal delegates its
subtype to the original bookkeeping helper. Generic state handling, actor movement,
interaction/indicator creation, actor-state initialization and spawn/removal
bookkeeping remain unconverted dependencies; their provisional names indicate
call context rather than tested gameplay behavior.

Eight connected actor meter routines add 648 exact C bytes:
`frame_initialize_actor_state` (`0x2C7D4`, 128), `frame_adjust_actor_needs`
(`0x2B824`, 244), `frame_low_need_mask` (`0x2B9E8`, 96),
`frame_empty_need_mask` (`0x2BA48`, 44), `frame_actor_need_delta`
(`0x2B97C`, 36), `frame_reset_actor_needs` (`0x2B918`, 28), and the
save/load pair (`0x2B958` / `0x2B934`, 36 each). The local subtotal is
71 functions and 12,236 bytes. Their final raw comparisons are under
`actor-needs/canonical/`; all 71 changed-source controls reject. An earlier
message overcounted this eight-function gain as 748 bytes; the exact sum is 648.

The factory's state pointer at actor `+0x60` addresses a 44-byte record containing
eight signed fixed-point values at `+0..+28`, an action countdown at `+32`, and
selection/start masks at `+36/+40`. Constructor indexing subtracts 32 from the
actor id and initializes each value with an independent random value shifted by
24 bits. It leaves the tail fields untouched. Reset copies the complete 44-byte
record from `0x08059BBC` and then clears the selected-action mask. Save/load pass
only two bytes per value through the original serialization helpers, shifting by
16; they do not serialize the tail fields. The meter/need names are inferred
from the bounded values, threshold masks and downstream action/indicator logic;
individual need labels and any on-screen meanings remain unverified.

The normal change getter selects one of two eight-word rate tables according to
object id zero; its state argument is unused. The low-value query respects the
local view flag `4` and its caller's enabled mask, and sets a bit for values below
`20 << 24`. The empty-value query sets bits only for values exactly zero. Need
adjustment uses the eight-column table at `0x08059C28` and multiplier table at
`0x0806475C`. Positive changes use the fixed multiply helper after shifting both
operands by eight; the result is shifted back by eight. Each updated value is
clamped to `0..100 << 24`. When the affected record matches the first view's
actor state and the base adjustment is positive, the routine sets `0x400 << meter`
in the 56-byte UI record selected by `local_player` at `0x03004134`. This identifies a concrete state
and display coordination edge without claiming a runtime UI test.

The pointer in the first local-view record and the local-player byte at `+0x31`
share the input configuration at `0x030040E0`; treating them as independent
globals initially produced an extra literal/load. The explicit shared input view
preserves the exact 244-byte adjustment extent. Separate assignment of the fixed
multiply result and its subsequent shift also preserves the original rounding
and compiler allocation. Raw failed alternatives remain under `actor-needs/`.

The next meter tick (`0x2B4D8`, 204) and action selector (`0x2B5A4`, 640) remain
unconverted despite semantic candidates. The tick is the multipart updater's
previously provisional `frame_update_actor_movement` dependency: it updates the
eight meters and clears remembered action bits when values recover above
`20 << 24`. Its original conditional expression calls the rate getter up to
three times for a meter; candidates retain that call count. The selector consumes
the threshold and empty masks, starts animations and variant states, creates
indicators/effects and dispatches audio cues. The actor callback's
`frame_update_actor_state` dependency at `0x2B2FC` actually applies OAM layer bits
from the world attribute grid via `0x2B478`; both candidates remain mismatched.
Those corrected interpretations supersede the older movement/state labels,
without counting the unmatched candidates toward coverage.

The meter tick at `0x2B4D8` now matches all 204 bytes as
`frame_update_actor_needs`, bringing the local subtotal to 72 functions and
12,440 bytes. Its proof is under `actor-needs/canonical/frame_update_actor_needs/`,
and the changed pause-exception index is rejected. The earlier unmatched status
above is superseded for this routine only. The caller's old provisional
`frame_update_actor_movement` symbol still denotes this address until its alias
is updated during integration.

A separate `FrameActorNeedTickState` view marks only the eight value words
volatile, leaving the ordinary storage/persistence view unchanged. This expresses
the observed tick's access pattern: it rereads a meter after each opaque rate
call rather than retaining an earlier value. The same conditional assignment can
invoke the rate getter three times. The qualifier is an explicit source access
view, not proof of recovered original declarations or asynchronous modification.
While paused it still updates meter index 6; after the loop it clears remembered
start bits for values above `20 << 24`. The local view flag and variant state 6
skip both loops. Candidate comparisons that changed induction pointers or
collapsed reads remain preserved under `actor-needs/`.

The zero-meter response at `0x2BA74` now matches 108 bytes as
`frame_handle_actor_empty_needs`. It tests the empty mask's low bits while
excluding bit `0x20`, and avoids restarting variant states 69 or 6. Its accepted
path switches state to 47, variant to 69 and animation to 72, then dispatches cue
30 and a second cue chosen from 151/152 by byte `+0x20` of the settings block at
`0x03003950`. The settings byte is named only as a cue variant; its user-facing
meaning remains uncertain. The modified mask control is rejected, with full raw
comparisons under `actor-needs/canonical/frame_handle_actor_empty_needs/`.

Five constructor dependencies now match 236 bytes: enabling four object parts
(`0x1384`, 104), setting a part's order byte (`0x156C`, 24), setting both position
copies (`0x14A4`, 12), refreshing velocity (`0x1524`, 36) and setting directional
acceleration (`0x14E8`, 60). Together with the meter response, the local subtotal
is 78 functions and 12,784 bytes. All 78 changed-source controls reject. The part
initializer enables sharing flag `0x40`, sets each part index to `0xFFFF`, copies
the object's palette and clears its variant pointer; other part fields remain
untouched. The velocity consumer calls the independently reconstructed
`frame_make_velocity` helper; the acceleration setter reads signed fixed-point
pairs from the 16-direction table at `0x0804EB80`, a pair view of that helper's
extended component table. These call and field relationships are static evidence,
not a runtime motion test. Raw constructor comparisons and failed alternatives
remain under `actor-construction/`.

Two adjacent velocity setters now match in C at `0x14B8` and
`0x14D0` (24 bytes each, including alignment). They test object byte `+0xD3`
bits four and five as signed one-bit fields, then store the selected X or Y
velocity. Unsigned negation preserves the target word wrapping. Bit five now
has a named field in the existing `FrameObject`; its broader rendering role
remains provisional. The source controls invert the predicates and reject by
one byte each; target layout and bit-mask objects verify the shared owner.
These previously isolated prologue candidates add source ownership, without
establishing runtime execution or closing incoming/writer domains.

The 640-byte selector at `0x2B5A4` now matches as
`frame_actor_choose_need_action`, bringing the local subtotal to 79 functions and
13,424 bytes. All 79 controls reject after the shared actor-header refinement.
The exact selector and changed-countdown proofs are preserved under
`action-header-revalidation/` and `negative-controls/`; hundreds of useful
unmatched selector alternatives remain under `actor-needs/`.

This closes a connected meter path: initialization/persistence and adjustment
feed the regular tick and threshold masks; the selector consumes those masks,
starts animations, changes actor variant states, creates indicators/effects and
dispatches audio cues. In actor states 16 or 22 it selects an eligible low-meter
action after the countdown expires, remembers selected/started bits, and reloads
the countdown to 450. Its 24-byte action records at `0x0805A468` contain the
variant byte, animation word (consumed as its low byte), indicator, duration and
cue pair. The original object duration field is a halfword at `+0x5E`, now named
`need_timer` in the actor view. The zero-mask path clears selection/countdown;
empty meters take priority paths for bits `0x20`, `4` and `1`. Names for individual
meters, effects and the world-dependent prohibition remain provisional.

A semantic local `bit = 1 << i` is explicitly bound to Thumb register `r1` for
the two shared eligibility tests. This preserves construction and reuse of the
bit value rather than the compiler's alternative shift-test of the mask; the
source contains the action algorithm and no original instruction bodies. The
binding is a compiler allocation constraint, not a gameplay claim or evidence
of the original source declarations. It also restores the reference's distinct
animation/counter stores and the duration load order. The actor view's field
refinement leaves all prior 78 local replacements byte-identical, including the
corrected sine/cosine aliases in the position helper.

The selector's indicator branch now has two exact replacements totalling 256
bytes: `frame_create_actor_indicator` (`0xB960`, 164) and its installed
`frame_indicator_tick` callback (`0xBA04`, 92). The local subtotal is 81 functions
and 13,680 bytes, with all 81 changed-source controls rejected. The creator
allocates object kind 25, copies the actor's position and OAM layer, selects a
16-byte animation record from `0x0804F2D8`, and records its actor pointer at
`+0x94`. It installs the shared resource before-step callback and its own tick.
A nonzero duration enables a halfword countdown; duration zero instead follows
the actor's removal flag. The callback changes state to 1 when the countdown
wraps to `0xFFFF` or the linked actor has flag 2, then marks its own flag 2 on the
following state-1 tick. The countdown is captured as a halfword before allocation,
which preserves the original input narrowing and call order. Exact and changed
proofs are under `indicator/canonical/` and `negative-controls/`. Display enabling
at `0x30220` remains an explicit original dependency.

The indicator's `0x30220` dependency now matches all 56 bytes as
`frame_acquire_palette_slot`, correcting the earlier provisional display-enable
interpretation. It sets the object's four-bit OAM palette slot, increments byte
6 of the selected eight-byte slot record at `0x03001E48`, and sets object flag
`0x08000000`. The creator requests slot 1. The slot counter is an unsigned byte
with no range or saturation check in this routine; ownership and release behavior
beyond this path remain uncertain. Its changed flag control rejects, and the
renamed creator call still matches 164 bytes. The local subtotal is 82 functions
and 13,736 bytes, with all 82 changed controls rejected.

The empty-meter bit-`0x20` effect branch now has an exact 424-byte constructor,
`frame_spawn_need_effect` at `0x2D618`. It allocates kind 5, sets direction 3,
initial position/state and flags, and creates a linked effect-state record.
Nonzero optional byte parameters override that state's fields at `+0x72`,
`+0x70` (shifted by eight) and `+0x5F`; the final enable byte is written at
`+0x62`. The object stores the state at `+0x64`, and the state records its object
at `+0x54` and subtype at `+8`. The constructor initializes the descriptor's
callback through the existing helper, sets layer 3 for requested kind 135 and
sets sharing/part flags for that kind after the update call. Requested kinds
195..200 share subtype/kind 139. These numbers are preserved without inventing
unverified gameplay labels.

The separate object/state views follow observed offsets; the callback at
`0x2E1E8` is installed in `on_remove`, `0x3698C` is the conditional step callback,
and `0x2DC0C` is the default step callback. The earlier candidate's swapped names
and a four-byte position-layout mistake were corrected from assignments and
raw differences, with those failed attempts preserved locally. The state pointer
is written through before the later conditional callback check, so this code
alone does not establish allocation failure behavior. Exact/changed proofs are
under `need-effect/canonical/` and `negative-controls/`. The local subtotal is 83
functions and 14,160 bytes, all 83 changed-source controls rejected. Effect update,
placement and commit at `0x2D7C0`/`0x2D8E4`/`0x2D9AC` remain explicit original
dependencies under active reconstruction.

The renderer-connected map lookup `frame_layer_at_position` at `0x2B478` now
matches its complete 96-byte extent, bringing this local subtotal to 84 functions
and 14,256 bytes. Its changed return-offset control rejects. It saves unsigned
input coordinates across the dimensions call at `0x3A018`, then rejects coordinates
strictly greater than the signed dimensions (converted by the unsigned comparison).
Equality is accepted by the original code; no additional map-edge check is added.
Negative signed inputs become unsigned coordinates and follow the fallback value
three. The lookup selects a 32-pixel block through the halfword pointer at
`03001DE0`, then one of sixteen eight-pixel cells through the byte pointer at
`03001DDC`. It returns the cell's high two bits plus two. The still-unconverted
caller narrows the result into the OAM layer's two bits. This motivates the name
without establishing runtime map correctness. A scoped R4 coordinate binding
preserves its lifetime across the dimensions call; it is a C allocation constraint,
not instruction glue. Exact and mutated comparisons remain under
`reports/agents/frame-input/actor-needs/layer-resume-2*`.

The connected `frame_update_actor_state` wrapper at `0x2B2FC` is now matching
C for its complete 44-byte extent. Its retained name is provisional: the only
observed operation applies the layer lookup result to the two OAM layer bits.
A `FramePoint` aggregate initialized from the signed high halfwords at object
`+0x22` and `+0x26` reproduces the original argument loads. The lookup at
`0x2B478` also remains exactly 96 bytes with the corresponding by-value point
prototype. This is static ABI and compiler evidence for a point argument, not a
claim that the original source declaration has been recovered uniquely.

The lookup still converts these signed pixels to unsigned coordinates before
its unsigned map-bound checks. Negative coordinates therefore select its
fallback value 3; equality with a map dimension is accepted by its strict `>`
checks. The returned values 2 through 5 are truncated by the wrapper's two-bit
OAM field. Neither the edge policy nor a gameplay layer interpretation has been
validated at runtime. Changing the wrapper's y coordinate to the x high
halfword rejects the match by six bytes, and the lookup's changed layer-result
control still rejects by one byte. Raw comparisons remain in ignored local
reports; no candidate renderer bytes are counted as matching C.

The renderer and the accepted sequence drawer now share two exact OAM staging
helpers: `frame_append_oam` (`0x2CEF0`, 80 bytes) and the provisionally named
`frame_note_oam` (`0x2CF40`, 36 bytes). The append helper checks the byte at
`0x03004400` as signed: values with bit 7 set reject with return value -1.
Otherwise it copies the eight-byte OAM record into the requested index of both
banks through `0x03004D20`, separated by 128 entries (1024 bytes), increments
that byte, and returns zero. Its byte-sized index is independent of the count
check; there is no separate index-range check. The source reloads the record for
the second copy, preserving the reference's observed copy order and possible
aliasing rather than assuming that the two writes share a cached value.

The companion changes only the second bank's two display-mode bits to value 2,
which disables that entry in the GBA OAM encoding. The accepted sequence drawer
calls it after appending, with the count minus one, when the sharing option
requires the alternate entry to be hidden. These names and buffer roles are
static inferences. The helper's signed index has no local bounds check, and no
runtime capacity or aliasing behavior has been established. Together with the
already matching `frame_prepare_oam_transfer`, which disables unused entries
in both banks and sets the IRQ transfer-ready field, this closes the drawing
caller's staging handoff without accepting the still-unmatched renderer.

The append declaration now records its observed integer return, replacing the
old provisional void declaration. The drawing caller still matches all 720
bytes and its changed-coordinate control rejects. Changing the append's second
bank offset from 128 to 127 rejects by two bytes; changing the hide mode from 2
to 1 rejects by one. Full linked extents, literal pools, alignment and these
compiled controls are preserved under the ignored
`reports/agents/frame-input/oam-staging/canonical/` and `negative/` directories.

The staging path's adjacent lifecycle now has seven further exact replacements,
totalling 376 bytes: initialization at `0x2CE7C` (44), allocation at `0x2CEA8`
(56), release at `0x2CEE0` (16), OAM reset at `0x2D0B8` (120), affine-slot reset
at `0x2D130` (36), enable at `0x2D154` (48), and disable at `0x2D184` (56).
Initialization points the paired OAM buffer at `0x03004520`, resets its contents
and affine ownership, and records an auxiliary pointer at `0x03004510` to
`0x03004D60`. The auxiliary pointer's later consumers and storage extent remain
uncertain; its name does not establish a sprite or matrix layout.

OAM reset copies the eight-byte record at `0x080616C4` into all 128 entries of
both banks. Its first attribute is `0x0200`, disabling the entry, and its remaining
six bytes are zero. It then uses DMA3 to copy the first bank's 256 words to
hardware OAM at `0x07000000` with control `0x84000100`, reads back the control,
and clears the staging count. The template's C view intentionally has no const
qualifier: the reference reloads the record for both writes on every iteration.
Adding const allows this compiler to hoist and cache its words, producing a
108-byte mismatch instead of the original 120-byte extent. This is compiler and
aliasing evidence for the selected view, not a claim that the physical ROM is
writable or that the original declaration is uniquely known. That failed source,
linked bytes and comparison are retained in `reset-const-view-failed/`.

Allocation scans the first bank with a byte index until its signed interpretation
becomes negative, covering entries 0 through 127. It selects the first entry
whose display mode is exactly 2, changes that entry in both banks to mode 0, and
returns its index; no free entry returns `0xFF`. Release narrows its argument to
a byte before disabling both entries with mode 2. The enable and disable helpers
accept a full integer index and have no local bounds check. The separate affine
reset clears the existing 32 ownership bytes and their high-water count. These
operations preserve the reference's limits and unchecked cases without a runtime
allocation claim. Each new function's changed-source control rejects, and all
linked extents, pools and padding remain in the ignored OAM staging proof folder.

The camera and map resource path now adds eleven exact C extents, totalling
592 bytes: view-origin read/write (`0x39FDC`, 28; `0x39FF8`, 32), map dimension
readers (`0x3A018`, 52; `0x3A04C`, 36), display-mode read (`0xD5F0`, 16), decoded
size read (`0x16A90`, 8), separate and combined map loaders (`0x3A070`, 92;
`0x3A0CC`, 92), map cell address/write (`0x3A170`, 52; `0x3A128`, 52), and
resource release (`0x39F58`, 132). These are connected to the accepted renderer
view-origin dependency and the actor terrain/layer dimension lookups. The
renderer itself remains unmatched and excluded from C coverage.

The two-word signed view origins start at `0x03001FA8`; the byte selector has no
local range check. The map container starts at `0x03005F50` with a separately
freed pointer, followed at `0x03005F54` by two records with observed stride
`0x900`. Each partial record has pointers at `+4`, `+8`, and `+0xC`, and unsigned
halfword width/height at `+0x14` and `+0x16`. The remaining bytes and most
pointer roles are uncertain. The names primary, combined and secondary follow
their allocation and read order; they do not establish an original type or
complete map format. Clearing `0x1204` bytes establishes the container extent
for this path, not a complete inventory of other game state.

The first dimension reader uses the low three bits of the display shadow's
control halfword: modes 0 through 2 return the first map's dimensions multiplied
by 32, while other modes return 240 by 160. The second reader always returns
the second map's dimensions multiplied by 32. Loading the primary resource
initializes width and height from its first two decoded halfwords. The combined
loader reserves the sum of the reported sizes, decodes the optional secondary
stream at primary-size minus four first, then decodes the primary at the base.
The resource size reader returns the upper 24 bits of its first word. The
connected 208-byte codec dispatcher at `0x16978` was matched in the same batch,
as detailed below; raw useful failed comparisons remain private.

Cell lookup shifts the full unsigned x/y arguments by five, truncates the
resulting column and row to halfwords, computes a halfword cell index, and
addresses primary data after its four-byte dimension prefix. Thus truncation is
after shifting, not a sixteen-bit input bound. It has no local coordinate or
record-index check. The writer reads a halfword at secondary index plus two,
adds the first combined word, and narrows the sum into the chosen primary cell.
Release frees combined, secondary and primary for each of the two records,
frees the container's prefix pointer, clears the whole container, and restores
the current local player's view origin from `0x08057974` unless frame flag
`0x20000` is set. The allocation/free/clear callees remain explicit original linked
dependencies. None of this establishes runtime map validity or
gameplay behavior.

All eleven replacements match linked bytes including pools and alignment with
the promoted shared partial views. Each deliberate source edit rejects:
view-origin read/write 19/1 differing bytes, dimension readers 1/34, display
mode and decoded size 1 each, both loaders 1 each, cell address/write 2/1, and
release 57. The failed sixteen-bit coordinate view and expression-order trials
are preserved alongside the canonical and negative proofs in ignored
`reports/agents/frame-input/camera-map/`. The OAM header now has an inclusion
guard; no OAM implementation or layout changed.

The connected resource codec dispatcher at `0x16978` adds another 208 exact C
bytes, bringing this camera/map batch to twelve functions and 800 bytes. It
extracts a four-bit codec from header bits 4 through 7 and a 24-bit size from
bits 8 through 31. Codec bit 3 selects the connected second pass at `0x16B78`,
whose body is reconstructed in the connected follow-up below. The low four
header bits remain unidentified.
Masking out the second-pass bit leaves selectors 0 through 7: selector 0 copies
word data after the four-byte header through the SWI `0x0B` wrapper; 1, 2, and 3
call wrappers with observed SWI numbers `0x11`, `0x13`, and `0x14`; 4 dispatches
through the existing tile-decoder pointer; and 6 dispatches the payload after
the header through the existing background-decoder pointer. Selectors 5 and 7
perform no first-pass operation. Wrapper names intentionally identify observed
SWI numbers without inferring an unsupported algorithm from their address.

The raw-copy control uses the nonnegative 24-bit size divided by four, masks
its word count to 21 bits, and sets control bit 26. A signed intermediate for
that division preserves the reference's separate size extraction and control
calculation; an unsigned shift allowed this compiler to merge those stages and
changed the instructions. Only the loaded metadata word retains an explicit
register binding. Removing the initially tested input, output, header and
payload bindings preserved the full match; no original instruction body or
output manipulation is used. This is evidence for a matching C expression and
compiler allocation, not a uniquely recovered original declaration.

The first indirect pointer's literal is `0x03003360`, matching the tile resource
upload path's existing global. An initial provisional `0x03003660` address was
incorrect and is retained in the failed one-byte-difference trial. The background
pointer is `0x030036C0`. Both callbacks receive the address of the local decoded
size and may change the size passed to the second pass. The return value reloads
the header's upper 24 bits. The pointed-to copied decoder bodies remain original;
this dispatch match does not establish their formats, accepted input bounds or
runtime decoding behavior. The corrected dispatcher matches all 208 linked
bytes, including its nine-entry jump table and literal pools. Changing the
codec mask from `~8` to `~4` rejects by one byte. Its canonical/control proofs and
the unchanged wrong-address trial remain under the ignored camera/map reports.

The decoder lifecycle follow-up adds four complete exact C extents, 332 bytes:
halfword second pass at `0x16B78` (36), its identical neighboring copy at
`0x16A98` (36), alternate dispatcher at `0x16ABC` (188), and RAM installation at
`0x16A48` (72). The second pass leaves the first halfword alone and adds each
preceding reconstructed halfword into the next, narrowing each sum to 16 bits.
It processes size shifted right by one; sizes below four perform no writes and
an odd final byte is ignored. The duplicate entry has the same static body but
no direct Thumb call or aligned entry pointer was found in the bounded local
reference scan; its higher-level role remains uncertain. Both dispatchers call
`0x16B78`, and no runtime second-pass output has been validated.

The alternate dispatcher shares the header, indirect callbacks and second pass,
but selector 0 uses the SWI `0x0C` wrapper with the masked word count alone;
selector 1 uses SWI `0x12`, selector 3 uses SWI `0x15`, and selector 2 has no
first-pass operation. Its observed direct callers at `0x2986E` and `0x2987C`
connect it to another resource consumer, whose complete format remains
unresolved. This establishes a distinct dispatch path without assuming from
its name that all destinations are hardware display memory.

Installation uses the SWI `0x0B` word-copy control `0x04000084` to copy 528 bytes
from `0x0800B36C` to `0x030036D0`, then publishes that ARM entry through the
pointer at `0x03003360`. Its second copy uses control `0x040000D4`, copying 848
bytes from `0x080002EC` to `0x03003370` and publishing the entry through
`0x030036C0`. The source/destination/control literal triples are at ROM
`0x16A70/74/78` and `0x16A80/84/88`. These installation and callback facts
resolve the copied addresses for the accepted dispatchers. They do not add C
coverage for the installed bodies.

Static disassembly places the first decoder's return at `0xB560`, followed by
another ARM prologue at `0xB564`: a provisional 504-byte body within a 528-byte
copy that includes 24 following bytes. The second decoder's terminal return is
at `0x614`, followed by the accepted Thumb frame scheduler at `0x618`: its
812-byte code/helper span is copied with 36 bytes from that next function.
The second body now has [complete assembly-origin source ownership](RESOURCE_BACKGROUND_DECODER.md),
including its carry-sensitive private readers. Its independently reconstructed
assembly matches at both ROM and RAM addresses, with no C credit or embedded
instruction data. The first decoder remains unconverted. Raw copy words, ARM
disassembly, inferred entry signatures and boundary distinctions are retained
in the ignored `decoder-copy-evidence.json` and accompanying raw files.

Each of the four follow-up source changes rejects by one byte: halving the
second-pass element count again, changing the alternate raw-copy count shift,
and reducing the first install count. Canonical linked images, controls and
full comparison records remain under `camera-map/neighbors/`. The original
208-byte dispatcher remains exact after the header extension. These are static
and compiler results only; allocation validity, malformed-resource handling,
copied-code execution and gameplay remain untested.


The map buffer lifecycle at `0x39E78..0x39F58` adds four exact C extents and
224 bytes: copied-routine installation (72), the two-source setter (20),
display-memory snapshot (92), and restore (40). The setter writes pointers at
container offsets `+4` and `+0x904`, establishing the first word of each
`0x900`-byte record as a source pointer. The pending selected-tile consumer
reads source metadata, and copied routines test this pointer before operating
on a record. This refines the partial record's former unknown word without
changing its layout; the precise serialized source type remains unresolved.
The initial setter candidate incorrectly wrote the primary buffers at record
`+4`; that failed comparison is retained and the accepted name is
`frame_set_map_sources`.

Snapshot first frees and clears both combined buffers, then allocates `0xC000`
bytes into the container prefix and copies display memory `0x06000000` through
the SWI `0x0C` wrapper with word count `0x3000`. It restores the current local
player's default view origin after that copy. Restore copies the prefix buffer
back with the same count, frees it and clears the pointer. The matching source
has no allocation-failure or null-prefix guard; adding such behavior would not
be supported by these linked bytes. The snapshot and loaded combined resource
reuse the same prefix pointer, but their runtime sequencing remains untested.
The heap names now follow the separately reconstructed allocation lifecycle.

The installer copies 336 bytes from `0x0800B564` to `0x03007160` with word
control `0x04000054`, and 228 bytes from `0x0800B6A4` to `0x03005E60` with
`0x04000039`. It publishes the entries at pointer locations `0x03001FC8` and
`0x03001FCC`. Their provisional single argument selects an eight-byte pair
in the view-origin table. Static ARM disassembly finds 320- and
216-byte spans ending in returns, so the install copies also include 16 and
12 bytes from the next ARM entries respectively. The second body is the owned
`frame_transfer_map_tiles` at `0xB6A4`; its first sixteen bytes also occur at
the end of the first installation. The second following entry
is the tile allocator already reconstructed separately. These copy sizes are
installation facts, not additional reconstructed C coverage. Raw disassembly,
literal triples and provisional signatures are retained in the ignored
`map-copy-evidence.json` and `map-copy-original.txt`.

The origin root at `0x03001FA8` gives a concrete callback-writer obligation:
index four selects both installed words at `0x03001FC8/0x03001FCC`. The native
setter has no range guard; its snapshot/release callers pass the zero default
point and a fresh local-player byte. The map updater separately stores computed
coordinates through this indexed origin path before loading its draw callback
at `0x08039BE2`. A native post-provider fixture with view and local player both
four overwrites and captures zero; controls zero through three preserve the
installed target. This proves the write-to-load dependency, not whole-caller or
gameplay reachability. Native range checks of the inspected handshake/copy
chain give counts zero through four and local-player bytes zero through three
or 255: diagnostic five returns before active-count publication. The primary
loop excludes view four only if every fresh count remains within that domain;
an initial snapshot bound is insufficient. Provider, callback, IRQ and indexed
alias writes still need noninterference evidence. Neither the installer nor
these conditional bounds establish a complete callback population or a new
executable target.

All four accepted linked images match, including pools and alignment. Their
changed-source controls reject by 19, 1, 1 and 1 bytes respectively. The prior
sixteen camera/map and decoder replacements and their controls were recompiled
against the refined record and canonical heap declarations; all retained their
matches and rejected their edits. Evidence is under `camera-map/map-lifecycle/`.
The larger selected-tile consumer at `0x39CF0` remains a semantic C candidate
with mismatching bytes and is excluded from coverage, alongside the first copied
ARM map body at `0xB564`. The second body's 216 C bytes remain counted once.
No runtime display-memory restore or map drawing has been validated.

Its current private owner view uses the actual unsigned control words, a
four-byte resource prefix followed by eight-byte chunk descriptors, and a
decoded halfword count followed by variable halfword indices. Required backing
is explicit. Integer tile-offset arithmetic finishes before forming the final
scratch pointer; older fixtures could form an out-of-object intermediate
pointer. The historical 392-byte / 11-difference fixture also used unsupported
volatile pointer homes and is not a current interface proof. No production
header or caller repair has yet been admitted from these private attempts.

A fresh interface qualification reproduces the current 392/109 body using the
canonical opaque formal and the caller's actual unsigned control-word object,
without overriding a header. Its provisional resource/selection views and
backing premises remain explicit; normal/strict bytes and real DMA-count
controls agree. A native-shaped inner search restores the repeated layout load
but loses offset strength reduction (384/321). Carrying the real descriptor
offset restores its recurrence but hoists both pointers (388/311). Loop syntax
alone does not explain the remaining native ownership and reloads.

A by-value control-word helper recovers the native word load and paired shifts
for both color-bit reads. Splitting the real count calculation into its two
evaluation phases then recovers native count-before-color read order, including
the DMA source/destination stores before its count read. The resulting source
emits 396 bytes with 212 byte differences, including four extra bytes, against
the native 392-byte extent. Forming the complete unsigned integer DMA source
address before converting it to a pointer then recovers the native base-add
before subtraction, leaving 396 bytes with 205 differences. This avoids an
out-of-object pointer intermediate; it does not establish live scratch backing.
The frame remains 20 bytes instead of 24, with different resource, control,
chunk-size and loop homes. Expression variants are closed pending a distinct
storage or lifetime fact; native stack copies alone do not justify volatile
storage or a fabricated work record. Allocation, decoded backing, initialized
scratch spans, callback writers and hardware execution remain conditional.

A review of the drawer's existing genuine eight-byte copies closes another
apparent source variation. Their grouped loads survive through CSE2, but the ARM
backend requires different base registers and separate pointer advances; later
optimization also loses the native width reload. The retained direct-copy
attempt is 332 bytes with 287 differences against 320 native bytes. This is a
different cause from the scalar-address decomposition in the two-four-byte-copy
attempt. Neither supplies a matching replacement.

The named row-six initial maps now have a bounded data check: both are 20 by
26, and all 1,040 stored tile indices select initialized 32-byte groups. Reusing
the calibrated original-ARM-body model, all six primary/combined/alternate
streams produce their advertised output. Applying the loader's alternate-first,
primary-second order leaves 15,876 and 8,868 initialized combined bytes, or 496
and 277 groups. The four-byte requested append tails remain uninitialized and
excluded. Replay and initialization-observer controls pass, and an independent
review reopens every map cell and assembled buffer. This is a controlled model
result, not whole-loader execution or a natural scene observation.

Initial validity does not close later animation writes. The rectangle caller
passes a byte index 0..255 to a secondary buffer with only 26 backed halfwords;
its loop and endpoint guards do not impose that backing limit. Eight fixed
scene-six payloads now satisfy the source and destination bounds for their
initial rectangles and conditional two-write forward segments. All start
disabled in state zero; the retained pack-two programs nevertheless provide a
conditional direct-state-four activation chain. Actor/view completion, wider
payload/writer populations and live allocations remain open. See the
[writer boundary](FRAME_MAP_ANIMATION.md#row-six-writer-domain).


The copied row-transfer entry stored at `0xB6A4` now adds 216 verified C bytes,
linked at its installed execution address `0x03005E60`. It considers both map
records and skips records without a source pointer. For the selected view, it
divides each signed coordinate by eight with truncation toward zero and masks
the quotient to two bits. The source halfword offset combines x with forty
times y. It reads the source header's byte `+1`, masks it to five bits, and
uses that value times `0x800` as the destination offset from display memory
`0x06000000`. DMA channel zero then transfers 22 rows with observed control
`0x8000001F`, advancing the source 80 bytes and destination 64 bytes each time
and reading the control register after every write. These are static register
accesses and a compiler match; hardware execution has not been tested.

The copied code accesses coordinate pairs at record `+0x18` and staged words
at `+0x40`. The unchanged `0x900`-byte record gives names to four view-coordinate pairs,
a fractional-scroll pair at `+0x38`, and 280 pairs of 32-bit staged words. The
camera writer described below distinguishes the fractional-scroll pair from
the initially inferred fifth coordinate slot. The staging interpretation is
provisional but its offsets, eight-byte pair stride and 80-byte row stride are
directly observed. The argument is narrowed to its low byte; the source has
no local check against this partial layout. Valid caller indices and runtime
bounds remain unresolved. All twenty previously accepted map and decoder
callers and their negative controls were reverified with the initial layout.

Two semantic values retain explicit register bindings: the source-layout
pointer and the screen-block offset. Removing the initially tested iterator,
source-address and row-counter bindings retained the match; removing either
remaining binding changed the generated instructions. The source contains C
address calculations, signed coordinate division, loops and volatile DMA
accesses, without an embedded ARM body or output alteration. It matches the
complete 216-byte body including the literal word and its branch around the
pool. Reducing the row count to 21 rejects by one byte. Public-source canonical
and control proofs are under `camera-map/copied-layout-revalidation-v2/`.

The two installed map copies total 564 bytes, while the separately bounded
staging and transfer bodies total 536 bytes. Only the transfer body's 216
bytes are reconstructed at this point. The staging body at `0xB564` and the
16- and 12-byte following prefixes remain explicit original code, excluded
from C coverage. The selected-tile consumer at `0x39CF0` and central renderer
at `0x23E8` also remain unmatched candidates.


The camera update and scroll publication path adds three exact C functions
and 516 bytes: `transition_get_view_position` at `0xEA44` (36),
`frame_update_map_view` at `0x39B10` (316), and
`frame_publish_map_scroll` at `0x39C4C` (164). The reader copies the two
position words at offsets `+4/+8` of the selected 48-byte view-motion record.
The camera update centers that fixed-point position by subtracting 120 and
80 pixels plus a ROM byte's vertical adjustment, shifts the coordinates to
integer pixels, and clamps them against the map dimensions minus the
240-by-160 viewport. The lower-bound test precedes the upper-bound test;
maps smaller than the viewport can still produce a negative upper bound.
No extra validation is inserted into the matching source.

The computed origin is stored in the independent view-origin array and in
both map records. For the local player, flags `0x110000` instead clear the
map-record origins and fractional offsets; the independent view-origin array
retains the computed coordinates. Otherwise local updates store `x & 7` and
`y & 7` at record `+0x38/+0x3C` and invoke the installed staging callback.
These writes establish the four origin slots followed by a separate
`fractional_scroll` pair, while preserving each record's `0x900` size.
The staging callback is still original ARM code; reconstructing its caller
does not establish a C match for that body.

Scroll publication runs only when the shared interrupt context's
`transfer_ready` halfword at `+0x38` equals one. It invokes the installed row
transfer callback with the local player, then writes the second and first
records' fractional offsets to display registers `0x04000014..0x0400001A`.
When the background animation's flags contain bit zero, its byte `+0x0F`
selects either an x-only write at `0x0400001C`, or x/y writes at
`0x0400001C/0x0400001E`, using the first record's full local-player origin.
The background-animation field's existing `transfer_enabled` name remains
provisional: this caller distinguishes values greater than one. These are
static accesses and exact compiler results, without runtime display tests.

The publisher's original return and final literal end at `0x39CF0`, making
its extent 164 bytes. An early 172-byte comparison accidentally included
eight bytes from the next function; that overlong raw comparison is retained
locally and was never credited. The three canonical functions match their
complete extents, pools and alignment. Changed-source controls alter the
first record's fractional x mask, the interrupt-ready condition and the
reader's y source; they reject by 132, 108 and 20 bytes respectively. All
21 previously accepted camera/map and decoder functions retain their matches
and reject their controls after the same-layout refinement. Raw linked
images and comparisons are under `camera-map/map-camera-promoted/` and
`camera-map/map-camera-layout-revalidation/`.

The scene/map loading continuation adds seven exact C replacements, 672 bytes:
`frame_load_scene_map_resources` (`0x263D8`, 328),
`frame_configure_deferred_display` (`0x12F4`, 16),
`frame_initialize_map_palette_slots` (`0x26BA4`, 36),
`frame_define_palette_slot` (`0x301F0`, 48),
`frame_decode_map_cell_types` (`0x2B160`, 68),
`frame_decode_extra_map_cell_types` (`0x2B1A4`, 96), and
`frame_create_map_registration` (`0x3B0DC`, 80). Each final complete linked
extent matches, and an actual changed-source compile/link control rejects.
These are source and static call findings; no gameplay validation follows from
this batch. Final comparisons and controls remain under the ignored
`reports/agents/frame-input/camera-map/map-loader-promoted/` directory.

The loader indexes 72-byte records at ROM `0x08056414`. The two selection
sources at record `+0` and `+4` feed the still unconverted selected-tile loader
at `0x39CF0`, using the tile resource at `+0x3C` and the two existing background
control words. Primary/secondary resource pairs at `+8`/`+0x14` and
`+0x18`/`+0x24` feed the matching two-map resource loader. Combined resources
at `+0x0C`/`+0x10` and `+0x1C`/`+0x20` load after either initialization or
VRAM restoration. Record `+0x40` remains unknown. The independent table base
and initial record pointer are ordinary C locals; their declaration order
preserves the original compiler's separate base and index allocation.
Useful failed alternatives and the earlier 31-byte mismatch are retained.

The byte at resource `+0x44` writes the queue field at `+0x20C` in RAM
`0x030015B8`. An early object-count interpretation is superseded by the
matching scheduler and multipart renderer: they respectively test this field
for deferred rendering and copy it into an OAM layer under the special
mirroring option. The existing `deferred_refresh` field name is retained;
`deferred_layer` and `frame_configure_deferred_display` express those observed
uses without claiming an independent count.

The metadata decoder writes decoded bytes to the buffer selected at RAM
`0x03001DDC` and its byte count at `0x03001DE4`. A second buffer selected at
`0x03001DD8` has a four-byte header; its decoded halfword count is stored at
`0x03001DE8`, and its leading halfword is widened into `0x030043F8`.
The optional extra pair appends data after the first byte span, decodes metadata
through the scratch pointer at `0x030043FC`, and copies the payload after its
four-byte header with DMA3 to the pointer at `0x03001DE0`, offset by twice the
stored count. The `cell_data` and `cell_types` labels are provisional roles
within this map load path. The buffers' allocation and input size guarantees
remain unconverted; these helpers retain the original unchecked arithmetic.

The palette reset defines slots 1 through 7 using pointer-array entries from
ROM `0x0805779C`. Its writer establishes a state header at RAM `0x03001E48`
with a four-byte palette-frame selector followed by sixteen eight-byte slot
records. A slot stores its ID, users byte and source-array pointer at record
`+0`, `+2` and `+4`; this agrees with the existing partial users-byte view,
whose base includes the four-byte header. Defining a slot loads sixteen palette
colors from its selected source into `slot << 4` through the existing alternate
palette loader. The slot selector and source-array range remain unchecked.

The grid constructor allocates and zeroes a 20-byte record, then calls the
original initializer at `0x48B78` with narrowed width, height and cell size.
An initializer result of one allocates `extent * extent` bytes and assigns the
result to the record's first word. The scene loader passes cell size 16,
installs this record as `g_frame_registration`, and decodes the scene resource
at `+0x38` into its data. Existing bounds registration, grid terrain and actor
route consumers support the grid interpretation. The initializer's observed
fields at `+4`, `+8`, `+0x0C`, `+0x10` and `+0x12` supply the partial origin,
span, extent and cell-size view; their exact coordinate semantics remain under
analysis. Allocation failure checks are absent in this path. The selected-tile
loader, first copied map staging body and central renderer remain explicitly
unconverted. The initializer is owned by the continuation below.

The grid initialization/projection continuation adds seven exact C replacements,
524 bytes: `frame_initialize_map_registration` (`0x48B78`, 128),
`frame_grid_coordinates_to_point` (`0x48CC4`, 76),
`frame_grid_cell_to_point` (`0x48D10`, 100),
`frame_grid_snap_point_to_center` (`0x48C50`, 52),
`frame_grid_snap_point_to_corner` (`0x48C84`, 64),
`frame_grid_cell_corner` (`0x48DB4`, 40), and
`frame_grid_cell_extents` (`0x48D74`, 64). All complete linked extents match
and all seven actual changed-source controls reject. Their final proofs are in
`camera-map/map-grid-promoted/`; failed inverse-projection and point-to-cell
candidates remain separate and receive no coverage.

The initializer divides width and height by the cell size with unsigned
division, narrows each quotient to a halfword, and sums half the first quotient
with the second. The sum supplies the extent halfword and, before that
narrowing, its product with cell size supplies the word span. It clears the
data pointer and both origins, transforms the coordinate pair `(height, 0)`,
then stores the negative projected X and negative projected Y plus eight as
origins. It returns one without testing the transformation's return value.
The source preserves this behavior, the halfword narrowing and the full-width
span product. The scene caller supplies cell size 16; zero-size and invalid
initialization inputs remain unchecked.

The coordinate transform checks both signed input axes against zero and the
span word interpreted as signed. It projects X as `origin_x + x + y` and Y as
`origin_y - x/2 + y/2 + 8`, with signed division toward zero. This establishes
the two diagonal coordinate axes for the existing grid context. The cell-center
reader checks the two low bytes of a packed cell against the extent, multiplies
each byte by cell size, and adds half the cell size before applying the same
projection. The accepted reader keeps the shared algorithm as an inline C
helper, which also preserves the original addressable temporary's stack slots.
Its return is zero for an out-of-range packed cell; after a valid packed-cell
check it returns one even if the subsequent span check leaves the output
unchanged. The corner reader omits the half-cell offset. The extents reader
returns two optional diagonal corners `(x*size, y*size+size-1)` and
`(x*size+size-1, y*size)` without checking the packed cell against the extent.

The snap wrappers call the original point-to-cell converter at `0x48AF8` and
use either the matching cell-center reader or corner projection. Raw converter
exits and the wrapper at `0x48C50` establish byte-sized zero/one return values
for both `frame_grid_point_to_cell` and `frame_grid_cell_to_point`; their earlier
void declarations are corrected without changing their existing parameter
views. Both accepted direct callers, `frame_find_actor_route` and
`frame_actor_direction_available`, still match exactly and their real controls
still reject after this declaration refinement. These proofs are retained in
`camera-map/map-grid-caller-revalidation/`. The packed-cell halfword and upper
halfword layout is unchanged: the low two bytes now have direct writer/reader
evidence for the two axes; the upper bytes remain unspecified. The inverse
projection and point-to-cell converter themselves remain unconverted. These
are compiler and static data findings, not runtime assertions about pathfinding
or complete map input coverage.

A clean current-header point-to-cell capture retains the actual two-point
16-byte work object, duplicate Y-bound test, ordinary byte outputs and the
existing signed-word BIOS division interface. It emits 116 bytes / 121 differing
or missing bytes against the complete 128-byte native extent. The R0 inverse-sum
chain survives optimization, but global allocation chooses context/output R5/R7
instead of native R7/R8. Older near-match records with missing helper contexts
or unjustified volatile output do not qualify this source. No C credit or
automatic binding, qualifier or profile follow-up follows.

The inverse `resource_project_point` at `0x48BF8` now has a shared provisional
zero/one status declaration in `frame_grid_math.h`. Native exits set R0 to zero
or one; both inspected callers ignore that result. The retained unsigned-byte
return spelling is compatible with those values, not a uniquely recovered
historical typedef. Its context is the canonical 20-byte registration selected
by `g_frame_registration` at `0x03004330`; the duplicate resource-context alias
and caller-local void declaration are removed. The existing 104-byte
`resource_object_before_step` still matches with genuine controls.

The [grid need-effect selection controller](../src/frame/frame_update_grid_need_effect_selection.c)
at `0x3C688` now matches all 720 bytes: 654 instruction, 60 literal and six
alignment bytes. Real X/Y offset-table address lifetimes close the match using
canonical provider declarations. It passes the same point as input and output
at `0x3C810`; the inverse reads both input words before its conditional stores.
The inverse remains unconverted and writes both words only on success, retaining
the repeated Y upper-bound test without adding an X upper-bound test.

Short `BUG` comments preserve the controller's unset-point uses after inner or
center projection failure. Valid backing, list/index and arithmetic domains
remain explicit; matching the original bugs adds no gameplay or bug-free claim.
The before-step caller still copies lower to upper bounds after projection
failure, with valid prior bounds remaining its caller premise.

The earlier canonical-header inverse diagnostic remains 88 bytes / two
differences, with unconsumed local-point stores. Its actual R5 origin-sum use
survives from initial RTL through final output; native saves R5 without a body
use. This source does not exhibit a late deletion and remains unqualified.
An explicit R7 context binding also fails semantically: frame-pointer
elimination rewrites its actual context reads into SP references, including
with omit-frame-pointer. Preserve these failures rather than inheriting their
owners as source contracts.

Genuine wide affine partials now demonstrate the previously missing save-mask
mechanism: LREG assigns a consumed conversion to R4/R5, then high-word
definitions disappear by GREG while the R5 save remains. The full source is
92 bytes / 64 differences; it regroups the arithmetic and is not a match.
Modular arithmetic checks retain the native word results. Native-order named
partials instead spill their conversions and expand the frame. An actual late
two-addend aggregate starts after the X store and consumes both fields in Y,
but takes R1/R2 and remains 92/54. Its explicit R4/R5 owner and inline-formal
copy are deleted by COMBINE before allocation. These findings close that owner
route without qualifying the old unused-store candidate. The known 104-byte
caller and actual changed-mask control remain exact/rejecting respectively.
Private source, pass evidence and full comparisons are retained in
`analysis/inverse-modular-affine-partials-20261026/` and
`analysis/inverse-y-addends-r4-owner-20261027/`.

The scene actor/view initializer `frame_initialize_scene_actors` at `0x26520`
adds one exact 400-byte C extent, including its first literal island and final
pool. It normalizes a zero or single-player count to one, clears the local
player index, prepares the selected serialized resource groups, and resets
and configures each player view. It then spawns and executes group zero and,
when the resource-group flag permits it, group one. Its remaining calls consume
the saved scene-entry record, install the primary actor pointer, conditionally
create a scene exit and restore the selected actor at the recorded spawn.
Several called scene-entry and actor-selection helpers remain unconverted;
this match establishes the coordinating code rather than complete actor setup.

The accepted source uses an eight-byte `FramePoint` by value for the view
configuration call at `0xE9E8`. The original caller loads the two consecutive
ROM words at `0x08053504` into argument registers one and two and the view byte
into register three. This aggregate argument preserves those loads inside the
player loop; the earlier four-scalar declaration allowed the compiler to hoist
the ROM pointer, changed register lifetimes and produced a nonmatching
404-byte candidate. The declaration is corrected in `transition_object.h`.
The unconverted window-transition candidate was updated to the same signature
and recompiled, but still differs and receives no coverage. No accepted direct
caller of that declaration required a behavior change.

`FrameSceneEntrySnapshot` is a partial view rooted at `0x03003A2C`, with saved
position words at `+0x348/+0x34C`, world byte at `+0x350` and exit flag at
`+0x352`. `FrameSceneActorSelection`, rooted at `0x03003950`, has position
words at `+0x430/+0x434`, world byte at `+0x43C` and selected actor byte at
`+0x740`. The last offset follows the observed `232 << 3` address calculation;
it is distinct from the previously inspected actor selector at `+0x748`.
These overlapping game-state views and names remain provisional. The source
keeps the explicit unset-actor value 42, byte-sized helper result comparisons
against one, and state 24/variant state two assigned after construction.

Final full-byte and changed-state controls are retained in
`camera-map/scene-actors-promoted/`; changing state 24 to 25 rejects the match.
The accepted `scene_initialize` caller now uses the established
`frame_load_scene_map_resources` and `frame_initialize_scene_actors` names at
the same addresses. Its 808-byte extent remains exact and its actual existing
control still rejects. The older arena/group loader candidate at `0xAD1C` was
inspected before extending it; it remains unconverted under the provisional
name `resource_prepare`. The initializer's compiler match and the static
argument/layout evidence do not establish runtime actor selection or gameplay.

The scene setup continuation adds seven exact C extents, 892 bytes:
`frame_allocate_object` (`0x1108`, 32), `frame_scene_read_spawn` (`0x16C04`, 76),
`frame_create_scene_primary_actor` (`0x2FAD0`, 112),
`actor_entry_mark_scene_collection` (`0x20B60`, 32),
`actor_entry_restore_scene_collection` (`0x20BF8`, 92),
`actor_entry_restore_collection_effect` (`0x20C70`, 92), and
`frame_scene_player_actor` (`0x1DE1C`, 456). Every complete linked extent,
including local literal islands and alignment, matches. Their actual controls
all reject; canonical and changed-source bytes are retained in
`camera-map/scene-dependencies-promoted/`. The 400-byte setup is reverified with
its same control after adopting the established restoration/factory names and
byte-sized spawn-index declaration.

The typed allocation wrapper calls the existing 320-byte object allocator,
returns null unchanged on failure, and otherwise writes the narrowed id and
clears the byte at `+0x84`. The spawn lookup traverses the primary object list,
searching for id 18 and the supplied byte-sized subtype. It optionally writes
the direction byte and always writes the two position words on success. Its
boundary includes two final alignment bytes, extending the prior 74-byte CFG
envelope to the complete 76-byte compiler extent. The primary actor factory
allocates id 27, sets flags `0x00100018`, clears actor byte `+0x4C`, initializes
position/state/animation and palette slot six, installs its step and resource
callbacks and clears the display layer. The step callback itself remains an
original routine.

The saved-entry routines use the existing `ActorEntryContext` pointer at
`+0x31C`, 12-byte collection records, and four-byte groups at collection
`+0x784`. The mark helper establishes bit zero of group byte `+2` as a flag;
the canonical group view now names this byte `flags` and retains its previous
four-byte layout. The restoration loop creates each group's saved effects
then clears the group using the matching existing collection helper. For each
record, the effect constructor consumes the first four bytes and argument one,
then effect byte `+0x83` is set while its saved packed cell is projected to a
grid corner. The low byte of record `+8` and the projected coordinates narrowed
to signed halfwords go to the original placement helper at `0x2D8E4`. That
helper remains unconverted. The temporary `linked` interpretation of byte
`+0x83` and the record names remain provisional; allocation and projection
failures are not checked by this path.

The player actor constructor allocates id zero and configures the shared
actor/frame fields, group palette, animation variants, commands and part
orders. The game-state mode byte at `+0x42E` selects one or two times the spawn
direction, a direction-table variant, and an unsigned flip threshold of four
or eight. An unsigned-byte local for the multiplier produces the exact
branch/lifetime behavior; the earlier signed-word local did not match. This
supports that type for the reconstruction without proving the original source
declaration. The constructor reads either a resource spawn's two signed
halfwords and direction byte or fallback fields at configuration offsets
`+8/+0x0A/+7`. It writes its pointer into the observed 12-byte player-view
slot, installs the two-object callback at object `+0xC8` and resource callback
at `+0x98`, assigns the state pointer at `+0x60`, and invokes the matching actor
state updater. The `+0xC8` callback is distinct from the normal actor callback
view at `+0xCC`; its type follows the original two-object consumer. The byte at
`+0xAE` is set to eight and used by that original callback as a fixed-point
spatial threshold; the byte at `+0x84` is set to three. Their wider roles remain
under analysis. These compiler and static-layout findings do not establish
runtime multiplayer or scene-restoration behavior.

Two further direct scene-setup dependencies add exact extents of 160 and 64
bytes: `frame_scene_actor_allowed` at `0x2CC08` and
`frame_spawn_saved_scene_effect` at `0x33674`. Their canonical and actual
changed-source comparisons are retained in `camera-map/scene-tail-promoted/`.
Changing the eligibility cutoff from five to four rejects one byte; adding
one to the saved effect value rejects twelve. The five existing functions
that include the player/scene header closure were recompiled exactly and their
existing controls rejected, including the 400-byte setup caller.

The eligibility predicate returns one when its enable byte at `0x03001E2C`
is zero. It preserves the actor-31 condition/world-37 exception, the selected
actor's existing world-exclusion query, the unsigned wrapped actor-minus-six
table index, null table handling, and an eight-byte row stride. The context
row is read as a signed byte at `+2`; its column comes from the original
helper at `0x10808`. Neither the table index nor row/column is bounds checked
by this routine. The formal actor value is kept as an unsigned word: its
entry copies the complete argument and does not narrow it. The caller already
supplies a loaded byte. An ordinary integer address accumulator for the ROM
pointer table preserves the original address-addition order without an
assembly body or register binding.

The shared selection view retains its layout and now exposes the observed
current-world byte at `+0x0A`, saved-effect value at `+0x438` and saved-effect
kind at `+0x43D`. Its position, world byte at `+0x43C` and selected actor at
`+0x740` remain at their previous offsets. The effect helper calls the
original factory at `0x332C8` with that kind and the two position words. On
success it writes the first player slot's object pointer to effect `+0x64`
and the saved value to `+0x6C`, then returns the pointer. Null is returned
unchanged. The setup caller ignores the return. Effect field names and the
eligibility context's row/column interpretation remain provisional; the
original factory and column helper were unconverted at this checkpoint;
both are reconstructed below.
These matches establish source bytes and static data access, not runtime
scene eligibility or effect behavior.

The eligibility dependency originally named `frame_scene_actor_world_slot` at `0x10808` is now
an exact 20-byte C replacement. The original signed halfword load at context
`+0`, signed remainder helper call with divisor seven, and final halfword sign
extension establish a signed `short` return. The context's `column` name follows
its use as the remainder input and subsequent table-column index; that semantic
name remains provisional. Its signed row byte at `+2` and all observed offsets
stay unchanged. The accepted eligibility caller explicitly narrows the returned
value to an unsigned byte; no bounds clamp has been added for negative inputs.
The previous unsigned-byte declaration described only that caller's use and has
been corrected to the observed callee return. Subsequent connected clock
arithmetic supersedes the coordinate interpretation: this helper is now named
`display_time_weekday`, reads the signed day component, and returns day modulo
seven. The byte at `+2` is the hour component; the eligibility table therefore
uses hour times eight plus the byte-narrowed weekday result. The offsets and
return narrowing remain unchanged. See [DISPLAY_TIME.md](DISPLAY_TIME.md) for
the arithmetic and current-header proof. The older raw receipts remain intact.

Changing `% 7` to `% 6` produces a one-byte mismatch. The canonical helper,
eligibility caller, scene setup, player factory, primary actor factory, spawn
reader, and current scene-object allocator all match under the refined header;
their real changed-source controls all reject. Raw linked outputs and comparisons
are retained in `reports/agents/frame-input/camera-map/world-slot-promoted/`.
This closes one direct eligibility dependency. The central renderer and
selected-tile loader remain excluded; the saved-effect factory is reconstructed
in the following connected batch.

The saved scene-effect path now adds seven exact C functions totaling 820 bytes:
`display_time_weekday` (`0x10808`, 20; originally `frame_scene_actor_world_slot`),
`frame_create_scene_saved_effect` (`0x332C8`, 252),
`frame_scene_effect_tick` (`0x33424`, 140),
`frame_scene_effect_interact` (`0x334B0`, 208),
`frame_scene_effect_refresh` (`0x335A8`, 64),
`frame_scene_effect_configure` (`0x335E8`, 40), and
`frame_scene_effect_remove` (`0x336D0`, 96). These close the factory and all three
callbacks installed by the previously matched saved-effect restore wrapper.
They are compiler/static results; no runtime scene, input or effect behavior
is claimed.

The factory allocates class six and snaps the two integer coordinates through
the existing grid-center helper before restoring fixed-point position words.
It sets the observed kind/subtype, direction four, default state 29, callback
pointers, sprite bits, kind-indexed speed, script, and before-step callback.
The owner pointer at `+0x64` is initially null and the value word at `+0x6C`
starts at `0x32000000`. The later restore wrapper overwrites these two fields.
The value's units remain unspecified. The original makes no allocation-null
check; this replacement preserves that behavior.

Animation refresh indexes a kind-specific pointer table at `0x08D71FCC`, a
signed requested-animation byte at object `+0x103`, and the existing direction
variant table before calling the matched animation-record setter. Configure
compares its unsigned byte argument with that signed field; on change it writes
the byte and marks pending bit four. Tick dispatches state 29 and 30 to original
bodies at `0x8E14` and `0x91F4`, then calls the original updater at `0x950C`.
These three children remain explicit unconverted dependencies, with address-based
provisional aliases. It refreshes velocity and animation from the observed
pending bits, selects horizontal flip from the saved direction, and clears
pending state. The descriptor dimensions and permitted animation indices are
not established by these matches.

The interaction callback takes two object arguments. It requires effect state
29, excludes variants 52 and 30, and requires other-object state 16. It obtains
the active player via the 12-byte slot records and local-player byte at `+0x31`
from the shared `0x030040E0` base also used by `InputConfig`. That overlap is
represented by a bounded view over the same base, avoiding a second symbolic
literal for the same address. The player's pressed-input index is loaded from
object `+0x13`, distinct from the generic owner-slot field at `+0x11`; its
`input_slot` name is inferred from these accesses. On an eligible bit-zero press
it aligns both objects, changes animation/state, stores the second object at
effect `+0x68`, and clears that bit in the input halfword. The shared effect
view therefore exposes `partner` as an object pointer without changing owner,
value or any offsets. The facing-availability body at `0xEBC` remains original.
The generic actor view still declares a one-argument `on_interact` field; the
factory's explicit function-pointer cast preserves that legacy view while the
new callback itself has the evidenced two-argument signature. The copied
collision dispatcher supplies both arguments at this callback offset.

Remove only records the position, current world and effect kind when the owner
equals the first player-slot object and the stored world is not 50. This is a
connected producer for the scene selection fields consumed by the restore path.
The inline byte-valued ownership predicate is semantic C and preserves the
original boolean materialization and literal placement.

The interaction extent ends at `0x33580`, where the next original entry begins
with its own `PUSH`. The first 248-byte trial mistakenly included that adjacent
function; its source, metadata and raw comparison remain unchanged under
`camera-map/effect-interact-0/`. The corrected 208-byte range includes the
callback's three final literals and alignment. All seven canonical sources and
real changed-source controls are retained under `camera-map/scene-effect-promoted/`;
each control rejects one byte. Every previously accepted source in the changed
player-header closure was recompiled and its control rechecked. Neither the
1,400-byte central renderer nor 392-byte selected-tile loader candidate is
accepted by this batch.

## Saved-effect callback closure: seven functions, 2,684 bytes

The next connected batch follows the callbacks installed by
`frame_create_scene_saved_effect`, rather than introducing a separate object
family. All seven replacements match their entire original extents. Each has a
compiled changed-source negative control. The public GCC2.9-derived Thumb
compiler remains selected; GNU binutils 2.10.1 supplies the original zero
alignment naturally. No generated bytes are rewritten.

| Entry | Matching bytes | Observed behavior |
| --- | ---: | --- |
| `frame_scene_effect_facing_available` at `0x0EBC` | 184 | Quantizes the displacement between two integer positions, then tests the first object's direction against the neighboring direction cases. |
| `frame_scene_effect_state_8e14` | 992 | Decrements a signed value, runs variant timers, creates and places a need effect, follows or walks, and releases the interaction partner after selected variants. |
| `frame_scene_effect_state_91f4` | 792 | Builds interaction label/action lists, consumes a selected action, changes both objects' state, and publishes the saved actor entry or restores its partner. |
| `frame_scene_effect_update_950c` | 516 | Responds to pending bit 2, selects animation modes and conditional audio cues, restores speed from the kind table, then clears that pending bit. |
| `frame_scene_effect_replenish_9710` | 28 | Adds `0x14000000` to the signed value and limits it to `0x64000000`. |
| `frame_scene_effect_walk_972c` | 44 | Chooses a walking direction when the existing `+0xAC` probe is nonzero, refreshes zero horizontal velocity, and refreshes terrain. |
| `frame_scene_effect_follow_9758` | 128 | Uses owner distance and route status to follow, stop, or return to the timed variant. |

The three large children are called directly by the existing matching tick at
`0x33424`. The facing predicate is called by its matching interaction callback
at `0x334B0`. The state names remain address based: their broader gameplay role
has not been established by runtime observation.

The guarded `frame_scene_effect.h` keeps a bounded work view with observed
fields at `+0x54` (route status), `+0x58` (signed timer), `+0x60` (actor-state
pointer), `+0x64` (owner), `+0x68` (partner), and `+0x6C` (signed value). The older
producer view copies the value as an unsigned word; the child view's signed
comparisons follow the original instructions. These interpretations preserve
the same four bytes and do not establish the complete allocation layout or the
value's original unit. The owner and partner fields remain separate. The menu
views likewise describe observed reads and writes: the label and action arrays
at `0x03002E70` and `0x03002E80`, request bytes at `0x03005A00`, selected result
at scene argument `+0x0C`, actor-entry pointer at game state `+0xF0`, and the
56-byte change-record stride beginning at `0x03004134`.

Two boundaries needed particular care. `0x950C` ends at `0x9710`, where the
next function starts with a new register save; it does not include the later
walker and follow helpers. The first idle candidate omitted variant 26's
shared tail. Its branch from `0x90CE` into `0x916E` proves that it replenishes
the value and requests partner cleanup after storing its timer. That behavior
is included in the exact replacement. The older failed candidate is retained.

The facing predicate's signed-short local and unsigned-short range comparisons
produce its original switch body. The current assembler initially differed
only at its two trailing alignment bytes. The historical assembler reproduces
those bytes without an explicit output patch or inserted instruction body.
The walker has the same naturally reproduced two-byte alignment tail.

The promotion proofs are retained under
`reports/agents/frame-input/camera-map/effect-children-promoted/`, with original
and candidate bytes, command receipts, and negative controls. Six controls
change one byte each; changing one facing interval produces a 180-byte output
with 42 differing or missing bytes and is rejected. Earlier semantic and
compiler-profile trials remain under the same ignored camera-map and renderer
report directories. The final renderer still has 18 differing bytes in its
1,400-byte candidate, and selected-map-tile loading remains unmatched. Those
bodies are excluded from matching C coverage.

This is compiler and static data-flow evidence. It does not establish gameplay
correctness, complete subsystem behavior, or a complete game inventory. Other
called bodies not yet accepted remain explicit original-ROM dependencies.

### Need-effect placement handoff

| Address | Function | Verified C bytes |
| --- | --- | ---: |
| `0x0802D8E4` | `frame_configure_need_effect` | 200 |

The placement helper consumes word arguments, stores the low byte of direction
at object `+0x12`, and narrows the two coordinates to signed halfwords. It asks
`0x3BA54` for a projected integer point. Failure uses the original narrowed
arguments, then the accepted position setter stores the coordinates in fixed
point form. The effect-state pointer at `+0x64` goes to predicate `0x2ECC0` with
mode 2. If that predicate succeeds, the helper converts the projected point to
a packed grid cell, looks up a nearby object through `0x2E5EC`, and passes a
non-null result to `0x7E68` with mode 1. The direct-callee role names remain
provisional; their reconstruction status follows the subsequent dependency
batch and the current manifest.

It enables object flag 1, calls `0x3B12C` with the registration context and mode
1, and returns that call's low byte after invoking the accepted
`frame_update_need_effect`. The final direction test writes the horizontal
flip bit at object `+0xD3`. The result is not the projection predicate's result.
The first candidate copied the requested point during fallback and kept two
long-lived aliases of the same object, which produced a 192-byte mismatch.
Explicit fallback values and one object alias match all 200 bytes without
register bindings. Those failed attempts and raw comparisons are retained in
the ignored `camera-map/need-placement-*` reports.

The saved-effect idle callback now calls the canonical placement name and
`frame_commit_need_effect`, whose 608-byte replacement belongs to the display
path. Its declarations use the observed word argument ABI. Rechecking all
seven saved-effect sources preserves their 2,684 matching bytes; their seven
changed-source controls still reject. The new placement control changes the
flip threshold from 4 to 3 and rejects a one-byte difference. Canonical and
negative outputs, header snapshots and command receipts are under
`reports/agents/frame-input/camera-map/need-placement-promoted/`.

This closes a compiler-verified handoff from the saved-effect state to placement
and display refresh. Grid registration still needs its own source evidence.
No additional runtime or gameplay validation is claimed.

### Placement projection and state lookup

| Address | Function | Verified C bytes |
| --- | --- | ---: |
| `0x0803BA54` | `frame_grid_project_effect_point` | 108 |
| `0x0802EC50` | `frame_need_effect_contains_cell` | 56 |
| `0x0802E5EC` | `frame_need_effect_find_neighbor` | 156 |

Projection first converts the integer point to the low two bytes of a packed
cell. Directions through 4 multiply each axis by registration `cell_size`;
larger directions choose the far end of that cell by adding `cell_size-1`.
The existing coordinate-to-point helper performs the final transform, and
only its return value 1 is accepted. The C reads the observed byte-sized field
at registration `+0x12`. Scoped arithmetic products preserve the original
evaluation order without register bindings; the initial equivalent expression
had 56 differing bytes, and the useful intermediate 14- and 6-byte mismatches
remain in the ignored reports.

Membership compares two coordinate bytes in ten records at state `+0xA4`,
with a four-byte stride. This is a bounded access view, not proof of a complete
state allocation or a count limit for other writers. Lookup traverses the
active need-effect state list at `0x03005868`, caches each next pointer, and
returns the first state whose membership test returns 1 and whose requested
action is available. It returns a `FrameNeedEffectState *`; kind at `+0x08`
and the shared pool-node layout establish this distinction. Placement's
neighbor local and the provisional `0x7E68` handoff target now use that type.
Those changes preserve placement's complete 200-byte match and its control.

The availability test checks the low halfword of state words at `+0xA4` for
action 1 and `+0x74` for action 4. Other actions scan five groups of five bytes
from `g_need_effect_action_sets[kind]+2`. No bound is inferred for `kind` or
the pointed allocation. Lookup contains the observed inline copy of the same
predicate reconstructed separately as `frame_need_effect_action_available`.
Its local group index is bound to `r3` only across call-free arithmetic and
loads. It uses the historical assembler for its original two-byte alignment
tail; the C contains no instruction body.

Each new function has a compiled and linked negative control changing a
direction or loop bound; each rejects one changed byte. All eight previous
placement and saved-effect sources were rechecked at 2,884 identical bytes,
and their eight controls still reject. The 22 canonical/control receipts and
raw comparison files are under
`reports/agents/frame-input/camera-map/need-placement-dependencies-promoted/`.
Grid registration at `0x3B12C` remains an explicit original body; the target
handoff's reconstruction follows below. This evidence does not establish runtime
or gameplay behavior.

### Placement cell rules and pattern rotation

| Address | Function | Verified C bytes |
| --- | --- | ---: |
| `0x0803BBA4` | `frame_grid_need_effect_cell_available` | 204 |
| `0x0803BC70` | `frame_need_effect_pattern_cell` | 132 |

These helpers are direct dependencies of the still-unconverted registration
body at `0x3B12C`. The cell rule reads the grid byte through two separate
`frame_grid_cell_data_pointer` calls. Its upper six bits are the existing
`occupied` view and its lower two bits the `terrain` view. Action 4 succeeds
before other tests. Other actions require terrain bit 0 or the incoming linked
flag; actions 1 and 3 reject occupied masks 61 and 21, action 2 requires occupied
mask 4 or the linked flag, and action 5 permits restricted terrain or linking
after its occupied-mask test. These are observed numeric rules, not inferred
gameplay labels for the action or terrain values. The restricted-terrain local
uses a semantic `r2` binding after both calls, across call-free tests only.

Rotation subtracts the pointed pattern's first two bytes from the supplied
column and row, calls `0x2F430` for two byte outputs, then applies direction
cases 1, 3, 5 and 7 before adding the packed anchor's two coordinate bytes.
Only the first dimension output affects this body. Direction remains a word
argument; the two result stores narrow to bytes. The dimensions helper's
reconstruction follows below; pointed pattern allocation types stay provisional.
Initializing the row from the input before subtracting its pattern offset
preserves the original saved-register lifetimes without any register binding.
Earlier 132-byte candidates with 10, 4 and 2 differing bytes are retained.

The following entry points at `0x3BC70` and `0x3BCF4` establish the complete
204- and 132-byte extents, including their two-byte alignment tails. The pinned
historical assembler reproduces both tails naturally; neither C source embeds
alignment bytes or an instruction body. Each new source has a compiled and
linked one-byte negative control, changing an occupied mask or the direction-7
offset. All three existing direct header consumers were rechecked at 412
matching bytes with three rejected controls. The ten comparison receipts are
under `reports/agents/frame-input/camera-map/need-validator-rotation-promoted/`.
Registration and the central renderer remain explicit unconverted dependencies.
This adds static and compiler evidence only.

### Pattern dimensions and bounds handoff

| Address | Function | Verified C bytes |
| --- | --- | ---: |
| `0x0802F430` | `frame_need_effect_pattern_dimensions` | 188 |
| `0x08007E68` | `frame_need_effect_handoff_bounds` | 96 |
| `0x0802EC88` | `frame_need_effect_increment_counter` | 12 |
| `0x0802EC94` | `frame_need_effect_decrement_counter` | 12 |

The dimensions helper scans the pointed pattern's 5 by 5 action bytes for
values 1 through 3, retaining the largest column and row. If none exists, a
second scan uses value 4. It subtracts the first two pattern bytes and stores
the resulting byte-sized dimensions plus one. Empty and undersized patterns
retain the observed byte wrap behavior; no validation or capacity assumption
has been added. The observed constant result is 1. Its word return declaration
is provisional because the accepted rotation caller ignores it. Preserving the
column's declaration initializer and an unsigned table index matches all 188
bytes with ordinary C. The initial candidate and useful 33- and 2-byte
mismatches remain in the ignored reports.

The handoff clears `before_step` at object `+0x98`. It reads the object pointer
from the supplied effect state at `+0x54`, adjusts that object's point at
`+0xA4`, and writes the same point at destination `+0x9C` and `+0xA4`. Nonzero
mode applies x minus one and y plus one; zero mode reverses those offsets. It
originally used a separate `FrameActorFinishBounds` view; the shared-owner
repair below replaces it with canonical `FrameObject` members. The lower/upper names and
coordinate units remain provisional, and the two equal output points alone do
not establish a complete bounding-box model.

Direct inspection corrects the earlier provisional interpretation of
`0x2EC88` as a neighbor-link writer: it only increments the state byte at
`+0xDC`; `0x2EC94` decrements the same byte. Both retain the unused second state
argument observed at their registration and unregistration call sites. The
counter's broader ownership role is not inferred. Its zero initialization is
also visible in the accepted state allocator. The wider state layout remains
the existing bounded access view.

All four new functions have compiled and linked one-byte negative controls.
Placement and rotation now call the canonical handoff and dimensions names.
The scene loader and scene initializer also use the separately reconstructed
palette reset's canonical name, `frame_reset_object_palette_slots`. Nine
existing consumers were rechecked at 2,120 identical bytes, with nine rejected
controls. The 26 canonical/control receipts and raw comparison files are under
`reports/agents/frame-input/camera-map/need-placement-small-promoted/`.
These are compiler matches and static data-flow findings. Registration, the larger renderer, and selected map-tile loading still have
their own excluded candidates; no runtime or gameplay claim is added.

### Removing need-effect registration

| Address | Function | Verified C bytes |
| --- | --- | ---: |
| `0x0803B4F0` | `frame_unregister_need_effect` | 336 |
| `0x0802EC18` | `frame_need_effect_contains_candidate` | 56 |

The reverse path clears the object's mode byte at `+0x82`, projects its signed
high-half position onto the grid, and walks the same pointed 5 by 5 action
pattern and direction transform as registration. A failed projection returns
before changing grid cells. Actions 1 and 5 remove mask 1, action 3 removes
mask 13, and action 2 searches for an action-3 neighbor. With a neighbor it
decrements that neighbor's `+0xDC` counter and registers mask 4; without one it
removes mask 61. These numeric masks and action roles follow the observed calls;
they do not identify gameplay concepts.

Action 4 scans the active state list, caching each next pointer before the
membership call. It excludes the object being removed. Mask 2 is removed only
when no other object's candidate records contain the cell. The separately
matched membership helper reads twelve four-byte records from state `+0x74`,
comparing only their first two coordinate bytes. This is a bounded access view,
not a complete effect-state allocation type. Registration's observed clearing
of 48 bytes at the same offset supports the record stride, while the writers'
count invariants and the wider state layout remain unresolved.

An explicit next-column local, computed after the inner index is initialized,
reproduces the original spill order. A semantic current-state pointer is bound
to `r2`; its last use precedes each call and the separately cached next pointer
survives the call. No instruction body or alignment bytes are embedded in the
new C. The next entry points at `0x3B640` and `0x2EC50` establish the complete
336- and 56-byte extents; the reverse path includes its original literal pool.
The useful 332-, 340- and 336-byte failed attempts and complete byte comparisons
remain in the ignored reports.

Both new sources compile and link identically, and both changed-source controls
reject by one byte. Ten existing consumers were rechecked at 1,112 identical
bytes, with ten rejected controls, including the accepted removal wrapper at
`0x2E1E8` (56 bytes). The 24 positive/control receipts are under
`reports/agents/frame-input/camera-map/need-unregister-promoted/`. The larger
renderer and selected map-tile loading remain excluded candidates. Registration
is reconstructed in the next batch below.
This closes the statically observed removal path; it adds no runtime claim.


### Registering need-effect cells and publishing their points

| Address | Function | Verified C bytes |
| --- | --- | ---: |
| `0x0803B12C` | `frame_register_need_effect` | 964 |

This closes the forward path from the accepted `frame_configure_need_effect`
caller through cell transformation, availability, grid masks, neighbor counters,
point handoff and the reverse removal path above. The same byte-return ABI and
address now replace the caller's earlier `frame_need_effect_register_3b12c`
alias. Names describe the observed data flow; they do not identify a gameplay
need or action. The entry at `0x3B4F0` and the complete comparison establish its
964-byte extent, including the original switch table, literal pool and alignment.

Mode 1 first calls the same function in mode 0 and requires result 1. That
validation pass also records target coordinates at state `+0xA4`; it is not a
read-only predicate. On success the outer call clears 104 bytes at `+0x74` and
sets the object's mode byte at `+0x82`. Both calls convert the signed high halves
of object position into a packed grid anchor, then walk a pointed 5 by 5 action
pattern through the already matched direction transform. Failed projection or
an unavailable cell returns zero at the observed stage. No rollback is added.

Action 1 and action 5 register mask 1. Action 2 increments an action-3 neighbor's
`+0xDC` counter when one is found, copies the neighbor object's state point at
`+0xCC` into that object's `+0xA4`, then performs the existing point handoff; it
registers mask 8 and removes mask 4. Action 3 uses occupancy bit 8 to choose an
action-2 neighbor and counter increment, or registers mask 4. Its occupied branch
preserves the original unchecked neighbor use. Action 4 registers mask 2 and
appends candidate coordinates at `+0x74`. Actions 1, 2, 3 and 5 append target
coordinates at `+0xA4`, including during mode 0. Action 0 and out-of-range action
values add no mask. These numeric masks remain the strongest supported labels.

After committing, the function reads cell extents for target coordinates, or
candidate coordinates if no target was recorded. The point at `+0xCC` receives
maximum x and minimum y; the point at `+0xD4` receives minimum x and maximum y.
The empty-set values remain `(0, 5000)` and `(5000, 0)`. The guarded registration
header records these observed offsets, twelve four-byte candidate records and
ten four-byte target records. Clearing lengths and existing membership readers
support those access views; this function adds no capacity clamp, and the
serialized patterns' count invariants and complete state allocation remain
unresolved. The words retain provisional `far_bounds` and `near_bounds` names.

Ordinary local near/far point records, initialized by component assignments and
published as complete points, reproduce the original paired transfers. Their
lifetimes also give the observed register and spill layout. The cell output
pointer is explicitly bound to callee-saved `r5` across the scan calls; candidate
x/y and target x use that pointer, while target y reads the packed local cell.
The equivalent unbound source remains a useful 964-byte candidate with 22
comparison differences. A small semantic table-access helper keeps the row and
column index calculation separate. No original instruction body or alignment
bytes are embedded in the C. The earlier 960-, 940- and 964-byte failed candidates,
raw mismatches, corrected post-counter neighbor reload and final lifetime trials
remain under the ignored camera-map reports.

The canonical replacement compiles and links identically. Changing the action-2
registration mask from 8 to 16 rejects by one byte. Eleven accepted consumers
of the placement header were rechecked at 1,448 identical bytes, and all eleven
of their real changed-source controls also reject by one byte. The 24 receipts
are under `reports/agents/frame-input/camera-map/need-registration-promoted/`.
This is a static and compiler-verified registration/removal subsystem path;
no runtime or gameplay claim is added. The larger renderer and selected map-tile
loading still retain excluded candidates.


## Registration division helper identity refinement

The 128-byte `frame_initialize_map_registration` (`0x48B78`) now uses ordinary
signed integer promotions for its `unsigned short` width/height and
`unsigned char` cell-size parameters. Inspection distinguishes signed division
at `0x0804CD2C` from the unsigned backend at `0x0804CED8`; the old
`__udivsi3` alias incorrectly described the signed callee. Removing the two
unsigned casts and binding `__divsi3` to the actual signed entry preserves every
linked byte and rejects the existing origin-offset changed-source control.
For the observed formal domains (width/height at most 65,535 and a nonzero
cell size at most 255), signed and unsigned quotients agree. Nonzero cell size
remains a caller precondition; no new zero check or runtime claim is added.
This source/alias correction contributes zero functions and zero coverage bytes.
The bounded raw helper comparison and before/after source proofs are retained
under ignored `reports/agents/vblank-wrapper/division-alias-audit/` and the fresh
`actor-attachment-controller-canonical/` receipts.


## Separate render-effect collection, stepping and drawing

Twelve connected replacements add 1,672 verified C bytes. The scheduler's
existing `frame_collect_objects` call now owns the 148-byte collector at
`0x305E4`; its `frame_finish_layer` call owns the 92-byte layer pass at
`0x31164`. The latter returns an integer whose value is narrowed from each
step's signed byte result. The scheduler ignores that result, so refining its
old provisional `void` declaration to `int` preserves all 648 scheduler bytes.
The existing scheduler's changed-source control also still rejects.

| Address | Function | Verified C bytes |
| --- | --- | ---: |
| `0x080305E4` | `frame_collect_objects` | 148 |
| `0x08030678` | `frame_step_render_effect` | 388 |
| `0x08030E24` | `frame_step_render_effect_animation` | 100 |
| `0x08030E88` | `frame_step_render_effect_linear` | 116 |
| `0x08030EFC` | `frame_step_render_effect_linear_alternate` | 116 |
| `0x08031098` | `frame_clear_render_effects` | 44 |
| `0x08031114` | `frame_step_uncollected_render_effects` | 80 |
| `0x08031164` | `frame_finish_layer` | 92 |
| `0x080311C0` | `frame_allocate_render_effect` | 60 |
| `0x080311FC` | `frame_destroy_render_effect` | 36 |
| `0x08031220` | `frame_draw_render_effect` | 428 |
| `0x080313CC` | `frame_render_effect_terrain` | 64 |

The allocation call passes 84 bytes to the generic intrusive pool. Its free
pool is `0x03001ED8`, active head is `0x030059E4`, count is `0x03001EE2` and
maximum is `0x03001EE4`. These differ from the published 72-byte transient
family's free pool at `0x03001EDC`, head at `0x030059E0`, count at
`0x03001EE6` and maximum at `0x03001EE8`. The adjacent active-head words are
separate pool heads; treating the second word as the first family's tail would
merge distinct allocations. The allocator increments count and maximum even
if the underlying allocation fails. No new null check or capacity clamp is
introduced. The pool calls retain explicit list/node view casts: their matched
implementations access only the intrusive first pointers.

The guarded `frame_render_effect.h` records the observed 84-byte access view.
It has resource pointer `+0x0C`, fixed-point origin `+0x10`, position `+0x18`,
velocity `+0x20`, OAM attributes `+0x28`, pointed tile indices `+0x38`, signed
countdown `+0x3C`, flags `+0x40`, tile base `+0x44`, signed animation counter
`+0x46`, and byte-sized frame/motion fields at `+0x48` through `+0x4E`.
The signed high-half position readers establish the pixel view at `+0x1A`
and `+0x1E`. OAM priority is also read through byte `+0x2D`, bits 2 and 3.
Unknown bytes and words stay explicit. This is an access layout supported by
allocation and matched readers; it does not establish a complete gameplay type.

The collector walks four priority bins and skips records carrying flag
`0x8000`. A record enters its priority bin, or the preceding bin when flag
`0x4000` permits it, and then receives `0x8000`. The layer pass steps the chosen
array backwards and clears that flag; the uncollected pass steps remaining
records and stops on signed result -1. Counts are bytes and destination-array
capacities remain unproven. Ordinary integer address accumulators retain the
observed pointer-addition roles; no assembly constraints are needed.

The main step expires countdown -1, advances animation or linear motion, and
selects stationary, sine-directed or circular position from flags 8 and 32.
Its direction remap at `0x08052870` indexes the already named component table
`g_frame_velocity_default` at `0x0804EB00`; the projected x calculation reads
the table's second component and y reads its first. Separate component locals
and a byte-offset address view reproduce the original lifetimes without
register bindings. Flag `0x80` suppresses terrain lookup. Terrain's top two
bits update OAM priority, while the low six bits are returned; terrain value 3
removes the record. Global flags `0x110000` suppress drawing. A signed draw
result -1 sets pending byte `0x03001EE0`.

The drawing function shares the existing sprite sequence/frame/part layouts
and OAM append path. It converts fixed-point position to signed pixels, applies
the selected camera origin unless flag `0x200` selects absolute coordinates,
and returns 2 outside the observed 240 by 160 origin rectangle. It walks the
frame's low-five-bit part count after its collider and attachment records,
adds pointed frame tile indices, and submits each OAM part. Its return is the
last append result narrowed through signed byte; an empty part list returns
zero and earlier append failures do not stop the loop. The clear function
caches each next pointer before releasing the current record.

All twelve complete extents, including literal pools and alignment, match.
The animation, two linear, drawing and terrain replacements use the pinned
historical GNU assembler profile to reproduce their original zero section
alignment naturally. The inventory's shorter animation/linear/terrain text
extents omit those two trailing bytes; the next entry's PUSH and raw comparison
establish the accepted 100-, 116- and 64-byte boundaries. The duplicated linear
functions remain two real, separate entry points. Useful modern-assembler and
ordinary pointer-index mismatches remain in ignored reports.

Fresh production-source proofs and twelve real changed-source controls are
under `reports/agents/frame-input/render-collection/promoted-current/`, along
with the 648-byte scheduler proof/control. Every control rejects. The guarded
new header imports the render layout once; transition camera declarations are
included only by the drawing source. This is compiler and static subsystem
evidence, not runtime or gameplay verification. The larger ordinary-object
renderer, selected map-tile loader and copied staging routine remain excluded
candidates.

### The adjacent 72-byte transient lifecycle

Three further connected replacements add 216 verified C bytes:
`frame_clear_transient_effects` at `0x3105C` (60 bytes),
`frame_step_transient_effects` at `0x310C4` (80 bytes), and
`frame_step_owner_transient_effects` at `0x3140C` (76 bytes). They use the
already published 72-byte transient record and its own active head/free pool,
keeping it separate from the 84-byte family above. The guarded transient header
adds only canonical declarations; the existing access layout is unchanged.

Clear walks the active head, caches next before releasing each node, and
reduces the 72-byte count. The general step skips nodes whose `+0x30` flags
carry `0x8000`, invokes the transient step, and clears that flag. The owner pass
invokes the step only when the owner pointer at `+0x08` matches its argument,
then sets `0x8000`. Both passes cache next across the call. They clear the
shared render pending byte at `0x03001EE0` inside the nonzero-count branch;
no new reset occurs when the count is zero. These observed calls connect the
72-byte update path to the separate render pool's pending handoff.

All three complete bodies, including original literal pools and alignment,
match the production header closure. Their actual changed-source controls
reject by two, two and one differing bytes. Raw proofs are retained under
`reports/agents/frame-input/render-collection/transient-promoted/`. This adds
static and compiler evidence only. The emitter and per-record updater are
reconstructed separately in the connected transient batch; the larger normal
object renderer remains excluded.
Five prior direct consumers of the transient header were also rechecked at
604 identical bytes, and all five existing changed-source controls reject.
Their fresh receipts are under the adjacent `transient-prior-current/` reports.

### Scheduler affine commit handoff

The scheduler's former `frame_finish_display` alias names the already matched
`frame_commit_affine` at `0x0802D010`. The canonical call retains the observed
`void (void)` ABI. After completing four display layers, the scheduler commits
the active affine parameter slots into both OAM banks through that routine.
This is a static connection between existing replacements and adds no C
coverage or runtime evidence. The shared frame header's layout is unchanged.

Both accepted sources that refer to either old or canonical identifier were
recompiled at their complete original extents: the scheduler's 648 bytes and
the affine commit's 68 bytes. Both match; their actual existing source controls
reject by 54 and 25 bytes. Receipts are retained under
`reports/agents/frame-input/renderer-resume/scheduler-affine-alias-current-*`.
The copied ARM sorter at `0x0800B840` and normal object renderer remain
unconverted candidates.

The connected `frame_write_affine_matrices` wrapper at `0x0804C8E0` is now
explicit Thumb assembly glue: the observed `SVC 0x0F` handoff followed by return.
Its complete extent is four bytes, ending before the next wrapper at
`0x0804C8E4`; it contains no literal pool or alignment tail. The existing
four-word ABI is inferred from the commit routine's two calls, which supply
the parameter table, destination, slot count and stride eight. The BIOS
implementation itself is outside the game ROM and remains unexamined here.

The linked four-byte extent is identical at its original ROM address, and
changing the service identifier from `0x0F` to `0x0E` rejects by one byte.
Source, linked bytes, boundary evidence and actual control receipts are retained
under `reports/agents/frame-input/renderer-resume/affine-svc-glue-current-*`.
This adds four verified glue bytes and zero C bytes; it establishes no runtime
or gameplay claim.

### Resource owner-slot handoff

`resource_set_object` at `0x0800AF34` adds 44 verified C bytes. Starting from
the resource root stored at `0x03002ED8`, it reads a halfword offset from
`root + 2 + group * 2`, then a second halfword offset from the selected group's
`data + 2 + slot * 2`. It stores its object pointer in the selected entry's
first word. Both indices are observed byte arguments. The function performs
no bounds check or special handling for index `0xFF`; storage size and entry
alignment remain caller and data-format preconditions.

The existing `frame_remove_object` calls this setter with a null pointer when
the object's flags have their signed high bit set, using the owner group and
slot bytes. The former `frame_drop_owner` name described that one use rather
than the callee's general operation. The canonical setter name and pointer
argument now reflect the actual word store. Resource builders and the paired
`resource_get_object` accessor below support this owner-slot interpretation.
No object or resource layout changed.

The accepted extent contains 38 instruction bytes, two zero alignment bytes
and the four-byte root literal. The next function begins at `0x0800AF60`.
Separate group and slot offset values, with table pointer views scoped to their
respective lookups, reproduce the original allocation without register
bindings. The real slot-stride control changes `slot << 1` to `slot << 2` and
rejects by one byte. The existing removal function also matches all 140 bytes
with its current header closure, and its existing source control rejects by
one byte. That caller recheck adds no C coverage.

Complete source, raw comparisons, boundary evidence and actual controls are
retained under `reports/agents/frame-input/renderer-resume/resource-owner-*`.
This is static and compiler evidence only; no runtime or gameplay behavior has
been verified for this handoff.

The paired `resource_get_object` at `0x0800AEE4` adds 80 verified C bytes. Its
entry explicitly narrows both argument words to bytes. The canonical C formal
spelling is now unsigned word, with observed byte indices retained locally;
the original source's formal spelling remains provisional. Ordinary entries
read the same two halfword offset tables as the setter, then return the first
pointer word. Group zero and byte slot `0xFF` instead select the view context
at `0x030040E0`, with the observed `(unsigned char)(0xFF - slot)` index and
12-byte slot stride. For that branch the narrowed index is zero; no additional
view-index validation or resource-table bounds are inferred.

One shared data pointer represents both paths. Its view address is expressed
as an unsigned 32-bit offset plus the context address, consistent with the
fixed ARM address space. Word local indices retain the argument-narrowing
order and avoid redundant narrowing after the context lookup. The final
source matches without register bindings. Failed byte-formal candidates,
separate pointer views and bound-pointer minimization attempts remain local
evidence rather than accepted source.

The getter's complete 80 bytes include both original literals and two separate
two-byte zero alignment spans. Changing the special-path threshold from
`0xFE` to `0xFD` rejects by one byte. All 106 previously accepted consumers of
the changed resource header, totaling 10,080 bytes and including 22 direct
getter callers, were recompiled with their actual changed-source controls;
every positive matches and every control rejects. Fresh setter, getter and
removal proofs also pass, totaling 124 new C bytes across the paired entries.
These receipts are under the adjacent `resource-owner-pair-canonical-*`
reports. Header and caller rechecks add no coverage or runtime evidence.

The connected player spawn lookup at `0x0800AE68` adds 84 verified C bytes.
It selects an eight-byte default record from `0x08D70AC0` using the slot byte,
then searches the arena rooted at `0x03002EE8` for the first record with the
requested group and slot. The arena count is the halfword at offset two;
records begin at offset four with an eight-byte stride. The already matched
arena copier at `0x0800AFA8` copies precisely that header and word-pair stride.
The player constructor reads the returned signed x/y halfwords and direction
byte, while the lookup proves the group and slot bytes at offsets four and
five. Those names replace the two unknown bytes without changing the existing
eight-byte resource layout. The byte at offset seven remains uninterpreted.

The search retains an eight-bit index and its original wrapping behavior. No
arena count bound, default-table extent or index validation is inferred. Its
count snapshot is used first by the nonempty check and then retained for the
loop; this ordinary C lifetime reproduces the original single load without
register bindings. The complete extent includes 74 instruction bytes, both
four-byte literals and two zero alignment bytes. `0x0800AEBC` starts a separate
40-byte accessor and is excluded from this replacement.

Changing the group equality test to inequality rejects by one byte. All 20
previously accepted consumers of the refined scene player header, totaling
4,784 bytes and including the 456-byte player constructor, still match with
their actual changed-source controls rejected. These rechecks add no coverage.
Fresh sources, controls, complete raw comparisons and boundary evidence are
retained under the local `resource-spawn-canonical-*` reports. This is static
and compiler evidence; runtime and gameplay behavior remain unverified.

### Resource payload to saved-effect construction

`resource_get_object_payload` at `0x0800AEBC` and
`frame_create_scene_saved_resource_effect` at `0x08033580` add 80 verified C
bytes together. The accessor narrows its argument words to group and slot
bytes, walks the same two halfword offset tables as the owner-slot getter and
setter, then returns the selected entry plus eight bytes. Unlike the object
getter, it has no special `0xFF` path. The entry's first eight bytes hold the
runtime owner pointer and an uninterpreted word; the returned region begins
at the already observed factory selector. No table bounds, full record length
or additional alignment guarantees are inferred.

The saved-effect caller reads signed x/y halfwords at payload offsets four and
six and the kind byte at offset eight. It converts the coordinates to the
observed 16.16 word representation and passes those values to the already
matched `frame_create_scene_saved_effect` constructor. The local partial
payload view names only these reads; its first four bytes remain uninterpreted.
Returning the constructor's pointer preserves the observed R0 result, while
the original caller's source-level return spelling remains provisional.

Separate group and slot byte offsets and scoped table views reproduce the
accessor's register allocation without bindings. Its complete 40-byte extent
includes 34 instruction bytes, two zero alignment bytes and the resource-root
literal at `0x0800AEE0`; `resource_get_object` begins at `0x0800AEE4`.
The connected caller's 40 bytes are all instructions, ending before the next
entry at `0x080335A8`. It also matches without bindings. Changing the returned
payload offset from eight to ten rejects by one byte; increasing the passed
kind rejects by 31 bytes. Both controls are compiled source changes.

The current static inventory records 30 direct callers of the payload
accessor. This batch converts the saved-effect caller among them; the other
29 bodies remain explicit unconverted regions. That inventory is incomplete,
and these counts describe its current mapped evidence rather than all game
callers. The new guarded declaration header changes no existing accepted
header closure. Canonical sources, raw comparisons, boundaries, caller rows
and real controls are retained under the local `resource-payload-canonical-*`
reports. This closes an offset-table-to-payload-to-constructor path using
static and compiler evidence; it establishes no runtime or gameplay claim.

## Timed resource-object factory and callbacks

The six connected replacements at `0x0800A258`, `0x0800A3D8`,
`0x0800A534`, `0x0800A624`, `0x0800A65C` and `0x0800193C` add
1,188 verified C bytes: 384, 348, 240, 56, 100 and 60 respectively.
The factory occupies observed pointer-table slot 21 at `0x0804F278` and installs
the tick and interaction callbacks. These names describe observed clock,
resource and movement handoffs; they do not establish a gameplay character's
identity or a complete factory-table inventory.

The factory uses the accepted two-offset-table payload reader and the 320-byte
object allocator. Its partial payload has an ID word, signed X/Y halfwords at
`+4/+6`, kind/direction bytes at `+8/+9` and activation group/slot bytes at
`+10/+11`. It initializes the two callback pointers, direction and animation,
then chooses a destination offset using two random values from 1 through 25.
The unsigned direction quadrant selects signs in pairs 0/1, 2/3, 4/5 and the
remaining values. No index or quadrant clamp is introduced. Coordinates are
stored through unsigned fixed-point arithmetic, retaining the original word
wrapping behavior.

Kind zero copies twelve uninterpreted bytes from `0x0804F128` to object `+0x40`,
sets flags `0x80000011`, speed `0x20000` and palette slot six, then checks the
start/end records at `0x0804F134`/`0x0804F13C` against the accepted world clock
at `0x03003958` with minute/hour mask six. A false byte result disables flag
one. Kind one sets flags `0x80050651`, palette slot two, state nine and variant
state seven, initializes observed halfword timers at `+0x5E` and `+0x68..+0x6E`,
and clears the interaction callback. Other kinds retain the common setup.
Both successful branches finish through the accepted actor-state update.
The animation table has two variant-record pointers per observed eight-byte
kind row; its complete length remains unknown.

The tick routes nonzero kinds through the accepted actor dispatcher. Kind zero
state zero repeats the clock gate before patrol; state one sets flag two and
activates the group/slot read from the same resource payload, then returns.
The common path captures direction and the initial pending mask eight, retains
the actual pending-byte pointer across calls, rebuilds velocity if needed,
selects idle or moving animation and refreshes/stops motion for masks four and
`0x12`, updates OAM X-flip according to direction greater than four, and clears
the pending byte. A separate initial-mask snapshot matches the original
pre-call load while later tests reload the byte after calls.

Patrol handles variant states seven, nine and two. State seven decrements its
signed countdown and, at minus one, measures distance to the object selected
through `0x030040E0`; distance's integer part at most 49 begins movement state
nine with countdown 60, otherwise countdown becomes 20. State nine compares
its destination direction with the current byte, records a changed direction
and pending bit 16, or chooses another destination when the countdown expires.
Direction eight changes to state seven and chooses a new destination away from
the selected object. State two resets to state seven and a random destination.
The paired 60-byte direction helper subtracts the second integer-position
snapshot from the first, unlike the accepted direction-toward helper at
`0x0800188C`. An initial private trial incorrectly reused the toward name for
`0x0800193C`; raw subtraction evidence corrected that alias before publication.

The two-object interaction callback compares next-position distance, accepts
only target ID zero and changes variant state to nine when the distance is
within `(object_byte_AE << 16) + 20`. The byte at `+0xAE` remains neutrally named;
its role in the general object/collision layout is not established here. The
partial timed-object view ends after observed OAM bytes at `+0xD0..+0xD7` and
does not redefine the allocation size or prove limits for the copied work,
kind table, active object pointers or signed countdown.

All six sources match without register bindings. Expressing kind/state as
switches preserves the original branch layout; sharing the actual chosen
quadrant across two patrol branches preserves the original result lifetime.
The factory includes 40 literal bytes and two zero alignment bytes; the tick
includes 28 literal bytes and four internal zero alignment bytes; patrol
includes eight literal bytes. The interaction and direction helpers each
include two trailing zero alignment bytes. The destination extent is all code.
Complete raw expected/linked bytes, local header snapshots, compile receipts,
useful failures and changed-source controls remain under the ignored
`reports/agents/frame-input/renderer-resume/resource-time-factory-*/` path.
Controls change initialization flags, pending-mask selection, distance limit,
interaction threshold, destination range and subtraction direction; all
compile and reject. Static connectivity and exact full-ROM replacement remain
separate from runtime execution and gameplay behavior, which have not been
validated for this path.

## Scene-selector resource factory and clock/notice callback

The paired factory at `0x08026C8C` and callback at `0x08026E6C` reconstruct
480 and 524 complete bytes, adding 1,004 verified C bytes. The observed factory
pointer is slot three of the same table at `0x0804F278` used by the timed-resource
path. This identifies a connected selector path, rather than a complete table
inventory or a proven gameplay identity. The factory payload supplies an ID
word, signed X/Y halfwords at four/six, half-width/half-height bytes at eight/nine,
a parameter/selector at ten/eleven and a subtype byte at twelve. No complete
payload length or subtype-table bound is inferred.

The factory suppresses creation when the current scene word is two, the payload
selector is thirteen and mask `0x2` of the save-header halfword at `+0xC` is clear.
Otherwise it uses the accepted scene-object allocator and immediately initializes
the result, preserving the original absence of an allocation-failure check.
It assigns ID/subtype, flags `0x000A0404`, state zero, the selector/parameter work
fields and the step/interaction callbacks. Subtypes two, five, three and four
independently select the four observed animation records, palette slots and
OAM layers; subtype four selects the alternate interaction callback. Other
subtypes retain the common initialization. The active primary list is then
walked to clear bit zero of each object's byte at `+0x50`, and the two clock-hour
bytes at `+0x67/+0x68` are cleared. Those work fields are selector-specific.

This constructor writes one collision record: count one at `+0xAF`, signed
X endpoints at `+0xB0/+0xB1`, signed Y endpoints at `+0xB2/+0xB3`, and kind one
at `+0xB4`. The endpoints come from the negated and positive serialized
half-extents. These writes corroborate the copied ARM collision dispatcher's
six-byte records and first-four-byte endpoint interpretation. They establish
count one for this constructor, without proving a global count limit. The
new partial selector view keeps these fields distinct from the registered
bounds at `+0xBC..+0xBF` in the general frame view and does not alter that layout.
Its observed view ends after OAM at `+0xD7`; the scene allocator still supplies
320 bytes. Values outside the signed-byte endpoint range remain unchecked.

The callback copies the eight-byte record at `0x08051AA4` twice and dispatches
through a nineteen-entry table after guarding its state byte at `+0x4D` against
values above eighteen. State zero handles variant one countdown completion or
variant eleven flag completion. The latter updates the scene-mode byte,
resolves the selected actor and submits the selector through the accepted
queued scene handoff. State one uses the accepted actor dispatcher, state
three decrements the countdown and restores state zero at minus one, and state
eighteen uses the selector completion helper reconstructed in the handoff follow-up below.

State four substitutes the two work-byte hours into the clock snapshots,
formats each into a twenty-byte local staging buffer, and copies the strings
to text fields one and two. The original formatting API supplies no output
bound; the local buffer size is not a proven formatting limit. It prepares the
existing result/notice byte views, looks up a text ID through the halfword table
at `0x080577FC`, copies text field zero, submits default request two, updates
its indicator's direction/animation/variant and enters state five. That state
requests indicator state sixteen, clears the pointer, sets countdown sixty and
enters state three. No missing-pointer check or additional state behavior is
introduced. The selector-label table length remains unknown.

The clock assignment replaces bits sixteen through twenty-three of the first
word while preserving the other bits. A local unsigned-word hour bitfield view
expresses this observed update and matches naturally; it does not establish
the original source spelling or change the shared signed clock record used by
the formatter. The entire callback matches without register bindings. The
factory also matches without bindings. Its complete extent contains 430
instruction bytes, 48 literal bytes and two internal zero alignment bytes;
the callback contains 392 instruction bytes, 128 literal/jump-table bytes and
four internal zero alignment bytes. The next callback begins at `0x08027078`.

The unconverted actor-selection wrapper at `0x0804559C` forwards both argument
words unchanged to `0x080457F4`. That body retains them in full-word registers,
performs unsigned scene/selector comparisons and forwards the selector without
byte narrowing. Accordingly its provisional declaration is refined from
`(void *, unsigned char)` to `(unsigned int, unsigned int)`. The existing script
command explicitly casts its retained same-address scene-context value to a
word; its bytes and behavior remain unchanged. This corrects the call view
without claiming reconstruction of either callee. All accepted consumers of
the changed command header, including any indirect consumers, are recompiled
with their actual changed-source controls.

Both new initialization/tested-flag controls compile and reject by one byte.
Raw complete bytes, include/source snapshots, literal and jump-table evidence,
ABI observations, useful failed word-update expressions and compiled controls
remain in the ignored `factory-followup-evidence-*` reports. Exact static and
compiler findings do not establish runtime execution or gameplay behavior.

## Selector interaction, player activation and completion handoff

Five connected helpers add 828 complete matching C bytes: the primary interaction
at `0x08010C18` (404), the alternate interaction at `0x08027078` (180), completion
at `0x0802712C` (180), player activation at `0x0802FB40` (52) and release at
`0x0802FB74` (12). The accepted selector factory installs the two interactions;
its tick calls completion and release. Alternate interaction calls activation.
These caller aliases now use the reconstructed names, with no duplicate coverage.

Primary interaction sets the byte at world `+0x42F` before testing object state
zero. It accepts ID-zero targets in states sixteen or twenty-seven, and subtypes
one through three or five additionally require bit zero of the pressed-key
halfword selected by object byte `+0x13`. A nonzero second-hour byte enables the
ID-twenty clock-window test: the signed hour is read from the established clock
at world `+8`, with a separate midnight-wrap comparison when first hour is at
least second hour. Failed clock gating clears the target state, requests selector
state four and records the target as its indicator. Equal hour endpoints retain
the observed wrap-branch behavior; no new interval policy is imposed.

World mode byte `+0x42E` restricts selector values above fourteen. Subtype two
queries the already reconstructed `condition_is_complete(2,4,2)` at
`0x0802A7C4`; it does not call the differently addressed condition-completion
mutator. Subtypes two and five coordinate cue forty-seven, variant eleven,
flag changes and target motion stop. The subtype-five check reloads the field
after the subtype-two calls, preserving possible callback mutation. Other
subtypes resolve the actor and submit the selected scene request. No table,
input-channel, pointer or allocation bounds are added.

The same-layout partial selector header exposes the input index at `+0x13`,
the world clock at `+8`, mode/flag bytes `+0x42E/+0x42F`, and the previously known
selection byte at `+0x748`. Names remain provisional. Alternate interaction
uses the established shared input root at `0x030040E0`: four twelve-byte player
slots precede the local-player byte at `+0x31`. A local access view joins these
already observed overlapping prefixes, without declaring a complete input
record or adding a local-player bound. It snapshots the low-byte bit-zero key
press for the selected player's input channel before the facing/ID checks.

Alternate interaction moves the active player to the signed high halfwords of
the selector's 16.16 X/Y position, activates flag one and assigns OAM layer minus
one narrowed to a halfword. Activation retains the low two layer bits and shifts
the coordinate words by sixteen; release clears flag one. The countdown becomes
three, and a pressed key requests selector state eighteen, sets target state zero,
records the indicator and clears the input state. Completion first stops the
indicator's motion, then handles variant zero notice creation or variant
fifty-five request completion. A previous request parameter of all ones cancels
and restores selector/indicator states and animation; other values submit the
selector. Notice/result meanings are inferred from this handoff, not runtime
UI observations.

Four functions match without register bindings. Primary interaction retains two
semantic boolean bindings in a small inline input-requirement query: its computed
result uses R3 and the caller's captured result uses R1. Both values are consumed
before any call. Removing either binding changes allocation and fails the complete
comparison; these controls of source form and the remaining ordinary variants are
preserved locally. This does not establish the original source spelling. Its
shared exit labels preserve the observed subtype reload and scene-submit routes.
An inline access view retains the two-`FrameObject *` callback signature without
requiring an incompatible function-pointer assignment.

All five actual changed-source controls compile and reject. They alter the
selector restriction, countdown, cancellation decision, activation bit and
release bit. Whole extents include all pools and zero alignment: primary
interaction contains two literal-pool groups; completion and alternate interaction
have their complete tails, and activation includes two trailing zero bytes before
the next prologue. Static byte boundaries and connection evidence are retained
with the useful failed attempts under ignored `factory-followup-evidence-*`
reports. The existing factory/tick are freshly recompiled with their own actual
controls against the refined header. Compiler/static results remain separate from
runtime and gameplay behavior, neither of which has been validated for this path.


### Variable serialized frame tails and alignment

The sprite sequence exposes its variable halfword-offset tail at byte twelve
using the pinned compiler's GNU89 zero-length-array extension. Its measured
prefix changes from sixteen bytes to twelve, retaining four-byte alignment
and every existing scalar offset. The sprite and animation frame views use
zero-length following-record tails at byte ten. Explicit packed, two-byte
alignment makes both measured frame prefixes ten bytes rather than the prior
twelve-byte, four-aligned declarations. Scalar widths and offsets are unchanged;
this declaration repair earns zero new C bytes.

The alignment change follows actual pointer producers. The accepted scene
resource constructor indexes sixteen-byte records and passes each record's
sequence pointer to animation readers. In the observed resource prefix zero
through 267, all 268 sequence roots are word-aligned. Their 317 frame roots are
halfword-aligned, and 288 are not word-aligned. The plain four-aligned frame
views therefore exceeded the alignment of these actual records, even though
the earlier function bytes matched. Pinned compiler diagnostics reject the
former declarations at an actual frame address as well as wrong widths and
packing. These observations are a bounded scene-resource check; they do not
establish every serialized resource, complete capacity or gameplay behavior.

Every current matching importer of the affected headers is freshly compared
with its actual changed-source control. Existing bodies and their C credit do
not change. The renderer remains unconverted; correcting these real type
relationships does not turn a near-match into a verified function.


### Shared owner for frame ordering points

The object words at `+0x9C`, `+0xA0`, `+0xA4` and `+0xA8` now belong to
`FrameObject.spatial.bounds.lower` and `.upper`, using the existing signed
`FramePoint` type. The union retains the original 32-byte byte view; its last
16 bytes remain unknown. The object still measures 312 bytes with four-byte
alignment. This is a bounded interpretation of four observed coordinate words,
not a declaration of a complete collision or rendering model.

The 104-byte resource callback supplies direct producer evidence: it passes the
lower point to the projection routine at `0x08048BF8`, then copies lower to upper.
Its other branch writes zero X and the signed integer part of the object's Y
position to both points. The projector can return without writing output; no
new initialization or success guard has been introduced. Its historical return
type and the coordinate names remain provisional. Need-effect registration,
center calculation and handoff consume the same two points. Actor creation,
state changes and interaction update these members through the same owner.
State twenty-seven copies the established 20-byte callback-and-points span
through character pointers and the compiler's representation-copy builtin,
replacing a foreign structure lvalue at `+0x98`.

Nine previously accepted functions, covering 3,240 C extent bytes, retain
identical full spans under ordinary and strict compiler checks. Each has a
compiled changed-source control. Target-compiler fixtures preserve every
previously named object member and bitfield, and the remaining members of the
partial actor-effect view. Wrong callback types, capacity, offset and signedness
are rejected, including same-size header mutations. This repair adds zero new
functions and zero C bytes. Other partial access views and their ownership
assumptions remain explicitly unresolved.

The ordinary finalizer was retried against these actual members and emits
340 bytes for the original 348-byte span. It remains unconverted and earns no
C credit. Earlier register-bound near-matches do not establish ordinary source
reconstruction. The renderer is also unconverted. These are static and compiler
results; runtime and gameplay behavior have not been established.

Two ordinary early-exit comparators now test actual pointers to cached geometry.
Separate addressed points retain backing but emit 360/313; one local two-point
cache recovers lower/upper order without a per-iteration copy but emits 352/258.
LOOP hoists pointer/value consumers into extra homes, leaving 32 local frame
bytes against native 28 and displacing the naturally obtained register roles.
Both complete sources and changed-source controls remain nonmatches; preserving
backing alone does not recover the native geometry observations.


### Complete display-part record ownership

The four display-part records now have one canonical layout at object offsets
`0x104`, `0x110`, `0x11C` and `0x128`, with a 12-byte stride. Each record owns
flags, palette and order bytes, its existing byte-count/index halfwords at
`+4/+6`, and the variant pointer at `+8`. The old partial view began at
`0x108`, inside the first record, and crossed later record boundaries. Group
and variant selectors occupy `0x134/0x135`; the object remains 312 bytes with
four-byte alignment. No unsupported volatile qualification remains on these
ordinary fields.

Target-compiler layout fixtures preserve all unrelated member offsets and
bitfield masks. Nine connected functions covering 2,980 C extent bytes retain
full equality and reject their compiled changed-source controls; the full
matching gate also revalidates every accepted function. This repair adds no
C credit. The truthful renderer baseline still fails at 1,404 bytes for its
1,400-byte slot; the existing valid 1,400-byte, 25-difference frontier remains
private. The finalizer remains unmatched. Neither this layout evidence nor
whole-ROM equality establishes runtime or gameplay behavior.


### Motion parameters and fixed-point helpers

The 16-byte routine at `0x08003568` copies three words into the canonical
object's 12-byte phase, rate and amplitude span at `+0x40`. Its builtin
representation copy uses the complete object's character view. It requires a
live 312-byte destination, readable initialized source backing, word alignment
and no overlap; the array parameter does not enforce capacity. Fourteen
instruction bytes and two zero alignment bytes match at the original address.

Three adjacent math helpers add 56 C extent bytes. At `0x08027304`, the signed
short denominator divides 65536 and the result narrows to a signed short before
promotion to `int`. At `0x0802733C`, the unsigned word representation of the
numerator shifts left sixteen bits before signed division. At `0x08027348`,
the quotient of 65536 shifts left sixteen bits as an unsigned word. The latter
20-byte extent includes two zero alignment bytes. Target-defined narrowing
and unsigned-to-signed conversions preserve the observed word representations;
unsigned shifts avoid overflowing or negative signed left shifts.

All three call the already owned software `__divsi3` at `0x0804CD2C` through
the existing `display_divide` declaration. Its zero-divisor path is preserved;
no new guard or assembly exception is introduced. The separately owned BIOS
division glue is at `0x0804C8C8`. Normal and strict compiler checks compare all
four full spans and reject actual changed-source controls. Target layout and
actual-definition API checks also reject wrong contracts. Syntactic Thumb-call
and exact entry-word searches found no incoming sites for these four routines;
computed targets, historical APIs and runtime execution remain unproved.


### Two unrooted input helpers

The provisional entry at `0x0801F574` takes a writable byte and replaces it
with its logical negation. The full 20-byte extent has no literal pool. The
chosen `void(InputU8 *)` interface describes the observed operation and return
sequence; incoming callers, additional unused parameters and original names
remain unidentified.

The separate entry at `0x0801F588` reads bit `0x200` of
`g_input_pressed[player]` at `0x03004228`. When the bit is set, it increments a
word below the supplied maximum. At or above the maximum, a nonzero wrap byte
replaces the word with the supplied minimum; otherwise it leaves the word
unchanged. It always returns the word. There is no decrement branch, minimum
comparison, ordering check between the bounds or added index guard. Its full
64-byte extent includes the original literal word and two zero alignment bytes.

The chosen interface uses `InputU32 *`, two word bounds and two byte parameters.
The fifth parameter's low-byte handling is preserved. The canonical pressed
array has four halfwords: the C view requires `player < 4` and a live, aligned
word object, but no incoming caller establishes that complete domain. The byte
helper likewise requires valid writable byte backing. Adjacency supplies no
shared lifecycle or runtime-root evidence.

Both complete spans match under the normal and strict compiler profiles. The
changed-source toggle controls contain twelve bytes against twenty and reject
at all twenty positions, including the eight missing bytes. The counter
controls retain 64 bytes and differ only at offset 24. All four actual type
cases pass their intended outcomes and twelve layout/type facts hold. The
fresh full gate checks the final header, all owned source/control pairs and
whole-ROM equality, including rejection of the changed-source whole ROM.

The actual source controls change logical negation to truth normalization and
select pressed bit `0x100` instead of `0x200`. Actual-definition type checks
cover the chosen interfaces and reject a word-pointer toggle, a byte counter
result and a word fifth parameter. These checks establish neither historical
unused arity nor all caller, callback, index, lifetime or gameplay domains.
