# Serialized need-effect factory

Two ordinary C replacements cover 248 original extent bytes. Observed factory
slot five at `0x0804F28C` contains `0x0802D53D`; it constructs class-five
need-effect objects through the existing spawn/configuration path. Its direct
collection-group query is reconstructed with the already established saved
collection layout. Both names remain inferred; matching and static evidence
are separate from runtime behavior.

| Original ROM extent | Function | Bytes |
| --- | --- | ---: |
| `0x20B44` | `actor_entry_collection_group_marked` | 28 |
| `0x2D53C` | `frame_create_need_effect_resource` | 220 |

## Payload and conditional construction

The factory narrows the serialized group/entry arguments to bytes and calls
`resource_get_object_payload`. Its payload starts with an opaque word and
signed coordinate halfwords at `+4/+6`. Six parameter bytes begin at `+8`:
kind, direction, optional mode, parameter, enabled and mode. The role header
is guarded and forward-only; complete existing provider layouts are included
only by the source that consumes them. This avoids the incompatible duplicate
frame include paths exposed by the first failed private attempt, without
modifying a shared header.

When enabled is nonzero, kind 130 tests and sets bit zero of game-state byte
`+0xE7`, and kind 140 tests and sets bit one. An already set bit returns null.
Other enabled kinds query the current world's saved collection-group mark and
return null when it equals one. These are observed factory latches; their other
writers/reset boundaries remain unresolved. No bounds check or allocation
guard has been invented.

Kind 33 is rewritten in the mutable serialized payload: game-state byte
`+0x20` selects 34 when nonzero and retains 33 otherwise. The wider meaning of
this selector is unknown. The factory then passes kind, optional mode,
parameter, mode and enabled to the existing `frame_spawn_need_effect`, sets
the object's byte `+0x83`, calls `frame_configure_need_effect` with the payload's
direction and signed coordinates, then clears that same byte. Its stable byte
address remains live across configuration. The byte's existing `linked` name
is provisional; there is no allocation-result check in this original path.

The spawn routine resolves the definition row and installs its initializer,
step/removal and pre-step callbacks. This supplies the actual serialized
construction boundary for the row-41 optional-mode-three effect lifecycle,
while retaining the original behavior of other descriptor kinds.

## Collection mark and exact source form

The saved root is the existing `g_scene_entry_data` at `0x03003A2C`, cast to the
established `ActorEntryContext` access view. Its collection pointer is at
`+0x31C`; four-byte groups start at collection `+0x784`. The query returns bit
zero of group byte `+2`. The adjacent accepted `actor_entry_mark_scene_collection`
sets that bit. `actor_entry_clear_collection_group` removes records and clears
the group's count while retaining its flag. The accepted `actor_entry_reset`
clears the complete `0x84C` collection buffer, including all group flags; its
prepare routine establishes that buffer's allocation and context pointer.
The existing array has 50 groups; the runtime world index bound is not proved here.

The first direct pointer-to-field factory form emitted only 212 bytes and
folded the game-state field address into a literal addend. Ordinary byte-base
address lifetimes produce the original base literals and immediate offset
arithmetic, giving the complete 220-byte match. They use no register binding,
volatile access, invented initialization or additional calls. Other successful
address forms and the unused binding experiment remain private predecessors.

The query includes the original `0x784` literal at `0x20B5C` and ends before
the independent accepted leaf at `0x20B60`. The factory includes its interspersed
game-state, saved-context and world-ID pools; its 218-byte native function has
two original zero alignment bytes before the accepted spawn prologue at
`0x2D618`. The preceding accepted catalog-detail extent ends at `0x2D53C`.
This corrects the inventory's provisional 218-byte factory envelope to the
complete compiler/linker extent without claiming the static inventory is complete.

Each new function has a real changed-source control. Thirty-five existing
payload, descriptor/list allocation, spawn, configuration, collection-mark,
restoration, reset and projection providers/callers are freshly checked with their
own controls and current literal headers. This includes all accepted spawn,
configuration, group-mark and group-clear importers in the current batch.
The configuration's point-to-cell helper at `0x08048AF8` remains an explicit
original region. Existing verified providers gain no new source credit, and
the finite static closure does not establish gameplay behavior.
