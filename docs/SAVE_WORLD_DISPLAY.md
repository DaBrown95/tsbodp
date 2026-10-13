# Selected-row display producers

Six connected routines add 576 verified matching C bytes: row palette refresh
at `0x0801EEE8` (88), indicator creation at `0x0801EF78` (116), gauge scaling at
`0x0801EF40` (56), percentage scaling at `0x08027524` (20), and percentage ratio
at `0x08027538` (16), plus the row gauge/object updater at `0x0801EB84` (280). Each complete linked extent includes its alignment and
literal pools. Five sources use ordinary C without register bindings. The 280-byte updater
uses two scoped semantic C register constraints described below. Every actual
changed-source control rejects against the fixed reference.

These functions connect the published 56-byte selected-row transition and
nullable object teardown to the original view updater at `0x0801E798`. That
updater tests the row flag `0x400000` before palette refresh, and calls the gauge
scaler for the selected needs display. The accepted gauge updater at `0x0801EB84` iterates eight entries and calls
indicator creation only for an empty slot. The main view function ends at the next prologue `0x0801EAC8`;
its 816-byte body and the adjacent 188-byte window completion remain
unconverted. These static call findings do not add C coverage.

Palette refresh compares the full incoming row index to the selection byte at
`0x030040E0 + 0x31`. Only the selected row loads original palette resources at
`0x080D04CC` and `0x080D098C` with extra banks one and two, then the palette-range
configuration at `0x08053518`. Every incoming row clears its flag `0x400000` at
`0x03004130 + index * 56 + 4`. An integer address view expresses these observed
byte strides and the flag-word offset; it introduces no new storage allocation.
The resource data remains in the original ROM and is not included in source.

Indicator creation allocates object id 24, stores it in the requested row slot,
clears the halfword at object `+0x0A`, assigns flags `0x200019`, and clears the
observed display-layer bits. Two original coordinate bytes per entry at
`0x08053528` produce fixed-point positions `(x * 8 + 2) << 16` and
`(y << 19) - 0x20000`. The object acquires palette slot six and animation record
`0x08053538`. The coordinate pair is explicitly packed: its observed stride is
two bytes, whereas this compiler's default two-byte struct occupies four bytes.
The initial unpacked candidate failed across 71 bytes; the packed pair gives
the complete 116-byte match. The original body does not check allocation failure
or its incoming byte index. Eight slots follow from the connected loop; that
loop does not validate arbitrary callers or establish a complete resource bound.

The gauge/object updater selects the same 56-byte row from the current selection
byte. For each of eight entries, a `4 << index` flag or changed need byte causes
a fresh byte snapshot at row `+0x30 + index`, a second need query for the displayed
level, and a one-column, three-row map copy from the pointer at `0x03004124`.
A forced refresh skips the comparison query, while the changed-value branch
performs that query as well. The original separately queries the comparison, snapshot and gauge inputs;
the source retains that observed call sequence. A zero row countdown and `0x400 << index` flag
require an indicator, creating it only if its slot is empty. Other cases release
a non-null slot through the published teardown helper. The final `0xFFFC0003`
mask clears the observed update and indicator-request bits.

The updater retains the actual object-slot byte offset in `r9`, incrementing it
by four for the eight slots. A semantic inline reader briefly holds the computed
slot address in `r0`: row base, plus the observed `0x10` object-array offset, plus
the live slot offset. It makes no call and releases that binding before either
object lifecycle callback. These constraints recover original address lifetimes
without embedding instructions or changing the algorithm. The initial ordinary
pointer loop became a moving object pointer and failed at 272 bytes. Keeping
the scalar slot offset recovered 280 bytes; the scoped address reader and the
observed direct-global argument form for the first need queries closed the full
extent. An otherwise exact trial with an unnecessary cached-pointer binding
remains private; the accepted source uses only the two necessary constraints.

The percentage helpers pass word products to the original signed division
provider at `0x0804C8C8`. Scale narrows only its second formal to an unsigned
halfword, multiplies it by the full first word, and divides by 100. Ratio
multiplies the full numerator by 100 and passes the full denominator unchanged.
Unsigned intermediate multiplication retains the observed low 32 bits before
the explicit signed argument conversion. No new denominator guard or saturation
is added, and the provider's exceptional-case behavior remains an original
implementation dependency. Gauge accepts a signed halfword value, unsigned
halfword maximum, and byte step count; for positive values it narrows the ratio
result to a halfword before scaling by `steps + 1`, then clamps the signed result
to zero through the step count. Nonpositive values return zero.

The existing pinned `binutils2101` assembler profile reproduces the original
zero alignment halfwords in the gauge and percentage helpers. Their modern
assembler trials retained the same instruction bodies but emitted a different
alignment halfword; those failed comparisons remain local. No padding statement,
section stripping, output patch or ignored comparison range is used. Positive
and actual mutated-source objects have `.text` as their only nonempty allocated
section, and the linked extents retain no unresolved relocations.

Proof inputs, failed candidates and raw bytes are retained under ignored
`reports/agents/display_audio/save-stream/`, with fresh canonical proofs in
`selected-row-public-proofs-*`. The ready receipt records exact sizes, symbol
addresses, assembler selection, source and header pins, and negative comparisons.
This establishes source compilation and byte equality. Timer units, complete row
roles, arbitrary index bounds and runtime UI behavior remain uncertain.
