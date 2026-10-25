# Selected-row scene membership

`save_world_scene_in_selected_row` at ROM offset `0x262B4` reconstructs a complete
292-byte C extent, including its compiler-generated 33-entry switch jump table
and literal pools. The source uses ordinary switches, no register bindings,
embedded instruction bodies or copied jump-table data. The name records an
observed membership test; the complete scene/row gameplay roles remain provisional.

The first argument remains a full scene word. Only the low byte of the second
incoming word is consumed, expressed as an explicit byte conversion. A nonzero
byte selects base-scene ids 6, 4, 9 and 14. A zero byte selects the variant groups
16–18, 23–25, 39–40 and 46–48. These groups respectively test the existing selected
row at game-state `0x03003950 + 0x440` against `<= 1`, `== 2`, `== 4` and `== 3`.
All other scene words return zero; successful membership returns one. No scene
normalization, extra row bounds or new default row is introduced.

This field already belongs to the published `SaveWorldConditionSource` view.
The current need-effect updater at `0x0802D7C0` calls the provider with option 1
for subtype 117; its old `frame_need_effect_world_test` alias is replaced by the
observed membership name. That caller's unchanged 292-byte instruction extent
and its actual palette-value source control are reverified with the corrected
prototype. All accepted consumers of the changed need-effect header receive
fresh positive and changed-source comparisons; no old proof is described as
current after a header change.

The [720-byte placement/selection controller](../src/frame/frame_update_grid_need_effect_selection.c)
at `0x0803C688` is a second original caller and now matches. It scans active
need-effect nodes, tests candidate membership and directional bounds, and
activates or releases the existing row selector object. The
[356-byte target-cell selector](../src/frame/frame_find_target_cell.c) also matches.
Their documented original unset-value paths remain; source ownership does not
establish runtime reachability.

The provider's actual negative control changes the first row test from `<= 1`
to `<= 2` and must reject the fixed reference. The low-byte option conversion was
also checked privately against the narrower formal view: both reproduce the
original entry's byte test. The published API keeps the observed full incoming
word and narrows inside the function. Original callback/table bounds and wider
scene semantics remain unresolved; this batch establishes source compilation and
whole-extent byte equality, with no runtime/gameplay claim.

The final current-header closure comprises 67 previously accepted functions
covering 11,164 C bytes, plus the new 292-byte provider. All 68 positive proofs
match complete extents and every actual changed-source control rejects. These
existing-function rechecks add zero C coverage; the batch adds one function and
292 bytes. The renamed effect updater is included in that closure.
