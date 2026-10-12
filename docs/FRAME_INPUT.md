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
