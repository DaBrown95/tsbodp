> Internal AI scratch notes. Names and field interpretations are provisional.

# Scene setup and VBlank character animation

This connected batch adds **15 matching C functions, 1,548 bytes**: nine scene
and character-animation routines (1,176 bytes), three display-reset routines
(140 bytes), the primary-frame refresh/OAM handoff wrappers (132 bytes), and the background
animation loader (200 bytes). All extents include their original literal pools
and alignment. Each replacement and a changed-source negative control were
compiled independently; the original matches and each mutation differs. These
are source/compiler claims, separate from whole-ROM and runtime verification.

## Scene setup

The 808-byte initializer at ROM `0x25CEC` connects scene requests to cached
display state, object/view initialization, background animation, audio selection
and the frame-paced transition path. The original next entry is `0x26014`.
The code owns two early literal-pool gaps as well as the final pool; neither gap
is excluded from comparison.

The request at `0x03004350` has word fields for mode at `+4` and scene at `+8`.
The scene context at `0x03004320` has flags, a time-period word at `+4`, and a
palette pointer at `+12`; `+8` remains unknown. The view context at
`0x030040E0` contains twelve-byte view slots, a count at `+0x30`, and the selected
view at `+0x31`. The shared partial view still names the count `unknown_30`.
The initializer establishes one view following a link-recovery flag, then
initializes and displays either every view or the selected view according to
mode bits. The link word at `0x03007334` is accessed with distinct reloads when
clearing its recovery flags; the source preserves those accesses with a
volatile declaration.

The initializer clears OBJ character memory through the existing BIOS CpuSet
wrapper at `0x4C8C4`, using a halfword zero, fill mode and `0x4000` halfwords.
It clears four palette indices and writes four scene-mode bytes using descending
pointer loops. Modes four through seven have a shared preparation path; modes
four and seven choose the byte fill value, with value six only for scene six
in mode four. Scene mode zero and mode two then take different resource/view
preparation paths. The exact meanings of all request modes remain unresolved.

Audio selection at `0x411BC` receives the resource-derived byte returned by
`0x26A9C`, unless flag eight in the shared audio control byte at `+6` blocks it.
The scene and VBlank wrapper share `audio_vblank.h`; they no longer define
competing control layouts. The twelve-byte records at ROM `0x57224` supply a
nullable palette-range configuration to `0x11634`, whose connected callee
allocates four-byte range descriptors from a count-prefixed resource. The word
at `0x030032E0`, cleared by the initializer, is the range enable mask. The
extent of the per-scene configuration list still needs caller evidence. Other unresolved preparation entries
retain address-based names, making their unconverted status explicit.

## Installed callback and character DMA

The initializer installs the 20-byte VBlank callback at ROM `0x3A15C`. That
callback runs the reconstructed frame update, the transition alpha update and
the 84-byte character-transfer commit at `0xF7B8`. An alignment-only directive
retains the original zero tail after the callback's semantic C body.

The character-animation state at `0x030018C0` has flag, selected-frame and
elapsed-tick bytes at `+0`, `+2` and `+3`, a background pointer at `+4` and a
resource pointer at `+8`. The resource begins with a byte frame count followed
by an explicitly unknown three-byte header. Each eight-byte record supplies a
source pointer, halfword byte count and halfword duration. The 72-byte tick at
`0xF754` advances only when the flags equal three, resets elapsed time at the
selected record's duration, advances and wraps the frame against the resource
count, and sets the pending-transfer bit four.

The 28-byte start routine at `0xF79C` binds the resource/background, resets the
frame and elapsed bytes, and selects flags three. Four 16-byte lifecycle
routines at `0xF80C..0xF83C` independently clear/set bits one and two. Both bits
are required by the tick's exact equality test. Pause/resume and enable/disable
names are inferred from that relationship; arbitrary flag combinations and
caller ownership remain separate questions.

The commit clears pending bit four and configures DMA3 at `0x040000D4`. The
source comes from the selected record, the destination comes from background
control bits two/three and a `0x06000000` base, and the count is the halfword
byte count divided by two. A word-width bitfield view preserves the original
control-word access. The routine reads the DMA control after starting transfer.
This static sequence does not prove VBlank scheduling under every runtime path
or validate resource counts and lengths for arbitrary inputs.

## Display reset and frame refresh

The display-mode setter at `0xD600` resets cached display state before writing
mode with bit `0x40` and setting dirty bit two. Its reset at `0xDDA4` walks all
four background states. The 60-byte per-background reset at `0xDDCC` conditionally
releases the pointer at `+8`, clears all 108 bytes through the fill helper at
`0x27A48` (distinct from the library fill at `0x4E8B8`), sets flags `0x60`, and uses
scale 256 with flags `0x68` for backgrounds two and three. This agrees with the
already reconstructed background-update fields; it does not independently
establish the released allocation's lifecycle.

The 32-byte refresh wrapper at `0x1168` sets the forced-refresh byte at
`0x030017CC`, schedules the primary object list at `0x030024F0`, and narrows the
result to a byte. Existing fade call sites still use their earlier provisional
address alias for this now-reconstructed wrapper.

The 100-byte OAM handoff at `0x2D054` disables every unused sprite from the
pending-sprite count through index 127 in both 1,024-byte OAM banks, then sets
IRQ transfer-ready. Ordinary typed pointers express the two bank traversals.
The shared previous-OAM pointer is reloaded between writes, retaining the
original alias-sensitive behavior. This connects the frame/fade refresh path
to the VBlank wrapper that consumes and clears transfer-ready.

## Background animation loader

The loader at `0xA6C0` completes the earlier VBlank animation lifecycle path.
Its twenty-byte descriptors start at ROM `0x4F14C`; five contiguous records
(indices zero through four) precede non-descriptor data at `0x4F1B0`. Record
zero has null pointers. Four populated records supply frame lists, a palette
resource, a background-control pointer, a final-frame byte, delay and flags.
The word at descriptor `+12` remains unknown. The loader does not bound its
index; static table extent and observed callers are not proof of safety for an
arbitrary argument.

The loader updates shared frame/timing state and, when the game flags allow
transfers, shows background three, loads its palette, loads the selected frame
resource and writes its map. It merges descriptor flags and clears the forced
reload bit. Resource ownership, the unused descriptor word, and index-domain
coverage remain future evidence targets. Retained near matches demonstrate
that descriptor-base/cursor lifetime changes compiler instruction scheduling;
the accepted source has both as ordinary typed pointers, with no instruction
body, output fixup or byte mask.

## Scene-table row 4 callbacks

All three callback bodies for row 4 of the phase table at `0x0805797C`
match as C: `scene_two_page_initialize` at `0x0801FAB4` owns 236 bytes,
`scene_two_page_step` at `0x0801FBA0` owns 324, and
`scene_two_page_shutdown` at `0x0801FCE4` owns 20. The row stores the Thumb
entries `0x0801FAB5`, `0x0801FBA1` and `0x0801FCE5`. These 580 extent bytes
establish ownership of the three bodies; their names remain provisional.

The initializer resets the request selector, configures the display and tile
allocator, loads the selected background and palette, draws its text, then
sets brightness and the initial transition state. The current `SceneRequest`
and display/text owners supply its accesses and provider interfaces. Each
12-byte row has a resource pointer, text ID, font byte and vertical halfword;
its byte at `+9` remains unknown. Two physical records are observed, without
proof that every selector reloaded after a call stays within them or that all
pointed resources and text inputs are valid.

The step stores the decremented word timer before testing its old value.
State 0 fades using the new timer, state 1 waits, and state 2 fades using
16 minus the new timer before advancing the selector. It rebuilds the next
observed row or enters state 3, which submits scene request 5. Brightness
arguments retain the actual unsigned-halfword interface, and row selectors
are reloaded at the original consumers around opaque calls.

The successful source gives each of states 0, 1 and 2 its own ordinary
old-timer result in a lexical block. A shared local across all three cases
initially produced the real old-value copies and tied decrements, but first
CSE preferred the shared pseudo's longer span, reversed the load/copy pairs
and untied the decrements. FLOW then deleted the redundant reversed copies;
REGMOVE was not the cause. Separate real results avoid that demonstrated CSE
preference. This explains the matching source's compiler behavior, without
claiming the original source used these scopes.

The shutdown sets black brightness for target mask 63 at level 16, then
resets palette jobs. Its C body is 18 bytes; the final two bytes are original
zero alignment represented by a standard alignment directive. The initializer
includes 202 instruction bytes, 32 literal bytes and two internal zero
alignment bytes; the step includes 300 instruction bytes and 24 literal bytes.
Every byte is compared at its original address.

All three bodies pass ordinary and strict positive builds with real source
controls. The step's control changes its actual scene request from 5 to 6,
changing one byte; the endpoint controls change brightness 16 to 15 and mask
63 to 62. The canonical step qualification checks 45 ARM-target facts against
17 actual definitions and rejects five wrong contracts. A full progress gate
rebuilds the changed header's existing initializer and the new step.

Resource backing, selector bounds, later request writers and the wider runtime
population remain open. Owning these callbacks does not establish complete
scene or resource lifecycle execution.

## Scene-table row 26 callbacks

The three callbacks for row 26 of the phase table at `0x0805797C` match as C:
`scene_previous_parameter_return_initialize` at `0x0802BAE0` owns 200 bytes,
`scene_previous_parameter_return_step` at `0x0802BBA8` owns 52, and
`scene_previous_parameter_return_shutdown` at `0x0802BBDC` owns 52. The row
at `0x08057AB4` stores Thumb entries `0x0802BAE1`, `0x0802BBA9` and
`0x0802BBDD`. Names and gameplay meaning remain provisional. These 304 extent
bytes contain 254 instruction bytes, 44 literal bytes and six zero alignment
bytes, all compared at their original addresses.

The initializer resets the display and tile allocator, enables the object
layer, loads background 3 and its palette, prepares text background 0, and
selects font 3. It draws text ID 308 from y = 5 in twelve-pixel steps while the
text cursor remains nonempty, then starts transition 63 and audio cue 54.
The step tests input mask 1 for the configured local player and, when set,
submits `(1, 0, g_scene_previous_request.parameter)`. This is the full word at
previous-request offset `+12`, not its scene word at `+8`. The shutdown runs
the second transition, releases the primary object list, resets the display
and palette jobs, and stores byte 7 at game-state offset `0x746` through the
existing character-array owner.

The previous parameter at `0x0300437C` is copied from outgoing active parameter
`0x0300435C` after the outgoing end callback runs. The row 11 and row 14 end
callbacks can store `0xFFFFFFFF` before that snapshot. The same previous word
also has a signed choice-index alias with an owned direct writer of 1. These
are actual storage and writer facts, without evidence that those particular
values reach row 26. One concrete producer is `condition_select_row`: outside
its kind-8 branch it stores a row-table scene byte into the active parameter,
then calls `resource_scene_event(26)`, an alias of the default request wrapper.
The inspected tail preserves that parameter. Intervening callers, the outgoing
end callback and later previous-word aliases can still overwrite it. The full
producer population, row-table extent and valid resource/scene index domain
remain open.

All three bodies pass ordinary and strict positive builds and real
changed-source controls. The controls change cue 54 to 55, input mask 1 to 2,
and the shutdown byte from 7 to 6; each changes one byte in the full extent.
Three ARM-target positive contract units contain the three new definitions
and all eighteen actual called providers, and reject three contradictory
return, extra-parameter and provider contracts. The host tool version was
queried separately after qualification, not by the qualification driver.
The initializer's standard alignment directive retains its two-byte zero tail;
no executable instruction body is embedded or patched.

This establishes the three callback bodies, not complete scene execution.
Local-player bounds, valid text progress and coordinate arithmetic, resource
backing, request producers and later aliases still require their own evidence.

## Scene-table row 24 selection path

Row 24 at `0x08057A9C` now owns its three callback bodies and six connected
helpers: nine C functions / 1,544 extent bytes. The existing 212-byte step at
`0x08023578` and 88-byte direction helper at `0x080238B0` are joined by the
initializer (224), shutdown (36), refresh (172), label creation (128), line
drawing (72), display preparation (204) and content drawing (408). Names and
the global-consuming helper interfaces remain provisional.

The direction helper preserves byte wrapping and directions 0..3. The step
preserves input reads across calls, refreshes changed selections and submits
request 11 on pressed mask 2. The initializer prepares display resources and
objects; shutdown runs the second transition, releases the object list and
resets display state. Preparation and refresh construct the observed labels
and content. Line drawing advances the actual tile/y homes while scanning
text. Content drawing retains fresh scene/permutation observations between
calls, captures each resource parameter before its formatter, and preserves
the two early returns and final font restore on the long path.

The matching content source uses separate locals for the two real parameter
values. Each has one definition and one death in the same block, allowing local
allocation before the longer-lived carriers. Its real y and tile assignments
also retain the observed initialization order. These measured compiler causes
do not establish the original source spelling.

The shared header supplies the same canonical object, condition, resource,
text, queue, input and audio interfaces used by qualification. All complete
extents, literal pools and alignment participate in matching and source
controls. Input arrays still require local-player indices below four. Scene,
permutation, level, text/resource backing, later writers and gameplay/runtime
populations remain open; owning the nine bodies does not close those domains.

## Local evidence

The ignored `reports/agents/vblank-wrapper/scene-batch-manifest.json` records
all fifteen extents, direct/Thumb symbols and changed-source controls.
`publication-<function>/` and `controls/<function>/` retain source snapshots,
compiler output, linked ELF, reference/candidate bytes and complete comparison
reports. `shared-header-irq_vblank/` and `shared-header-background_animation_tick/`
revalidate the existing matches after shared declaration changes. Rejected
scene-loop, character-control and animation-loader attempts remain local.

## Phase-table row 15 menu callbacks

Row 15 at ROM `0x08057A30` names the 744-byte initializer at `0x0803E518`,
736-byte step at `0x0803E800` and 156-byte shutdown at `0x0803EAE0`. Their
Thumb entries are odd. These three callback bodies cover 1,636 extent bytes;
the initializer was already owned. The separate 80-byte result-effect helper
at `0x08040F44` completes the step's direct local path. The new three C bodies
add 972 extent bytes: 820 instructions, 140 literal bytes and 12 alignment
bytes. These are source/compiler extents, separate from runtime closure.

The step captures the request phase after transient-effect updates. Its first
phase handles pressed navigation and activation, the second handles held
navigation with a four-tick repeat byte, and the third advances selected
result effects and their countdown. Codes three, four and five select the
helper's five-tick effect cadence. Cancel submits the existing scene request
and greeting cue. The byte position is promoted to signed `int` before
conversion to `double`; addition of negative 116 produces the native signed
conversion/add/multiply sequence. The actual compiler's constant words and
full linked bytes establish that result, not a host floating-point layout.

Shutdown captures the object and old relation byte, narrows the getter's
result to a byte, performs cleanup, then subtracts the two signed-byte values.
The narrowed difference is stored at object byte `+0x64`, inside the existing
`motion_storage` owner. The relation byte at `+0x20` lies inside its 136-byte
owner. Matching preserves this order; it does not prove that the captured
object survives every cleanup input.

The chosen `void(void)` callback interfaces agree with the current phase
table contract. Player selectors, code scans, object slots, greeting/resource
indices, incoming request kinds and later writers remain open domains. A
finite table prefix or successful byte match supplies no broader bounds or
gameplay claim. See [display state](DISPLAY_RECONSTRUCTION.md#phase-15-menu-display-state).
