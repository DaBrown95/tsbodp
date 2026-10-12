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
RAM calls explicit and preserve the original interworking thunks. Their bodies
remain unconverted ARM code and receive no C credit.

The initializer at `0x109C` provides static source and size evidence for both
RAM copies: ROM `0xB840` to RAM `0x03002900`, 71 words / 284 bytes; ROM `0xB0E8`
to RAM `0x03002A20`, 160 words / 640 bytes. Each call passes the corresponding
word count plus CpuFastSet control bit `0x04000000`. This establishes copy
mapping, not runtime execution or a decompiled dispatcher.

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
