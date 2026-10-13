# Condition panel object and label path

The three object/label functions cover 576 verified matching C bytes. Their
connected input consumer adds another 484 bytes, bringing this path to four
functions and 1,060 bytes. The connected close and marker lifecycle add three
functions and 340 bytes, for seven functions and 1,400 bytes:

| Function | ROM address | Complete extent |
| --- | --- | ---: |
| `condition_panel_create_objects` | `0x0801D888` | 232 bytes |
| `condition_panel_draw_row_labels` | `0x0801D7DC` | 172 bytes |
| `condition_panel_update_column_objects` | `0x0801D730` | 172 bytes |
| `condition_panel_step_input` | `0x0801D39C` | 484 bytes |
| `condition_panel_close` | `0x0801D970` | 48 bytes |
| `condition_marker_create` | `0x0801D9A0` | 120 bytes |
| `condition_marker_step` | `0x0801DA18` | 172 bytes |

The 460-byte setup at `0x0801D1D0` calls all three functions and the still
unconverted detail drawer at `0x0801D580`. It configures backgrounds, invokes the
matching selected resource loader at `0x0803AFF0`, and selects a condition row
and cell before these display operations. This direct call path and the shared
condition-definition/cell accesses motivate the provisional panel names. The
setup and detail drawer remain original ROM regions; their private C trials
have no source-coverage credit.

The creator writes exactly fifteen object-pointer slots from `0x030043B0`:
six column objects at indices 0 through 5, four fixed/selected controls at
indices 6 through 9, and five detail objects at indices 10 through 14. These
slots overlap the existing scene UI object storage. They establish this
path's sixty accessed bytes, not independent storage ownership or the complete
allocation. The creator reloads the selected row after factory calls and
chooses each column object's subtype from the cell's first byte and the
definition's first byte. These byte roles remain neutral. Two separately scoped
`r0` bindings retain real factory return pointers only until their stores;
neither pointer is used across a subsequent call. Other locals and both
updaters use ordinary C without register constraints.

The row label loop writes number substitutions 1 through 5 and draws localized
text at five four-byte coordinate records rooted at `0x0805344C`. The selected
label's style also depends on the shared request mode at `0x03004350`; mode
zero changes object slot 9's ID and requests its variant state. Other labels
compare against the world row limit. The returned tile index is carried into
the next draw. No claim is made about the rendered words, colors or appearance.

The column updater scans six object slots. A zero first definition byte clears
object flag bit 0. Otherwise it writes the subtype halfword, requests variant
state 58, sets that flag and refreshes the object's animation resource. It
reloads the object slot after calls as the original code does. The semantic
cursors retain the observed four-byte pointer and 24-byte cell advances.

The partial world view is rooted at `0x03003950`. It observes an integer at
`+4`, a selected-row word at `+0x440`, and 24-byte cells beginning at `+0x444`
with a 144-byte row stride. Its one declared outer row documents an access
view; it does not establish a complete world-state extent or the incoming row
domain. The column-definition view begins at `0x08059A44`, eight bytes into the
existing 32-byte `ConditionRow` table at `0x08059A3C`. Six pointer fields are
followed by an eight-byte stride tail overlapping the next row header. That
tail is not interpreted as additional columns. The original operations have
no guards for the supplied row, definition pointers or created object pointers;
the reconstruction preserves their behavior rather than adding checks.

The input consumer first gates directional work on the pressed-key array at
`0x03004228`. Its mode and selection tests use the distinct local pressed-key
array at `0x03004250`, indexed by the established local-player byte at input
context `+0x31`. Masks `0x80/0x40` enter or leave mode one and update slot 8's
visibility flag. Masks `0x20/0x10` move within the six columns in mode one;
other modes move the requested row from zero through the world row limit. A
column move redraws details and changes slot 8's ID and variant. A row move
invokes the matching labels and column objects before the original detail
drawer. Directional cue zero is requested even when a tested limit prevents a
move, as in the original. The tests establish no general validity guarantee
for an incoming request value, object slot or definition.

The final local masks `0x100/0x200` write command 17 or 16 to the byte at world
`+0x73F`, then submit the corresponding default request and cue 11. This byte
is a distinct offset from the neighboring world fields used by other paths.
Its guarded alternate prefix view expresses the observed base-plus-offset
store without declaring a complete world layout. If neither local command is
selected, mask `0xA` comes from the pressed-key array at `0x03004228`; it submits
kind 1, mode 2 and the word at `0x03004334`, followed by cue 2. The neutral
panel return-argument alias is distinct from the existing `g_resource_scene_arg`
word at `0x03004370`; these are separate observed addresses. Preserving
these two array roots resolves the otherwise missing final halfword read.
Direct C input expressions retain the original mask-register choices without
register bindings or volatile qualifiers. The detail provider, setup routine
and their useful failed matches remain explicit originals.

All seven complete original extents, including literal pools and alignment,
match independently. Real changed-source loop/column-bound, close-parameter, marker-variant and
marker-flag controls produce different bytes. Source objects and linked extents contain only allocated `.text`, with
one function span and no unresolved linked relocations. Useful failed attempts
and the actual comparison bytes remain in ignored local reports. These compile
and byte results are separate from runtime/UI behavior and whole-ROM equality.

The close operation resets the shared full-word request parameter to -1, runs
the existing second transition dispatcher with 63 and zero, and releases the
primary object list before resetting display state and clearing scene slots.
The original transition dispatcher and display stage at `0x080117BC` remain
explicit unconverted providers. The five cleanup calls also appear in the
already matching scene-close path; the extra parameter reset establishes this
panel-specific entry.

Entry 22 of the existing factory table at `0x0804F278` contains this marker
constructor, and its literal pool supplies the step callback at `0x0801DA18`.
These observed pointers connect the matching resource-spawn dispatcher to the
constructor and callback without establishing the table's complete bounds.
The constructor agrees with the existing two-byte-argument resource-factory
interface. The marker factory obtains the existing group/slot payload, allocates the object
from its ID, positions it from two signed halfwords, and installs its own step
callback in the shared object callback field. It initializes state zero and
variant seven, copies row, column, entry and completion-selection bytes into
object offsets `+0x64` through `+0x67`, and enables flag eight. It retains the
original allocation-null test and the absence of a payload-null test. The
unsigned fixed-point shifts preserve the halfword bit patterns without adding
a signed-negative left shift. The payload view observes fourteen bytes; its C
alignment does not prove an allocation size or record stride. The state overlay
ends at `+0x67` and does not declare a complete object allocation.

In state zero, the marker chooses complete or active condition fields from its
completion-selection byte. Entry 255 selects the group-level field; other
entries select the entry-level field. It tests only the result's low byte and
requests state one when that byte is nonzero. State one sets object flag two,
reloads the object's payload through owner ID and slot, and activates the group
and slot at payload `+0x0C/+0x0D`. Other states perform no work. No condition
index bound, callback invocation guarantee or rendering behavior is inferred.

This path exposed a return-interface refinement in the four existing condition
getters. Each original getter uses a byte load which produces a complete
zero-extended return word. The canonical C return model now expresses that word;
the stored fields remain bytes and can hold any value from zero through 255.
Ten previously matching direct callers retain explicit observed low-byte casts.
The merged marker result likewise narrows at its final truth test. All four
provider definitions, ten direct callers and the remaining current shared-header
consumers have fresh complete-extent matches and real changed-source controls.
This is a consistent ABI/access model supported by the bytes, not a claim that
original type declarations or a boolean-only field domain were recovered.
