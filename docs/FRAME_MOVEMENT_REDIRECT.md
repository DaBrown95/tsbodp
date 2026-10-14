# Movement redirection

`frame_redirect_movement` covers the complete 284-byte Thumb region at
`0x0802ADF8..0x0802AF14`. Ordinary C with no register annotations or inline
assembly produces the original instructions, 12-byte literal pool, internal
zero alignment and trailing two zero bytes under the pinned agbcc and
binutils 2.10.1 profile. The C symbol is 282 bytes; its natural section tail
is included in the comparison. The next independent entry is the accepted
240-byte offset query. Names and roles remain provisional; byte equality and
bounded fixtures do not establish gameplay.

The contact line root is the existing `g_frame_movement_contact_lines` at
`0x08059B3C`. Its four-byte `FrameTerrainLine` union now also exposes the
actual `unsigned char bytes[4]` representation, without changing its word,
nibble fields, size, alignment or offsets. The direction root at `0x08059B2C`
uses the same physical stride; four direction records precede the contact
root. The accepted terrain classifier keeps its source, metadata, profile
and original changed-source control. Its current normal and strict proofs
are refreshed after this header addition, with no new C credit for that
refinement.

The redirect reads byte one before byte zero, forms signed low/high-nibble
differences, and queries the direction provider with an eight-byte point by
value. The early endpoint snapshots have disjoint scopes. The final pair
survives its query and supplies the real scaled offsets, reusing the same
working point. The two early X-coordinate annotations in the preceding
private candidate can both be removed with the byte-array union view while
retaining the complete match. Each point component lies between -15 and 15
before multiplication by 16384. No extra reads, initialization, traffic or
qualifiers were introduced to obtain the allocation.

Contact 37 returns before table access, while contact 3 skips the contact
line query. The sole accepted direct caller, `frame_apply_movement_contact`,
passes contacts 2 through 35 when response is 3. Contact 2's unsigned
`contact - 4` arithmetic wraps. The source forms the actual 32-bit unsigned
root address plus the shifted word offset, then converts that address to a
const line pointer. This reaches the physical contact root minus eight bytes
without an out-of-object array-index operation. The pinned compiler proves
unsigned integers and pointers are four bytes. No guard or contact-table
capacity is inferred; integer-to-pointer conversion follows the target's
32-bit address model.
The classifier's 32 accessed records are an observed prefix. Direction
indices, pointer validity and arbitrary capacities remain unchecked; the
four direction records do not establish a general bound.

The object direction's low bit is reloaded after the contact query. The
initial direction divided by two remains captured. Both filter words are
read after the final direction query; the first is at `0x03001DF0`, the
second at +4. A zero/zero filter tries the original scaled offset and, only
on a nonzero low-byte status, tries its negation. A nonzero/zero filter tries
the negation; zero/nonzero tries the original; nonzero/nonzero stops. The
final offset status is ignored. A provider change to the filter during the
first offset query is not followed by a fresh filter decision.

Normal and strict positives compare against the fixed ROM over all 284
bytes. Genuine contact-37-to-36 source controls reject in both profiles.
Layout and API diagnostics check the four-byte representations, actual byte
widths and word contact/point contracts, with real wrong-width, packing and
prototype failures. The connected accepted caller, both query providers,
terrain classifier and dimensions provider retain their own real controls.

The retained finite packet compares original, compiled and semantic-model
results in 1,487 cases with 80 changed-source divergences and three
interpreter failures. It executes actual ROM byte reads, while direction
and offset services are explicitly abstract hooks. Cases include contact 2
and 3, contact-37 early return, low-byte status consumption, all 256 direction
bytes as unchecked ROM-address diagnostics, direction reload and filter
mutation boundaries. Caller-saved poisoning and callee-save/stack checks
pass. These are initialized finite inputs, not arbitrary-capacity,
hardware-fault or gameplay evidence. Useful predecessor mismatches, the rejected indexed-array contact view and
wrong-width, alignment or incompatible declaration diagnostics remain private.
