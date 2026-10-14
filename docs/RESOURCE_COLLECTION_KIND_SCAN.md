# Selected collection kind scan

`resource_selection_has_kind_0804573c` reconstructs the complete 88-byte Thumb
extent at ROM `0x4573C..0x45794`, including its literal pool. Its address-based
name and existing unsigned-byte interface remain provisional. This finding
supersedes earlier descriptions of this scanner as original code in
[the selection notes](RESOURCE_ACTOR_SELECTION.md); the connected removal
routine still remains unconverted.

The accepted `resource_select_actor` caller uses the result to choose response
4 or the removal path and response 2. The scanner visits scene IDs 15 through
49, calls `save_world_scene_in_selected_row(scene, 0)`, and checks only selected
groups for entry kind 48. It returns at the first hit. These groups differ from
the stage selector's smaller row-to-group mapping.

The existing collection view follows the context pointer at `+0x31C` from
`g_scene_entry_data` (`0x03003A2C`), placing the pointer cell at `0x03003D48`.
Group descriptors begin at collection `+0x784`, have four-byte stride, and
contain unsigned-byte start and count fields at offsets zero and one. Records
have 12-byte stride; their kind byte lies at collection `+4 + 12 * index`.
The source computes the target's four-byte address sum explicitly, then reads
the kind through a byte cursor. Nonempty selected groups retain the observed
second collection-pointer load. Unselected groups do not read records.

One short compiler register hint remains: R4 for the record counter. Its live
native interval ends at `0x08045780`, before the next selected-row call.
Removing this hint changes five native bytes. Count, start and cursor hints
were removed after unchanged matching compilations; the final start-to-cursor
handoff in R1 is compiler allocated. The field root is unbound so the compiler
preserves R7 in the function prologue and epilogue; an earlier bound-root attempt
failed the callee-save contract and is excluded.

Normal and strict compilations, changed-source controls, original-address
linking, owned function extent, literal pool and alignment checks are separate
from layout and finite execution checks. Layout checks cover the observed
prefixes and four-byte target address arithmetic. Seventy-six initialized
finite cases compare original and compiled execution with a selected-row
provider hook and deliberately clobbered caller registers. Sixteen cases
distinguish the actual kind-49 source control. Five malformed-input or
interpreter controls reject. This bounded model checks call arguments,
collection-pointer reads, return values, stack and callee saves; it does not
establish arbitrary provider behavior, allocation bounds, hardware timing or
gameplay behavior. No complete collection capacity or complete game inventory
is claimed.
