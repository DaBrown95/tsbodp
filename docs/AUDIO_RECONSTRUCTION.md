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

## On-row volume-column selector bound

The indirect volume-column call at `0x0804A382` can select only the ten
corroborated callback records at `0x08D6F77C`. This is a local static target
bound, adding no source bytes or runtime observation. The separate between-row
call at `0x0804A3F8` remains dependent on saved track state.

On every ordinary local path from `audio_player_process_row` at `0x08049F64`,
the volume register comes from zero initialization or an unsigned byte load.
The call's sole incoming branch follows the unsigned `vol > 0x60` test.
Subtracting `0x60` therefore produces `1..0x9F`, and the native shift pair
selects rows zero through nine. Checking all 256 byte values gives 97 values
that skip this call and 159 that select one of those ten nonnull, source-owned
Thumb callbacks. No restriction on serialized volume-byte content is needed.

The dispatch block computes the selector in registers before storing the value
to track byte `+0x5D`. It then loads the callback from immutable ROM into R4 and
calls the `BX R4` veneer. There is no intervening branch, callback or track-field
reload. Changes to the stored track field therefore cannot change this already
captured immediate target. Native local predecessor and reaching-definition
checks corroborate the accepted C expression; entry into an arbitrary interior
instruction is outside this function-entry claim.

The between-row consumer instead freshly reads track byte `+0x5D`; its local
byte/shift sequence admits indices zero through fifteen. Row decoding writes
zero or the bounded difference, and player startup clears the track buffer, but
jingle restoration copies saved player/track state and callbacks run between
row and tick processing. This result does not supply the complete reaching-writer
invariant for that later read. The shared observed table retains
`targets_complete: false`. The inventory separately validates the on-row native
control flow, byte provenance, guard, selector operations, table and veneer
before marking that physical call site complete. A stale source pin, bypassing
path or changed operation rejects the annotation. This removes one unresolved
call-site observation without adding an entry, instruction or source byte.

The neighbouring track-effect call at `0x0804A1A0` remains open. Its effect byte
is multiplied by twelve without a capacity guard. A fixed-ROM instruction model
from the ordinary row entry, using explicit RAM backing and the minimal stream
`[0x80, effect, 0, 0]`, reaches that call for effect 51 or 52 after 90 instructions
and no earlier call. Effect 51 selects the first volume callback at
`0x08D6F77C`; effect 52 reads the volume flag word `1` at `0x08D6F788`, which
passes the non-null target test. These are concrete counterexamples to a local
bound within the 51 observed track-effect rows.

The model checks all 256 effect bytes and stops before the indirect call. It
does not establish that shipped patterns admit those bytes or that gameplay
reaches them. Closing this site requires an upstream effect-domain proof for
the streams admitted by player setup and restoration. The neighbouring words
retain their established volume-table roles; no additional track-effect rows
or complete target set are claimed.

One actual producer now has a bounded pattern certificate. The owned
[`save_world_show_row_flag_notice`](../src/save/world_show_row_flag_notice.c)
passes descriptor 58 to notification playback. Its fixed module at
`0x08B2F2A8` has one order selecting the 596-byte pattern at `0x08B2F054`:
64 rows, 132 events, channels zero through seven, and explicit effects only
5, 6 and 11. All sixteen seek indices agree with independently parsed row
boundaries. For this intact module/order-zero state, all 256 row-byte inputs
to the native loader select the parsed row `r & 63`. A ROM-backed row-one
loader-to-consumer fixture reaches effect 6 at the actual indirect call;
absence of an intervening writer is an explicit fixture condition. No complete
scheduler or gameplay execution is established.

Saved-stream provenance also depends on channel bounds. The unchecked track
calculation places track 20 at the backup player's base, so its instrument
field overlaps `backup.stream`. A separate hypothetical prefix with instrument mode set to one
and bytes `[0x34, 2, 1, 0]` reaches a write of ROM word `0x00270000` to that
saved pointer before any external call. The model stops before dereferencing
the loaded word; no shipped pattern or subsequent restoration is shown to
admit this prefix. Descriptor 58 excludes it through its channel and mode
values. Wider closure still requires the admitted descriptor, channel, effect
and saved-state writer domains; the shared calls remain unresolved.

## Conditional descriptor producers

Six independently checked producer populations now supply a conditional union
of 68 descriptor IDs. Each retains its own input and writer premises; this is
not a complete gameplay population or a declared descriptor-table length.

| Producer population | Descriptor IDs | Conditions |
| --- | --- | --- |
| Thirteen literal notification sites in ten owned callers, plus the optional playback selector | 27, 54–58, 60, 61, 63, 68–70 | Each literal call has one immediate argument definition. The optional selector's complete local paths produce only 68, 69 or 70 after its random-number call. Reaching a call is not established by this static proof. |
| Four period fields in each of the fifty backed scene records | 0, 2–4, 7–11, 13, 15–23, 26, 65–67 | The scene index must remain in 0–49 while periods 0–3 select the record's bytes 8–11. Other unsigned period values return zero without reading the scene table. |
| Handler 7 records in the retained fifty-root, 105-pack resource population | 12, 24, 58, 65 | Correct program copying, unchanged command/parameter bytes and execution reaching the record remain premises. |
| Thirty-one physical literal selector calls in nineteen owned callers | 0–7, 9, 14, 21, 22, 28, 29, 35, 37–39, 46, 47, 60, 61 | Complete local control-flow and argument checks corroborate the literals, including three guarded switches. Thirty-three source occurrences merge into thirty-one native calls. Reaching those callers remains a separate question. |
| Three contact-table prefixes | 3, 25, 26, 28, 30–34, 36, 40–45, 65 | Main scene index 0–7, activity-three subtype 0–4, or activity-six option 0–4, with intact table and object storage. Main scene 6 skips its call. These are conditional prefixes, not global index bounds. |
| Eleven attachment-94 parameter rows | 48–53 | Execution reaches phase zero with a valid object and freshly read signed parameter 0–10. The provider itself has no such range guard. |

The period helper's native body was checked for all 200 physical field
combinations and six default-path boundary values. Its unsigned branch
partition separately establishes the default result for every other 32-bit
period. The underlying 600-byte table has twelve-byte records; the fifty-row
backing follows the existing independent adjacent-table evidence. The helper
has no scene-index guard, and scene-request/writer provenance remains open.

The resource projection reopens all 250 distinct program groups across 354
copied contexts with the existing parser. Exactly six physical handler-7
records occur, in scenes 2, 9 and 28: two supply 12, two supply 24, one supplies
58 and one supplies 65. Complete record lengths, terminators, hashes and
retained selector contexts agree. Only the first ID-24 record belongs to an
initially requested group; even that membership does not prove execution.
The producer, copy walkers and audio consumer retain their current exact
positive builds and rejected changed-source controls.

The contact prefixes contain eighteen records and seventeen delivered calls.
Each native index case agrees with its record: eight 28-byte main records,
five 56-byte activity-three records and five 12-byte activity-six records.
The last prefix ends before independently consumed palette data. Attachment
94 reads an eleven-row, four-byte-stride prefix at `0x080534D8`; the next
independently consumed viewpoint data begins at `0x08053504`. Its twelve-byte
parameter provider sign-extends a byte. All 256 byte cases confirm a range of
minus 128 through 127, so the eleven checked call compositions establish only
the stated `0..10` subset. They do not establish how callers populate it.

The descriptor root at `0x08D73F34` has a separate physical frontier at
`0x08D7416C`, where an owned render-resource consumer reads an animation-pointer
table. The intervening 568 bytes hold 71 eight-byte records. This is adjacent
data evidence, not an original array-size declaration or a selector guard.
IDs 59, 62 and 64 are the only numbers in that observed `0..70` prefix absent
from the conditional producer union; no producer is inferred merely to fill
those slots, and they are not classified as unused.

The current inventory identifies 32 source owners with a direct selector call,
ten with a direct notification call and two with a direct player-start call:
43 distinct owned callers because these groups overlap. Their current sources,
positive builds and genuine changed-source controls have been rechecked. All
inventoried selector owners fit the populations above or stored-ID replay.
An independent native BL-call census across all 2,460 accepted C bodies
confirms the same owner sets: 46 selector, thirteen notification and two
player-start call sites, 61 in total. Legacy assembler outputs without useful
code/data mapping symbols use their retained compiler assembly to distinguish
instructions from literal pools. No additional direct BL caller is found in
those bodies. Tail transfers, assembly-only and unconverted code, and indirect
incoming execution remain outside this census; the inventory's complete-code
flag remains false.

These 68 IDs reference 44 modules and 418 distinct, nonoverlapping pattern
spans: 404,644 encoded bytes, 26,752 rows and 104,488 events. The projection
includes every non-marker pattern referenced by a declared order, as a data
superset without asserting that every order plays. Twenty-three order entries contain
marker 254 and remain part of the control-state/restoration dependency. All
sixteen seek indices per pattern match independently parsed row starts;
107,008 certified native-loader model cases cover all 256 row-byte values for
every pattern. The two new deltas execute 37,376 cases and retain the earlier
69,632 after artifact and fixed-ROM checks. A separate fresh parser checks the
complete combined population, all declared non-marker orders and disjoint
spans; it does not rerun those native cases. Current consumer and target
positive/control artifacts remain qualified.

The observed events use channels 0–15, nineteen explicit effect IDs no greater
than 45, and volume bytes 16–80. All 44 module instrument-mode flags are zero;
their channel counts are 4–15. Thus these encoded events stay inside the
twenty-track span cleared at startup and inside the observed effect-table
prefix. They supply no nonzero volume-column effect assignment; an omitted
volume can still preserve an earlier saved value. The newly admitted mark
effect calls the player callback with code 3, adding an explicit callback
preservation premise. These data facts alone do not close intervening writers
or restoration.

The stronger claim that every event channel is below its module's declared
channel count is false for this population. Nineteen patterns contain 1,117
exceptional events in descriptors 15, 20 and 44: respectively channel/count
8/8, 15/15 and 9/9. The additional descriptor-44 event is at `0x08B209C2`,
the eighth event of row zero in pattern `0x08B2098C`. Independent parsing and
the native row-seek checks agree. No exceptional event is first in its row,
so no call-free loader-to-consumer trace for such an event is claimed.
These records remain inside the twenty-track span cleared at startup; their
playback consequences are unverified. The tighter count must not be used to
close the writer domain. Input admission, mutable program storage, option/current
ID replay, saved pointers and callback/alias writers remain outstanding. Both
shared callback sites remain open.

## Reset-seeded live and saved volume state

The accepted reset copy installs EWRAM from `0x08FDBA28` into
`0x02000000..0x020027F8`. In that fixed ROM image, both complete 1,972-byte
player states at `0x02001644` and `0x02001DF8` are zero. The later unused-RAM
clear begins at `0x020027F8`. This supplies an initialized base case for all
twenty `volume_effect` bytes in each player, rather than assuming the backup
was cleared by the audio initializer.

For valid canonical track pointers and the conditional 68-ID stream domain,
named row assignments either clear `volume_effect` or preserve it. Startup
clears all twenty tracks; the fixed 1,972-byte save and restore copies carry
the predicate between live and backup states. All eighteen distinct admitted
effect owners preserve this field through their named writes. The mark effect's
external callback has a preserving footprint for either named installed target,
as qualified below; other targets still need their own argument. Under these premises, induction
over the named transitions keeps all forty protected bytes zero, including
when a later jingle replaces one while retaining an earlier backup. The weaker
generic named-writer bound `0..0x9F` also survives these copies without the
encoded-volume restriction.

Provider footprints are a real dependency. The owned ARM pan setter indexes
44-byte mixer channels using `handle & 255` and checks handle equality, without
an index-below-32 guard. Static address arithmetic shows that indices 104, 127
and 151 can alias protected bytes in the live or saved players. Its disabled
hardware path writes `0xC0`. This is not evidence that such handles are
produced: valid indices 0–31 have a disjoint footprint. Handle provenance,
sample/object pointer validity, callbacks, DMA/IRQ writers and interference
during copy/restore still need their own preservation arguments.

The extended sample allocator preserves the low-byte range `0..31` when its
input already has that range. A matching identity retains its input index;
a mismatch scans the 32 channels and returns a bounded index or zero. The
generation shift does not change that low byte. This is range preservation,
not arbitrary-handle validation: a matching out-of-range identity bypasses
the scan. The exhausted scan also reads the active byte at index 32 before
returning; no C array-safety claim follows.

Reset seeds all twenty live, twenty saved and six standalone track handle
words with zero. Live-track clearing, fixed player save/restore copies and
the named assignments from allocator returns preserve their low-byte range,
provided all other writers and object indices preserve it. The standalone
initializer does not clear its handles; their base case comes from reset.
Its separate outer instrument identity still needs an index in `0..5`.
The 1,568 allocator and 128 pan model cases corroborate the native range and
footprint paths. Stale generations may fail equality, or repeat after
`2^24` allocations; identity validity and address range are separate properties.

A separate constructed-state model copies a pre-existing `0xA0` byte into
backup, clears live tracks, restores it and reaches selector 10 at the later
volume call. It reads the actual following-data flag 50 and pointer
`0x00190000`, then stops before the call. That fixture refutes a bound derived
only from the current module; it is not a counterexample to the reset-seeded
induction or a demonstrated gameplay path. The native copy/clear/restore
fixtures and thirty zero-state consumer cases remain retained evidence.
The additional fourteen modules share the checked count and field conditions;
no new native consumer execution is claimed for them. Global writer closure
at `0x0804A3F8` is still open.

## Named player callback preservation

The accepted C direct-BL population contains two caller sites for the activity
callback selector: audio initialization supplies index zero, and activity-six
initialization supplies one. Local predecessor and argument checks corroborate
both constants. The selector reads `0x080414C1` or `0x080414F5` from the
observed table prefix at `0x0807FA84`; its sole mapped setter call stores that
pointer at `0x020025B4`. Reset seeds the slot with zero. The selector has no
general index guard, and the setter accepts arbitrary pointers, so these
named installations do not establish every possible slot writer or target.

Both installed targets are complete owned leaf functions. Their full native
control flow and store-base definitions give these non-stack writes:

| Target | Callback kind | Writes |
| --- | --- | --- |
| Default `0x080414C0` | 2 or 6 | OR mask `0x02` into flags at `0x03007366` |
| Default | 5 | OR mask `0x10` into the same flags byte |
| Parameter `0x080414F4` | 2 or 6 | OR mask `0x02` into the same flags byte |
| Parameter | 3 | Store the parameter word at `0x03007360`, then OR mask `0x04` into flags |
| Either target | Other kinds for that target | No non-stack writes |

For every 32-bit kind and parameter, these footprints preserve the forty
volume bytes and 46 handle low bytes. Each leaf also saves its return address
at entry SP minus four. A valid call stack must keep that word separate from
both the protected bytes and the eight notice bytes `0x03007360..0x03007367`;
otherwise a parameter store could overwrite the saved return address. The
initialized IRQ/system stack locations and model fixtures meet this condition.
The kind partition and native stores support the general claim; 22,528 model
cases corroborate it without claiming hardware execution.

The mark producer supplies kind 3 and its encoded byte operand; the checked
finish-jingle suffix supplies kind 5 and parameter zero after its preceding
restore/providers return. Given either named installed target and the stack
premise, these two callback boundaries preserve the protected bytes. Slot
aliases, other installation paths, period/frequency callbacks, mixer providers
and other writers remain separate dependencies. Notice writes can still
change later control flow and do not prove descriptor admission.

The standalone instrument entrypoints have no additional static producer in
the checked incoming population. Across all 2,460 accepted C bodies, including
conditional and unconditional B/BL instructions, only the instrument initializer
has a direct incoming call. A raw aligned branch-encoding scan using the
physical `0x08000000` ROM origin finds the same call; exact even/odd entry
words, including ROM mirrors, occur nowhere. The branch scan does not model
copied or ROM-mirrored instruction-PC origins. These searches also do not
exclude computed, split, compressed or mutable pointers. The five playback/query
entries are not classified as unreachable or unused, and the six standalone
handle premises remain explicit.

## Current-selection sentinel and option replay

The option paths preserve a byte, not its membership in the admitted ID set.
Three native suffixes checked over all 256 values show that the current ID is
copied to the cache unless the previous kind is 13, that kind 13 preserves the
cache, and that re-enabling playback passes the previous byte to the selector
after setting the current byte to 255. These 768 conditional cases require
the preceding calls to return and the stated object/storage premises; no
startup-to-options execution is claimed.

The selector does not unconditionally reject sentinel 255. With volume off it
stores the byte and returns. With volume on, current ID 255 and clear flags it
returns without a descriptor read. If `flags & 0x02` is set, the same ordinary
entry instead loads the computed slot at `0x08D7472C` and prepares a player
start with `R0 = 0x0C101010`, `R1 = 12`, `R2 = 12`. That slot overlaps the
independently backed scene-zero object-group length directory beginning at
`0x08D74728`; it is not admitted as another audio descriptor.

The actual default callback sets mask `0x02` for kinds 2 and 6 while preserving
the current ID. A conditional callback-to-selector composition therefore
reaches that load with current ID 255. It stops before the player-start call,
without a crash, hardware-address interpretation or natural call-order claim.
The initialization suffix seeds 255 with flags zero. The actual named startup
handoffs choose language selection (kind 12) or timed notice (kind 3), then
proceed through kind 3 to pages (kind 4) and the default menu (kind 5).
Both the timed notice and default menu select literal ID zero before their
later input paths. This is a conditional ordering result for those dispatch
edges and returning providers, not a complete startup or scene-reachability
trace. It supplies no initialized witness for the constructed sentinel case.

The options menu's own mute-and-enable cycle has a more specific relation.
Its positive-to-zero branch stops sequence playback before setting zero
volume; the actual stop-return suffix clears pause mask `0x01`. On re-enable,
the selector receives the captured prior ID, while 255 is only the temporary
stored current ID. After playback and synchronization return, the selector
clears mask `0x02` and restores the requested ID only if its fresh read finds
mask `0x01` clear. All 256 flag bytes were checked at the stop and return
suffixes, using three representative requested IDs for the latter, for 1,024
native model cases. Calls before the suffixes are not emulated.

Thus this named options cycle preserves an admitted current/cache ID when
its providers and intervening writers preserve the stated fields and flag
relation. The named callbacks preserve mask `0x01` and current ID under their
stack premise. The scroll-text detour retains the earlier cache while selecting
ID 9; the language detour copies the still-admitted current ID. Neither copy
adds a membership guard.

Activity six is a distinct zero-volume producer: initialization saves the
previous volume, forces 255 and selects its option ID; completion later
restores the saved byte without clearing pause mask `0x01`. The retained
250-group resource population contains one pause command, at `0x08D7994C`
in scene 28 / pack 2 / group 10, and no resume or sequence-volume command.
Record presence does not establish execution or an intervening pause during
activity six. That lifetime relation, wider writers and other incoming paths
remain open. If mask `0x01` is supplied at the re-enable return suffix, 255
survives; no normal initialized call-order witness for that premise has been
established.

## Standalone instrument lifecycle and activity handoff

Twelve connected extents add **1,400 matching C bytes**, including a copied ARM
activity check and the ROM ARM fade mixer. All use ordinary C without instruction assembly, register
constraints or output changes. The instrument processor called here is the
previously accepted 776-byte routine; it is not counted again.

| Operation | ROM entry | Complete matching C extent |
| --- | --- | ---: |
| Standalone instrument start | `0x0804ABC4` | 516 |
| Instrument envelope release | `0x0804BC88` | 112 |
| Instrument stop | `0x0804BCF8` | 56 |
| Process six instrument tracks | `0x0804BD30` | 20 |
| Instrument handle validation | `0x0804BD44` | 40 |
| Initialize six instrument tracks | `0x0804BDAC` | 36 |
| Set/get player channel volume | `0x0804BD6C` / `0x0804BD8C` | 32 / 32 |
| Copied ARM handle/activity check | `0x08FDAA40` | 56 |
| Audio initialization coordinator | `0x080496F8` | 32 |
| Stop the current jingle | `0x0804BB58` | 28 |
| Mix the stopping sample's fade ramp | `0x08049BF0` | 440 |

### Contextual track identity and allocation

The six standalone records begin at `0x020025B8` with the same observed 96-byte
stride and envelope fields as the player tracks. Their word at `+34` stores an
instrument handle. Player panbrello uses that same offset as a waveform pointer;
the shared view now makes these two contextual meanings an explicit union.
The existing field offsets and stride remain unchanged. This does not establish
that an instrument handle and waveform pointer are interchangeable in one
context, or that every track has either role at every point.

The instrument handle has an eight-bit channel and a 24-bit generation. The
start routine first compares the selected record's identity with the supplied
old handle. A match reuses that slot. Otherwise it scans envelope-enabled bytes
first; only when all six appear enabled does it scan the copied ARM backend's
handle/activity check. That envelope-first pass belongs to the earlier game
version and differs from the inspected later upstream's single backend scan.
The original tests each record before the six-record limit; no extra guard or
reordered read is added. The interface still requires valid caller handles and
storage/input domains. Matching does not prove that arbitrary low-byte indices,
notes or exhausted searches are safe.

The global generation word at `0x030015AC` is incremented and narrowed into the
24-bit handle field. The routine selects the instrument's sample index, copies
sample volume/pan defaults, derives a linear period and initializes the earlier
volume/pan envelope state already observed in the row decoder. A volume envelope
starts the sample at volume zero; otherwise it uses the sample default. Both
branches call the accepted extended ARM sample starter and store its handle.
A zero backend handle clears the instrument identity and returns zero.

Release and stop validate the complete identity first. Release changes volume
and pan envelope states, including the earlier unconditional pan-state update,
or releases the backend when no volume envelope is active. Stop clears the
envelope-enabled byte and releases the backend. Validation calls the accepted
Thumb activity check after identity validation. Initialization sets channel
volume to 64 and the sine-table pointer on six records; processing passes those
same six records to the accepted instrument processor.

### Copied ARM activity and coordination

The startup audio copy places the 56-byte activity-check extent at
`0x030005C8`. The instrument starter's literal at `0x0804AC3C` and indirect `r7`
transfer identify this entry. Its C selects a 44-byte backend channel by the
handle's low byte, compares the stored full handle and returns whether the
active byte is nonzero. It includes its original literal pool. The following
four-byte counter storage remains explicit data. The RAM map records this
additional entry within the existing startup copy; no new copy is claimed.

Player channel-volume accessors bound the channel to 20, clamp a supplied
unsigned volume to 64 and read/write the signed channel-volume byte. The jingle
stopper tests observed flag four before calling the accepted finish/restore
path. The initialization coordinator calls the still-unconverted master-volume
routine with 128, initializes and activates the accepted hardware path, then
initializes the six instrument records. Its natural Thumb alignment requires
the pinned current assembler; old assembler zero alignment differs in two bytes.

The ARM fade mixer closes the sample-release path's backend state consumer.
It uses the lesser of the remaining fade count and requested sample amount,
mixes four left and four right samples per iteration and advances the two
16-bit ramp words with their observed narrowing. The accumulator is interpreted
as signed before shifting by four; left/right volume products are shifted by
three. After reducing both counts by four, it clears the active byte when the
fade count reaches zero and hands any remaining amount to the still-unconverted
copied ARM bias mixer at `0x03000AB4`. Its return and the following clear
prologue bound a provisional 72-byte body. The old 316-byte mapped envelope also
contains a clear helper, counter words and the converter; all remain explicit. The source retains the required four-sample count domain; no remainder
loop or new count guard is invented. The release routine's reused table-index
byte and tail words now have an exact matching consumer as well as producer.

### Evidence and remaining boundaries

Every new extent matches and rejects its actual changed-source control.
Canonical raw comparisons, commands and include snapshots are retained in
ignored `reports/audio-root/instrument-lifecycle-canonical/`; initial layout,
unsigned-bound and backend-expression failures remain in `instrument-lifecycle/`
and `instrument-active-ram/`. All 65 existing shared-track consumers (9,932 C bytes) also match and reject
their controls. That audit is in `instrument-track-context-audit/`. Sources adapted from the pinned LGPL Krawall
files retain their notices and licence reference. The common track refinement
also preserves existing player/effect source controls.

The 124-byte master-volume/clip-table routine at `0x08049968` remains
unconverted. Its copied shift patcher and bias mixer now have the assembly
source ownership described below; their writable domains remain open.
Private master-volume trials are retained in `master-init-lifecycle/`. The later
upstream variable-index final write does not reproduce the original. A literal
minus-1024 index with HWI32 reproduces the original address calculation but
still emits a store where the reference has a no-op. That unexplained two-byte
difference is preserved; no store is suppressed, output patched or candidate
credited. Original sample/instrument/frequency data remains explicit. This
static and compiler evidence does not establish audible playback or gameplay.
The fade mixer's adapted LGPL source, full extent and changed-source control
are retained in `fade-mixer-canonical/`; the independent original-expression
trials are in `fade-mixer/`. No assembly or value constraints are used there.


## Assembly-origin mixer primitives and converter

The pinned public Krawall `lib/mixer_func.S` source now rebuilds the complete
1,604-byte block stored at ROM `0x08FDAA7C` and copied to RAM `0x03000604`.
This is an assembly-origin exception, not a difficult C match replaced with
assembly. The upstream file at revision
`8d338581bf0ed0afad15b66bf5979ad4c4d15ed0`, blob
`6d4975102527644490e195357d841976f588e412`, already expresses every one of the
398 ARM instructions in assembly, including register assignments, paired-sample
arithmetic, shared left/right tails, converter load sites and their modifying
routine. The earlier 300-instruction kernel correspondence in the RAM map is
now corroborated by assembling the entire original upstream algorithm with the
game's separately identified clip-table address. No raw instruction body from
the ROM is incorporated into the source.

`src/audio/mixer_primitives.s` preserves the LGPL-2.1-or-later notice and licence
reference. Changes expand register macros, express channel offsets and shift
constants as assembler `.equ` names, replace the writable-IWRAM section with
`.text`, make labels private, and leave clip-table storage in the explicit
original data. The instruction sequence is unchanged. The external
`g_audio_clip_table` address is `0x02001238`, supplied by the original converter
literal, rather than the later upstream storage choice.

The 12 entry points are listed below. The physical byte column counts each
instruction once; it is not an invented standalone function extent. In
particular the two right-channel entries branch into their left counterparts.

| Upstream label | ROM address | RAM address | Physical instruction bytes |
| --- | --- | --- | ---: |
| `mixLeft` | `08FDAA7C` | `03000604` | 128 |
| `mixRight` | `08FDAAFC` | `03000684` | 32 |
| `mixCenter` | `08FDAB1C` | `030006A4` | 132 |
| `mixStereo` | `08FDABA0` | `03000728` | 152 |
| `mixLeftHQ` | `08FDAC38` | `030007C0` | 228 |
| `mixRightHQ` | `08FDAD1C` | `030008A4` | 36 |
| `mixCenterHQ` | `08FDAD40` | `030008C8` | 232 |
| `mixStereoHQ` | `08FDAE28` | `030009B0` | 260 |
| `mixBias` | `08FDAF2C` | `03000AB4` | 72 |
| `mixClear` | `08FDAF74` | `03000AFC` | 52 |
| `mix16to8` | `08FDAFB0` | `03000B38` | 184 |
| `mix16to8_patch` | `08FDB068` | `03000BF0` | 84 |

The block has **1,592 instruction bytes** and **12 non-executable bytes**:
the two initialized volume-counter words at RAM `0x03000B30/0x03000B34` and
clip-table pointer pool at `0x03000C44`. These assembly-owned bytes receive no
C credit. Bias, clear and conversion close the accepted channel mixer's three
lower-level handoffs; the eight kernel entries are the known original-image
entries reached by its shared dispatch table. The table's complete runtime
index domain and writable channel state remain separate inventory questions.

All local branches, counter accesses and converter-patch addresses are relative
to the same block, so the same object bytes are valid at both its ROM storage
and RAM execution address. The clip-table literal is the only external absolute
address. Private labels and `defines_symbol: false` retain existing fixed RAM
aliases for C callers, without teaching stable build tooling a second assembly
execution-address mechanism. An independent RAM-address link of the upstream
source and the ordinary ROM-address source comparison both reproduce all 1,604
reference bytes.

The stable isolated candidate gate records `identical: true` and
`assembly_glue_verified: true` in
`reports/audio-reconstruction-20261016/named-constants-canonical-report.json`.
Its actual changed-source control alters the first saved-register set, compiles
to the same size, and differs by one byte. Twelve additional individual entry
controls each change that entry's first instruction, compile to the same
1,604-byte extent, and differ by one byte; their receipts are retained in
`entry-controls.json` and the corresponding subdirectories. These are original
image and source-sensitivity proofs, not audio or gameplay execution evidence.

The converter patcher remains self-modifying code. It clears instruction bits
`0xF80`, then ORs the incoming argument shifted left by seven into eight
converter instructions. It does not locally mask that argument. Therefore a
shift-field-only interpretation still requires proof of the incoming domain;
this exact initial-image rebuild does not close every possible modified
instruction state or justify a full audio-completeness claim. The C-origin
master-volume/clip-table initializer at `0x08049968` also remains unresolved,
with its previously recorded two-byte final-store discrepancy unchanged.

## Game initialization and identified converter-shift inputs

Four connected game-level entries add **120 matching C bytes**: the default
initializer at `0x08041244` (20), initializer at `0x08041258` (76), hardware
shutdown at `0x080412A4` (12), and pacing setter at `0x080412E0` (12).
All four ordinary C candidates match complete extents with the existing agbcc
profile. Their actual changed-source controls each compile to the same extent
and reject by one byte. Receipts, source/header snapshots and comparisons are
under `reports/audio-reconstruction-20261016/game-initialize/canonical/`.
The existing source alignment directive preserves the observed alignment; no
instruction bodies, output patches or register bindings are introduced.

The default entry stores pacing eight before calling the initializer. The main
entry initializes the accepted backend with mode one, sets master volume to
`0x40080`, selects mixing mode two, reapplies the shared pacing byte and saved
sample/sequence volume options, sets sequence ID 255, clears the volatile flags
byte and installs callback-table entry zero. Its volatile eight-bit flag view
preserves the original read before the zero store. The pacing setter writes the
low input byte; hardware shutdown calls the already accepted deactivation body.
Names describe these observed operations and do not establish audible behavior.

The current rooted inventory identifies two direct master-volume callers:
accepted `audio_initialize` passes 128, and the now reconstructed game
initializer passes `0x40080`. The original master-volume body sends five to the
converter patcher when the upper halfword is zero, otherwise sends the upper
halfword. Therefore these two identified paths choose converter shifts five
and four respectively. A whole-ROM byte search finds no word containing
`0x08049968` or `0x08049969`; the sole exact patcher pointer word is at ROM
`0x499D4`. This corroborates the known paths but does not prove absence of
computed or currently unresolved callers. The patcher's lack of a local mask
and the broader inventory limits remain explicit.

## Copied hardware timer/DMA IRQ

The 140-byte extent stored at ROM `0x08FDA47C` and installed at ARM RAM
`0x03000004` now rebuilds exactly from `src/audio/timer_irq.s`. It contributes
120 hardware-IRQ instruction bytes and 20 literal-pool bytes, counted separately
from C. The four bytes immediately before it contain the hardware-enabled byte; those
bytes and the four volume/mode bytes immediately after it remain explicit
non-executable original data.

The source adapts the assembly IRQ in the same pinned Krawall revision's
`lib/directsound_asm.S`, blob `c2f82e5d2971b5405c9b88009063984ade358b29`.
Its LGPL-2.1-or-later notice and licence reference are retained. The original
MMIO register sequence follows that assembly source: reset DMA1, reset DMA2
when its start bit is set, stop/reload/restart timer 1, then return through LR.
The earlier game increments the shared full-word stamp rather than toggling
the later upstream byte. It reloads timer 1 with `65536 - 1104`, using the full
observed four-phase buffer size, rather than the later half-buffer expression.
These observed earlier operations, private labels, named constants and the
external stamp address are documented adaptations, not raw ROM instructions.

The original first-IRQ behavior also differs from later upstream. Both DMA
paths reach the timer tail at `0x0300004C`. After programming the timer, the
source loads its existing unconditional `BX LR` instruction word at
`0x03000078` and stores that word over the timer tail's first load. Later IRQs
therefore increment the stamp, reset the active DMAs and return at that same
tail address. The source introduces neither the later upstream front-branch
patch nor its backup/undo routine. Both initial and modified return behavior
are explicit; unrelated writers and complete interrupt scheduling remain
outside this local proof.

The five original pool words are at RAM `0x0300007C` through `0x0300008C`:
stamp `0x020008B0`, DMA1 control `0x040000C6`, DMA2 control `0x040000D2`,
timer 1 `0x04000104`, and reload `0xFBB0`. All internal references stay relative
to this copied block. The stable isolated source/control gate and a separately
retained RAM-address link match the entire extent. Increasing the stamp step
from one to two compiles to the same size and rejects by one byte. A second
control redirects the self-modifying store to the existing final return;
it compiles to the same size and rejects by two bytes. Source snapshots,
commands, objects, raw comparisons and receipts are retained under
`reports/audio-reconstruction-20261016/timer-irq/final-canonical/`,
`ram-address-proof/` and `patch-target-control/`. No device, audible-output or
gameplay execution is claimed.

## Unrooted backend query closure

Six library entries add **120 matching C bytes** while closing gaps that were
absent from the rooted inventory rows. The getter bodies and their literal
pools are now rebuilt from readable C; no incoming execution or call is thereby
observed. Their names follow the matching fields and pinned Krawall interfaces.

| Entry | ROM address | Complete C extent | Observed read |
| --- | --- | ---: | --- |
| Sample-mixer volume | `0804995C` | 12 | Byte one at `03000090` |
| Channel frequency | `08049A40` | 24 | Signed step at channel `+14`, arithmetic shift by two |
| Channel volume | `08049A58` | 20 | Unsigned byte at channel `+00` |
| Channel pan | `08049A6C` | 24 | Signed byte at channel `+01` |
| Channel position | `08049A84` | 28 | Cursor `+08` minus start `+04` |
| Player volume target | `0804BC7C` | 12 | Word at `020025AC` |

All channel offsets in this table are hexadecimal. The four queries narrow the
handle to an unsigned byte before multiplying by the existing 44-byte stride.
They do not validate the complete handle, active state or array index. The
explicit byte conversion produces the original left/right shift pair; an
integer `& 255` candidate instead emitted an AND and different register
lifetimes. Keeping the position's two direct array-field expressions reproduces
the observed separate offset additions; collapsing them into a local channel
pointer does not. These are bounded, falsifiable type/dataflow refinements,
without register constraints or instruction assembly.

The frequency result retains an arithmetic shift of the signed step and then
converts to the unsigned return type. It does not take an absolute value. The
inspected later upstream's unsigned temporary likewise makes its `ret < 0`
branch ineffective. The position is a byte-pointer difference, rather than the
fractional step accumulator. The sample-volume query reads table byte one,
shared with its accepted setter; it does not read byte zero used for the
separate global volume. The player query reads the requested target word,
shared with the accepted fade setter, rather than the current-volume word at
`02001640`. A pending fade can therefore report its target before the current
volume reaches it. The query alone does not establish audible output.

The new files retain the pinned Krawall revision and LGPL-2.1-or-later notices.
Their isolated header closes over the existing channel layout without editing
accepted shared headers. All six complete extents match with the existing
GCC 3.0.2 and GNU 2.10.1 profiles. Their actual changed-source controls preserve
size and reject by one or two bytes: frequency scale, channel-index width,
position field, mixer table byte, and cached-word read width. Exact source and
header snapshots, commands, positive bytes, changed inputs and raw comparisons
are retained in `reports/audio-query-closure-20261016/publication-canonical/`.

## Master-volume compiler producer and remaining NOP

A minimal three-body compiler reproducer now explains the bad final literal.
With constant external-array indexing, `store_field` receives bit position
`-8192`; `store_bit_field` receives the same bits as an unsigned compiler
integer, then divides by eight, producing `0x1FFFFC00`. Live tracing of the
unchanged pinned 32-bit-integer GCC build corroborates this exact producer.
Pointer-parameter and variable-index forms avoid that constant field-offset
path. All 24 RTL stages nevertheless retain the final memory store, and both
pinned assemblers emit the ordinary byte-store opcode. Invalid negative-offset
assembly is rejected rather than silently replaced by a NOP.

The original NOP at `080499B0` is reachable fallthrough immediately after the
address addition and before register restoration. It is not an internal branch
target. Its address and section-relative offset are already word aligned, so
ordinary Thumb word alignment would emit no padding there. The actual pool
alignment occurs at `080499D2`, where the reference and old assembler both have
two zero bytes. The compiler candidate has no alignment directive between its
address addition and byte store. A historical post-assembly change is possible
but unproven; this failure is not evidence of assembly origin and authorizes no
store omission, instruction insertion or output patch.

As a separate diagnostic, the locally pinned USA revision 1 entry at
`08049A4C` matches all 116 bytes when the final constant `[-1024]` becomes the
later upstream variable `[-i]` expression. Its gain-mask control compiles to the
same size and rejects by one byte. That secondary-ROM comparison corroborates
the compiler and variable-index workaround; it does not change this project's
reference or contribute USA/Europe revision 0 source coverage. The required
ordinary C explanation for revision 0's NOP remains unresolved. The original
initializer's loops write 2,047 distinct clip-table bytes; index `-1024` is left
unchanged, and the startup copy initially sets it to zero. Neither that fact
nor the known four/five patch shifts closes all runtime writers and indices.
Causal inputs, RTL, debugger commands/log, secondary-ROM diagnostic and concise
findings are retained under `reports/audio-master-causal-20261016/`.

## Complete original-image accounting of the startup audio copy

The fixed startup `audio_iwram` copy contains **5,552 bytes**. Its current source
owners cover `03000004–03000090`, `03000094–03000600` and
`03000604–0300115C`: 4,432 extent bytes, comprising 2,632 credited C bytes and
1,800 separately counted assembly bytes, including inline BIOS glue. This
accounting uses the existing matches and adds no recovered source bytes.

The remaining 1,120 bytes have supported storage roles:

| RAM span, end exclusive | Bytes | Original-image role |
| --- | ---: | --- |
| `03000000–03000001` | 1 | Hardware-enabled byte, initially zero |
| `03000001–03000004` | 3 | Zero alignment/reserved storage, with no field meaning assigned |
| `03000090–03000094` | 4 | Two volume bytes initially 128, mixing mode zero and fade option zero |
| `03000600–03000604` | 4 | Sample generation counter, initially zero |
| `0300115C–030015AC` | 1,104 | Stereo intermediate buffer: 552 signed halfwords, initially zero |
| `030015AC–030015B0` | 4 | Instrument generation counter, initially zero |

Pinned upstream declarations corroborate these object types and sizes; accepted
producer/consumer bodies and 18 fixed original-literal references establish the
game addresses. The game's initial fade-option zero is retained explicitly;
the later upstream declaration initializes its corresponding byte to one.
Zeros alone are not the classification evidence. Source ranges are disjoint,
and all 23 known/source entry addresses fall in instruction ranges.

The complete physical partition is **4,288 instruction bytes, 136 literal
bytes, 1,125 mutable-data bytes and three alignment/reserved bytes**. The eight
volume-accumulator data bytes inside the assembly source block belong to the
mutable-data total. The IRQ's return instruction, also read as its replacement
word, is counted once as an instruction. Compiler pool directives and exact
source/control proofs distinguish instruction words from pools within the
source extents; no broad between-entry envelope is treated as code.

The sanitized separate initial-image partition is recorded in
[`audio_initial_image_partition`](../config/code-evidence-us-eu.json), with all
33 physical ranges, 12 source owners, fixed storage references and upstream pin.
It does not change the inventory algorithm or census counts. The ignored
reproducible read-only audit is `reports/audio-copy-partition-20261016/audit.py`;
its `partition.json` retains source-proof pins and initial-data hashes. This
closes the original-image extent gap for this particular copy. Runtime
writer/input domains remain separate: the known IRQ write changes
`0300004C`, and the shift patcher changes eight converter words without a local
argument mask. Potential later installations, writable callbacks, unbounded
inputs and transfer veneers outside this copy still require their own evidence.

## Cue playback with an existing handle

The ordinary C entry at `080410D8` extends the already matched cue dispatcher:
with sample volume enabled, it keeps an active previous handle; otherwise it
plays a fixed sample or an eligible random variant and sets its pitch. Disabled
volume or an ineligible variant returns zero. Its accepted status query returns
a byte, matching the original status narrowing. No incoming execution has been
observed for this entry; its descriptor/handle input domain remains provisional.

Putting playback in the first arm of `if (!audio_game_sample_active(previous))`
places the previous-handle assignment at the shared return. This ordinary branch
layout also lets agbcc merge both cases' identical pitch/synchronization tail;
the opposite source-arm order duplicated that tail and produced 240 bytes. The
matching 228-byte extent includes 226 bytes of code and pools plus two original
zero alignment bytes before the next word-aligned entry at `080411BC`. The
explicit zero-filled alignment follows the existing game-wrapper convention;
it inserts no instruction. The random bound and kept-handle increment controls
each preserve all 228 bytes of size and reject by one byte. Source/header
closure, commands and comparisons are retained in
`reports/audio-cue-handle-20261016/publication-canonical/`.

## Remaining game-audio interface entries

Three ordinary C entries close the source-ownership gaps in the local
`08040FFC–0804155C` interval, end exclusive:

| Entry | Address | Complete extent | Source behavior |
| --- | --- | ---: | --- |
| `audio_game_pause_forwarder` | `0804138C` | 12 bytes | Calls the accepted pause routine |
| `audio_game_disable_timer1_irq` | `0804147C` | 36 bytes | Clears interrupt-enable bit 4 |
| `audio_game_enable_timer1_irq` | `080414A0` | 32 bytes | Sets interrupt-enable bit 4 |

The mask routines use volatile halfword accesses in the original order: write
zero to IME, modify IE, then write one to IME. They unconditionally enable IME
on exit. The disable mask narrows to `0xFFEF`; the matching literal follows from
the halfword store. Both first semantic C candidates match, without register
bindings or assembly. The pause forwarder includes the two original zero
alignment bytes before the next word-aligned entry, following the existing
source convention. It contains no assembly instruction.

Each actual-source/header proof includes a same-size changed-source control:
Timer1 bit 4 becomes bit 5, or pause becomes resume. Each control rejects by
one byte. API/header closure compiles. The current proofs and metadata are
retained in `reports/audio-timer1-mask-20261016/publication-canonical/` and
`publication-metadata.json`. The read-only `audit_local_interfaces.py` verifies
all 28 source owners against their raw byte/control proofs: their extents cover
exactly 1,376 bytes, with no gap or overlap. This is local extent accounting,
not an expanded claim about the whole ROM.

No original-ROM raw Thumb BL encoding or aligned/unaligned Thumb pointer word
was found targeting any of the three entries. The inventory previously omitted
the two leaf mask routines. Matching C establishes their static source roots;
it adds no observed execution and does not close arbitrary indirect incoming
transfers or later writable targets.

## Bounded converter execution and remaining input domains

The [corrected boot probes](RUNTIME_OBSERVATIONS.md) distinguish bias fill
at `0x03000AB4` from conversion at `0x03000B38`. The converter has 268
arrivals; all eight known writable instruction sites have 18,492 arrivals
each. The eight retained samples per site contain the shift-four instruction
words. This links the known modified words to this boot path; arrivals do
not establish instruction retirement, every later state or a complete domain.

The two named master-volume callers select shifts five/four. Other incoming
transfers and arbitrary writer aliases remain unclosed. Mix-buffer bounds also
depend on valid sample geometry, frequency/fit arithmetic, channel and volume
state, and timing invariants; the SDK's documented ranges are not a proof that
every game producer enforces them. Source ownership and one finite no-input
boot do not establish that executable storage can never receive other writes.

## Track-buffer byte-clear provider

The ordinary C provider `audio_zero_bytes` at ROM `0x0804E7B4` now rebuilds
28 bytes: 26 instruction bytes and the original two zero alignment bytes before
`display_text_copy_bytes` at `0x0804E7D0`. Player start calls it at
`0x0804A964` with its track buffer and 1,920 bytes. Its existing declaration in
`audio_sequence_player.h` remains unchanged; no instruction assembly or glue
bytes are added.

The pinned AGBCC libc `string/bzero.c` corroborates the byte-clear operation;
its Makefile selects the old Thumb compiler with `-O2 -fno-builtin`. Both files
match revision `da598c1d918402c42c0c0d7128ba14567f3175e9`. This provider is an
independent C reconstruction, with no upstream source copied. The explicit
`previous = bytes--` lifetime matters: a direct `while (bytes--)` becomes a
comparison against minus one in initial compiler RTL, whereas the explicit
previous value retains the original count/test flow. Changing counter signedness
did not explain that difference. The public input compiles identically with the
pinned old profile; changing the stored zero to one produces a same-size control
with a one-byte mismatch. This proves source ownership, not arbitrary destination
bounds or the complete caller/input domain.

## Source-owned Thumb interworking entries

Seven four-byte entries at ROM `0x4C874`, `0x4C878`, `0x4C888`, `0x4C88C`,
`0x4C890`, `0x4C894` and `0x4C898` now rebuild from the pinned Krawall
[`lib/stub.S`](https://github.com/sebknzl/krawall/blob/8d338581bf0ed0afad15b66bf5979ad4c4d15ed0/lib/stub.S)
(LGPL-2.1-or-later). Each loads a separately placed ARM provider address into
scratch `r3` and tail-branches through it. The providers already have RAM source
ownership. The stubs preserve their at-most-three register arguments, SP and LR;
play forwards the sample handle returned by its provider.

The ten disjoint extents contain 28 instruction and 28 literal bytes, with no
padding and no C credit. Three data-only pool blocks retain their original
locations, including the gap for the excluded extended-play target word. Named
fixed entry/pool addresses express ordinary PC-relative LDR operands because the
assembler cannot relocate an external Thumb pool operand. Separate joint ELFs
contain exactly the selected sections and no sections for unowned gaps. Every
extent passes the existing verifier and rejects its changed-source control.

As an independent origin check, assembling the upstream file verbatim with the
eight native provider aliases reproduces all 56 selected bytes exactly. Its
12 differing bytes are confined to the excluded extended-play trampoline.
That diagnostic does not by itself justify replacing the differing body.
Current accepted game/VBlank callers corroborate the first four routes; no
current accepted binding was found for the three volume, pan and position
stubs. Assembly ownership does not close incoming transfers, gameplay arguments
or the providers' later writable-code states.

The remaining PlayExt body at `0x4C87C` and pool word at `0x4C8A4` now rebuild
under the justified hardware-glue exception: twelve instruction bytes and four
literal bytes, without C credit. The Thumb BL/private BX-R5 path has an
independently established CPU-mode-adapter purpose, the same named handwritten
SDK stub/pool role and seven exactly reproduced neighbours. The source adapts
that interworking glue; its exact historical variant remains unidentified.
No ordinary C game algorithm has been replaced by assembly.

Its unusual native protocol remains explicit. With incoming SP `S`, provider
entry uses `S-8`; its first two stack-argument slots contain saved caller R5
and LR. R0-R3 pass unchanged, and ordinary Thumb return restores SP/R5. The
source does not advertise a normal six-argument forwarding API. No accepted
incoming alias, raw main-code Thumb call or raw ROM word pointer was found in
the bounded scans; computed targets and writable callbacks remain possible.
Controls changing the saved register and ARM destination both reject. A joint
source-only ELF reproduces all 72 bytes across the eight entries and their
pools (40 instruction / 32 literal bytes), with no gaps, padding or ROM-body
fallback. This closes that initial source interval, not the audio module's
remaining C or writable-state domains.


## Conditional converter states during identified initialization

The original master-volume body selects exactly one converter-patcher call:
`08049974` forwards the nonzero high halfword; `080499CC` forwards five when
that halfword is zero. Both reach the same clip-table work afterward. The
accepted backend initializer passes 128, and its enclosing game initializer
subsequently passes `0x40080`, so this identified initialization sequence
selects five, then four. The two local indirect targets are established; this
does not exhaust incoming arguments or constructed/writable targets.

Starting with the fixed installed image, a serialized execution of those two
calls with no other writer has exactly nine distinct joint converter-word
states. The default-five call leaves the image unchanged. The shift-four call
updates `03000B70/B74`, `03000B8C/B90`, `03000BB0/BB4`, then
`03000BCC/BD0`, each pair's first word before its second. After each store,
a prefix of zero through eight words has shift four and the remainder shift
five. These are conditional storage states; no atomic eight-word update or
execution of every intermediate image is claimed.

The patcher reads only the first pair, clears `0xF80` and ORs its unmasked
argument shifted left seven. Non-shift corruption in that first pair persists
and propagates; a later valid call can instead overwrite corruption confined
to a later pair. No bad input is established reachable. The generic native
master path permits high halves 1 through 65535, while exhaustive incoming
producers, writer/reinstallation aliases and nested patching remain open. The
known Timer-1 self-store is disjoint, and the writable IRQ dispatcher at
`03001C9C` still has an incomplete target population. IME (`04000208`) on entry
to the two master calls remains unproved. A bounded native walk now closes the
earlier named software callee frontier: 25 startup calls before the audio wrapper
expand to 97 source-owned bodies and 109 direct call edges, without an unresolved
body transfer. The two literal loads of the IME address occur in the same
save-transfer DMA helper. That leaf saves IME into R6, clears IME, waits for DMA
completion and restores R6; R6 is unchanged between those operations. The three
leaves between the two master calls do not access IME. BIOS/reset entry state,
the SWI 0B boundary, data/DMA aliases and asynchronous writers remain open;
this does not establish unconditional IRQ exclusion. The bounded receipt is
`analysis/audio-startup-ime-callee-closure-20261024/receipt.json` and adds no source,
instruction-census or runtime credit. The ordinary master-volume C producer and
converter read/fit domains remain separate blockers. The private reproducible
receipt is `analysis/audio-converter-shift-cohort/receipt.json`; it adds no
source ownership and repeats no runtime trace.

## Full master-input converter storage domain

Starting from the fixed installed image, the native master's complete
32-bit input domain selects high halfwords 1 through 65535, with zero selecting
five. Under completed serial patcher calls, without another writer or nested
entry, these inputs produce exactly 1,024 distinct completed eight-word images.
Each image contains four copies of one word pair; the eight words are not
independent choices. Further completed calls stay within that set. The five
shift bits are replaced, while five other initially zero bits can only become
one through the patcher's unmasked OR.

The wider input domain can change the encoded writeback, base and destination
register fields as well as the shift. The encoded ASR field ranges from zero
through 31; zero encodes ASR 32. Some encodings name PC or combine writeback
with overlapping registers. This is a finite integer storage result, without
proof that those inputs occur in the game or that every encoding is valid or
executed. The eight separate stores still expose intermediate images; this
completed-image count does not count all interleavings or replace the separate
nine-state four/five initialization result. The retained derivation is
`analysis/audio-patcher-full-master-domain-20261023/assessment.json`, with
witness reachability recorded as unproved in its `semantic-correction.json`.
It supplies no explanation for the native NOP at `0x499B0`, new source coverage
or closure of competing writers and incoming targets.

## Implicit alignment after two owned functions

The halfwords at `0x49716` and `0x4C872` are current assembler code-alignment
fill after `audio_initialize` and `audio_volume_effect_portamento`. Their
compiler-emitted function sizes are 30 and 38 bytes; object text sizes are 32
and 40. The extra `0x46C0` already exists before linking, outside each function
size, under Thumb `$t` mapping. There is no authored terminal instruction.

Two assembler-only controls change each output's sole initial `.align 2` to
`.align 1`. Both remove only the final halfword, lower section alignment from
four to two, and preserve all previous bytes, symbols and relocations. The
fixed unmodified object, linked extent and native bytes agree. These are positive
alignment-role facts, without new source or observed instruction credit,
historical-toolchain identification or alternate-execution exclusion.

The reachable NOP at `0x499B0` lies inside the separate master-volume worker
at `0x49968`; this section-completion mechanism does not explain its mismatch.
Its ordinary C reconstruction and writable-state domains remain open.
