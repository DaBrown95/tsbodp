# Resource command reconstruction evidence

This continuation adds 48 verified C functions covering 2,880 bytes: all 47
nonzero resource-program callbacks cover 2,856 bytes, and the object-group count
reader covers 24 bytes. Complete linked extents match at their original ROM
addresses, including literal pools and zero tail alignment. Each replacement has
a compiled, linked changed-source negative control. These are static and compiler
claims; runtime and gameplay behaviour have not been tested.

The callback table at `08051B18` has 48 entries in this observed dispatch family.
Entry zero is null and represents the terminator handled by the previously
accepted `resource_execute_group`; entries 1 through 47 are Thumb callbacks.
The corresponding byte-length table is at `080528E0`. All 47 bodies occupy the
connected span `08011E40` through `08012968`, whose end is independently confirmed
by the last callback's literal pool and the following function. Table pointers,
control flow, literals and full byte comparisons establish the accepted
boundaries; an exploratory scanner's estimated ends were not treated as proof.
The tables themselves remain original, explicit unconverted data.

| Command | Address | Provisional name | Extent bytes | Record bytes |
| ---: | --- | --- | ---: | ---: |
| - | `0800AE50` | `resource_group_object_count` | 24 | - |
| 16 | `08011E40` | `resource_command_start_view_motion` | 248 | 12 |
| 18 | `08011F38` | `resource_command_start_view_timer` | 148 | 12 |
| 21 | `08011FCC` | `resource_command_start_window_transition` | 84 | 16 |
| 1 | `08012020` | `resource_command_wake_object` | 40 | 8 |
| 2 | `08012048` | `resource_command_set_object_timer` | 48 | 8 |
| 3 | `08012078` | `resource_command_set_object_flag` | 36 | 8 |
| 4 | `0801209C` | `resource_command_clear_object_flag` | 36 | 8 |
| 5 | `080120C0` | `resource_command_pause_audio` | 12 | 4 |
| 6 | `080120CC` | `resource_command_resume_audio` | 12 | 4 |
| 7 | `080120D8` | `resource_command_select_sequence` | 32 | 8 |
| 8 | `080120F8` | `resource_command_play_cue` | 12 | 8 |
| 9 | `08012104` | `resource_command_set_sequence_volume` | 12 | 8 |
| 10 | `08012110` | `resource_command_set_sample_volume` | 12 | 8 |
| 11 | `0801211C` | `resource_command_start_delay` | 36 | 8 |
| 12 | `08012140` | `resource_command_decrement_counter` | 36 | 8 |
| 13 | `08012164` | `resource_command_increment_counter` | 36 | 8 |
| 14 | `08012188` | `resource_command_select_resource` | 40 | 8 |
| 15 | `080121B0` | `resource_command_reset_object` | 72 | 8 |
| 17 | `080121F8` | `resource_command_select_actor` | 88 | 8 |
| 19 | `08012250` | `resource_command_stop_view_effects` | 72 | 4 |
| 20 | `08012298` | `resource_command_position_object` | 56 | 12 |
| 22 | `080122D0` | `resource_command_load_background_animation` | 36 | 8 |
| 23 | `080122F4` | `resource_command_attach_object` | 84 | 12 |
| 24 | `08012348` | `resource_command_start_object_interval` | 96 | 16 |
| 25 | `080123A8` | `resource_command_start_object_effect` | 76 | 8 |
| 26 | `080123F4` | `resource_command_set_object_animation` | 92 | 8 |
| 27 | `08012450` | `resource_command_submit_scene` | 44 | 4 |
| 28 | `0801247C` | `resource_command_scene_event` | 28 | 4 |
| 29 | `08012498` | `resource_command_set_group_flag` | 76 | 8 |
| 30 | `080124E4` | `resource_command_clear_group_flag` | 76 | 8 |
| 31 | `08012530` | `resource_command_wake_group` | 76 | 8 |
| 32 | `0801257C` | `resource_command_branch_view_first` | 72 | 12 |
| 33 | `080125C4` | `resource_command_branch_view_second` | 72 | 12 |
| 34 | `0801260C` | `resource_command_branch_view_value` | 96 | 12 |
| 35 | `0801266C` | `resource_command_branch_view_value_alternate` | 96 | 12 |
| 36 | `080126CC` | `resource_command_set_triple` | 20 | 8 |
| 37 | `080126E0` | `resource_command_set_display_kind` | 24 | 8 |
| 38 | `080126F8` | `resource_command_start_object_effect_alternate` | 84 | 8 |
| 39 | `0801274C` | `resource_command_follow_object` | 72 | 8 |
| 40 | `08012794` | `resource_command_signal_follow_target` | 36 | 8 |
| 41 | `080127B8` | `resource_command_stop_object_effect` | 48 | 8 |
| 42 | `080127E8` | `resource_command_start_special_object_effect` | 68 | 8 |
| 43 | `0801282C` | `resource_command_branch_arguments` | 124 | 12 |
| 44 | `080128A8` | `resource_command_prepare_display` | 24 | 8 |
| 45 | `080128C0` | `resource_command_finish_object_effect` | 40 | 8 |
| 46 | `080128E8` | `resource_command_reset_selected_objects` | 56 | 4 |
| 47 | `08012920` | `resource_command_set_view_flag` | 72 | 8 |

The records begin with a word selector and byte arguments. The C record view
uses a zero-length trailing byte array so it preserves the four-byte selector
size without inventing a fixed command size. The original byte-length table
contains records of 4, 8, 12 and 16 bytes. Halfword arguments are loaded from
observed aligned argument positions. No bounds checks absent from the original
have been added. Group object counts come from a relative halfword table at
`03002ED8`; the object pointer lookup at `0800AEE4` remains unconverted.

The commands connect the resource group walker to frame-object flags, state,
animation requests, positions, countdowns and follow targets. The object state
view exposes the observed bytes at `4D`, `4E`, `4F`, `51`, countdown word at `58`,
and command-dependent words or packed fields at `64`, `68` and `6C`. Unions express
these differing uses rather than assign a universal meaning to each field.
Positions written by the command at `08012298` are signed halfword arguments
shifted into the object's fixed-point words. The animation command at
`080123F4` saves the special byte before narrowing the animation selector, sets
state six, requests selector plus `60`, then stops velocity and acceleration.
These names follow the observed reads, writes and connected callees and remain
provisional.

The 248-byte view-motion and 148-byte view-timer handlers configure repeated
40-byte records at `030030B0`. They use the shared view context at `030040E0`:
12-byte slots contain an object pointer and halfword flags, and the byte at `30`
is the view count. The motion handler saves velocity, clears it, selects either
the requested object or the view object, and initializes effect parameters,
phase and completion bytes. The timer handler scales its duration by 30,
configures a signed fixed-point parameter and selects mode three. No frame-rate
or duration-unit runtime claim follows from the constant 30. The command at
`08012920` changes mask `0004` in the current view's slot flags. These observations
refine the shared transition context without changing its known offsets.

The conditional handlers read the game-state base at `03003950`. One partial
view exposes 24-byte cells beginning at `444`, with six cells per 144-byte row;
another exposes the selected actor byte at `748`. They share a single union
global so the two address views do not acquire conflicting global types. The
outer cell extent is unknown; the one-row declaration describes a partial
layout, not a validated allocation limit. Two scalar predicates inspect the
first or second byte; the other two copy a cell into stack storage and inspect
its values. The argument predicate at `0801282C` copies two eight-byte defaults
from `08051AA4`, sets their row and column bytes, and compares them through
`0801081C` with context `03003958` and selector six. Each branch activates one of
two command-supplied resource group pairs through `resource_activate_groups`.

Display commands hand off to the accepted background-animation and transition
paths. Audio commands select a sequence, play an animation cue, pause/resume,
set sample/sequence volume or stop a handle. Canonical names from `audio_game.h` are used
for the cue and sequence calls. The connected audio continuation also replaces
the game-facing pause, resume, volume and stop helpers; their lower-level player
and mixer dependencies remain unconverted. This does not claim the entire audio
engine. Scene submission, actor selection and several
display configuration callees also remain explicit unconverted dependencies.

`resource_command_follow_object` uses one fixed C register binding for its
object local to reproduce the compiler's allocation. This is a compiler
constraint around semantic C, not an embedded instruction body or runtime
evidence. The standalone alignment directives provide the original zero tail
alignment only. No replacement patches an output, masks a difference or changes
the reference ROM or hashes.

The ignored agent reports retain exploratory disassembly, useful failed
candidates, complete compiler inputs and linked outputs, raw expected and
candidate extents, and all changed-source controls. An early pause/resume
control referencing an undeclared alternate alias failed to link; it was not
accepted. The retained final controls make two calls to the same declared
helper and produce real linked differences. All formatted public sources and
controls were reverified, as were the affected published resource builders and
scene initializer. Remaining connected targets include the resource controller
at `0800AD1C`, word-group copier at `0800B018`, object lookup at `0800AEE4`, view
effect updates and the called scene/configuration operations.
