# Resource group reconstruction evidence

The original connected batch added 14 verified C replacements covering 1,352 bytes.
All full extents match at their original ROM addresses, including literal pools
and zero tail alignment. Every replacement has a changed-source negative control.
This is static/compiler evidence; no runtime or gameplay claim follows from it.

| Address | Provisional name | Bytes |
| --- | --- | ---: |
| `08001AE0` | `resource_object_before_step` | 104 |
| `0800A9F0` | `resource_build_object_groups` | 220 |
| `0800AACC` | `resource_build_object_group` | 132 |
| `0800AB50` | `resource_build_word_groups` | 216 |
| `0800AC28` | `resource_build_program_groups` | 220 |
| `0800AD04` | `resource_allocate_arena` | 24 |
| `0800AD98` | `resource_activate_groups` | 52 |
| `0800ADCC` | `resource_execute_group` | 88 |
| `0800AE24` | `resource_group_is_enabled` | 44 |
| `0800AFA8` | `resource_copy_arena_header` | 72 |
| `0800AFF0` | `resource_copy_object_payload` | 40 |
| `0800B05C` | `resource_build_program_group` | 68 |
| `0800B0A0` | `resource_offset_table_bytes` | 32 |
| `0800B0C0` | `resource_align_word` | 40 |

The transition controller at `0801869C` activates object and command groups
through `0800AD98`. The activation predicate excludes group zero and also group
one when the resource flags contain bit zero. The object factory walker at
`0800A964` and command walker at `0800ADCC` consume offset tables from RAM bases
`03002ED8` and `03002EE4`. Factory and command callback arrays at `0804F278` and
`08051B18` account for the indirect calls. The factory table's complete entry
inventory and callback semantics remain incomplete. All 47 nonzero command callbacks
are now reconstructed in the connected continuation documented in
[RESOURCE_COMMANDS_RECONSTRUCTION.md](RESOURCE_COMMANDS_RECONSTRUCTION.md).

The arena allocator reserves 8,192 bytes and stores the pointer at `03002EE8`.
The selected resource controller at `0800AD1C`, `resource_prepare`, is now a
complete 124-byte C replacement: 104 instruction bytes and 20 literal bytes,
with no alignment tail. It clears the arena and chains the header copy, object
builder, word builder and program builder. The byte selector at `03002EDC`
indexes the serialized directory; the selected record and each builder's
returned cursor feed the following call. The builders place halfword counts and
relative halfword offsets into runtime tables. Resource flag bit zero includes a default object
and program group from the base resource and prepends the base word groups.
The source word-group counts are initially read as bytes but loop limits are
read as halfwords; this access distinction is preserved.

For each object group, the serialized count is a byte, the object payload-size
array starts at byte two, and payload data starts at the rounded word boundary
of count plus two. Each runtime entry reserves eight bytes before the copied
payload. The factory walker subsequently treats that prefix as an object pointer
and an unknown word and reads a halfword factory selector at entry offset eight.
The `unknown_04` name remains deliberate: its meaning has not been proved.
The table helper rounds a halfword-entry count to an even number of entries;
the byte helper rounds a byte count to a multiple of four.

Command records begin with a word command selector. A byte table at `080528E0`
gives each record length. The executor stores the current group byte at
`03002ED0`, invokes the selected callback for nonzero commands and advances by
the associated length. A zero selector terminates the walk. Record copying also
copies the zero terminator using the length table. Neither walker introduces
bounds checking absent from the original. The program copy uses a fixed C
register binding for its halfword local count to reproduce compiler allocation;
it contains no instruction assembly or copied instruction bytes.

The default object callback at `08001AE0` uses object flag `00040000` to choose
between projection through `08048BF8` with context `03004330` and a direct vertical
coordinate path. It reads the signed high halfwords of the position words at
object offsets `18` and `1C`, writes the point at `9C/A0`, and copies that result
to `A4/A8`. These fields are represented by a partial object view rather than
claiming the entire unknown object area has been decoded. The exact role of the
projection context and the flag remains provisional.

Useful mismatches, compiler inputs, linked outputs and raw comparisons remain
in the ignored local agent reports. The word-group copy at `0800B018` remains
an explicit unconverted region and the next connected builder dependency. A
fresh current-header replay of its original authored candidate is 64 bytes / 61 differences against the native
68-byte extent. Its eight-byte assignment lowers as a DI copy rather than the
native block transfer. A fixed eight-byte representation copy from the existing
four-aligned access-view records instead selects the native block transfer without
a helper or stack frame. Retaining the actual offset-table base at source +2,
as in the neighboring owned builders, then gives 68 bytes / seven differences.
Materializing the actual per-record byte offset and typed element pointers
avoids the compiler's deferred-multiplication address ordering and repairs the
two loop ADD instructions, giving 68 bytes / three differences. Only the two
return-size instructions differ. A previously authored late byte-count model
repairs the native shift but still misses the full-size result. Replaying its
existing two-value form also fails: combine removes the explicit result copy
before local allocation. A compound form has no established protection from an
earlier legal combine, so it does not justify another trial. Unique attempts
and selected compiler passes remain; retired old raw outputs do not establish
another current match. This candidate has no source credit or assembly exception.
The resource selection/cleanup operations, object lookup and view effect
updates remain next connected targets. The group object-count reader at
`0800AE50` is now accepted with the command continuation.

## Variable arena-header tail

The arena copier at `0800AFA8` indexes eight-byte records up to the observed
halfword count. Its former one-element `records[1]` declaration did not describe
that variable tail. The shared header now uses the pinned compiler's GNU89
zero-length-array extension, `records[0]`. This is a type correction with zero
new C bytes: the physical prefix remains a size halfword at zero, a count
halfword at two and records beginning at four. The prefix has size four and
four-byte alignment; each record has size eight and four-byte alignment. These
are access-view sizes, while the existing allocator still reserves 8,192 bytes.
The compiler's header size changes from twelve to four; all field offsets,
the eight-byte record stride and the arena allocation remain unchanged.

All ten header importers in the declaration-correction batch, and its
allocation/clear providers, received fresh positive and changed-source controls;
the copier also has a strict declaration pair. Pinned layout and API checks
reject the old one-element bound, incorrect field widths, record stride, packing and return type. The old declaration can
still compile to the same complete 72 bytes, which demonstrates why byte
equality alone does not validate a declared array bound. Actual wrong count and
size-word declarations change native bytes; packing the record introduces an
unmatched compiler copy-helper call and is rejected without inventing a link
alias. Original source and diagnostic evidence are retained privately.

The zero-length member describes the observed variable-count access rather
than a valid-capacity guarantee. Serialized counts, pointers, source alignment,
byte-size values and the arena's remaining capacity stay unchecked.
The 68-byte word-group copier remains unconverted; no runtime, hardware or gameplay
result follows from this declaration correction or the controller match.

## Selected resource controller

The controller uses only the existing resource-builder and heap headers. Its
proper `void(const unsigned char *)` contract is checked against the existing
scene-actor declaration, together with complete definitions of all five called
providers. ARM32 checks retain the four-byte arena prefix, records at offset
four, eight-byte record stride and the byte selector. Normal and strict
positives match the complete fixed extent; changing the clear size from 8,192
to 4,096 produces the same one-byte rejection in both profiles.

The source reuses a real cursor for the directory address, the selected-byte
address, the selected resource and provider results. Taking the selected-byte
address before its read preserves the separate directory snapshot through
first CSE and later register moves. The existing R4 input and R6 base constraints
operate on real values: the halfword base offset is consumed before R6 becomes
the base pointer. Its offset value is dead at that addition; the base then
crosses the builder calls. Combine emits the native halfword load into R6 and
addition of the input, without a stale offset use, instruction assembly or
extra memory observation. This explains the matched producer, not a unique
original source form.

Serialized directory and selected-record extents, source alignment, clear/input
aliasing and the arena's available capacity remain caller obligations. The
zero-length arena tail does not establish a valid selector or blob population.
No runtime or complete resource-system claim follows from the controller.

## Retained word-group storage domain

The existing decoded ledger covers 50 scene roots and 105 physical packs. Four
retained cases have nonempty word groups: scenes 1, 6, 31 and 39 contain eight,
four, five and two records respectively. All 19 records have trailing word
`0xFFFFFF00`. Their source group addresses and derived arena offsets are
four-aligned; a four-aligned live arena base is still required. This finite
ledger does not establish every selector, writer or valid runtime input.

The owned point readers share the word-data root `0x03002EE0`. Their stored
record has two signed halfword coordinates and four unspecified bytes, with
eight-byte stride and two-byte C type alignment. The returned two-int
`FramePoint` is a converted value. That conversion omits the four trailing
bytes and expands the packed coordinates; its result cannot replace the
stored record in a faithful representation copy. Physical alignment in the
selected cases does not establish a four-byte alignment requirement for the
canonical stored type.

Both actual builder calls consume only the copier's advanced `R0` pointer.
They supply no second size result or tail-size lifetime. The 68-byte / three-
difference candidate remains unowned: LOCAL ties the compatible dying count-
and-size quantities, while the retained fixed-register attempt loses its
intermediate copy at COMBINE. These storage facts do not justify repeating
those closed source/register trials.
