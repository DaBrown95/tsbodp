# Resource group reconstruction evidence

This connected batch adds 14 verified C replacements covering 1,352 bytes.
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
`08051B18` account for the indirect calls; their complete entry inventory and
callback semantics remain incomplete.

The arena allocator reserves 8,192 bytes and stores the pointer at `03002EE8`.
The selected resource controller at `0800AD1C` clears this arena and chains the
header copy, object builder, word builder and program builder. Its reconstruction
is still unconverted. The builders place halfword counts and relative halfword
offsets into runtime tables. Resource flag bit zero includes a default object
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
in the ignored local agent reports. In particular, the controller `0800AD1C`
and word-group copy `0800B018` remain explicit unconverted regions. The latter
is the next connected builder dependency; its current candidate differs only
in the final arithmetic register allocation and is not counted as source.
The remaining command callbacks and resource selection/cleanup operations are
next connected targets.
