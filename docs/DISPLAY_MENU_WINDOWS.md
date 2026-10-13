# Menu text and window setup

The connected menu text producer at ROM `0803EFB8` matches its complete 352-byte
extent. Its scene setup's window producer family also matches: disable at
`08048854` (24 bytes), configure at `08048884` (112 bytes), and rectangle at
`080488F4` (80 bytes). The connected scene/menu initializer at `0803E518` matches 744 bytes. The five
functions add 1,312 verified C bytes. They compile
as Thumb C at their original ROM addresses, including all literal pools and
alignment. These bodies do not execute from copied RAM.

## Menu text evidence

The menu producer clears five byte positions and walks five row codes. It selects
font group 3, highlights the row equal to the scene-request word at `+8`, and sets
line height to 12. Code 29 skips a row. Codes 0 through 21 select a text base from
the existing 44-byte greeting descriptor and add the row parameter. Code 22 uses
text 1152. Codes 23 through 26 use a pointer table, a selected 24-byte record and
that record's five byte entry selectors to choose another record's halfword text
ID. Code 27 uses the parameter indexed by the scene-request word plus 1154; code
28 uses text 1153. The selected string passes through the published text lookup
and tile drawing consumers. Drawing starts at tile 258, x=72, width=144, and
advances the following row's byte Y position by 12 until the string is consumed.

The partial menu state at `03002198` has definition word `+4`, record-group word
`+8`, five codes at `+14`, five parameter bytes at `+19`, six observed position
bytes at `+1E`, and selected-record byte `+25`. The table at `08D715C8` contains
record pointers; each observed record stride is 24 bytes, text ID is at `+0`, and
five entry bytes begin at `+4`. The table and greeting descriptor declarations
remain unsized. This establishes offsets and the producer's five-row walk, not
complete storage bounds or validation of the definition, variant, record, or
request indices. Catalog-state word `+440` is read through an explicit integer
address beyond the existing partial context view; its broader meaning remains
provisional.

The existing greeting descriptor's unknown first word becomes
`const unsigned short *text_ids`. The initializer also establishes a background resource pointer at `+0C`. The
remaining bytes stay explicit (`unknown_04[8]` and `unknown_10[16]`), with cue
pointer at `+20` and cue variant at `+25`. This preserves the 44-byte stride. The existing actor state 46, which
reads those cue fields, recompiles exactly and its actual control is rejected.
There is no claim that the complete greeting resource format is understood.

For row codes other than 0 through 29, the original falls through without
updating the text pointer. The retained source preserves that access and does
not invent validation or a default text. The producer itself supplies no proof
that these codes are reachable or that all callers initialize a valid code.
The accepted initializer resets all five codes to 29; later code population and
its complete input-domain guarantees remain unconverted.

The loaded halfword text ID has a short local C binding to r0, released before
text lookup. The entry pointer and final ID arithmetic remain ordinary C.
Earlier natural pointer candidates differed despite the correct total size;
a separate semantic entry pointer and a loaded ID scope reproduce the observed
allocation. No instructions, original body bytes or output changes are embedded.

## Window producer evidence

The disable helper reads a halfword from the unsized mask table at `080841F0` and
passes it to the accepted display-layer disable helper. The configure helper
updates the observed `WININ` and `WINOUT` halves at `04000048` and `0400004A`,
then enables the mask selected by the same table. Index 0 writes the low inside
byte; index 1 writes the high inside byte. Both preserve the high outside byte
and write the caller's outside mask. The halfword arguments retain the observed
narrowing. The routines do not establish index bounds or sanitize mask bits.
Volatile accesses describe these observed hardware register reads and writes.

The rectangle setter writes four complete signed position words into the
60-byte window records at `03007460`, at offsets `+8`, `+C`, `+24`, and `+28`.
A named fixed-point union exposes each word and its signed upper half. It packs
those upper halves into `WIN0H/WIN1H` and `WIN0V/WIN1V` at `04000040` and
`04000044`. The setter rereads left, right and top integer halves after storing
the words, and uses the bottom argument's arithmetic upper half. The adjacent
left/top pair pointer reproduces the observed access structure without an
instruction transcription. The partial overlay preserves the current record
stride and matches the signed halves already consumed by the accepted VBlank
window commit. That existing 108-byte commit and its actual control are freshly
rechecked. The setter makes immediate register writes; it does not itself mark
the VBlank dirty flag.

The index-1 configure branch uses short local C bindings for its selected mask
(r1) and combined register value (r0). Both finish at the immediate register
store and neither crosses the layer-enable call. Unbound variants and alternate
semantic expressions remain preserved as failed evidence. These are compiler
allocation constraints, not replacements with assembly instruction bodies.

## Scene/menu initialization

The 744-byte initializer connects these window and text producers to the
accepted background, palette, audio-cue and transition operations. It first
clears an existing effect list through an unconverted dependency, sets display
mode 0, enables object display and configures four background layers using
control words at `0807F688` through `0807F694`. It fills those layers and assigns
the layer-0 control to the text raster. The added menu view exposes the observed
bytes at `+26` through `+2B`; their broader meanings remain unknown. Byte `+24`
becomes `resource_shown`, following its clear and its set after a background load.
The six bytes are appended without moving the existing row or choice fields.

Unless request mode is 1, the initializer copies the request's `+8` word into
menu definition `+4`, then clears request words `+8` and `+10`. It tests the
catalog-state byte at `+3A + 4*definition`: zero plays greeting cue record word
7; nonzero switches request mode to 2 and plays cue word 0. It reuses the existing
partial relation-state view's `records[].unknown_02[0]`, keeping that byte's
meaning unresolved. Mode 1 with request word `+8` equal to zero switches to
mode 0. This preserves the observed accesses without asserting complete request
or greeting-index validation.

The initializer resets all five menu row codes to 29, resets the selected-record
byte and two adjacent bytes, and passes catalog-state `+10` and `+30` to the
unconverted relation preparation/read helpers. It stages a 16-color palette,
loads the greeting descriptor's background resource or its palette according to
request mode, loads another palette resource and range definition, and invokes
another relation-resource stage. Background 3 receives velocity `-65536` on each
axis, consistent with the accepted signed fixed-point motion fields. Background
1 receives the panel resource; its returned map pointer is stored as the observed
32-bit menu word at `+10`. The panel filler receives catalog-state `+20` as its
resource descriptor pointer. These pointer roles follow actual load/store and
call shapes; broader asset formats remain unconverted and no assets are copied
into source.

The title uses text base `0x1789 + definition`, then footer preparation runs. The
initializer configures both windows with inside mask `0x3F`, outside mask `0x3E`,
and fixed-point rectangles (72,116)-(216,152) and (16,32)-(120,92). Request modes
0, 1 and 2 invoke separate unconverted stages and disable the appropriate window.
It clears request word `+8` and invokes transition kind 0 for target mask 63.
The forward declarations keep these unresolved dependencies explicit.

The initializer uses ordinary C without register constraints. Separate scopes
for initial state setup, relation/background setup and the returned panel map
keep the actual values' lifetimes bounded. The five-code reset accesses the
canonical global row array. Earlier longer pointer scopes, flat address reads
and alternative field views failed; their raw comparisons are preserved. The
new greeting resource pointer refines the same 44-byte layout. The accepted menu
producer and actor state 46 remain exact with the current shared header and real
controls, as do the new window producers and the prior VBlank commit.

## Verification

Canonical public sources and header snapshots are compiled independently. Real
changed-source controls alter the skipped row code, mask-table index, preserved
mask bits and stored bottom position. They reject with respectively 1, 14, 29,
and 55 differing bytes. The initializer's real control changes the reset row
code from 29 to 28 and differs in one byte. The two existing consumers' controls
also reject.
Full expected and linked bytes, source hashes, commands and useful earlier
mismatches remain under the ignored
`reports/agents/display_audio/catalog-presentation/` directory, with ready
metadata in `menu-window-ready.json`.

Names and roles follow the observed callers and fields. Exact linked bytes and
static connection to scene setup, tile rendering and VBlank transfer do not
establish runtime execution, gameplay behavior or complete subsystem coverage.
The unconverted downstream mode stages and other original regions remain
explicit.
