# Object finalization

[`frame_finalize_object`](../src/frame/frame_finalize_object_original.c) at
`0x08003248` owns its complete 348-byte extent: 326 instruction bytes, twenty
literal bytes and two compiler-emitted alignment bytes. Its current caller is
[`frame_schedule`](../src/frame/frame_schedule.c); the canonical declaration
receives one object pointer. The match does not establish the historical
return type or declarations.

The function appends the object to the frame list. Flag `0x800` takes the
count-update exit. Otherwise it snapshots bounds and flags, scans preceding
objects, applies the original category, geometric and priority tests, and
moves the object backward through the list when those tests select it. The
source retains the original seven-word stack work and its read/store order.
Names and the inferred object/point views remain provisional.

The final commit has three real inputs: the first computed destination in R0,
the table base in R1, and the object value in R2. Both words of the input tuple
are assigned before their own reads and feed existing stores or address
calculations. The preceding mask/category definitions bound the earlier R2
lifetime; the object pointer has its own later definition. No whole
uninitialized record is read.

Partial tuple assignments keep the table input through combination, allowing
the compiler to allocate the actual index and loop-test values to R7 later.
A direct R7 declaration instead triggered frame-pointer canonicalization and
was rejected. The ordinary geometry carrier also retained those late roles,
but introduced load/copy relays. These failed sources remain private.

Computing the actual four-byte index offset before the table birth removes the
remaining table relay. Pointer addition still placed the base first, leaving
one byte different. The guarded 32-bit offset-plus-address expression preserves
the native operand order and computes the same aligned table destination on
the original defined index domain. This is target-specific address arithmetic,
not proof of the original source spelling.

The complete source matches under the pinned default compiler flags and four
canonical headers. Changing gate `0x800` to `0x1000` rejects by one byte.
Full-ROM equality, its actual changed-source control, progress generation and
tooling tests are separate publication gates. The two alignment bytes at
`0x334E` are already included in the C extent; their data role supplies no new
entry or execution exclusion. This adds one source owner, no assembly bytes,
runtime observation or independent executable-inventory closure. The renderer
and broader target/writer populations remain open.
