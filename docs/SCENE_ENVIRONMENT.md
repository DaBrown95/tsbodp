# Scene clock, palette, audio and retained display

Seven connected replacements add 644 matching C bytes. Each complete original
extent, every literal pool and all alignment bytes match after compiling and
linking the current public source. All seven are ordinary C with no register
bindings or instruction-body assembly. Their separately compiled changed-source
controls reject. This establishes source and byte comparisons; it does not
establish runtime scheduling, gameplay behaviour or a complete game inventory.

| Function | ROM offset | Bytes | Changed-source differences |
| --- | --- | ---: | ---: |
| `scene_refresh_environment` | `0x266B0` | 228 | 1 |
| `scene_refresh_period_audio` | `0x26854` | 180 | 1 |
| `scene_allocate_retained_palette` | `0x26908` | 32 | 2 |
| `scene_retain_display` | `0x26928` | 84 | 1 |
| `scene_release_display` | `0x2697C` | 16 | 1 |
| `scene_clear_retained_display` | `0x2698C` | 100 | 1 |
| `scene_step_early_exit` | `0x269F0` | 4 | 1 |

The accepted primary-scene step calls the clock/audio refresh paths for its
selected changed view. The accepted primary exit calls the two retained-display
paths according to the queued scene kind. The accepted request-queue initializer
calls the palette allocator. These are observed call connections, separate from
proof of every possible runtime caller or scene-kind domain.

## Clock and audio connection

The current clock at `0x03003958` uses the already reconstructed eight-byte
`DisplayTimeRecord`. The access view adds clocks at relative `+0x71C` and `+0x724`
and an enable byte at `+0x72C`. Only those fields are named; the intervening bytes
and complete world storage remain unknown. The names `first` and `second` reflect
the observed order of comparisons rather than an established gameplay event.

The refresh captures a null palette result before reading the clock period.
A changed period updates scene context `0x03004320 + 4`, then queries the
reconstructed palette selector. For an unchanged period with the enable byte set, the accepted
time-equality helper compares hour and minute through mask six. A first-clock
match sets context flag one and can load background animation one; a second-clock
match clears that flag and can stop the default animation. Game flag `0x10` gates
the animation operations, and the load also requires scene ID at most fourteen.
The alpha configurator follows either eligible animation change.

The palette selector is queried after the enabled-clock branch even if neither
clock comparison matched. A nonnull result creates the accepted palette job for
first colour 64, count 192, duration eight, interval zero and flags one. Its index
is stored at context `+8`, still named `unknown_08` in the existing shared type.
The compiler match does not justify changing every use of that shared word.

The audio refresh independently reads the current period and compares the saved
context period. Unless audio-control flag eight is set, periods zero through
three select one byte at table-record offsets eight through eleven; other
periods pass zero. Records at `0x08057224` have the same twelve-byte stride and
base as the existing palette-range configuration access view. The new bounded
view interprets only these four audio bytes and does not infer a table bound.
The call uses the accepted `audio_select_sequence` provider.

## Retained display connection and boundaries

The allocator obtains 512 zeroed bytes for context `+12` and writes scene ID 50.
The retain path forces a background-animation reload, stops the actor speed cue
through the accepted provider at `0x9DF0`, and snapshots map VRAM through the
accepted map helper.
Unless game flag `0x20000` is set, it retains the primary object list through the
accepted provider at `0x121C` and sets game flag eight. It then sets request mode two and copies 256 halfwords
from OBJ palette memory `0x05000200` to the retained palette allocation. The
BIOS-copy control is the original halfword count, not an inferred byte count.

The short release path calls the accepted background-animation reset at `0xA834`
and the accepted map resource release. Its complete boundary is `0x2697C..0x2698C`: the next PUSH at
`0x2698C` begins a separate 100-byte cleanup function. An earlier raw inspection
range combined them; that range is retained as evidence and is not credited as
one function.

The separate cleanup runs only with game flag eight. It clears that flag,
restores the retained primary objects through `0x125C`, releases that linked list and
calls the reconstructed need-state cleanup at `0x2EB9C`, then clears both
reconstructed transient-effect families. It clears audio-control bits one and eight, destroys map registration
through the canonical grid helper, clears the registration pointer, and calls
the short release's two providers. The volatile audio-control field retains its
observed read/update accesses. The separate provider now has a complete compiler
match, as described below.

The primary-step early-exit query is exactly four bytes at `0x269F0..0x269F4`
and returns byte zero. The following PUSH at `0x269F4` begins a separate dispatch
body. Its table and cases receive no credit from the constant query. The byte
return spelling is supported by its accepted caller's narrowing and comparison;
it remains a provisional C contract.

## Verification and retained failures

Local complete comparisons and current header/source receipts are recorded in
`reports/agents/frame-input/scene-primary-view/scene-environment-ready.json` and
its canonical proof directory. Each source has a real separately compiled
mutation: palette-job duration, audio gate, allocation size, request mode,
release provider, cleanup gate or query result. No comparison was masked and
no output was patched.

The earlier complete-size palette-selector attempt differed in 85 bytes. Its
initial 188-byte attempt, pointer-lifetime variants, raw original and rejected
compiler diagnostic remain private; a later connected replacement closes the
complete 192-byte extent as described below. Failed prefixes receive no C credit.

The central object renderer and copied ARM sort remain difficult explicit
candidates. The fixed 319,640 mapped-extent comparison baseline is not a claim
of complete game coverage.

## Primary-list, cache, background and cue providers

A further six connected replacements add 248 matching C bytes, bringing this
clock and retention path to thirteen functions and 892 bytes. Every new provider
has a complete linked match and a separately compiled one-byte mutation rejection;
all use ordinary C without register bindings. Existing callers and shared-header
consumers receive fresh positive and actual changed-source-control proofs, with
zero additional coverage credited to those existing functions.

| Function | ROM offset | Bytes |
| --- | --- | ---: |
| `frame_retain_primary_objects` | `0x121C` | 64 |
| `frame_restore_primary_objects` | `0x125C` | 60 |
| `frame_enable_primary_object_flags` | `0x1298` | 32 |
| `frame_disable_primary_object_flags` | `0x12B8` | 36 |
| `background_animation_reset` | `0xA834` | 16 |
| `scene_stop_actor_speed_cue` | `0x9DF0` | 40 |

The retain helper traverses the primary list, releases each object's display
allocation through the accepted deferred-release routine, and sets object flag
`0x02000000`. It reloads each next pointer after those calls, matching the original
sequence. It then copies the primary first/last pointers into a retained list at
`0x03002CA0` and clears both primary pointers. The meaning of the flag beyond this
paired retention/restore use is provisional.

Restore moves those two links back, clears the retained list, clears the same
flag across the restored primary list, and fills 572 bytes at the existing shared
display-cache pointer with zero. That observed byte count does not establish a
record-count bound or the complete cache layout. The separate flag helpers consume
full unsigned masks and directly update each linked object's flags; they add no
list, mask or allocation guards. The accepted scene initializer also uses restore
and the enable helper, preserving its previous ABI and bytes under canonical names.

The background reset calls the already matching stop routine and then the already
matching 16-byte state clear. Its own body is fourteen instruction bytes followed
by the original two zero alignment bytes; natural assembly under the pinned
assembler preserves the complete sixteen-byte extent. The cue helper checks the
existing scene-player mode byte at world `+0x42E`; mode one passes the existing
speed-cue handle at `0x03002E94` to the accepted sample-stop routine. No sample
activity or mode-domain claim is inferred from that static call.

The new `scene_retention.h` is guarded and contains forward declarations, globals
and prototypes. It imports no structure-bearing legacy headers. Existing scene
and environment types keep their layouts; `scene.h` only replaces the two obsolete
provider declarations with this guarded interface. The scene/environment callers
use canonical names, and their metadata retains the original physical addresses.

The first two private attempts used source mask `0x20000000` and differed by one
byte each. The original `MOV 128` followed by a shift of eighteen establishes
`0x02000000`; correcting that source constant closes both comparisons. The failed
source, assembly and raw bytes are retained without output editing. Fresh controls
change that mask, switch the flag update operation, alter the reset provider or
change the cue's mode condition. The exact providers and all affected callers are
recorded in the ignored `scene-retention-ready.json` and its current proof tree.

## Palette selection and need-state exit cleanup

Two further connected replacements add 296 matching C bytes. This documented
clock and retained-display path now contains fifteen matching functions and
1,188 bytes. Both new complete extents, pools and alignment match under their
recorded compiler and assembler profiles. Both use ordinary C with no register
bindings. Fresh actual changed-source controls reject; the existing environment
functions and accepted scene-initialization palette caller also receive fresh
positive and changed-source comparisons, without additional C coverage.

| Function | ROM offset | Bytes | Changed-source differences |
| --- | --- | ---: | ---: |
| `scene_palette_source` | `0x26794` | 192 | 70 |
| `frame_clear_need_effect_states` | `0x2EB9C` | 104 | 1 |

The palette table at `0x0805747C` has an observed sixteen-byte stride with four
pointer slots. Period zero chooses slot three when context flag one is set and
slot zero otherwise. Period one chooses slot three only with that flag; periods
two and three choose slots one and two. Other periods take the fallback directly.
Any selected null pointer also takes the fallback word at `+0x40` in the existing
72-byte scene-resource record at `0x08056414`. That shared word keeps its neutral
name: this caller's use as an address does not establish all serialized uses.
Neither table's complete bound or possible scene-ID domain is established here.
The complete selector boundary is `0x26794..0x26854`, including its literal pools;
the next PUSH begins the already matching period-audio function.

The exact selector uses a named integer table address and a retained scene-ID
pointer, then reads the selected real pointer slot. Its explicit missing-palette
switch block keeps the shared default scene-ID load before the flag-false period
one branch. Placing that block last instead produced a 196-byte mismatch, retained
alongside the earlier failures. Changing the second pointer-slot offset from four
to eight makes the control's compiled case sharing differ; the resulting 172-byte
candidate rejects against the full 192-byte expected extent. No output bytes were
edited or ignored.

The exit helper traverses the need-effect active list at `0x03005868`, caching
the next node before calls. It uses the existing 256-byte state access view and
three observed 24-byte actor records at state `+0x0C`. A nonnull auxiliary object
at `+0x58` receives state one through the accepted transition helper, then its
pointer is cleared. Each nonnull actor in those three records is detached using
the existing legacy object ABI cast. If the current node is the active tail, the
helper updates the tail to its previous pointer, then releases the node through
the accepted pool helper and free-pool root at `0x03001E34`. The casts do not assert
that this 256-byte state has the complete layout or semantics of a frame object.

The helper adds no bounds, callbacks or guards absent from the original. Its
complete boundary is `0x2EB9C..0x2EC04`, including literal words at `0x2EBFC` and
`0x2EC00`; the next PUSH is a distinct entry. The current retained-display caller
uses its canonical `void(void)` interface. The primary-scene exit is a separate
caller whose alias and verification are maintained with that module. Changing
auxiliary state one to two compiles and rejects by one byte.

The public `scene_palette.h` owns only the bounded four-pointer record and its
provider declarations. The public `frame_need_effect_clear.h` owns only the
cleanup prototype. Their source files import the existing role/layout headers
separately, avoiding repeated definitions from legacy unguarded scene/frame
headers. Current source/header hashes, complete raw comparisons and actual
controls are recorded in the ignored `palette-need-cleanup-ready.json`. These
are static and compiler findings, separate from runtime or gameplay evidence.
