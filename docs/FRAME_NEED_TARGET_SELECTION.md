# Actor need-target selection

`frame_find_need_target` covers the complete 272-byte span at `0x08006F20`.
It connects the existing actor states 24, 26 and 35 to need-effect checks,
action-list production and the accepted target-use handoff. Those callers and
providers gain no additional coverage from this replacement. Names and field
roles remain inferred.

The routine reads eight need values through the existing byte-return provider.
Values at most 30 increment a byte count and append their index to a local
eight-byte array. The original subsequently uses the random ordinal directly,
without reading that collected array. The source preserves this behavior;
it does not substitute the collected need index or infer the intended algorithm.

When the count is nonzero, the routine selects an ordinal from zero through
count minus one, then walks the existing need-state list. It captures `next`
before calling anything, checks definition byte `+34`, calls the state's
word-return predicate at `+0xE4` and tests only its low byte. An accepted node
receives a cleared seven-byte action buffer through callback `+0xE8`; that
callback's return value is unused. The routine scans at most seven nonzero
codes, stopping at zero, and compares the existing action-text row's first
halfword with the selected ordinal. The first match writes the target pointer,
then the full-word action code, and returns one. Failure returns zero without
writing the outputs.

The actor's need-state pointer is copied from four bytes of the whole canonical
`FrameObject` representation at `+0x60`. This stays within its 312-byte extent
and avoids introducing another actor word overlay. The state/list access uses
the existing `FrameActionSearchNode` view and callback declarations. Reuse does
not prove universal effective-type compatibility of every legacy allocator,
list and state view. The copied pointer must have a valid target representation.

The current observed definition prefix contains 149 rows of 36 bytes. Its
allocator copies definition `+28` to state `+0xE4` and definition `+4` to
`+0xE8`. All six observed predicate targets have matching word-return C
contracts. The observed action producers include 21 matching C targets and
38 original targets; their wider capacity and side effects remain uncertain.
Null action callbacks in observed rows 125, 126 and 139 are excluded by their
zero enabled byte. This finite table finding does not exhaust writable callback
assignments or establish a complete runtime population.

Calls require a live, finite list, backed definition/action rows, compatible
callbacks and output objects, and valid need storage. The action writer must
stay within seven bytes and must not retain the buffer beyond the call. Clearing
the buffer and bounding the scan do not prove that every original writer obeys
that contract or writes a terminator. Callbacks must leave the current node and
captured next node valid for the remaining accesses.

The meaningful source control changes the eligibility threshold from 30 to 29.
With one need byte equal to 30 and the other seven equal to 31, the positive
source selects ordinal zero while the control has no candidates. Existing
definition row 3 supplies a concrete conditional witness: its capacity check
passes with three empty state attachment records, capacity one and empty actor
attachment slots; optional mode zero and clock hour six produce action 33,
whose first table halfword is zero. The positive writes target/action 33 and
returns one; the control returns zero. This requires the existing callback's
320-byte actor backing, beyond the core layout's 312-byte extent. It is static
source/ROM evidence, not a gameplay observation.

The native function has 256 instruction bytes, twelve referenced literal bytes
and two internal zero alignment bytes. Its 270-byte function symbol is followed
by two further zero alignment bytes before the independently called state-34
entry. Matching includes the full 272 bytes. The explicit assembly directive
only requests alignment; it contains no original instruction body.

The match uses ordinary C with independent byte counters for the two scans,
a function-scope action buffer and a sequenced local store before the count
increment. These source producers account for the retained compiler results;
they do not identify the original source spelling or historical toolchain.
Whole-ROM matching, finite static mapping and runtime behavior remain separate
claims. No inventory discovery or existing provider adds recovered-C credit.


## Connected action writers

Two ordinary C callbacks add 236 verified extent bytes through the existing
need-effect definition and consumer paths. This includes pools and alignment;
it adds no credit for existing callers, providers or inventory findings.

| Entry | Callback | Bytes | Observed definition rows | Output writes |
| --- | --- | ---: | --- | --- |
| `0x080432CC` | `frame_select_optional_attachment_kinds_432cc` | 124 | 5, 6, 7 | Bytes 0 and optionally 1 |
| `0x08016F24` | `frame_select_optional_attachment_kinds_16f24` | 112 | 104 | Bytes 0 through 3 at most |

The time-based writer selects 45 or 22 for optional modes 1 or 3. Other modes
map the current time period to 28, 32, 30 or 31. Mode 2 appends 12 only when
the signed interpretation of the parameter exceeds 10,240. Its second mode
read remains fresh after the first output write and the time-provider call.
The control changes `>` to `>=`: mode 2, parameter 10,240 and hour six produce
`[28, 0]` from a cleared buffer, versus `[28, 12]` in the control.

Row 104's writer checks the low byte of the optional-ready word result.
Readiness selects 45; otherwise a zero signed parameter selects 57. Other
parameters first write 56 and 100, then reread the parameter before appending
the pairs for `0xA00`, `0xB00` and `0xC00`. Output bytes may alias state storage,
so caching that read would change the source meaning. The first two cases
share an ordinary C append destination for their common final 101. The 57-to-58
control uses optional mode zero and parameter zero with the actual predicate
returning zero.

Rows 5, 6, 7 and 104 have enabled byte one. Their table assignments and the
existing consumers provide conditional static routes, without proving every
such state reaches a consumer or establishing gameplay use. Both callbacks
return the existing word value one. They append no terminator and leave unused
output bytes unchanged. Calls require live seven-byte output backing; the
target selectors clear their local buffers, while the embedded choice-buffer
path retains its own initialization and lifetime requirements. Existing partial
state/list/allocator owner relationships remain provisional. The signed-short
accesses and conversions use the pinned target's 16-bit representation; current
layout/API checks do not identify historical source types.

The two bodies contain 230 instruction bytes, four referenced literal bytes
and two internal zero alignment bytes. The full 236-byte extents are included
in matching. Whole-ROM equality, static routes and runtime behavior remain
separate claims. The 319,640 mapped extent bytes remain the historical
comparison baseline.

## Further action writers

Two further callbacks add 224 matching extent bytes. The former row-97 hold
at `0x08017AC4` now matches its complete 124-byte span; the row-87 writer at
`0x080220C0` matches 100 bytes. Existing consumers and inventory findings add
no recovered-C credit.

| Entry | Callback | Observed row | Behavior |
| --- | --- | ---: | --- |
| `0x08017AC4` | `frame_select_need_actions_17ac4` | 97 | Writes one code: 66, 65 or 64 |
| `0x080220C0` | `frame_select_optional_attachment_kinds_220c0` | 87 | Modes 4 through 9 write 92 through 97; other modes write nothing |

Row 97's writer selects 66 when the signed parameter is positive. Otherwise,
the existing signed-parameter return is converted to unsigned for its `> 3`
and `> 6` tests. Exact low-byte condition checks select 65 or 64. Repeated
condition and parameter calls stay fresh and short-circuit in the original
order. Its 66-to-67 control uses parameter one and calls no providers. The
row-87 writer reads its byte mode once and calls no providers; its 92-to-93
control uses mode four. Both controls change the emitted byte while retaining
the word return value one and leaving unused output bytes unchanged.

The two sources retain eight explicit address operations: the output pointer
is converted to the target's 32-bit unsigned integer, combined with the local
index by bitwise OR, then converted back. Each index is initialized to zero,
never changed and never exposed to another function. Thus the operation keeps
the same pointer bits within this pinned target's pointer/integer conversion
contract. This is implementation-specific C, with no claim that the historical
source used this spelling, that addresses contain tags, or that the operation
works for a nonzero index. The surrounding conditional, switch and provider
logic remains ordinary C. The only assembly directive requests alignment and
contains no instruction body.

Both callbacks write at most output byte zero, retain no output pointer, and
append no terminator. The consumers' live seven-byte backing and initialization
requirements still apply. The signed parameter uses the corresponding signed
16-bit view of the existing field. The existing partial state/list/allocator
relationships remain provisional; matching and target-width checks do not
prove universal effective-type compatibility or runtime state populations.

Row 87 has enabled byte one. Row 97 has enabled byte zero, so both guarded
target selectors skip its factory-installed callback. The choice-builder calls
the action callback before later enabled checks, supplying a conditional
source route. All codes emitted by these two callbacks have first action-row
halfword eight, while the current need selector compares an ordinal from zero
through seven. That selector cannot accept these codes under its current
comparison. These table and consumer facts do not establish gameplay use or
exhaust all possible callback assignments.

The complete spans contain 186 instruction bytes, 32 referenced data bytes and
six alignment bytes. The data includes the bounded six-case switch table and
its referenced pointer. Four newly owned trailing zero bytes account for the
inventory extent changing from 324,000 to 324,004 and the treemap extent from
324,008 to 324,012; the remaining two alignment bytes are internal. Existing
estimated boundaries are not reclassified as complete game-code coverage.
The 319,640 mapped extent bytes remain the fixed historical comparison baseline.
