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
provisional 812-byte code/helper span is copied with 36 bytes from that next
function. The second span contains internal register-based helper calls and
carry-sensitive bit-reader operations, so its entry boundaries and internal
interfaces require separate reconstruction. Neither code span is represented
by an embedded instruction body or credited as matching C. Raw copy words,
ARM disassembly, inferred entry signatures and boundary distinctions are retained
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
`0x03001FCC`. Their provisional single argument selects an eight-byte view
coordinate pair within a map record. Static ARM disassembly finds 320- and
216-byte spans ending in returns, so the install copies also include 16 and
12 bytes from the next ARM entries respectively. The second following entry
is the tile allocator already reconstructed separately. These copy sizes are
installation facts, not additional reconstructed C coverage. Raw disassembly,
literal triples and provisional signatures are retained in the ignored
`map-copy-evidence.json` and `map-copy-original.txt`.

All four accepted linked images match, including pools and alignment. Their
changed-source controls reject by 19, 1, 1 and 1 bytes respectively. The prior
sixteen camera/map and decoder replacements and their controls were recompiled
against the refined record and canonical heap declarations; all retained their
matches and rejected their edits. Evidence is under `camera-map/map-lifecycle/`.
The larger selected-tile consumer at `0x39CF0` remains a semantic C candidate
with mismatching bytes and is excluded from coverage, alongside the copied ARM
map bodies. No runtime display-memory restore or map drawing has been validated.


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
analysis. Allocation failure checks are absent in this path. The initializer,
selected-tile loader, copied map staging body and central renderer remain
explicitly unconverted and receive no coverage from this batch.

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
