# Connected map terrain classifier

`frame_map_terrain_at` owns ROM `0x2abb0..0x2ac6c`, including all 188 bytes,
three internal literal words, two internal zero alignment bytes and two trailing
zero alignment bytes. The C symbol is 186 bytes. Its five already matching
movement, actor and render-effect callers pass a concrete `FramePoint` value in
R0/R1. The accepted 52-byte dimension provider writes two signed words through
an output point pointer. The classifier captures its incoming coordinates as
unsigned words and returns a full word; callers may narrow or mask that result.
Names and coordinate meanings remain inferred from these accesses.

After querying dimensions, the classifier returns three when either unsigned
coordinate exceeds its corresponding dimension. Equality passes the boundary
check. Negative input words therefore take the rejection path for the bounded
nonnegative dimension fixtures. The source preserves the native inclusive
comparison and does not add map capacity, pointer or coordinate guards.

The block pointer cell at `0x03001de0` supplies halfword indices. Block selection
uses `(x >> 5) + (y >> 5) * (dimensions.x >> 5)`. The byte plane pointer cell at
`0x03001ddc` supplies 16 subcells per selected block. The subcell uses two low
bits of `x >> 3` and two low bits of `y >> 3`, with the vertical component shifted
by two. Only the plane byte's low six bits become the initial result. Both map
pointer cells are loaded after the dimension provider call; their values are not
cached across that call.

Results four through 35 index 32 observed four-byte records rooted at ROM
`0x08059b3c`. The low halfword contains four unsigned nibbles at bit offsets zero,
four, eight and twelve. The remaining halfword is not interpreted. A word/byte
union access view gives a four-byte size and alignment and retains the single
native word load. The names x0, y0, x1 and y1 describe the subsequent arithmetic:
the classifier forms a direction and a local point, then returns zero when their
cross product is negative. Other results and nonnegative cross products retain
the original six-bit result. Complete table capacities and gameplay meanings
remain unknown.

Earlier word-bitfield candidates reused decoded origins and missed the native
shifts, producing at best 184 bytes with 62 differences. Both byte and halfword
nibble access views compile to the full original extent. This does not identify
an original typedef uniquely. The selected union uses byte nibble fields and an
explicit uninterpreted halfword. Physical initializer checks verify nibble bit
placement, word alignment and the point layout; real counterexamples exercise
changed widths, offsets, const storage and nominal API types.

Two coordinate annotations constrain actual values to callee-saved R4 and R5.
They capture R0/R1 before the real dimension call and remain live through their
last native coordinate reads at `0x0802ac2e` and `0x0802ac36`. Both registers are
saved and restored, and no overlapping pointer or unrelated value shares either
annotation. Removing x, y or both annotations fails the complete byte comparison.
The dimension call's caller-saved registers are poisoned in the finite fixtures.
The only assembly statement supplies original zero alignment after the C symbol;
it contains no instruction body and adds no glue coverage.

Fresh normal and strict declaration profiles verify the classifier and its real
changed-source control. Its six connected existing bodies are also rebuilt with
their own controls. Removing the actual dimension declaration can leave legacy
bytes identical while strict compilation rejects the source. The default
assembler matches, as does the separately inspected older assembler; that
observation does not establish historical compiler or assembler provenance.

The initialized finite packet covers 2,292 cases, including all 32 line records
at every local eight-by-eight coordinate, other kinds, high result bits, block
and subcell boundaries, inclusive dimensions, unsigned negative coordinates and
map pointer rebinding during the provider call. Original bytes, linked C and an
independent arithmetic model agree. The real six-bit-mask control diverges in
901 cases. Five interpreter rejection controls cover unsupported instructions,
truncation, instruction budget and null map pointer roots. The dimension provider
is an abstract bounded hook; those failures are interpreter limitations rather
than claimed hardware faults. No gameplay or arbitrary map-capacity claim follows.

The original three-cell movement probe, movement redirection, renderer and
finalizer remain explicit until their own C extents match. The classifier's
acceptance does not reconstruct those connected regions.
