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
allocator at `0x08027864`, zeroed allocation at `0x080278E4`, and release at
`0x08027988`; sizing remains an explicit unconverted dependency. Buffer setup
is reconstructed with the tile row path below.
The connected line selection and alignment consumers are reconstructed below. This compiler
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
style, resolves a string, forwards it to the reconstructed alignment routine
`display_text_draw_line` at `0x0801A958`, then returns the full word from the width routine at
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
catalog loops scan 149 records beginning at `0x080616CC`; this is a loop
limit, and the name helper itself does not enforce it. Connected selectors
also access indices 195 through 215 in that same 24-byte record array, so
149 is not a storage bound. The declaration is unsized and the full table
extent remains unknown.
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

## Line selection and drawing alignment

Two connected consumers add 688 matching C bytes: `display_text_draw` at
`0x0801A7C8` (400) and `display_text_draw_line` at `0x0801A958` (288). Both
complete linked extents, their intervening literal pools and final alignment
match after public source/header compilation. Changing the newline break to
carriage return and center style from one to three each rejects by one byte.
Fresh closure and control receipts are indexed by the local
`reports/agents/display_audio/background_motion/scene/redraw/text-draw-ready.json`.

Line selection scans until zero, newline, or a signed maximum width is exceeded.
It records the last space and the last hyphen endpoint whose width fits. A
newline or fitting terminator supplies the split; otherwise it uses the space
or hyphen, returning the original first word if neither exists. It measures
`@` substitutions with the shared font-width operation and consumes two-byte
font prefixes. It copies the chosen prefix into a 96-byte local line while the
caller limit is nonzero, decrementing that limit per copied byte. A final `@`
causes its following index byte to be copied without another decrement. The
source does not add a capacity check or check that the line is nonempty before
reading its preceding byte. These unchecked paths remain faithful to the
observed body; safe input bounds are not established by this match.

After terminating the line, it updates the caller's text cursor, calls the
alignment consumer, then consumes one newline and any following spaces. Both
functions return the first word supplied by the tile-rendering dependency at
`0x0801AA78`. That still-unconverted body advances it after tile-row writes,
supporting a provisional tile index/cursor role. Existing callers that ignore
this return remain byte-identical. Coordinate and maximum-width declarations
use signed words, supported by the signed comparisons and division in the
bodies; earlier unsigned callers pass the same register words.

Alignment compares the complete style word against one for horizontal center,
two for right alignment, four for vertical center, and eight for bottom
alignment. It subtracts `(width + 1) / 2`, width, `(height + 1) / 2`, or height
as appropriate, then forwards to the explicit unconverted tile renderer.
These are equality tests, not independently combinable style bits. The shared
inline measurement header produces the observed expanded C loops naturally.
The separately callable width (84) and height (28) wrappers still match; real
wrapper cursor-offset controls reject by 24 and one bytes. Canonical naming
replaces the prior address-only alignment alias, and fresh catalog/text update
positives and controls both pass. All these algorithm bodies use ordinary C
without fixed registers or embedded instruction bodies. Earlier loop-break,
local initialization and register-lifetime failures remain in ignored reports.

This closes line selection and alignment feeding the text update's transfer
path. Tile rasterization, row reading, sizing and further setup callers remain
connected reconstruction targets; the row emission and font producers are
reconstructed below. Full-ROM equality,
static data roles and runtime/gameplay behavior remain separate evidence.

## Font setup and tile row emission

Nine connected producers and consumers add 676 matching C bytes. Their whole
linked extents match at their original addresses, with the two explicit
zero-filled alignment directives separated from the C bodies. Public closure
receipts and compiled controls are indexed by the local
`reports/agents/display_audio/background_motion/scene/redraw/text-raster-ready.json`.

| Function | ROM address | Bytes | Control differences |
| --- | --- | ---: | ---: |
| `display_text_load_font` | `0x0801AD2C` | 100 | 2 |
| `display_text_flip_tile` | `0x0801AD90` | 104 | 1 |
| `display_text_initialize` | `0x0801ADF8` | 52 | 2 |
| `display_text_set_background_control` | `0x0801AE2C` | 48 | 1 |
| `display_text_set_buffers` | `0x0801AE5C` | 24 | 1 |
| `display_text_select_font` | `0x0801AE74` | 72 | 1 |
| `display_text_fill_rows` | `0x0801B2B0` | 80 | 1 |
| `display_text_emit_rows` | `0x0801B38C` | 160 | 1 |
| `display_text_map_position` | `0x0801B42C` | 36 | 2 |

Font loading reads an eight-byte resource record beginning at `0x08052E08`,
containing a serialized font pointer and line-advance word. It fills a
20-byte runtime font record: height byte at zero, first/last halfwords at
two/four, line advance byte at six, glyph-offset pointer at eight, width
pointer at twelve and pixel pointer at sixteen. The serialized first/last
values are read as halfwords at zero/two, height as byte four, and each
pointer offset is assembled high-byte first from six/seven, ten/eleven and
fourteen/fifteen. Pointer offsets, glyph tables and serialized data bounds are
not validated here. The partial font header now represents these observed
fields; no game assets are included in the source or documentation.

Runtime bank records begin at `0x03001980`; each bank contains two 20-byte
fonts. Initialization loads slot zero of banks zero through three, then
clears 60 bytes of raster state at `0x03001A20` and allocates 2048 work bytes.
It does not initialize the second slots, free an existing work allocation or
check allocation success. Other loader callsites and full resource count
remain unaudited. Both resource and bank declarations keep their outer extent
unsized; the four-iteration initialization loop is not a general index bound.
The state begins with the same two font-pointer words already exposed by
`g_display_fonts`, rather than a separate copy of those pointers.

Font selection installs both pointers for the chosen bank, copies the first
font's line-advance byte to the state's line-height word, and stores the fill
argument. For color mode one it retains the complete palette argument and
clears palette bits; otherwise it retains the low nibble as color base and
shifts the signed high part into the map palette position. The left shift
uses an unsigned value after the observed arithmetic right shift, retaining
word wrapping without a signed left-shift overflow. Buffer setup installs
map/current-map and tile pointers and derives tile byte size as
`(mode + 1) * 32`. No mode validation has been added.

The background-control producer derives map base
`0x06000000 + map_block * 0x800`, tile base
`0x06000000 + tile_block * 0x4000` and 32/64-byte tile size from control bits
eight through twelve, two through three and seven. Its local union records
only those consumed bitfields, leaving other bits unnamed. The mixed
halfword/word bitfield view produces the observed separate mode extraction;
it does not embed original instructions. Prior arithmetic and bitfield
layout failures remain local. Canonical names replace the prior address-only
aliases in the scrolling scene and group-label callers. Those callers still
match 252, 308 and 204 bytes, and their real controls reject by 104, one and
100 bytes respectively, including changed candidate lengths.

Map positioning divides signed x/y by eight with truncation toward zero,
then computes the halfword at `row * 32 + column`; it adds no coordinate
clamp. Row fill repeats a supplied value across 64 bytes per row in mode one,
or repeats its low nibble across 32 bytes otherwise. Row emission copies
`tile_bytes / 4` words for each consecutive tile index, updates a map
halfword and advances the map by 32 halfwords per row. In mode one it writes
the tile index directly. Otherwise fill minus one preserves the existing
high palette nibble; other fill values use the configured palette bits.
It does not mask the tile index to ten bits or validate pointers, stride,
count or storage bounds. These are CPU copies through configured pointers,
separate from the DMA transfer performed by the text object update.

Tile flipping reverses eight rows of eight bytes in mode one. Otherwise it
reverses four packed bytes per row and swaps each byte's nibbles, preserving
the corresponding eight-pixel horizontal flip. This is the direct dependency
of the still-unconverted row reader when map flip bit `0x400` is set. The
remaining row reader at `0x0801B300` (140) and rasterizer at `0x0801AA78` (692)
remain outside coverage; their semantic candidates and raw mismatches are
retained locally. All nine accepted bodies are ordinary C without fixed
register constraints. Fresh font measurement, line selection, alignment,
transfer and catalog closures also match after the shared font refinement,
and their actual controls remain preserved. This compiler evidence does not
independently establish safe runtime inputs or gameplay behavior.

## Height and line-limit consumers

Three callers of the accepted line-selection path add another 260 matching C
bytes, bringing the connected font/row/consumer batch to 12 functions and 936
bytes. Fresh public-source proofs and real compiled controls for all 12 new
functions and ten affected existing closures are indexed by the same local
receipt. Every positive has zero differing bytes; every control rejects.

| Function | ROM address | Bytes | Control differences |
| --- | --- | ---: | ---: |
| `display_text_draw_block` | `0x0801AF98` | 112 | 2 |
| `display_text_draw_limited_line` | `0x0801B008` | 68 | 1 |
| `display_text_draw_all_lines` | `0x0801B04C` | 80 | 1 |

The block consumer draws while the pointed-to string is nonempty and the
remaining signed height is at least the current line height. It advances y
and subtracts that line height after each call, reloading the state after the
callee. The limited-line consumer applies the same height guard once and
passes its caller's count pointer through. The all-lines consumer advances a
local string pointer through repeated calls and advances y without a height
bound. The block and all-lines variants initialize their shared count to
`0x7FFFFFFF`; the limited-line variant retains the supplied count.

All three return the resulting tile cursor. The shared prototypes now expose
their observed signed coordinate and dimension arguments and word return;
this refinement adds no checks absent from the original. In particular the
all-lines loop does not detect a line-selection call that leaves the string
pointer unchanged, and the height loop does not validate a positive line
height. Progress, valid buffer capacity and safe text inputs remain runtime
questions. These three bodies use ordinary C without register constraints or
assembly, and the row reader and rasterizer remain explicit unconverted
dependencies.

## Staging fields and expansion consumers

Eleven connected functions add 972 matching C bytes. Public positives and real
compiled controls, including the 308-byte scene object constructor's renamed
callee closure, are indexed by the local
`reports/agents/display_audio/background_motion/scene/redraw/text-fields-ready.json`.
Every positive matches its complete linked extent; every control rejects.

| Function | ROM address | Bytes | Control differences |
| --- | --- | ---: | ---: |
| `display_text_copy_field` | `0x0801B12C` | 36 | 1 |
| `display_text_copy_field_zero` | `0x0801B150` | 32 | 1 |
| `display_text_copy_field_one` | `0x0801B170` | 36 | 1 |
| `display_text_copy_field_two` | `0x0801B194` | 36 | 1 |
| `display_text_number_field` | `0x0801B1B8` | 20 | 21 |
| `display_text_number_field_zero` | `0x0801B1CC` | 16 | 17 |
| `display_text_number_field_one` | `0x0801B1DC` | 20 | 9 |
| `display_text_number_field_two` | `0x0801B1F0` | 20 | 9 |
| `display_text_copy_expanded` | `0x0801AEC8` | 96 | 1 |
| `display_text_expand_resource` | `0x0801B21C` | 148 | 1 |
| `display_text_format_number` | `0x08044D00` | 512 | 1 |

The copy/number producers address 64-byte slots beginning at `0x03001A60`,
immediately after the previously observed raster state. Generic producers
use their supplied slot index; specialized forms target slots zero, one and
two. Copying includes a zero terminator and adds no capacity check. Number
formatting delegates to the accepted decimal formatter at `0x08044D00`;
its negative-sign/digit stores and original-destination return support the
provisional formatter name and pointer return. The shared
inline address helper retains the ordinary C byte-offset calculation in
the specialized copy forms. These bodies require no register constraints.

The producer bank differs from the active substitutions at `0x03000E20`
read by measurement, glyph rasterization and both new expansion consumers.
Separate unsized declarations preserve that distinction. The transfer or
selection between these banks remains unconverted; adjacency, equal slot
stride and matching source do not establish a runtime handoff. The scene
object constructor at `0x0800F168` supplies its state word at offset four
to the slot-zero number producer before loading text ID `0x25`. Renaming
that former address-only callee leaves the constructor and its actual
changed-source control intact; the state's earlier `text_id` field name
does not establish that the formatter argument itself is a text resource ID.

Copy expansion scans a source string, replacing each `@` plus following
byte with the selected active slot string. It appends a terminator and
returns the copied byte count. The two observed length calls are retained
because a string-copy callee lies before them, and the source slot index is
read again before each call. Replacement text is copied without recursively
expanding its markers. Ordinary characters advance destination before source,
which reproduces the original source schedule without assembly.

Resource expansion obtains the shared lookup buffer, tests for a marker and
modifies that buffer in place. It moves the trailing text including its zero
terminator before copying the replacement, then continues at the end of that
replacement. A mutable access view follows the lookup implementation's
observed writable global buffer; other lookup callers keep their existing
read-only pointer view. The move/copy, character search, string copy/length
dependencies remain explicit unconverted calls. The signed
temporary for the next index and grouped destination offset preserve the
observed calculation and register lifetimes; earlier reassociated forms and
raw mismatch evidence remain local.

Neither consumer checks lookup failure, marker termination, slot extent,
destination capacity or overlap beyond the move helper's role. Replacement
markers are not rescanned here, in contrast with recursive measurement.
These are static and compiler findings; no safe-input or gameplay claim is
added. The only assembly in the two larger sources requests zero-filled
alignment separately from their C bodies.

The formatter covers 512 bytes: instructions end at the return through
`0x08044EC6`, and fourteen literal words occupy `0x08044EC8` through
`0x08044EFC` before the next prologue at `0x08044F00`. The source uses one
semantic decimal-place macro for powers from one billion through ten,
retaining a minus-one digit sentinel to suppress leading zeroes. Once a
leading digit is written, lower places are emitted even when zero. The
configured separator byte at `0x030021F9` follows the billion, million and
thousand places. The ones digit and terminator finish the buffer; there is
no capacity check. Signed division/remainder helpers at `0x0804CD2C` and
`0x0804CE08` remain unconverted dependencies.

For negative inputs the explicit unsigned subtraction followed by the
target's signed word view preserves wrapping negation without introducing
a signed-negation overflow in the C expression. It does not add a correction
for the most-negative word's retained sign. A cursor initialized before the
local value copy produces the observed entry register lifetime naturally;
the prior equivalent parameter-use form differed in five bytes. The macro
and wrapping form both match independently, and the public source control
changing the negative guard to include zero rejects by one byte. No register
constraints, output changes or embedded instruction bodies are used.
