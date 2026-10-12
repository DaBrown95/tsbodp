# Background motion state producers

This batch reconstructs the complete adjacent setter family from `0x0800DE08`
through `0x0800E164`: 23 functions and 860 bytes. Each complete linked extent,
including its literal pool and alignment, matches the fixed reference ROM.
Each also has an actually compiled changed-source control that rejects.
These are compiler and static findings, not a runtime or gameplay test.

| Source function | ROM address | Complete extent |
| --- | --- | ---: |
| `display_set_background_position` | `0x0800DE08` | 44 |
| `display_set_background_position_x` | `0x0800DE34` | 32 |
| `display_set_background_position_y` | `0x0800DE54` | 32 |
| `display_offset_background_position` | `0x0800DE74` | 60 |
| `display_set_background_rotation` | `0x0800DEB0` | 52 |
| `display_set_background_angle` | `0x0800DEE4` | 32 |
| `display_set_background_angle_step` | `0x0800DF04` | 48 |
| `display_set_background_center` | `0x0800DF34` | 40 |
| `display_set_background_scale_limits` | `0x0800DF5C` | 32 |
| `display_set_background_scale_step` | `0x0800DF7C` | 48 |
| `display_set_background_scale` | `0x0800DFAC` | 32 |
| `display_set_background_velocity` | `0x0800DFCC` | 44 |
| `display_set_background_velocity_x` | `0x0800DFF8` | 32 |
| `display_set_background_velocity_y` | `0x0800E018` | 32 |
| `display_reset_background_waves` | `0x0800E038` | 48 |
| `display_reset_background_wave_x` | `0x0800E068` | 32 |
| `display_reset_background_wave_y` | `0x0800E088` | 32 |
| `display_set_background_wave` | `0x0800E0A8` | 36 |
| `display_set_background_wave_x` | `0x0800E0CC` | 36 |
| `display_set_background_wave_y` | `0x0800E0F0` | 40 |
| `display_set_background_wave_phase` | `0x0800E118` | 28 |
| `display_set_background_wave_step` | `0x0800E134` | 24 |
| `display_set_background_wave_amplitude` | `0x0800E14C` | 24 |

## Shared record and update path

The first fourteen functions load base `0x03002EF0` and use a `0x6C` index
stride. Their field offsets are eight bytes beyond the corresponding offsets
in the accepted background record at `0x03002EF8`. The header's
`DisplayBackgroundSystem` names this prefix-plus-record view: the existing
eight-byte display control state followed by the four background records.
`g_display_background_system`, `g_display_control` and `g_background_states`
therefore describe overlapping addresses, not independent allocations.
The later nine functions load the record base `0x03002EF8` directly. The
four-record count comes from the accepted update and commit loops; these
setters perform no index checks.

The position fields at record offsets `0x24/0x28`, velocity at `0x2C/0x30`,
scale at `0x3E`, scale step at `0x40`, limits at `0x42/0x44`, angle and its
step at `0x46/0x48`, and center at `0x4A/0x4C` are consumed by the accepted
`display_step_backgrounds` at `0x0800D17C`. Velocity setters set flag `1`,
which selects the updater's movement path. Angle and scale step setters set
flags `2` and `4` respectively for nonzero steps, or flag `8` for a zero
step. Direct angle, scale and center setters set flag `8`, which selects
matrix and reference-coordinate recalculation. None of these operations
clears a previously set update flag. Scale limits only write their two
halfwords.

Position setters and offsets mark flag `0x40`. The update path copies base
position into scroll state and applies phase offsets before the accepted
VBlank commit path writes scroll registers. The updater's outer condition
requires one of flags `1/2/4/8`; setting `0x40` alone does not establish that
an update will run. The commit also requires its separate pending context.
These conditions are retained and limit what can be claimed about a setter
call's immediate visible effect.

## Phase offset state

The record's final twelve bytes, offsets `0x60` through `0x6B`, are six
halfwords: x/y phase, x/y phase step and x/y amplitude. Their names follow
the accepted `display_offset_background` at `0x0800D4F0`, which increments
each phase when its step is nonzero, reads the high phase byte, and adds a
sine or cosine sample times the corresponding amplitude to scroll state.
The setters that accept phases shift their argument left by eight before
the halfword store. This establishes the stored representation, not an
external angle convention. Step and amplitude signedness follows the
updater's signed loads and arithmetic; the setter stores alone establish
only their halfword width. The angle and scale step APIs preserve the
explicit unsigned-halfword truncation before the zero comparison.

The x/y reset functions clear the corresponding phase, step and amplitude.
The combined reset calls both and then clears flag `0x40`. The twelve-byte
wave setter copies all six fields together and marks that flag. Individual
phase, step and amplitude setters do not change flags. `DisplayBackgroundWave`
is a typed view of those twelve bytes, not a separately discovered object.

A bounded Thumb branch scan through ROM offset `0x50000` found callers of the
velocity setter in several mapped routines, including `0x0800EB90`,
`0x08013F3C` and `0x0801BD18`. Position
calls occur in `0x080153EC`, `0x08016078` and `0x08048DDC`; the x-only setter
has a call in `0x080253B0`. The combined wave reset calls its two channel
resets directly. No aligned exact Thumb function-pointer words for these
entries were found in the ROM scan. These observations do not establish
runtime reachability or identify the gameplay meaning of those callers.

## Compiler evidence

All functions use ordinary semantic C without register constraints. The
prefix-view functions access individual indexed members directly. A local
shared record pointer changed the pinned compiler's base and addressing
allocation and failed; that useful attempt is retained. The 48-byte angle
step and scale step functions end with two zero alignment bytes after the
return. Their sources make this alignment explicit without embedding an
instruction body.

The ignored receipt index is
`reports/agents/display_audio/background_motion/ready.json`. It records
23 exact positives and 23 rejecting changed-source controls, including
changed update flags, phase shifts, reset values, center/limit values and
step/amplitude values. Raw complete outputs, expected slices, commands and
failed comparisons remain in the same ignored directory. The call evidence
and original disassembly are also local there. These source names and type
views remain inferred; no proprietary source or asset was used in them.

The retained 640-byte map writer at `0x0800CEFC` and the interpolation and
tile-fill candidates remain outside this batch's accepted coverage.
