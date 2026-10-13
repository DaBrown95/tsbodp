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

## Local evidence

The ignored `reports/agents/vblank-wrapper/scene-batch-manifest.json` records
all fifteen extents, direct/Thumb symbols and changed-source controls.
`publication-<function>/` and `controls/<function>/` retain source snapshots,
compiler output, linked ELF, reference/candidate bytes and complete comparison
reports. `shared-header-irq_vblank/` and `shared-header-background_animation_tick/`
revalidate the existing matches after shared declaration changes. Rejected
scene-loop, character-control and animation-loader attempts remain local.
