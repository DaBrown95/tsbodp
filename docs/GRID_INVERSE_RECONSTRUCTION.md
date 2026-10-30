# Grid inverse projection

The point-to-cell converter at `0x08048AF8` and inverse projector at
`0x08048BF8` compile to their complete original extents: 128 and 88 bytes.
Their function bodies occupy 126 and 86 bytes; each extent includes two
alignment bytes. See the [converter](../src/frame/frame_grid_point_to_cell.c),
[inverse](../src/frame/frame_grid_inverse_point.c) and
[build metadata](../config/build-us-eu.json).

Both functions first snapshot point X/Y and registration origin X/Y. Their
common projection computes:

```text
x = origin_y - origin_x/2 + point_x/2 - (point_y - 8)
y = origin_x/2 + origin_y + point_x/2 + (point_y - 8)
```

Signed divisions truncate toward zero. The original guard tests X against
zero, tests Y against the span twice, and omits the upper X test. Both sources
retain that bug. Failed guards leave the caller's output unchanged.

The source uses two views of the same eight-byte origin pair. Each word is a
real arithmetic input and is assigned before its own read. The record's low
word assignment retains the partial-word lifetime; the complex imaginary
assignment exposes the high word to forwarding. The pinned compiler removes
the high-word transfer and reader during combination in the converter and
register movement in the inverse. Allocation then deletes the remaining
low-word transfer while retaining the native R5 save history. The emitted
bodies do not use R5. This explains the matching
source representation; it does not establish the original historical type.

The converter retains two private coordinate objects and a sixteen-byte
frame. It divides each accepted coordinate by the byte cell size and writes
only the two cell bytes. The first byte store precedes a fresh second cell-size
read, preserving possible alias effects. The inverse has an eight-byte frame
and publishes both accepted coordinates through the existing provisional
`resource_project_point` API. Its point inputs and outputs may alias.

Intermediate complete candidates isolated different constraints: a returned
point lost the native backing storage; an addressed value consumer left the
original mismatch; a record origin pair recovered the save/context roles but
retained a high-word copy; the complex-only pair forwarded that copy but lost
the required lifetime. Combining the supported low and high views matched the
converter, and the identical producer then matched the standalone inverse.
Intermediate regressions receive no source credit.

Default pinned compiler flags and canonical headers reproduce both functions.
Changing the actual Y adjustment from eight to nine rejects each complete
comparison by one byte. Full-ROM equality, its changed-source control and
progress gates are separate checks. The two source owners add 216 C extent
bytes, with no assembly exception, new runtime execution, callback-domain
closure or complete executable-inventory claim.
