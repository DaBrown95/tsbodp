# Condition panel object and label path

The three object/label functions cover 576 verified matching C bytes. Their
connected input consumer adds another 484 bytes, bringing this path to four
functions and 1,060 bytes. The connected close and marker lifecycle add three
functions and 340 bytes. The detail drawer adds another 432 bytes and its setup adds 460 bytes, for
nine functions and 2,292 bytes:

| Function | ROM address | Complete extent |
| --- | --- | ---: |
| `condition_panel_create_objects` | `0x0801D888` | 232 bytes |
| `condition_panel_draw_row_labels` | `0x0801D7DC` | 172 bytes |
| `condition_panel_update_column_objects` | `0x0801D730` | 172 bytes |
| `condition_panel_step_input` | `0x0801D39C` | 484 bytes |
| `condition_panel_close` | `0x0801D970` | 48 bytes |
| `condition_marker_create` | `0x0801D9A0` | 120 bytes |
| `condition_marker_step` | `0x0801DA18` | 172 bytes |
| `condition_panel_draw_details` | `0x0801D580` | 432 bytes |
| `condition_panel_initialize` | `0x0801D1D0` | 460 bytes |

The matching 460-byte setup at `0x0801D1D0` calls the three object/label functions
and the matching detail drawer at `0x0801D580`. It configures backgrounds and
invokes the matching selected resource loader at `0x0803AFF0`, and selects a condition row
and cell before these display operations. This direct call path and the shared
condition-definition/cell accesses motivate the provisional panel names. The
setup is a verified C replacement over its complete original extent. Useful
failed setup and detail candidates remain preserved locally.

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
invokes the matching labels and column objects before the matching detail
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
register bindings or volatile qualifiers. The connected setup now matches, and
useful failed detail and setup attempts remain local.

All nine complete original extents, including literal pools and alignment,
match independently. Real changed-source loop/column-bound, close-parameter,
marker-variant, marker-flag, detail-tail-bound and setup-default-mode controls
produce different bytes. Source objects and linked extents contain only allocated `.text`, with
one function span and no unresolved linked relocations. Useful failed attempts
and the actual comparison bytes remain in ignored local reports. These compile
and byte results are separate from runtime/UI behavior and whole-ROM equality.

The detail drawer clears a background rectangle before reading its selected
text-ID word. The observed table at `0x08053460` has six words per row, a
24-byte row stride and a four-byte column stride; its full extent remains
unknown. A zero selected word skips subsequent detail work. Otherwise the
selected cell's first byte determines whether to draw its heading. The function
then reads the pointed definition's count byte at `+3` through the existing
six-column pointer fields at `ConditionRow +8` and scans that many four-byte
entry records. Entry bytes at world cell `+4/+5` control text and object
visibility, then choose animation frame one or zero. The caller's row and
column are complete words, while the loop index is explicitly a byte.

The function clears remaining detail-object flags through index four after
the count-driven loop. The creator's five detail slots establish the initialized
slots, not a proven `count <= 5` precondition: the original drawer does not
clamp the count, supplied indices, definition pointers or object pointers.
The reconstruction retains that absence of guards. It does not establish a
complete object-table allocation, localized text contents or runtime behavior.

The matching C separates the initial cell predicate's two unsigned scale
factors from their later saved values. The initial pair/block factors and
column byte offset use short `r3`, `r2` and `r1` bindings, consumed and copied
before any call. The initial title and world roots are scoped `r10` and `r8`
pointer values; the returned tile index remains in `r9` across draw calls.
These are genuine C values, with no synthetic read or guard. The count reader
and incoming row/column use ordinary C. Row-first title address arithmetic and
the separate factor lifetimes recover the original argument and loop storage
choices without long fixed argument bindings. The complete 432-byte extent
contains eight literal words, including repeated table roots, and the original
zero alignment before its internal pool. The changed-source tail-bound control
differs at both comparisons, and the connected 484-byte input consumer remains
exact with its own actual column-bound control.

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

# Connected selected-group initialization

The matching panel setup at `0x0801D1D0` and initializer at `0x0802A580` are
separate replacements. The latter is an exact 264-byte C replacement over the
same condition storage; a direct caller edge from the panel setup is not established.
It marks earlier columns for rows zero and one, then marks the requested group
and entries and publishes non-`FF` display kinds. This connects the panel/marker observations to
the reconstructed condition initialization and refresh path. The complete
extent, literal pool and alignment match; an actual changed-row-threshold
control is rejected. The caller's unchecked row/column/count contracts and the
broader runtime validity contracts remain unresolved. See
[the condition evidence](RESOURCE_CONDITIONS_RECONSTRUCTION.md) for the storage
alias, full-word counters and compiler-lifetime constraints.

# Connected panel setup

The existing scene-phase table at `0x0805797C` stores setup, input and close
at row 14's begin, step and end pointers: `0x0801D1D1`, `0x0801D39D` and
`0x0801D971`. The matching queue dispatchers use their existing `void(void)`
callback interface. The setup consumes no incoming argument before writing its
own call arguments, so its canonical interface agrees with that observed table
contract. Arbitrary request-kind bounds and actual callback invocation remain
separate runtime questions.

Setup configures four backgrounds and the text background control, clears the
shared request's selected column to zero, copies the world row at `+0x440` into
the full-word request parameter, and selects mode one. It tests the initial
cell's second byte at world `+0x445`. While that byte remains nonzero, it
checks the next column's first byte at `+0x444`, publishes the next full-word
column, and stops when it equals the row's count byte at `ConditionRow +6`
minus one. The row count is distinct from the pointed detail-definition count
at `+3` used by the drawer. The 144-byte cell-row stride, 24-byte cell stride
and 32-byte condition-row stride are the same observed strides as the connected
panel consumers. The original has no selected-row, column or count guard;
zero counts and unchecked access domains have not been assigned new behavior.

The setup then loads its background resources and selected resource, palettes
and palette-range configuration. It draws a heading and a number-substitution
line, creates the panel objects, draws row labels, updates column objects and
invokes the detail drawer before the existing first transition dispatcher.
The resource contents, display appearance and complete transition behavior are
not claimed from these static calls.

The matching source separates the initial row-address calculation from the
saved selection-loop values and keeps the current next-cell address for its
second-byte test. It reloads the shared selected column and row count as the
original does. The address helper, row multiplier, request, world, loop roots,
strides and tile values all use ordinary C. One `r5` binding carries the real
second-line style argument across the intervening drawing, font, number-field
and lookup calls; it is a callee-saved value and contains no instruction glue.
Earlier constraints were removed after these semantic lifetimes were separated.

The entire 460-byte original extent matches with sixteen literal words and its
original two-byte zero alignment before the pool. Source and linked objects
contain only allocated `.text`, one complete function span and no remaining
linked relocations. Changing the actual default request mode from one to zero
produces different compiled bytes. These compiler/byte results establish no
new world-state bounds, complete original type declarations or runtime UI
claim.
