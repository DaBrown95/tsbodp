# Condition panel object and label path

Three connected functions add 576 verified matching C bytes:

| Function | ROM address | Complete extent |
| --- | --- | ---: |
| `condition_panel_create_objects` | `0x0801D888` | 232 bytes |
| `condition_panel_draw_row_labels` | `0x0801D7DC` | 172 bytes |
| `condition_panel_update_column_objects` | `0x0801D730` | 172 bytes |

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

All three complete original extents, including literal pools and alignment,
match independently. Real changed-source loop-bound controls produce different
bytes. Source objects and linked extents contain only allocated `.text`, with
one function span and no unresolved linked relocations. Useful failed attempts
and the actual comparison bytes remain in ignored local reports. These compile
and byte results are separate from runtime/UI behavior and whole-ROM equality.
