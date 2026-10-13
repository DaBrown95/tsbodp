# Game audio coordination evidence

The first accepted game audio slice contains two C functions, 260 bytes:
`audio_play_animation_cue` at ROM `0x40FFC` (220 bytes) and
`audio_sync_game_state` at `0x41534` (40 bytes). Each complete extent,
including its literal pools and alignment, matches the fixed reference.
Changed-source controls alter the cue variant limit and handoff mask;
both compile and fail the byte comparison. These are static/compiler
claims; no runtime or audible-output test has been performed.

The animation command decoder's `0xF6` operation calls the cue dispatcher.
The dispatcher reads a four-byte record at `0x08D73B9C`, checks the sample
volume byte at `0x03005D98`, and dispatches record kinds 1 and 2. Kind 1
uses a four-byte sample/step record at `0x08D73708`; kind 2 selects one of
eight such records per group at `0x08D73A7C`, with sample ID 255 suppressing
playback. The helper at `0x08035450` narrows its limit to 16 bits and scales
a masked 15-bit value returned by `0x080355AC`; passing 7 selects 0 through
7. Its random interpretation is inferred from that arithmetic. The
caller explicitly narrows the result to a byte. Array counts beyond the
observed eight-record group are not established.

Both cases look up a sample pointer in `0x08D54690`, call the Thumb
`0x4C878` thunk into copied ARM code at `0x030002EC`, and pass the returned
handle plus a 16-bit step value through `0x4C88C` to `0x030003E8`. The
latter validates the handle against a 44-byte channel record, shifts the
step left by two, and preserves its direction sign. Sample, pitch and
handle names remain provisional. The copied ARM step setter is now separately
reconstructed below; the playback body and Thumb thunks remain explicit
original regions and receive no C credit.

Before playback, the dispatcher sets bit `0x80` in the shared control
byte at `0x03007366`. VBlank defers the audio step while that bit is set
and records the deferral in bit `0x40`. The accepted synchronization helper
runs `vblank_audio_step` if bit `0x40` is set, then clears bit `0x80`.
That step thunk enters the copied frame mixer at `0x03001080`; the mixer
remains unmatched; its ring-buffer acquisition function is reconstructed below.
The control view preserves a volatile eight-bit bitfield only for the
flags. Ordinary bytes at offsets 4 and 5 are the pacing and sequence ID
views observed by scene/audio callers. These are partial views, not a
complete declaration of the audio state.

The scene sequence selector at `0x411BC` has a semantic candidate with
one remaining instruction mismatch and receives no coverage credit.
Further connected targets are that selector, sequence start `0x4A808`,
the VBlank frame mixer and the channel/envelope timing routines. Failed
compiler and structure experiments are retained in ignored local reports.

## Game volume and playback controls

Six further functions at `0x412EC`, `0x41308`, `0x41340`, `0x41398`,
`0x413C8` and `0x413FC` contribute 228 verified C bytes. The two volume
setters narrow their input to a byte, call the mixer/player volume
implementation, and save the result in the game options at offsets 8 and
9. The sample mixer clamps its global volume to 255; the sequence setter
passes a zero fade argument. Inspection of those callees corrects the
earlier provisional enable/tempo interpretation: these are volume levels,
and zero also suppresses their respective playback/control operations.
The two resource command names and shared option fields now reflect that
evidence, with unchanged exact command extents.

Pause checks the sequence volume and the player's paused state, sets game
control bit 1 and calls player pause. Resume clears that bit and calls
resume only while it is set. Sequence stop clears the same bit and calls
player stop when sequence volume is nonzero. Sample stop instead checks
sample volume and passes the unsigned sample handle through the `0x4C888`
Thumb thunk to the copied ARM implementation at `0x03000320`, reconstructed
below. The view
effect stop command uses this sample handle; it is distinct from sequence
stop. Each new complete extent and the renamed existing callers passed
positive byte comparison and a compiling changed-source rejection.

The accepted game audio total is eight functions and 488 bytes. The player
and mixer bodies called by these controls remain explicit original
regions, except where separately reconstructed and counted. No audible or
gameplay behavior is claimed by these compiler comparisons.


## Notification and handle-status handoff

The notification selector at ROM `0x41424` contributes a further 72 matching
C bytes. It narrows the selector to a byte, checks sequence volume, sets the
shared handoff bit `0x80`, starts the selected descriptor with mode four and
its second parameter byte, then calls the accepted synchronization helper.
Its semantic parameter register constraint preserves the observed lifetime;
this does not establish the complete descriptor table extent or mode meaning.

The handle-status wrapper at ROM `0x4146C` contributes 16 matching C bytes.
It calls the validator at `0x49A10` and narrows its result to eight
bits. A changed-handle control compiles and rejects 13 bytes. Static inspection
of the validator shows a 44-byte channel stride at `0x020008B4`: the low byte
of the handle selects a channel, the stored word at `+0x18` must equal the
full handle, and the active byte at `+2` determines the zero/one result.
The validator and copied ARM release body at `0x03000320` are now separately
reconstructed below. Failed semantic candidates and their
raw comparisons remain in local reports. No range check for indices 32
through 255 is observed.

The wrapper closes the actor speed handler's status-call edge. Together these
ten accepted game audio coordination functions cover 576 bytes. They do not
establish the mixer, complete channel lifetime, audible output or gameplay
behavior. The next connected audio targets remain the handle validator,
sequence start and VBlank mixing path.

## Sample-channel backend

Eleven connected backend functions contribute 812 matching C bytes:
handle validation at `0x49A10` (48), global volume at `0x49AA0` (20),
channel marking/resuming/clearing at `0x49B24`, `0x49B5C`, `0x49B80`
(56, 36, 36), mixing-mode configuration at `0x498E0` (104), channel
volume calculation at `0x49BA4` (76), and the copied ARM step setter
at ROM `0xFDA860`, executing at `0x030003E8` (76), copied sample release
at ROM `0xFDA798`, executing at `0x03000320` (200), and frame-buffer
acquisition at `0x497F8` (120), and tick-callback configuration at `0x49AB4`
(40). Each full extent,
including alignment and literal pools, has a compiling changed-source
rejection. The existing game status caller remains exact after sharing the
backend declaration. The game sample-volume caller uses a separate mixer
entry at `0x49948`, whose body remains unmatched.

The common view is a 44-byte record at `0x020008B4`, with 32 records in
the observed bulk loops. It preserves the full handle at `+0x18`, active
byte at `+2`, signed step at `+0x14`, volume byte at `+0`, signed pan
at `+1`, left/right volumes at `+0x1E/+0x1F`, mixing mode at `+0x20`,
and flags at `+0x22`. The byte at `+0x24` selects a volume-table entry
during playback; unmatched stop/fade code also reuses that location.
Unknown fields remain explicit. Handle validation still indexes by the
low eight bits without a bounds check. Marking only changes state-one
channels and, unless its first argument is nonzero, requires `+0x24`
to be zero. These names describe observed accesses rather than a complete
channel or lifetime specification.

Volume calculation multiplies the channel volume by the selected byte from
`0x03000090`, scales it by `64-pan` and `64+pan`, and shifts both results
right by thirteen. The global-volume setter writes the first byte of this
same address after clamping an unsigned word to 255. Mixing configuration
stores option bit four at `0x03000093`, limits the low four-bit mode to
zero through two at `0x03000092`, and updates each active channel's mode
from that value and its flags. Meanings beyond these operations remain
provisional. The step setter preserves the sign of the existing step when
writing the new value shifted left by two. Release validates the same handle,
then clears the active byte immediately unless fade is enabled, state is one
and volume exceeds five. That fade branch reuses `+0x24` as a counter of
sixteen, derives two halfwords from the sample cursor, resets cursor to start,
clears step/mode/handle, and sets the byte at `+0x21` to seven. The subsequent
fade execution is still unmatched.

Frame-buffer acquisition writes both output pointers only while the ring
enabled word is nonzero. Its offset selects matching regions in the two
1104-byte buffers at `0x02000000` and `0x02000450`. Equal current/previous
stamp words permit acquisition directly; a changed stamp is saved and permits
it only when the phase minus one is at most one as an unsigned word. A
successful acquisition advances by 276 bytes, increments the phase, wraps
both phase and offset after phase three, and returns 276. The stamp is a
volatile access view because the original rereads it; other views retain
their ordinary accesses. Buffer size follows the four observed phases and
the spacing between the two bases, not a claim about the entire audio arena.

Tick-callback configuration stores the callback at `0x02001638`. With a
nonnull callback it restores the current tick samples at `0x0200163E` from
the saved halfword at `0x02000E34`; with a null callback it copies the current
samples to that saved halfword instead. The three literal addresses establish
this direction. An earlier failed candidate confused this operation with
the separate tick-period word and remains retained as local failed evidence.

These functions use explicitly selected GNU GCC 3.0.2 with pinned public
source, a documented host compatibility patch, and a fingerprinted native
build. Five functions also select GNU binutils 2.10.1, whose unmodified
ARM emitter naturally supplies the zero-filled alignment in the reference.
Later GNU assemblers fill that alignment with Thumb NOPs. No emitted
assembly or output bytes are rewritten. This establishes a reproducible
matching compiler configuration, not the historical game's toolchain.
Both assemblers use a consistent GNU object ABI and software floating-point
convention for the full link; their code bytes remain checked against the
fixed reference, with ordinary linker compatibility checks enabled.
An inspected Krawall source revision helped form the compiler hypothesis;
its channel layout differs, and it does not establish the game's source
revision. The accepted bodies were reconstructed from the reference's
operations, without importing its instruction bodies or substantial
upstream source. No runtime or audible-output evidence is claimed.

The next connected backend targets are the VBlank frame mixer, sample
allocation, fade execution and sequence timing. Their partial
candidates remain excluded from C coverage.

## Hardware and buffer initialization

The connected initializer at ROM `0x49718` contributes 224 further matching C
bytes. It sets the byte at `0x03000000`, enables the sound block at
`0x04000084`, and writes `0x9A0C` to sound control at `0x04000082`. When the
input narrows to zero, the two read/modify/write operations also access
`0x04000082`: they set bit eight and retain the low twelve bits. The literal
address loaded before the original branch establishes that register; an earlier
failed candidate instead modified `0x04000084` and is retained locally.

DMA channel one reads the shared buffer at `0x02000000` and writes the FIFO at
`0x040000A0`; channel two reads `0x02000450` and writes `0x040000A4`. The
initializer sets channel one's control halfword to `0xB640` and copies that
halfword to channel two only for a nonzero narrowed input. Timer one receives
`0xFBCD` and control `0xC4`; timer zero receives `0xFC00`. It then sets the
buffer phase to two, offset to 552, and both stamp words to zero. These are
observed operations; the inferred stereo and timer interpretations do not
establish audible behavior.

The source uses ordinary C with volatile individual MMIO views and the existing
shared buffer declarations. GNU GCC 3.0.2 and GNU binutils 2.10.1 reproduce the
entire extent, including both intervening pools and zero alignment. A changed
sound-control constant compiles and differs by one byte. Both existing accepted
functions that directly include the shared frame header also passed fresh
positive comparisons and their compiled negative controls. The copied ARM frame
mixer, channel mixing loop and remaining sequencer bodies still receive no C
credit.
