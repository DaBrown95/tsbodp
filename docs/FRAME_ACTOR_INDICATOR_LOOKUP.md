# Actor indicator selection from saved condition displays

The read-only lookup at `0x0802C9C0` has a complete 112-byte matching C extent.
It connects the saved condition-display bitset to actor indicator updates and
both primary menu population and restored menu choices. These are compiler and
static connections; the function name and data views remain inferred.

The argument is narrowed to a byte by the observed entry sequence. The lookup
then compares the full word `actor + 18`, without narrowing that sum, with word
IDs rooted at `0x0805F860`. It scans rows zero through fourteen and bits zero
through seven in ascending order. A zero display byte skips its entire row;
an unset bit skips the corresponding ID load. The first enabled matching ID
returns the flat selector `row*8 + bit`, in the range zero through 119. Failure
returns the full word 255. This selector is an index into display-related
choices, rather than the ID word stored in the table.

The bytes at `0x03001E00` already have matching setters, a 15-byte clearer,
save-stream readers/writers and a completion path which clears its chosen bit.
The accepted `condition_lookup_kind` uses the same word ID root through the
separate condition record index and subtracts eighteen. Together these readers
and producers support the lookup's inferred actor-to-condition role. They do
not establish complete table ownership, the validity of every setter index or
which states can arise during gameplay.

The accepted actor tick passes the narrowed `subtype - 18` and tests the result
against 255 before creating or removing its indicator pointer at `+0x90`.
The serialized actor constructor clears that same pointer. The primary menu
passes its narrowed definition and retains the returned selector in its
observed indicator-choice fields. The restored menu-choice path looks up the narrowed recorded group and passes
its result to the accepted condition-display completer; that path does not
check the failure sentinel before completing it. All three direct accepted callers and all
accepted bitset/table providers have fresh actual source controls and complete
current header closures. No caller ABI or shared layout is changed.

The source snapshots each nonzero display byte for the inner loop. The guard
and snapshot fold into one native byte load per outer iteration, matching the
original. The row table address uses an ordinary byte offset plus the target's
32-bit integer address representation. One register binding retains the actual
word-table base in `r1`; its literal load at `0x0802C9E0` is consumed by the row
pointer addition at `0x0802C9EE`. The next reuse of `r1` is at `0x0802C9F4`.
There are no calls, stores or clobbers during that lifetime. The byte offset
and current word walker remain unbound. No initialized dummy value, additional
memory traffic, volatile access or instruction-body assembly is introduced.

Local causal reductions preserve both useful unmatched ordinary forms. Removing
the table-base binding from the final integer-address form gives 124 bytes with
117 byte differences. Replacing the byte-address calculation with ordinary
pointer addition gives the correct 112-byte extent with nine differences.
An earlier exact two-binding form was reduced successfully: binding the byte
offset to `r0` was unnecessary and was removed. The semantic negative control
changes only `actor + 18` to `actor + 17`, producing one byte difference.

The complete symbol owns both mid-function pools at `0x2CA08` and `0x2CA0C`,
containing the saved byte root and the word ID root. It ends after the return at
`0x2CA2E`, immediately before the independently accepted lookup at `0x2CA30`.
Its native symbol and allocated section are both 112 bytes, with no trailing
alignment outside the symbol. Full raw comparisons retain all pools and bytes;
no reference, output or mask is changed. Integration and runtime behavior
remain separate checks.
