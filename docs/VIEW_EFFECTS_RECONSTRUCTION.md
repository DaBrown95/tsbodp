# View effect reconstruction evidence

The connected continuation of the resource view commands adds 18 verified C
functions covering 1,528 bytes. Each complete extent matches at its original
address, including literal pools and zero tail alignment, and each has a compiled
and linked changed-source negative control. These are static/compiler results;
runtime and gameplay behaviour have not been tested.

| Address | Provisional name | Bytes |
| --- | --- | ---: |
| `0800E32C` | `transition_reset_view` | 124 |
| `0800E6F4` | `transition_approach_view` | 448 |
| `0800E920` | `transition_get_view_mode` | 24 |
| `0800E938` | `transition_set_view_origin` | 36 |
| `0800E95C` | `transition_set_view_position` | 60 |
| `0801E248` | `resource_prepare_object` | 40 |
| `0801E0F8` | `resource_view_actor_tick` | 196 |
| `0800E998` | `transition_configure_view_move` | 80 |
| `08027218` | `frame_sine` | 68 |
| `0802725C` | `frame_cosine` | 76 |
| `0802731C` | `frame_fixed_multiply` | 32 |
| `080273B8` | `view_subtract_point` | 24 |
| `080273D0` | `view_copy_point` | 12 |
| `08027420` | `frame_direction_from_velocity` | 72 |
| `08001978` | `frame_make_velocity` | 84 |
| `08027468` | `view_direction_angle` | 44 |
| `08027494` | `view_point_distance` | 80 |
| `08027548` | `resource_scale_value` | 28 |

The scene initializer calls the controller at `0800E3A8`. The controller and the
accepted resource command handlers use repeated 40-byte effect records at
`030030B0`; the controller also uses repeated 48-byte motion records at
`030017D8`. This identifies a connected configuration/update path. The motion
record has an object pointer at zero, four eight-byte point fields at `04`,
`0C`, `14` and `1C`, a speed word at `24`, mode halfword at `28`, delay halfword
at `2C` and interpolation byte at `2E`. The two unnamed points retain provisional
names because their complete roles have not been established. The reset function
clears all four points through `080273D0`, selects mode one, clears the object
pointer and effect state, and sets interpolation to one.

The movement configurator receives a point by value in the first two argument
registers, followed by speed, delay and a byte view index. Its field-wise writes
reproduce the original allocation and stores; it selects mode two and clears the
effect mode. The two-word point type follows the observed calling convention and
shared position accesses, not a recovered original declaration.

The 448-byte approach function receives the same point by value. It adjusts the
speed through the helper at `08027218` while the effect's elapsed halfword is at
most 63 and its done byte is clear, advances that halfword by two, and sets done
when the threshold is crossed. When near the target it instead decreases the
elapsed halfword. The accepted helper at `0802731C` divides each signed input by 64, multiplies
the results, then divides the signed product by 16, preserving truncation toward
zero. The accepted point-distance and direction helpers are described below.
Their names describe the observed inputs and results and remain provisional.

The function classifies the current point against the target plus or minus the
current speed. Classification eight snaps both coordinates to the target and
returns eight. Otherwise it computes a delta, obtains a byte direction selector,
scales the two-word vector from `0804EC00` by speed, advances both coordinates
and returns zero. The direction result is masked to 31, so this path addresses a 32-vector table.
The vector table remains original, explicit unconverted data.
The C contains the nested classification decisions rather than copied original
instructions. Its exact match required explicit assignments in each branch;
several semantically related expression and type variants are retained as failed
local comparisons. The three view functions and eight initial math helpers need no fixed register binding.

The sine and cosine helpers use the quarter-wave table at `08057860`, whose
observed values at indices zero and 64 are zero and 65,536. They fold a byte
phase according to its upper two bits and negate the second half of the cycle.
The cosine helper first adds 64 to that byte phase. This evidence corrects the
earlier sine/cosine aliases used by the frame position caller: `08027218` is
sine, and `0802725C` is cosine. No table data is replaced by C in this batch.
The functions retain integer argument prototypes and explicitly narrow the
phase internally, reproducing both complete original extents.

The point-copy and subtraction helpers use two signed word components. The
approximate distance takes two points by value, forms their difference, takes
component magnitudes and returns the larger magnitude plus three eighths of
the smaller. Inline semantic subtraction and magnitude helpers reproduce the
original stack storage without copying instructions. The direction helper
shifts both fixed-point components by 16, narrows them to signed halfwords,
calls the BIOS arctangent wrapper at `0804C8BC`, rounds the angle into 32 sectors
and adds eight sectors modulo 32. The BIOS wrapper remains explicit unconverted
low-level code and receives no C credit from this function.

The connected velocity helpers extend this path into frame movement. The
72-byte classifier at `08027420` receives a two-word point by value, takes the
sign and magnitude of its components, and combines four classification bits:
x sign, y sign, x greater than three times y, and y greater than three times x.
It indexes the 16-byte direction lookup at `08057964`. The table remains
unconverted data; the by-value point declaration is inferred from the register
moves and the exact match, not from an original source declaration.

The 84-byte producer at `08001978` selects a component table at `0804EB80`
when flag `20000000` is set, `0804EB40` when flag `00004000` is set, and
`0804EB00` otherwise. It multiplies both selected vector components by the
speed through the accepted fixed multiply helper, writing an output point.
The table names are provisional descriptions of these three choices. The C
advances a typed component pointer between x and y reads. It binds that pointer
to `r4` to reproduce the original compiler allocation and branch scheduling;
this is a compiler constraint on semantic C, with no embedded instructions.
The complete 84-byte match and a changed flag negative control establish the
compiler result, not runtime coverage of direction indices or flag combinations.

The resource scale helper is used by the accepted 248-byte view-motion command.
It treats the input halfword's high bit as a sign and its remaining 15 bits as
a magnitude, scales that magnitude by 256 and applies the sign. This follows
the observed shift, mask `007FFFFF` and signed test; it does not establish the
original source's numeric typedefs. Overflow and extreme-input behaviour have
not been validated at runtime.

The mode getter and two direct point setters complete the simple motion record
access path. `0800E938` changes the current position only; `0800E95C` changes
both current position and target through chained component assignments. The
latter is called by the unconverted transition window callback at `080184D4`.
Both setters receive a two-word point by value followed by a byte index. This
refines the earlier scalar x/y declaration while preserving its observed ABI;
the old windows candidate and comparisons remain preserved locally.

The accepted resource command handlers at `080123A8` and `080126F8` install
an actor callback for object ID zero through the 40-byte helper at `0801E248`.
The installer writes callback `0801E0F8` to the object's step slot at `88` and
sets bit one in the current 12-byte transition view slot. The callback covers
196 bytes including its zero tail alignment before the next function at
`0801E1BC`. It calls the still-unconverted actor state interpreter at `08005804`,
reads direction at `12` and pending update flags at `4F`, regenerates velocity
for bit eight, and updates animation variant for bit four. For bits `12`, variant
state three chooses animation six and regenerates velocity; other variant
states choose animation one and clear both velocity words. Direction above four
sets render byte `D3` bit `10`, and other directions clear it. The callback then
calls the layer/state helper at `0802B2FC` and clears the pending update byte.

The actor callback reuses the frame subsystem's partial actor object view and
the signed direction-to-variant table declaration at `0804F1B0`. Its word-sized
local direction and pending values, and per-access typed views of the same
object pointer, reproduce the original register lifetimes without bindings.
The callback role follows the installers and fields; it does not establish the
complete actor state machine or behaviour during gameplay. Its exact match and
changed direction-threshold control are recorded with the other accepted proofs.

The controller at `0800E3A8` remains unconverted. Its six-way switch connects
tracking, movement, delay, return movement and the mode-five resource effects.
A semantic candidate exists with useful raw comparison evidence, but differences
in pointer/type evaluation and compiler allocation prevent source coverage.
The mode setter at `0800E8B4` also remains unconverted: a compact candidate does
not reproduce the original table and extent. Whole-ROM matching retains their
original bytes and does not grant them C credit.

Local ignored reports preserve source snapshots, compiler inputs and assembly,
linked outputs, complete expected/candidate extents and changed-source controls.
Further connected targets are the controller, the view mode setter and the
view projection/display handoff. No output
patches, difference masks or reference changes were used.
