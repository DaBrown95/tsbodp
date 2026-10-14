# Serialized actor construction

The constructor at `0x0802C6C8` adds 88 bytes of ordinary matching C. Observed
factory slot seven at `0x0804F294` contains its Thumb pointer `0x0802C6C9`.
It connects serialized resource entries to the existing scene eligibility,
actor construction and indicator update paths. Names and access views remain
inferred; this is compiler/static evidence without gameplay claims.

The payload has an opaque initial word, signed coordinate halfwords at
`+4/+6`, and actor/direction bytes at `+8/+9`. Its complete serialized ownership
and length are not established. The constructor narrows its group and entry
arguments to bytes before calling `resource_get_object_payload`. It passes the
loaded actor byte as a full word to `frame_scene_actor_allowed`, together with
the current-world word and the established `DisplayTimeRecord` view at
`0x03003958`. The predicate's existing signed row byte, wrapped actor-minus-six
table index and return-byte contract are reused, without new bounds guards or
a shared callback ABI change.

When the predicate returns one, the constructor calls the canonical
`frame_create_actor(unsigned int, unsigned char, int, int)` interface. Its
coordinates are signed halfwords multiplied by 65536; every possible signed
halfword product fits the target's signed 32-bit integer. This source form
matches the original fixed-point word conversion without shifting a negative
C value. The complete argument and pointer-return types are explicit in the
new guarded, forward-only role header. Initial generic word-view and implicit
constructor-declaration forms remain unaccepted private predecessors, even
though they produced the same native bytes.

The new object uses the existing `FrameActorObject` layout, and its indicator
pointer at `+0x90` is set to null. The accepted `frame_actor_tick` checks this
same pointer, creates an indicator through `frame_create_actor_indicator`, or
requests its removal and clears it. These consumers support the field's
inferred name/type. The generic interaction callback view remains provisional
and is unchanged. The original constructor path does not check the actor
allocation result; a failed eligibility test returns null before allocation.

The whole 88-byte replacement includes current-world and serialized-state
literals at `0x2C70C` and `0x2C710`. Its 86-byte native symbol is followed by two
original zero alignment bytes before the accepted independent choice helper
at `0x2C720`. This replaces the inventory's provisional 86-byte envelope with
the complete compiler extent. No output bytes, reference hash, pools or
alignment are patched or masked.

A real changed-source control changes only the X coordinate scaling factor.
Existing payload, eligibility, actor, update and indicator providers and all
accepted direct constructor/eligibility/tick importers are freshly checked
with their actual controls and current literal header closures. The original
indicator-kind resolver at `0x0802C9C0` remains explicit: it scans the 15 saved
condition-display bytes and their eight word IDs per row. Its bounds and
connection are static findings; it receives no new C credit in this batch.
Whole-ROM integration and runtime behavior remain separate checks.
