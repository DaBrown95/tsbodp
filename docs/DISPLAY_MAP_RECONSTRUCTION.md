# Background map rectangle operations

Eight record-based and palette functions at `0x0800D90C` and
`0x0800DAE0..0x0800DD80` own 764 matching bytes. The independently bounded
background-dimensions reader at `0x0800D9D4` adds 52 bytes. These nine complete
linked extents total 816 bytes, with exact compiler comparisons and rejecting
changed-source controls. Runtime use and incoming roots remain separate questions.

| Source function | ROM address | Complete extent |
| --- | --- | ---: |
| `display_write_map_palette_rectangle` | `0x0800D90C` | 92 |
| `display_read_background_dimensions_unrooted_d9d4` | `0x0800D9D4` | 52 |
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

The [640-byte background-map writer](DISPLAY_RECONSTRUCTION.md#dimension-prefixed-background-map-writer)
at `0x0800CEFC` and the [24-byte tile reader](DISPLAY_MENU_PAGES.md#hint-resource-and-map-read)
at `0x0800DA08` are separately source-owned. They are outside this document's
nine-function subtotal. The copied-RAM map drawer remains unconverted.

## Independently bounded background dimensions

The [reader](../src/display/read_background_dimensions_unrooted_d9d4.c) owns
42 instruction bytes, eight literal bytes and two compiler alignment bytes.
Its balanced stack/return path, literal references and next entry at `0xDA08`
bound the complete 52-byte body. No incoming direct call or aligned function
pointer has been identified in the bounded searches. Its three consumed
arguments and void result describe the chosen project interface; historical
names, extra unused arguments and complete incoming domains remain unknown.

The source uses the canonical 440-byte `DisplayBackgroundSystem`, with four
108-byte records beginning at offset eight. A byte view of that whole owner
forms each indexed prefix and reads byte nine, the selected record's control
high byte. Index zero through three keeps these accesses within the owner.
The high two bits select one of four observed width/height pairs. This local
read view adds no ownership credit for the external 16-byte table.

It writes width before reading the control byte again for height. The second
observation matters for the native byte-memory interface: with size code three,
a width output at the selected control's low halfword stores 512 (`0x0200`),
so the next size observation is zero and height becomes 256. Caching size three
would instead produce 512. This is a bounded target-access witness, without a
universal effective-type or alias-population claim. Source inputs still require
properly backed, aligned halfword outputs and valid owner/index storage.

Ordinary table and system-base captures before the indexed address reproduce
the native value lifetimes without register bindings. Normal/strict positives
and real source controls cover this definition and the actual configuration
writer separately. Actual-definition API checks, wrong-contract rejections and
target layout facts preserve their distinct compilation contexts. The alignment
role does not exclude alternate entry execution. No runtime or gameplay
observation is added.

## Independently bounded background buffer lifetime

The background buffer pair at `0x0800E21C` and `0x0800E254` owns complete extents of
56 and 44 bytes, including literals and alignment. Both use the canonical 108-byte
`BackgroundState` records at `0x03002EF8`, with the source pointer at offset eight
and the flags word at offset 24. The chosen one-word index and void interfaces
describe the consumed native arguments and effects; incoming roots, additional
unused formals and the complete index domain remain unknown. Indices zero through
three stay within the declared four-record owner.

The [enable
operation](../src/display/display_enable_background_buffer_unrooted_e21c.c)
allocates 2,048 zeroed bytes only when the source pointer is null, stores the
result, and clears flag `0x20` on that branch even if allocation fails. It always
sets flag `0x10`. The [release
operation](../src/display/display_release_background_buffer_unrooted_e254.c) clears
flags `0x30` before testing the pointer, then frees a non-null source and clears
that pointer. Existing background reset and commit routines independently consume
the same fields. No extra allocation guard or index check is added.

Normal and strict compilation reproduce all 100 bytes. Real flag mutations reject,
and checks against the actual caller sources, accepted heap provider definitions and
canonical record layout preserve their separate compilation contexts. Names and
incoming reachability remain provisional; these source comparisons add no runtime or
gameplay observation. The separately reconstructed `0xE1EC` query and possible
`0xE1EE` alternate entry remain outside this pair.

## Independently bounded display-control flags query

The [full leaf at
`0xE1EC`](../src/display/display_read_control_flags_unrooted_e1ec.c) returns the
complete word result of `g_display_control.flags & mask`. The canonical flags
word is at `0x03002EF0`; the consumed mask arrives in R0. This is a bitmask
result, with no boolean normalization, state mutation or additional consumed
input at that full entry. The 16-byte extent contains ten instruction bytes, two
zero alignment bytes at `0xE1F6` and the four-byte global-base literal at
`0xE1F8`. Normal and strict positives match the full extent; real AND-to-OR
source controls reject by one byte. Current source API/layout checks preserve
the full word contract.

The full 16-byte source owner at `0x0800E1EC` does not resolve a possible
interior entry at `0x0800E1EE`. The sole aligned ROM word containing
`0x0800E1EF` is at `0x08088B14`; its data owner and executable consumer remain
unknown. Entry at `0x0800E1EE` skips the global-base load and would require R0
as mask and R1 already addressing readable word backing. This is an unresolved
register precondition, not a recovered second formal of the full-entry source.
The manifest retains this observation in `unresolved_interior_entries`.

The inventory seeds full source bodies before weak pointer candidates and skips
pointer targets already decoded as instructions. It may therefore omit the old
eight-byte E1EE candidate without adding a folded-entry record. This reflects
physical source coverage; it does not establish a caller, root, ABI or runtime
execution. E1EE remains instruction-bearing and receives no separate C-function
credit.
