# Active need-effect average and need 7 update

This connected batch reconstructs two functions, 276 bytes of ordinary C:
`frame_need_effect_average` at ROM offset `0x2E4CC` (160 bytes) and
`frame_update_need7_from_effects` at `0x3C614` (116 bytes). Names describe the
observed operations provisionally; the gameplay meaning of need 7 is unresolved.
Both own their complete original extents, literal pools and zero tail alignment.
The source uses no register bindings or instruction bodies.

The average walks the existing active-list head at `0x03005868`, caching each
node's next pointer before a possible callback. It indexes the 36-byte definition
table rooted at `0x08062E7C` by the state's word kind at offset `+8`. It reads
definition byte `+0x18` through a distinct strided view,
`g_frame_need_effect_average_callbacks`, rooted at `0x08062E94`. This is the
same field that the published allocator copies into state callback `+0xFC`;
it is not a second definition-table root. The accessed word is
accessed as a callback returning a byte from a state pointer; the original call
uses the Thumb `r1` veneer and explicitly narrows the result. Callback targets,
valid kind bounds and list integrity remain unresolved.

For optional byte values 1 and 2, the contribution is 100 minus the signed high
byte of the parameter halfword at `+0x70`; the prior accumulator has a signed
16-bit view in that subtraction. Other states call the table callback, or add
100 when it is null. The accumulator wraps to an unsigned halfword and the count
wraps to a byte after every node. A nonzero wrapped count divides the unsigned
halfword total by that byte using the signed BIOS divide wrapper at `0x0804C8C8`;
both operands are nonnegative in their observed domains. The quotient narrows to
a byte. A zero count yields 50, and an optional output pointer receives the
wrapped count. No count bound, clamp or nonempty-list guarantee is added.

The wrapper operates on the existing local need-state storage at `0x03003A00`.
For scenes in the published idle-exclusion predicate, or scene 28, it reads need
7 and the effect average, substitutes target 25 for zero wrapped count, and
chooses adjustment row 41 or 43 when the current byte is below or above target.
Other scenes select row 42. The adjustment call uses amount 1. This establishes
a connected provider/caller path; it does not establish the gameplay role of the
rows or prove runtime behaviour.

The guarded table lifetime and a staged signed contribution/previous-total
expression recover the original compiler scheduling without register constraints.
Earlier 144-byte and type/lifetime variants are retained with complete raw
comparisons in ignored reports. Changed-source controls alter default average
50 to 51 and the wrapper's zero-count target 25 to 26; both must reject. The
adjoining 720-byte placement controller and its unresolved selection dependencies
remain explicit unconverted targets, as does the retained 356-byte target selector.
