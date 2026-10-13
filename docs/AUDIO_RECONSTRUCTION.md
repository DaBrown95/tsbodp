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

The next connected backend targets are sample mixing primitives, sample
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
positive comparisons and their compiled negative controls. The sample mixing
primitives and remaining sequencer bodies still receive no C credit.

## Activation and channel lifetime dependencies

Five further connected backend functions contribute 176 matching C bytes:
activation at `0x49870` (48), deactivation at `0x498A0` (28), state-one channel
counting at `0x498BC` (36), indexed channel clearing at `0x499E4` (44), and the
actual game sample-volume backend at `0x49948` (20). Each complete extent and
its compiling changed-source control pass the respective positive/rejection
gates. They use ordinary C with the pinned GNU GCC 3.0.2 and GNU binutils
2.10.1 profiles; no instruction bodies or output edits are involved.

Activation sets interrupt-enable bit four at `0x04000200`, writes 128 to timer
zero control at `0x04000102`, and sets the shared ring-enabled word to one.
Deactivation clears timer-control bit seven and clears that word. Their leaf
boundaries include the intervening literal pools and original zero alignment:
the activation extent ends at the next entry, `0x498A0`, rather than the
46-byte static envelope ending at its return.

Channel counting walks the same 32 records and counts only active-state byte
one, rather than every nonzero state accepted by the handle validator. Indexed
clearing sets that byte to zero only where both the reused `+0x24` byte is
nonzero and the state is one. The subsequent interpretation of other states and
the reused counter still requires the unmatched fade bodies.

The sample-volume setter clamps an unsigned word to 255 and writes byte one
of the table at `0x03000090`. This is distinct from the accepted global setter
at `0x49AA0`, which writes byte zero. The original game caller's address
`0x49948` is retained and its declaration now comes from the shared backend
header. All currently accepted consumers of the changed audio headers were
recompiled with their existing negative controls; their complete bytes remain
exact. These matches close the observed game volume call and hardware
activation edges, but do not establish the complete audio implementation,
audible output or gameplay behavior.

## Copied ARM frame-audio coordinator

The 220-byte function stored at ROM `0xFDB4F8` and executed at RAM `0x03001080`
now matches as C, including its literal pool. The separately audited audio
copy establishes that address relation. It acquires left and right output
buffers, divides the available samples at tick boundaries, invokes the
channel mixer, and calls the tick callback before reloading the tick period.
When no callback is active, or the next tick exceeds the available samples,
it mixes the remaining samples and reduces the current tick count. It returns
one when buffers were acquired and zero otherwise.

The callback at `0x02001638`, tick period at `0x0200163C`, and current sample
count at `0x0200163E` agree with the accepted buffer and callback functions.
The channel mixer called at ARM address `0x03000C48` is covered in the following
batch, with its inline BIOS glue accounted for separately.
The acquisition function at Thumb address `0x080497F9` uses GNU's `long_call`
attribute on both its declaration and definition: the copied ARM coordinator
loads its address and transfers through `BX`, while the acquisition body's
existing 120 bytes remain identical. No hardcoded instruction body or emitted
assembly rewrite supplies that call.

The C coordinator adapts `kramWorker` from
[Krawall revision 8d338581bf0ed0afad15b66bf5979ad4c4d15ed0](https://github.com/sebknzl/krawall/tree/8d338581bf0ed0afad15b66bf5979ad4c4d15ed0),
`lib/mixer_private.arm.c`. This adaptation preserves its LGPL 2.1-or-later
notice and the complete [licence](../licenses/Krawall-LGPL-2.1.txt), and records
the game-specific globals, explicit tick reload and ARM/Thumb call changes.
It is an exception to the independently reconstructed bodies described in the
earlier backend batch; the inspected revision does not establish the game's
original source revision.

Pinned GNU GCC 3.0.2 reproduces the complete ARM extent at its execution
address. Changing the tick comparison from `<=` to `<` compiles and produces
a one-byte mismatch. All five previously accepted direct consumers of the
frame-audio header also passed fresh positive comparisons and their existing
changed-source controls. This closes the frame scheduling handoff from the
VBlank path. Its lower-level sample mixing calls remain explicit and unconverted.
Timing, audible output and gameplay have not been verified.

## Channel mixing and explicit inline BIOS glue

The complete 1,080-byte mixer at ROM `0xFDB0C0`, copied to ARM address
`0x03000C48`, now compiles and links identically. Its C portion contributes
1,024 bytes. Two inlined BIOS divide-with-remainder wrappers each contribute
28 separately reported assembly-glue bytes. Neither wrapper receives C credit
or a green C interval in the public treemap.

The mixer clears the stereo intermediate buffer, visits the 32 shared 44-byte
channel records, and processes only active state one. A zero-volume channel
advances its cursor without mixing; normal and bidirectional loops wrap or
reverse its signed step. Other channels accumulate their left/right volumes,
select the mixer callback from the sum of the `+0x20` and `+0x21` bytes, and
mix until the buffer is complete or the sample stops. Near a sample boundary,
the BIOS operation computes the number of output samples that fit. That number
is rounded to a multiple of four before mixing, wrapping or applying the bias
tail. Finally the downsampling callback writes the two output buffers.

The reference's sample estimate multiplies the signed step shifted by eight
with the remaining output count, shifts that product by eight, and adds one
for forward movement. This differs from the inspected upstream estimate, which
shifts the step directly by sixteen. The game-specific estimate and 44-byte
record layout are retained. Names for the end pointer, loop length, fractional
position, loop mode and dispatch index follow their observed loads and uses.
At `+0x28`, the loop-start pointer overlaps the two fade halfwords already
observed by release: the shared header now expresses that storage as a union,
and the accepted release function retains its identical bytes.

Literal pools establish the intermediate buffer at `0x0300115C`, channels at
`0x020008B4`, volume accumulators at `0x03000B30` and `0x03000B34`, and mixer
dispatch table at `0x08D6F4A4`. The clear (`0x03000AFC`), downsample
(`0x03000B38`) and bias (`0x03000AB4`) operations remain explicit calls into
unconverted ARM routines. Resolving their callback table entries and sample
primitives is the next connected backend work; the observed algorithm does
not establish audible or gameplay behavior.

This function adapts `mixReal` from the same pinned Krawall revision as the
coordinator. The explicit hardware wrapper adapts `FastIntDivideRem` from
`lib/tools.h`; its ARM register setup, conditional BIOS operation and result
stores remain in a separate licensed header. Non-emitting begin/end labels
prove each wrapper's linked byte span at offsets `0x120` and `0x2AC`. The
verification tools reject missing, shifted, overlapping, out-of-range or
unclaimed marker spans. Source receipts and the full build use those checked
spans to split C and glue coverage without altering any output byte.

Reducing the channel count from 32 to 31 compiles and differs by one byte.
Changing BIOS operation six to seven in the retained header compiles and
differs by two bytes, one per wrapper. The canonical mixer, all 153 accepted
consumers of its shared audio headers, and their changed-source controls were
reverified. The tooling suite adds failure cases for span accounting, stale
treemap credit and controls outside a retained include closure. No reference
hash, instruction body or compared range was changed.

## Sample handoff and channel controls

Four further copied ARM functions contribute 456 matching C bytes, including
all literal pools: sample start at RAM `0x030002EC` (52 bytes), volume at
`0x03000434` (128), pan at `0x030004B4` (196), and position at `0x03000578`
(80). The audited copy maps these to ROM `0xFDA764`, `0xFDA8AC`, `0xFDA92C`
and `0xFDA9F0`, respectively. Each compiles identically at its RAM address
with pinned GNU GCC 3.0.2 and ordinary C, without instruction assembly or
register constraints.

The three channel setters choose the low-byte handle index, then require the
record's complete stored handle to match. Volume narrows the requested value
to a byte. Volume and pan both recompute the left/right byte volumes from the
selected table entry using `(64 - pan)` and `(64 + pan)`, shifted by thirteen.
The hardware-enabled byte at `0x03000000` also selects the pan path: a nonzero
byte derives a mixer index from the requested signed pan; zero forces index
one and pan minus 64. These exact game values differ from the inspected
upstream mono path. Position moves the cursor only when the requested offset
is below the sample end, and clears the fractional position. A valid handle
returns one even when that position was rejected; this is the observed
behavior, not an invented error check.

The start wrapper passes the sample header's word at `+8`, volume byte at
`+0xE` and signed pan byte at `+0xF` to the 600-byte extended allocator at
`0x03000094`, which remains unconverted. The partial header also records its
statically observed loop length, end pointer and loop/mixing bytes; these
names and the fixed-step interpretation remain provisional until the allocator
and its consumers close that evidence. The Thumb playback thunk still remains
an explicit original region. The channel setters now connect to the accepted
channel mixer and release lifecycle; no audible-output claim follows.

These bodies adapt `kramPlay`, `kramSetVol`, `kramSetPan` and `kramSetPos`
from `lib/mixer.arm.c` at the pinned Krawall revision above. Their source
notices retain LGPL 2.1-or-later and record game layout, mixer-index and
parameter differences. Changing the volume factor, mono pan, fractional
reset and sample-header volume selection each compiles and rejects with a
one-byte mismatch. Fresh canonical comparisons retain every expected and
candidate byte plus compiler/link commands in ignored local reports.

## Extended sample allocation closure

The complete 600-byte ARM allocator at ROM `0xFDA50C`, executed at
`0x03000094`, now matches as C. It completes the start wrapper above and
connects handle allocation to the reconstructed release, setters and channel
mixer. If fade is enabled it first releases the input handle through an
inlined C helper with the same verified release semantics. It then reuses
an exactly matching record or scans the 32 channel records for an inactive
one. Exhaustion returns zero. The selected low-byte index is combined with
the incremented generation word at `0x03000600` shifted by eight.

The allocator stores the table selector's low bit and new handle, derives
mixing mode, applies the observed stereo/mono pan selection, narrows volume,
and sets the signed fixed-point step from the supplied word shifted by two.
It computes the left/right volumes, then copies the sample's mixing flags,
data start, loop length, end and loop mode. Fraction is cleared, loop start
is end minus loop length, and active becomes one. The quality calculation
reads the record's previous mixing-flags byte before the new sample flags
are stored; that observed ordering is retained rather than silently corrected.

The reference contains an inlined release path, and the C helper reproduces
it without an instruction body. The sample-header view in the shared playback
header is now backed by these loads as well as the start wrapper. No dynamic
sample bounds, valid-handle range, allocation lifetime or audible behavior is
established. In particular, the low-byte index is used before any bounds
check, and the free-channel scan's access/limit order remains as observed.

This adapts `kramPlayExt` from the same pinned `lib/mixer.arm.c`, with its
LGPL notice retained. The original union handle's low-byte update is expressed
as a selected index and handle word before installing the new generation.
Two semantic register bindings retain the channel index in `r4` and the
bounded scan counter in `r1`. Removing either yields a preserved raw mismatch;
there is no instruction assembly in the function. Ordinary C selects the
remaining temporary registers and inlines the release algorithm. Compiler
options and these constraints are matching evidence, not historical source
provenance.

Reducing the scan limit from 32 to 31 compiles and changes one compared byte.
All four existing playback-header consumers retain their exact extents and
reject their actual source controls. Canonical source/header snapshots,
expected and candidate bytes and commands remain in ignored
`sample-allocation-canonical/` reports. Lower-level mixer primitives, Thumb
transfer thunks and the sequence player remain explicit unconverted regions.

## Sequence-player pause, resume and volume handoff

Five matching Thumb functions add 264 C bytes: callback setter `0x4BB74`
(12), pause `0x4BB80` (52), resume `0x4BBB4` (56), paused-state query
`0x4BBEC` (24), and volume setter `0x4BC04` (120). They use ordinary C
without instruction assembly or register constraints. The pinned GCC 3.0.2
Thumb profile at `-O3` reproduces their instruction choices; the separately
pinned GNU assembler 2.10.1 reproduces the zero alignment before their literal
pools. Those choices do not establish the historical toolchain.

The partial player prefix starts at `0x02001644`: its flags word is at zero,
state word at four, song pointer at eight and signed volume byte at `+0x1D`.
Pause acts only in state two, changes it to one, marks channels in slot two
or three according to flag four, and disables the tick callback. Resume acts
only in state one, changes it to two, resumes the corresponding channel slot,
and installs the still-unconverted tick callback at `0x0804A758`. The query
returns whether state is one. These paths connect the published game pause
and resume controls to the reconstructed mixer channel controls.

The fade branch compares the request with the current volume word at
`0x02001640`, writes a new target at `0x020025AC`, and selects a signed step
of minus or plus one at `0x020025B0`. This corrects the reversed word roles
in the first private experiment; instruction and literal-pool evidence agree.
Without an active fade request, the function clears the step and stores both
volume words immediately. It multiplies current volume by the song's byte at
`+0x163` and the player's signed volume, shifts by thirteen, calls the accepted
mixer-volume setter, then refreshes channel volumes. A null song instead uses
128 times 64. No new clamp or bounds check is added. The callback setter stores
the notification function pointer taking two integer arguments at `0x020025B4`; its invocations
remain in the unconverted tick/fade path.

These sources adapt `krapPause`, `krapUnpause`, `krapIsPaused`,
`krapSetMusicVol` and `krapCallback` from the pinned Krawall `lib/player.c`,
retaining its LGPL 2.1-or-later notices and recording the observed partial game
layout and addresses. State, query, shift and callback-assignment mutations
all compile and reject; the volume shift changes two bytes and the callback
assignment changes seven, while the three other controls change one each.
Four existing direct game callers also remain exact and reject their controls.
Source/header snapshots and complete compared bytes remain in the ignored
`player-controls-canonical/` reports. Player start/stop, row/effect processing,
tick scheduling and instrument envelopes still have excluded candidates;
no audible, timing or gameplay claim follows from these matches.

## Sequence ticks, between-row effects and instrument envelopes

Three connected C extents add 1,088 bytes: tick callback `0x4A758` (176),
between-row effect dispatcher `0x4A3C8` (136), and instrument-envelope updater
`0x4A450` (776). Together they complete the timing callback installed by the
published resume control and called by the accepted frame mixer. The main
row decoder remains unconverted at `0x49F64`; it is an explicit dependency,
so this is not a claim that the entire sequence player is reconstructed.

The tick increments an unsigned byte at player `+0x0F`, compares the wrapped
value with speed at `+0x0E`, and selects row or between-row processing. A flag
at `+0x20` gates instrument processing, using the song's first byte as its
count. During a fade it updates the current volume, refreshes the global and
channel volumes, and clears the signed step when the target is reached. The
notification callback receives code one and a zero second argument, as observed
in the ROM; this differs from the pinned current Krawall source. The real tick
source control increments by two and changes one byte.

The between-row dispatcher advances through 96-byte track records. Its volume
column byte is at `+0x5D`; the high nibble indexes eight-byte descriptors at
`0x08D6F77C`. The ordinary effect byte at `+8` indexes twelve-byte descriptors
at `0x08D6F518`. Enabled callbacks and optional second callbacks run with a zero
second argument. The effect byte is reloaded after the first callback, preserving
its possible mutation. Neither index gets a newly invented clamp. Changing the
nonzero effect condition to greater than one changes two bytes.

The instrument path observes the handle at track zero, signed volume/gain/pan
at four/five/six, period at `+0x0E`, instrument pointer at `+0x14`, vibrato table
at `+0x24`, active flag at `+0x4B`, volume-envelope fields at `+0x4C` through
`+0x55`, pan-envelope fields at `+0x56` through `+0x5C`, and vibrato phase at
`+0x5E`. The player frequency converter is an indirect call through `+0x28`.
The track array is represented without an asserted allocation count. Other
track and player bytes remain explicit unknown fields.

Instrument envelopes use naturally aligned four-byte node records and
52-byte envelope views at instrument `+0xC0` and `+0xF4`. The preceding 192
bytes remain unclassified in the public view. Fade/sustain/loop transitions,
volume and pan application, inactive-handle release and sample vibrato follow
the complete observed path. Pan addition narrows to a signed byte before the
minus/plus 64 clamp. The source uses ordinary C and inline semantic helpers,
without register constraints or instruction assembly. Changing fade subtraction
to addition produces a one-byte mismatch. The accepted ARM mixer functions are
called through explicit long-transfer declarations at their real RAM addresses.

These algorithms and layout names adapt the pinned Krawall `lib/player.c` and
`lib/mtypes.h`, preserving its LGPL notices and recording game-specific changes.
The tick and between-row bodies use the ordinary GCC 3.0.2 profile at `-O3`;
the envelope body explicitly selects the separately pinned 32-bit compiler
integer profile described in [the host-width note](GCC302_HOST_WIDTH.md).
Fresh canonical source controls, complete expected/candidate bytes, commands
and shared-header caller proofs remain under `reports/audio-root/`.
The five published player controls remain exact after the field refinements.
Player start/stop, row decoding and individual effect callbacks remain excluded
where unmatched. No audible or gameplay validation is claimed.


## Sequence startup, row positioning and jingle restoration

Five further complete extents add **1,476 verified C bytes**:

| Inferred source role | ROM offset | Complete extent |
| --- | --- | ---: |
| Load pattern row | `0x49DA8` | 132 |
| Advance order/row | `0x49E2C` | 312 |
| Start sequence | `0x4A808` | 732 |
| Restore interrupted sequence after jingle | `0x4AAE4` | 224 |
| Stop sequence | `0x4BB0C` | 76 |

These are ordinary C adaptations of Krawall `lib/player.c` and its partial
`lib/mtypes.h` layouts at revision
`8d338581bf0ed0afad15b66bf5979ad4c4d15ed0`. The source notices and
[LGPL licence](../licenses/Krawall-LGPL-2.1.txt) are retained. All five use the
existing GCC 3.0.2 profile at Thumb `-O3` and the pinned historical assembler;
none uses register constraints or instruction assembly. Complete literal pools
and zero alignment are compared. The ordinary LP64 compiler already matches
these functions; the separate host-wide-integer profile is unnecessary here.

The [partial player view](../include/audio_player.h) still has a 52-byte prefix
and 96-byte tracks. The calls/accesses expose tempo `+0C`, row/order `+10/+11`,
stream `+14`, signed pending order/row `+18/+19`, loop bytes `+1A..+1C`, volume
slide `+1E`, vibrato offset `+1F`, fast-slide flag `+21`, period callback `+24`,
restart order `+2C` and current pattern `+30`. Unknown bytes stay named as such.
Names for vibrato/tremolo/panbrello fields follow upstream roles and the game’s
matching initialization/accesses; the original source names are unproven.
Eight existing player consumers and their real changed-source controls were
recompiled after this same-layout refinement.

The [module/pattern view](../include/audio_sequence_player.h) has a byte row
count at pattern `+20`, hence data begins at `+21`. Sixteen halfword indices select
a four-row block; zero stream codes finish rows, and flag bits 5/6/7 skip 2/1/2
payload bytes. Module accesses support 256 order bytes from `+03`, 32 signed pan
bytes from `+103`, 64 song-start bytes from `+123`, global volume/speed/tempo at
`+163..+165`, flags at `+166..+168`, and pattern pointers from `+16C`. Pattern
counts, stream validity and module channel counts remain input preconditions;
no missing bounds checks or recovery behavior was invented.

The game fork handles a pending order immediately: it clamps it against the
module order count, resets row zero and reloads the stream. Pending rows clamp
against the byte row count. This differs from current upstream’s deferred
order-minus-one/large-row scheme. Marker, completion, loop and restored-jingle
notifications use observed codes 4, 2, 6 and 5 with a zero second argument; the
completion notification precedes the stop call. A zero player state returns from
stop; active tracks clear their envelope byte and call the already accepted ARM
release routine through its copied-RAM address. A `long_call` declaration supplies
that transfer, while C coverage remains ordinary source.

Startup distinguishes an existing jingle, a backed-up song and a normal sequence.
The game conditionally stops pause slots 2 and 4 when leaving a jingle, marks slot
4 when saving the previous song, and copies **1,972 bytes** to/from the backup at
`0x02001DF8`. It clears **1,920 track bytes** and initializes the observed per-track
state. These byte operations support a twenty-track storage region for this path;
the public track tail remains flexible and does not impose a new validated bound
on arbitrary serialized channel counts. Only a song index at least 64 is clamped;
negative signed indices are not given additional behavior. Volume refresh preserves
the argument load before the fade step is cleared and both volume words are
stored, as in the matched inlined upstream API call.

The row-processing entry `0x49F64` is reconstructed in the following batch.
Individual effects, tempo conversion, period calculators and the zero-byte helper
remain explicit unconverted dependencies. Static
and compiler evidence establish these paths and transfers; no audible playback,
BIOS execution, complete audio subsystem or gameplay validation is claimed.


## Connected pattern-row decoder

`audio_player_process_row` at ROM `0x49F64` matches all **1,124 C bytes** through
`0x4A3C8`, including two literal-pool islands. It closes the row branch of the
published tick callback and calls the newly accepted row-advance path. The source
adapts Krawall `processRow`, note playback, envelope initialization/release and
channel refresh helpers, with the same pinned revision and LGPL notices as above.
Its shared structs are in [the player header](../include/audio_player.h),
[sample data header](../include/audio_sample_data.h) and
[decode handoff header](../include/audio_player_decode.h).

The matching source uses GCC 3.0.2 with the separate 32-bit host-wide-integer
profile described in [the compiler note](GCC302_HOST_WIDTH.md), Thumb `-O3`, and
the pinned historical assembler. It contains no register constraints or
instruction assembly. With the normal profile the shared source produces 1,128
bytes and differs; the accepted profile reproduces the negative pan-floor
constant choice as well as every instruction, pool and alignment byte.
Earlier near-matches that cached the instrument pointer are retained privately.
The accepted envelope initializer rereads `c->instrument` after the observed
byte-field writes. Its existing return-value form is preserved even when this
caller ignores that return; changing it changes compiler allocation, not the
claimed extent or comparison rules.

The stream's follow byte selects a track with its low five bits. Unlike the
current upstream encoding, the game consumes **two** note/instrument bytes: the
first note byte's low bit supplies instrument bit 8, and the remaining seven bits
supply the note. No third instrument byte is read. Follow bits 6 and 7 supply
volume and effect/operand bytes. Sample defaults set the track volume directly;
the earlier game has no extra current-volume or current-pan copies. A normal
instrument note selects a sample, takes its default pan, and initializes envelopes
before the period call, rather than delaying that initialization until playback.
The initializer does not add upstream's later vibrato-rate activation condition.
The game’s envelope release path sets the pan status to active or active without
sustain even if its previous status was zero; no nonzero guard was added.

The complete observed call chain is packed stream → instrument/sample tables →
period callback → row effect callback → copied ARM sample start/position/volume,
then untouched-track/effect refresh → signed-byte pan clip → row advancement.
The instrument table at `0x08B18554` and sample table at `0x08D54690` are unsized
pointer declarations. The first 192 instrument bytes are now a same-layout view
of 96 halfword sample selectors. The shared sample header splits `+0C/+0D` into
fine-tune and relative-note bytes; `+0E/+0F` remain volume/pan defaults. Period,
note and destination track fields are signed halfwords; `+49/+4A` are the note
play and touched flags. Names for other effect-state bytes follow the upstream
96-byte layout and remain hypotheses until their individual effect consumers are
reconstructed. Explicit unknown bytes and unused input preconditions remain.

The copied ARM entry declarations retain the observed calling convention and
RAM addresses: extended start `0x03000094`, release `0x03000320`, sample step
`0x030003E8`, volume `0x03000434`, pan `0x030004B4`, and position `0x03000578`.
These are accepted compiled C callees within the audited copy map. The direct
function declarations use long transfers; this does not add assembly glue bytes
to the row decoder. Effect and period callbacks are represented as typed C
function pointers. The following batches reconstruct the period callbacks and
some effect targets; remaining effect entries stay explicitly unconverted.

All current consumers of the refined player, instrument and sample views are
freshly compiled with their real controls, including existing copied ARM sample
start routines and the previous sequencer batches. The decoder control moves
the packed instrument bit from bit 8 to bit 7 and rejects with a compiled byte
difference. Raw comparisons and header snapshots are retained locally. The
low-five-bit track selector and serialized instrument/sample/note indices have
no invented clamps; this path does not validate every module or prove audible
playback, runtime execution or complete audio reconstruction.

## Connected pitch calculation and tick timing

The decoder's two period callbacks and two final-frequency callbacks now compile
at their original entries. The startup path selects each pair according to the
module's linear-slides flag. The tempo setter completes the existing startup,
row-advance and jingle-resume calls into the tick scheduler.

| Entry | Inferred role | Full extent | Matching C | Explicit BIOS glue |
| --- | --- | ---: | ---: | ---: |
| `0804BDD0` | Amiga period from note and sample fine tune | 36 | 36 | 0 |
| `0804BDF4` | Amiga frequency from period | 40 | 28 | 12 |
| `0804BE1C` | Linear period from note and sample fine tune | 24 | 24 | 0 |
| `0804BE34` | Linear frequency from period | 40 | 40 | 0 |
| `08049ADC` | Tick interval from BPM | 72 | 60 | 12 |

This adds **five functions / 188 C bytes**, plus **24 separately counted Thumb
BIOS glue bytes**. Ordinary GCC 3.0.2 Thumb C with the pinned binutils 2.10.1
assembler matches all five complete extents, including literal pools and
alignment. No register bindings or output changes are needed. Changed C source
controls reject all five; changing each new BIOS service number also rejects
its containing extent. The previously accepted ARM mixer, both of its marked
BIOS divisions, its C control and its hardware-glue control still match or reject
as appropriate with the shared header extension.

The Amiga period calculation reads the original unsigned halfword tables at
`08D6F9CC` and `08D6FABC`, scales their product by 15 bits and returns the low
16 bits. Sample offset `+0C` is signed fine tune; this path shifts it by two
before adding the 32-entry lookup bias. The Amiga frequency path divides
`8363 * 1712` by period through BIOS service 6. The linear period path instead
adds `(note << 6)`, `2 * 768` and the signed fine tune shifted by one. Its final
frequency path derives an octave with the observed unsigned reciprocal
multiplication, computes the remainder for the original word table at
`08D6FB3C`, and shifts by `23 - octave`. These ROM tables remain explicit data,
not reconstructed assets. Their names follow the inspected Krawall source and
these concrete loads; they do not establish provenance for the whole engine.

The tempo setter clamps signed BPM to at least 384, divides `15 * 16384` by
that BPM using the same Thumb BIOS handoff, and shifts the result left by two.
It stores the low 16 bits in the tick period at `0200163C`, the active sample
count at `0200163E`, and the saved count at `02000E34`. Existing player calls
supply `24 * tempo`. This is static and compiler evidence for scheduler
coordination; no audible timing measurement is claimed.

`audio_bios_divide_thumb` is a small explicitly marked hardware wrapper adapted
from Krawall's `FastIntDivide`, with the original licence and pinned-source
notice retained. Its six instructions and zero-denominator branch are outside
C coverage. Non-emitting labels prove each 12-byte glue span in the linked ELF;
the separate ARM remainder wrapper remains unchanged. Valid note/table indices,
linear frequency shifts and serialized sample inputs are caller preconditions.
No new bounds checks, period clamp or synthesized division behavior has been
introduced to make a candidate match.

## Connected pitch slides and vibrato

Eleven effect callbacks add **1,644 matching C bytes** to the pitch path. All use
ordinary GCC 3.0.2 Thumb C, the shared 96-byte track view and typed long transfers
to the accepted copied ARM sample-step and sample-release routines. Each complete
extent and its changed-source control are checked independently before full-ROM
integration; no register bindings or instruction bodies are added.

| Effect slot | Original entry | Inferred role | Verified bytes |
| --- | --- | --- | ---: |
| 15 | `0804B27C` | S3M upward pitch slide | 228 |
| 11 | `0804B360` | S3M downward pitch slide | 176 |
| 19 | `0804B410` | Slide toward the pending note | 332 |
| 31 | `0804B55C` | Fine vibrato | 204 |
| 14 | `0804C014` | XM upward period slide | 76 |
| 16 | `0804C060` | Fine upward period slide | 72 |
| 17 | `0804C0A8` | Extra-fine upward period slide | 72 |
| 10 | `0804C0F0` | XM downward period slide | 100 |
| 12 | `0804C154` | Fine downward period slide | 100 |
| 13 | `0804C1B8` | Extra-fine downward period slide | 96 |
| 20 | `0804C218` | Vibrato | 188 |

The original table at `08D6F518` has 12-byte entries: the primary function pointer
at `+0`, a possible second callback at `+4`, and the between-row enable word at
`+8`. The listed slot pointers are static evidence for these boundaries and
roles. Slot 24 additionally points its second callback at the accepted note-slide
entry; its volume-slide callback is now reconstructed below. The decoder invokes
on-row callbacks with a true argument, while the accepted between-row processor
uses a false argument for enabled entries. The table data remains an explicit
ROM region and is not counted as reconstructed source.

The eight direct pitch-slide variants now establish the meanings of the stored
ordinary, fine and extra-fine operands at track `+44/+45/+46`. The note slide
uses the signed period at `+0C`, signed increment/destination at `+1A/+1C`, and
signed glissando note at `+1E`. It clips movement to the destination, walks the
original note-period table when glissando is enabled, and sends either the period
or selected semitone period through the current frequency callback. The S3M
variants interpret high-nibble `E/F` operands as extra-fine/fine row slides and
retain ordinary slides for between-row calls. Lowering variants release a
sample when the narrowed signed period is non-positive, exactly where observed;
no additional stop or clamp is invented. The conventional XM names follow the
inspected upstream effect vocabulary: these upward variants increase period,
and the downward variants decrease it. Converter direction remapping and audible
pitch direction are not independently verified here.

Both vibrato callbacks use track `+20/+21/+22/+23/+24` as position, speed, depth,
retrigger flag and signed-halfword waveform pointer. A new note with retrigger
reads the player's offset byte at `+1F`. The low/high effect nibbles independently
update depth/speed; fine vibrato then divides a newly supplied depth by four.
Between rows, signed waveform multiplication adjusts a temporary 16-bit period,
sends that frequency to the mixer, wraps position to 64 steps and marks the note
for later reset. The stored reset flag also preserves the observed handoff from
combined volume-slide/vibrato. Waveform selection, arpeggio, volume coordination
and other table consumers remain connected reconstruction targets. Table bounds
and valid module/track state remain caller preconditions; these matches provide
no runtime or audible-output evidence.

## Modulation waveforms and temporary volume/pan handoffs

A further six callbacks add **676 matching C bytes** to the same effect path:
glissando enable `0804C300` (24), vibrato waveform `0804C318` (100), tremolo
waveform `0804C37C` (100), panbrello waveform `0804C3E0` (100), tremolo
`0804B628` (184), and panbrello `0804B6E0` (168). Their table slots are respectively
37, 38, 39, 40, 30 and 35. Each has a complete matching extent and an independently
rejected source control. Extending the shared C helper header also preserves all
eleven pitch-slide/vibrato positives and their real controls.

The waveform callbacks select the original signed-halfword tables at
`08D6F7CC`, `08D6F84C`, `08D6F8CC` and `08D6F94C` using the low two operand bits.
The sine/ramp/square/random names follow the inspected upstream source and the
observed pointer selection, with the table data still explicitly unconverted.
Operands below four enable note retrigger; the others disable it. Glissando is
enabled exactly when the effect operand is nonzero.

Tremolo and panbrello establish the corresponding position/speed/depth/retrigger
and waveform-pointer groups at `+28..+2C` and `+30..+34`. On-row calls update
speed and depth from separate operand nibbles and reset position only for a new
note with retrigger enabled. Between-row tremolo adds a signed-byte waveform
delta to base volume, narrows the temporary result to a signed byte, and clips
it to `0..64`. The earlier game helper takes that temporary value as an unsigned
word, multiplies by channel and envelope volume, and shifts logically by **six**
bits before the ARM volume call. This observed scaling differs from the later
inspected upstream helper's 12-bit scaling; it is preserved without inventing a
volume-cache field or changing the result. Audible behavior is unverified.

Panbrello indexes the waveform with position divided by four, adds its signed
byte delta to base pan, narrows the temporary pan to a signed byte, then adds the
signed envelope pan through a separate signed-halfword helper and clips to
`-64..64`. Both routines advance their byte position and request a later note
reset. Tremolo wraps to 64 positions; panbrello's byte assignment wraps to 256.
The unsigned volume argument, narrowed pan temporary and helper argument widths
are supported by complete compiler comparisons, including preserved failed
signed-volume and wide-pan attempts. Remaining combined volume-slide callbacks,
tremor, retrigger and arpeggio are connected targets; no runtime or complete-audio
claim follows from these finite matches.

The whole pitch/timing/modulation batch comprises **22 functions / 2,508 C
bytes**, with **24 additional BIOS glue bytes** kept outside that source count.

## Volume/pan slides, tremor, retrigger and arpeggio

Eight further connected callbacks add **1,972 matching C bytes** and **12 explicit
BIOS remainder-glue bytes**. The original table entries establish the roles and
connections to the accepted row and between-row processors:

| Effect slots | Entry | Inferred role | C bytes | Glue bytes |
| --- | --- | --- | ---: | ---: |
| 6, 23, 24 | `0804ADC8` | S3M volume slide and combined pitch effects | 376 | 0 |
| 7, 49, 50 | `0804AF40` | XM volume slide and combined pitch effects | 184 | 0 |
| 33 | `0804AFF8` | Global volume slide | 184 | 0 |
| 26 | `0804B0B0` | Channel volume slide | 156 | 0 |
| 28 | `0804B14C` | Pan slide | 304 | 0 |
| 21 | `0804B788` | Tremor | 148 | 0 |
| 29 | `0804B81C` | Retrigger | 368 | 12 |
| 22 | `0804B998` | Arpeggio | 252 | 0 |

The shared semantic helpers in `audio_volume_effects.h` retain signed-byte base
volume, channel volume and pan. Compound updates narrow before clipping; regular
volume multiplication shifts arithmetically by 12 bits, distinct from the
earlier temporary tremolo helper's observed six-bit shift. Regular pan narrows
the base/envelope sum to a signed byte before clipping to `-64..64`. Global
slides use player bytes `+1D/+1E` and coordinate the global mixer volume with the
accepted channel-volume update. No cached track fields are invented.

The S3M callback remembers nonzero operands, recognizes row fine slides from
the `F` nibbles, and permits ordinary row slides when player byte `+21` enables
them. The XM callback retains ordinary between-row slides. Their combined
vibrato reset handoffs inspect the current/previous effect and reset flag.
Pan slide preserves the observed low-nibble fine-slide branch that sets the
volume-slide flag at track `+3F`, rather than the pan-slide flag at `+41`; this
is also present in the inspected upstream source and is not silently repaired.
Pan slide requires the verified GCC 3.0.2 HWI32 profile; the normal host-width
candidate differed in 216 bytes. Other callbacks match the normal profile.

Tremor uses track bytes `+39/+3A/+3B` as count, audible interval and total
interval, with both operand nibbles gaining one. It mutes through the explicit
temporary-volume helper, restores the regular volume at the total boundary,
and preserves the note-reset handoff.

Retrigger remembers track byte `+47`, resets the copied ARM channel position
when needed, and tests the tick remainder against the **full byte operand**.
Unlike the later upstream code, the original does not mask the denominator
to the low nibble. Its six-instruction Thumb BIOS remainder span at entry
`+84..+96` reads `r1`; it is separately marked and excluded from C coverage.
The zero-denominator branch remains explicit glue. Volume changes retain the
original nibble-directed powers of two, half/double, three-halves and
`342 * volume >> 9` forms, including signed-byte narrowing before clipping.

Arpeggio remembers bytes `+42/+43`, cycles the count through three values,
selects base/high-nibble/low-nibble notes and clips the unsigned halfword to
119. It inlines the observed linear period/frequency arithmetic and original
frequency table lookup, then calls the accepted RAM sample-step routine.
It does not call the public linear calculator entries or claim those original
tables as C. Valid sample pointers, note inputs and table/shift bounds remain
caller preconditions; audible output and complete playback are unverified.

All complete extents, pools and alignment match; eight meaningful source edits
and the BIOS `swi 6` to `swi 7` control reject. The three previous inline BIOS
callers also retain their full positives, source controls and glue controls
after the header extension. Raw attempts and comparisons remain in ignored
`reports/audio-root/volume-slide-effects/`, `retrigger-arpeggio/` and
`volume-slide-canonical/`. Sources are adapted from the pinned LGPL Krawall
files with their notices retained. The remaining volume-column and table
callbacks are reconstructed below; envelope consumers remain connected targets.

## Bounded effect-table callback closure

The final **26 functions / 1,676 matching C bytes** close every nonzero callback
pointer in the bounded tables at `08D6F518` (51 track entries, stride 12) and
`08D6F77C` (10 volume-column entries, stride 8). Both callback words of each track
entry and the single callback word of each volume entry resolve to **51 distinct
matching C functions**, including those accepted in the earlier connected pitch,
modulation and slide batches. The two table regions total 692 original data
bytes and remain explicitly unconverted. This closure concerns these tables,
not every audio callback, caller input, envelope or runtime playback path.

| Connected operations | Complete matching C bytes |
| --- | ---: |
| Speed, BPM and combined speed/BPM | 96 |
| Mark callback and order/pattern break/loop | 136 |
| Fine volume slides, global/channel/base volume and pan | 440 |
| Sample offset, note cut and note delay | 228 |
| Ten volume-column callbacks | 776 |

Speed/BPM operations preserve nonzero-operand and `0x20` threshold behavior,
store player tempo and call the accepted tick-period setter with `24 * tempo`.
The mark operation calls the nullable registered callback with observed event
number three and the operand. Jump and break write the signed-byte pending order
or decimal-nibble row. Pattern loop initializes the count once, predecrements
the signed byte, ends at minus one and otherwise retains the saved row. The
earlier game uses byte row/count fields, rather than the later upstream widths
and postdecrement expression. No extra bounds or state checks are introduced.

The sample-offset effect keeps the operand for a new note and otherwise calls
the copied ARM position setter with a byte position shifted by eight. Note cut
suppresses an immediate zero-operand note; on the specified later tick it clears
the envelope flag and releases the sample, rather than setting its volume to
zero as in the inspected later upstream code. Note delay suppresses immediate
play for a nonzero operand, then starts the sample on its matching tick. The
inlined earlier note-start handoff clears the reset flag, uses current-frequency
conversion, sends base/channel volume shifted by six and base pan to the accepted
extended ARM sample starter, stores its returned handle and applies a saved
nonzero position. This finite earlier path does not imply reconstruction of every
upstream note-start or instrument-envelope operation.

The volume-column callbacks read track byte `+5D`. They provide ordinary/fine
volume slides, vibrato speed/depth, pan and pan slides, and portamento operand
coordination. Pan uses the observed `4370 * 128` reciprocal form, with operand
seven centering it; it retains signed-byte narrowing and clipping through the
regular helper. The portamento column stores the low nibble shifted by four on
row, conditional on the ordinary effect operand. Its between-row branch calls
the accepted note-portamento callback with a true row argument. That apparently
unusual handoff is present in both the original and inspected upstream and is
preserved without a behavior correction.

Pan, volume-column pan and both volume-column pan slides use the verified HWI32
profile. Other entries use normal GCC 3.0.2. The complete 40-byte portamento
column extent includes natural `mov r8,r8` Thumb alignment from the pinned
current assembler; the old assembler's zero padding failed the two-byte tail.
No instruction assembly, padding bytes, output edits, masks or fixed register
bindings are added to any of these 26 C sources.

Every complete extent and its actual changed-source control passes/rejects
respectively. Expected bytes, candidates, commands, header snapshots, useful
failures and the final assembler comparison remain under ignored
`reports/audio-root/effect-table-closure/`, `portamento-alignment/` and
`effect-table-canonical/`. `effect-table-pointer-audit.json` records the bounded
pointer resolution and original table hashes. Names follow observed accesses
and the pinned LGPL Krawall vocabulary; original resource/table data remains
explicit, and runtime/audible behavior remains untested. Remaining envelope
callers, player/mixer entries and those callers' input domains are the next
connected audio targets; the core 776-byte instrument processor already matches.
