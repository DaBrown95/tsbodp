# Background map rectangle operations

This connected batch reconstructs seven record-based functions at `0x0800DAE0` through
`0x0800DD80` and the connected palette-field rectangle writer at `0x0800D90C`.
The eight complete linked extents total 764 bytes. Each has an exact compiler
comparison and a compiled changed-source control that rejects. These are
static and byte-matching results; runtime use of every routine has not been
established.

| Source function | ROM address | Complete extent |
| --- | --- | ---: |
| `display_write_map_palette_rectangle` | `0x0800D90C` | 92 |
| `display_reload_background_map` | `0x0800DAE0` | 88 |
| `display_copy_map_rectangle` | `0x0800DB38` | 96 |
| `display_copy_background_map_forward` | `0x0800DB98` | 96 |
| `display_copy_background_map_backward` | `0x0800DBF8` | 112 |
| `display_copy_stored_background_map` | `0x0800DC68` | 108 |
| `display_write_background_map_tile` | `0x0800DCD4` | 48 |
| `display_write_incrementing_background_map` | `0x0800DD04` | 124 |

The generic rectangle copy owns 94 bytes through its return and two zero
alignment bytes before the next function. Its source makes that alignment
explicit; no instruction body is embedded. Literal pools and padding in the
other extents also remain part of the comparison.

## Record and algorithm evidence

`include/display_map.h` is a narrow view of the same background records used
by the accepted display update and commit routines: base `0x03002EF8`, stride
`0x6C`, flags at offset `0x18`. The separate symbol name identifies this view,
not another allocation. Fields at `0x04`, `0x08`, `0x0C`, and `0x10` are pointer
slots. Their names describe these routines' observed accesses and remain
provisional. Existing display code provides evidence for four records; these
functions themselves do not check the supplied index.

The pointer at offset `0x04` addresses two unsigned halfword dimensions followed
by halfword tile entries. The reload routine clamps each dimension to 32 and
copies from this stored map into the buffer at `0x0C`. It uses the stored width
as the source stride and 32 as the destination stride. The generic copy takes
independent signed dimensions, origins and strides; it copies halfwords in row
order and advances by each stride minus the rectangle width after each row.

The forward and backward routines copy within the buffer at `0x0C`, with a
32-entry row stride. The backward routine starts at each rectangle's bottom
right corner and visits entries and rows in reverse order. This establishes
the traversal directions; it does not establish that callers choose a safe
order for every possible overlap. The stored-map copy reads the dimensions
and entries at `0x04` and writes through the pointer stored at `0x10`, using a
32-entry destination stride. The tile writer writes through the pointer stored
at `0x08` and adds
`palette << 12` to the tile value before the halfword store. The reload, three record-based rectangle copies and single-tile writer
set flag `0x20` after their operation, including empty copies.
The generic copy does not access a background record or set a flag.

The palette-field rectangle writer accepts a map pointer and signed origin,
width and height. It uses the same 32-halfword row stride, preserves each
entry's low twelve bits and adds the shifted palette field before storing.
It does not access a background record or mark a dirty flag. Its complete
extent includes two zero alignment bytes after the return.

The original signed comparisons for zero or negative dimensions are retained.
No bounds clamp, index check, null check or overlap guard has been added. The
reload's first height access uses a local volatile view to retain the observed
comparison read separately from its conditional value read; this is an access
annotation, not evidence of asynchronous modification. C register constraints
on the reload's width and height-map pointer and on the three copy routines'
remaining-row value preserve the pinned compiler's allocation. They constrain
semantic values and do not insert machine instructions.

A bounded Thumb call scan found `display_reload_background_map` directly
calling `display_copy_map_rectangle`. No direct Thumb calls or exact Thumb
function-pointer words to the other record-based operations were found in
that scan. Their connection is the shared record and map representation;
whether particular gameplay paths invoke them remains unresolved.

## Preserved comparisons

The ignored local receipt index is
`reports/agents/display_audio/map_rect/ready.json`. It names exact positive
receipts and changed-source controls. The controls change a
copy count comparison, the reload clamp, each copy's source or destination
row adjustment, the tile writer's palette shift, and the palette rectangle's shift. All were actually
compiled and linked against the fixed original ROM slices. Failed natural
and constrained compiler trials, raw bytes and disassemblies remain locally
under the same ignored report directory.

The sequence writer at `0x0800DD04` visits rows at a 32-entry stride, increments
a halfword tile value with 16-bit wrapping after each entry, and marks flag
`0x20` only for rows that write entries. Its single unsigned address value
starts as the row offset and becomes the full destination address. The final
wrapped addition is expressed through the inverse row offset to preserve the
pinned compiler's commutative operand allocation. This algebra and two C
register constraints on the x-byte offset and dirty flag are compiler-facing
source choices; they are not claims about original syntax. A compiled change
from incrementing tiles by one to incrementing by two rejects by one byte.

The 640-byte background map writer at `0x0800CEFC` and its text/affine map layout
remain a retained unmatched candidate, excluded from the eight-function
coverage above.
