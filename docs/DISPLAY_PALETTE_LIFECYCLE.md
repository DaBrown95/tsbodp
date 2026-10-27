# Palette lifecycle connected to scene transitions

This batch reconstructs fifteen C functions totaling 596 bytes. The frame-side
coordinator at `0x080117d4` advances the twelve eight-byte range records, then
calls the already matching block scheduler. Seven matching fade paths and the
scene request handoff call this coordinator. The scene shutdown, primary exit
and condition panel close call the reset coordinator at `0x080117bc`.
Their former address-based aliases now name the same two providers directly.
The VBlank commit and DMA transfer paths remain the separately verified
consumers of the resulting palette jobs.

The range constructor writes the interval, clears the delay and initializes
the source/destination range and its two counts. Configuration replaces its
flags/interval and clamps a larger delay. Its clamp compares the stored byte
against the complete incoming interval word before storing a byte. Enable and
disable consume the low byte of the incoming index; disable also consumes the
low byte of its restore argument. The restore branch moves the destination
start back to its source start and marks the range for transfer. These are
static field roles, with no new runtime or original-header claim.

Reset visits all twelve range and block records through the matching single-job
reset providers. The global counts are cleared before these calls, then the
queue count is cleared by the combined coordinator. This preserves the block
reset provider's conditional decrement and the absence of an enabled-mask
clear. The constructors preserve their unchecked allocator indices and byte
stores: the existing block lookup can return twelve when all slots are busy,
and the range allocator increments without a capacity check. No bounds guard,
overflow recovery or caller precondition has been invented.

The two sequence constructors extend the existing 20-byte block constructor
with its palette count. One reads a resource's observed eight-byte prefix:
a palette pointer followed by first/count/duration/interval bytes. This view
does not establish complete resource ownership or table capacity. The integer
address expressions form the observed eight- or twenty-byte record stride
before adding its RAM root, preserving the original literal-load scheduling.
They rely on the pinned target's 32-bit address representation.

Initialization at `0x080116b4` sets the cached curve halfword to `-257`, calls the
curve provider with 256, allocates two zeroed 512-byte staging
buffers, supplies palette RAM destinations `0x05000000` and `0x05000200`, then
resets the jobs. The pair initializer at `0x080119b0` retains the original
unchecked allocation result. The connected 216-byte lookup-curve provider at
`0x0801155c` is reconstructed in the next batch described below. The 400-byte interpolation body at
`0x08011c60` now has a matching source owner, described below. Valid argument
domains, complete ownership and runtime behavior are not established by the
matching lifecycle sources.

All fifteen source bodies use ordinary C with no register bindings or added
memory traffic. Each full extent includes its literal pools and alignment up
to the following independently observed entry. The sixteen-byte range reset
and combined step coordinator explicitly retain their final two zero alignment
bytes. Every accepted replacement has a compiled changed-source control;
current callers and all importers of the four refined role headers are rechecked
against their final literal header snapshots. Raw failed source forms and
comparisons remain local, including the initial root-load order differences
and the excluded interpolation register collisions. These checks establish
matching source extents and static connections; they do not establish complete
palette reconstruction or gameplay behavior.

# Lookup curve and its arithmetic providers

The initialization dependency now has matching C for the complete 216-byte
curve at `0x0801155c` and its direct 28-byte multiply and 24-byte divide helpers
at `0x080272d0` and `0x080272ec`: three functions and 268 bytes. The multiply
also serves the already matching background matrix update. The following
range loader at `0x08011634` was already accepted; it contributes no new bytes
to this batch.

The curve consumes the incoming word's low halfword, compares it with the
signed cached halfword before applying its signed upper clamp, and calculates
two piecewise byte-output runs. Its accumulators and steps retain their
observed halfword wrapping. The loop increment is a signed word converted
from the step before the loop, and the destination address adds the index
before its RAM root. These value scopes reproduce the native conversions
without register bindings, extra reads, volatility or added guards. The
second run uses a shifted unsigned word followed by the observed signed-high
interpretations; no negative signed left shift is introduced.

The arithmetic providers consume signed low halfwords and return a complete
sign-extended word after their low-half result. Multiply adds 255 to a negative
full-word product before its shift by eight, preserving truncation toward
zero. Divide multiplies the signed numerator by 256, delegates signed division
to the explicit original runtime helper, then narrows the result. The existing
`int(short, short)` multiply interface remains unchanged. These are evidence
based ABI and eight-fractional-bit models, rather than recovered original
headers or a claim that every caller's numerical domain is established.

Multiply retains one binding for its actual full-word product in `r0`; that
value is confined to a leaf and crosses no calls. Ordinary unbound predecessors
and the alternative rounded-value binding remain in local evidence. Divide
uses ordinary C and explicitly retains its two final zero alignment bytes.
The curve owns its two literal pools before the independent range-loader
entry; multiply ends at the divide entry, and divide ends at `0x08027304`.
Each full extent and its compiled changed-source control is verified, along
with all accepted importers of the refined cache comment and the existing
background and initialization callers.

The output is declared as an unsized byte view. The nominal two runs reach
indices through 31, but negative input values, complete table ownership and
valid caller domains remain unestablished. The source preserves unchecked
division and index behavior; it adds no zero-denominator handling, clipping of
negative inputs or capacity guard. Matching extents and these static data-flow
connections do not prove palette appearance or gameplay behavior. The
400-byte interpolation routine is reconstructed below.

## Block interpolation

The worker at `0x08011c60` now has matching C for its complete 400-byte extent,
including three literal words and four alignment bytes. It advances byte delay
and duration counters, rotates configured palette sequences or clears completed
jobs, then interpolates changed RGB555 entries toward the selected target.
Each color pair is captured once; the remaining-step byte is captured once
for its three signed divisions. Channel results retain their unsigned-halfword
conversions before the final masked pack. Equal input words skip the output
store. The unchecked backing, counts and original completion behavior remain.

Two packed local word owners retain the actual two-byte input values through
the masked reads, without overlaying game memory. Their aggregate HI mode keeps
the current word separate from the blue result and reproduces the late target
spill. Restoring the ordinary job flag reads supplies the remaining compiler
copy in buffer selection. This matches with the pinned compiler without register
bindings, extra observations or output repairs; it does not identify historical
source declarations. Normal/strict complete comparisons and changed-delay-flag
controls pass. The connected constructor, reset, scheduler and arithmetic owners
are rechecked by the full build. Source ownership adds no runtime observation
or closure of palette backing, writer or callback populations.
