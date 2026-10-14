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
explicit original curve provider with 256, allocates two zeroed 512-byte staging
buffers, supplies palette RAM destinations `0x05000000` and `0x05000200`, then
resets the jobs. The pair initializer at `0x080119b0` retains the original
unchecked allocation result. The 216-byte lookup-curve provider at `0x0801155c`
and 400-byte interpolation body at `0x08011c60` remain unconverted. Their byte
stores, incoming halfword consumption and nominal lookup range are static
evidence; valid argument domains, complete ownership and runtime behavior are
not proven by this batch.

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
