# Primary menu row parameters

The reader at `0x08040E30` adds 84 bytes of ordinary matching C to the connected
primary menu path. The accepted row producer invokes it for each of the five
observed row slots and stores the low byte of the result in its parameter array.
The result itself is a complete unsigned word: the native return copies the
word accumulator to `r0`, without a final byte conversion. The prior byte-return
declaration represented the caller's store width and is corrected to the observed
callee width. The row argument remains a full word, and the existing random
provider keeps its unsigned-halfword argument and result contracts.

The reader addresses the menu code byte at `0x03002198 + 20 + row`. It retains
both original unsigned tests: codes greater than 21 skip selection, and code 22
also skips it. These nested tests are redundant for the observed byte domain,
but both occur in the original. A signed-first comparison is not equivalent:
it would admit codes 128 through 255. That earlier, closer-looking private
candidate remains excluded, as does an unsupported volatile form.

For an eligible code, the function sums the preceding byte counts from the
read-only table at `0x08060E6C`, then adds an inclusive random sample whose limit
is the selected count minus one, narrowed to an unsigned halfword. A zero code
skips the prefix loop. A zero selected count still produces the original limit
65535; no guard, clamp or inferred valid-resource precondition is added. The
count table's complete ownership and the validity of arbitrary row arguments
remain unresolved. The name describes the observed menu consumption rather
than recovered original terminology.

An ordinary byte-code base is established before adding the row. Separate nested
guards preserve the original reload before the prefix loop. These lifetimes
match the native instructions without register bindings, added memory traffic,
volatile accesses or instruction-body assembly. Earlier folded-address and
combined-guard forms remain as raw mismatches in local evidence.

The full extent ends at the independently accepted result helper at
`0x08040E84`. It owns the menu and count-table literals at `0x40E7C` and
`0x40E80`, and the two original zero alignment bytes before those pools. The
source and linked section retain every byte; no output, reference or mask is
changed. A real changed-source control changes the upper code threshold from
21 to 20 and fails comparison.

All 23 accepted literal importers of the refined primary-menu header are
recompiled with their real source controls. The bounded random provider and
its word generator are checked as well. The sole direct accepted caller retains
its byte store under the complete word-return declaration. These source, ABI
and static data-flow checks remain separate from full-ROM integration and
runtime behavior. The connected row-code reader at `0x0803F260` remains explicit
original code in this batch, with a 380-byte complete extent inferred from its
return, alignment and following independent entry.
