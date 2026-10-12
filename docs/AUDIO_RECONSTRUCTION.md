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
handle names remain provisional; these copied ARM bodies and thunks are
still explicit original regions and receive no C credit.

Before playback, the dispatcher sets bit `0x80` in the shared control
byte at `0x03007366`. VBlank defers the audio step while that bit is set
and records the deferral in bit `0x40`. The accepted synchronization helper
runs `vblank_audio_step` if bit `0x40` is set, then clears bit `0x80`.
That step thunk enters the copied frame mixer at `0x03001080`; the mixer
and its ring-buffer acquisition function remain unmatched candidates.
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
Thumb thunk to the copied ARM implementation at `0x03000320`. The view
effect stop command uses this sample handle; it is distinct from sequence
stop. Each new complete extent and the renamed existing callers passed
positive byte comparison and a compiling changed-source rejection.

The accepted game audio total is eight functions and 488 bytes. The player
and mixer bodies called by these controls remain explicit original
regions, except where separately reconstructed and counted. No audible or
gameplay behavior is claimed by these compiler comparisons.
