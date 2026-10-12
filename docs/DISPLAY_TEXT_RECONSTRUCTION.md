# Text object rendering and tile transfer

`display_text_update` at `0x080451A8` adds 304 bytes of matching C. Its complete
linked extent through `0x080452D8`, including literal pool and alignment, matches
at its original address. The public source and literal header closure were
compiled again after promotion, and changing the height threshold from eight
to seven rejects by one byte. The ignored receipt index is
`reports/agents/display_audio/background_motion/scene/redraw/text-ready.json`.

This is the direct update called by the reconstructed text object allocator
at `0x080450A0` and the scene label factory at `0x080282D4`. It first calls the
explicit unconverted sizing routine at `0x0804511C`, allocates a 120-byte work
buffer and `(tile_size_bit + 1) * 1920` bytes of pixel storage, installs both
buffers through `0x0801AE5C`, and calls the drawing routine at `0x0801A7C8`
with width 240 and an initial limit of `0x7FFFFFFF`. It releases the pixel
buffer and then the work buffer through `0x08027988`. Allocation failures and
buffer limits are not checked here; no checks have been added to the source.

For height at most eight, it sets OAM size one and transfers `columns * 128`
bytes to object tile memory in one DMA3 operation. For larger heights, it sets
OAM size two, then performs four pairs of 32-byte transfers per column. Each
pair writes a row and its partner 128 bytes later, advances the source by
64 bytes and the destination by 32, then advances the destination another
128 bytes after the four rows. The destination starts at
`0x06010000 + tile_index * 32`. DMA control is read after every launch, as in
the original body. These are direct hardware accesses; this function does not
establish a VBlank scheduling guarantee.

The partial `DisplayTextObject` view exposes OAM at `0xD0`, halfword width,
height and column count at `0xD8`, `0xDA` and `0xDC`, and halfword byte count and
tile index at `0xFC` and `0xFE`. The sizing candidate corroborates width and
height semantics but remains unaccepted. This view overlaps sprite-resource
fields in the general frame object, so it is used only for the text object's
accesses. Gaps and complete allocation bounds remain unknown. The public ABI
retains `struct FrameObject *` and uses explicit per-field text views, avoiding
conflicting declarations in the already accepted allocator.

All body logic is ordinary C with no register constraints or assembly glue.
An earlier separately named view pointer created an extra copy and a
308-byte mismatch; initializing the taller transfer's source and destination
after the OAM size assignment preserves the original lifetime and ordering.
The raw failures and exact comparison are preserved locally. The allocation
calls distinguish the fixed work buffer and variable pixel buffer. The
[reconstructed heap lifecycle](HEAP_RECONSTRUCTION.md) now supplies the general
allocator at `0x08027864` and release at `0x08027988`; the zeroed allocator at
`0x080278E4`, sizing, buffer setup, and text drawing remain explicit unconverted
dependencies. This compiler
match does not independently prove runtime or gameplay behavior.

## Catalog text selection

The connected name drawing helper at `0x0802D1BC` adds 444 matching C bytes,
and its text lookup at `0x08045008` adds 36. Their complete extents, including
both twelve-entry switch tables, intervening literal pools and final
alignment, match after public source/header compilation. Changing the special
item ID `0x52` to `0x53` and lookup capacity 1024 to 512 each rejects by one
byte. The receipt index is
`reports/agents/display_audio/background_motion/scene/redraw/catalog-text-ready.json`.

The name helper preserves its first three drawing arguments and supplied
style, resolves a string, forwards it to the unconverted drawing routine at
`0x0801A958`, then returns the full word from the width routine at
`0x0801AF28`. For item IDs `0x52` and `0x20` with index other than minus one,
it reads the type byte at offset two of a four-byte record and selects one of
twelve literal string IDs. The two semantic switches generate the original
inline jump tables; no original instruction body is embedded. A type outside
zero through eleven retains a null text pointer and still reaches both
downstream calls. Other items, including these IDs when index is minus one,
use the text-ID word at offset eight of the 24-byte catalog record. No index
or pointer checks have been added. The width routine's signedness is unknown;
both signed and unsigned word return declarations match, while a halfword
return introduces extra narrowing instructions and fails.

The context pointer is read at offset `0xF0` from `0x03003950`, the same state
base used by the scene label text buffer. Its pointee's word at offset four
addresses the four-byte type records. The new state/context views retain all
unknown gaps and do not assert complete allocation bounds. The existing
catalog loops observe 149 records beginning at `0x080616CC`; this is an
accessed prefix, and the name helper itself does not enforce this limit.
The type numbering and string IDs are static observations without asset or
gameplay meaning assigned to them.

The lookup uses the pointer stored at `0x030021F4`, calls the explicit
unconverted loader at `0x0801F028` with capacity 1024, and returns that global
pointer on status zero or null otherwise. It reloads the pointer after the
call, preserving a possible loader update. Reordering the success/error
returns produced a five-byte branch-layout mismatch; ordinary success-first
C matches naturally. Earlier switch, return-width and branch-order failures
remain local. Catalog description/page rendering and text sizing remain
unconverted connected targets.

## Font measurement

Three connected measurement routines add 160 matching C bytes: width at
`0x0801AF28` (84), height at `0x0801AF7C` (28), and glyph width at
`0x0801B450` (48). Width is used by the catalog name helper, both measurements
feed the unconverted text sizing routine, and the width loop directly calls
the glyph helper. Changing the substitution marker, height font slot, and
fallback width index each rejects by one byte after public closure compilation.
Their receipts share
`reports/agents/display_audio/background_motion/scene/redraw/heap-measure-ready.json`
with the connected heap batch.

Width sums glyph advances until a zero byte. Marker `@` consumes the next byte
as an index into 64-byte substitution records beginning at `0x03000E20` and
recursively measures that record. A byte above `0xEF` consumes the following
glyph through the second font pointer; other bytes use the first pointer at
`0x03001A20`. Height returns zero for an empty string and otherwise the first
font's leading height byte. These routines do not check null strings,
substitution indices or recursion cycles; asset validation is a separate task.

The glyph helper narrows its argument to a halfword. Zero has width zero;
otherwise it subtracts the font's first glyph and uses the indexed width byte
when the signed difference is in range, falling back to width byte one when
outside the first/last interval. The partial font view identifies height at
zero, first/last halfwords at two/four and the width pointer at twelve. The
rest of the font record and glyph encoding are unknown.

The width source uses one `volatile const unsigned char` access view for the
second observed read that selects the font prefix. Ordinary C removed that
read and produced 80 bytes; preserving it matches the complete 84-byte extent.
This describes an observed access, without asserting the original qualifier
or asynchronous mutation. Width and glyph width each have separate explicit
two-byte zero-filled alignment directives; all algorithm bodies remain C with
no fixed register constraints. Word-result signedness remains provisional.
