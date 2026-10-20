# Optional attachment routes 12, 23 and 60

Seven previously mapped routines now have matching C for 572 complete extent
bytes: 542 instruction bytes, 20 literal bytes and ten zero alignment bytes.
The observed need-effect definition rows 11 and 12 share the initializer at
`0x1A360`, begin callback at `0x1A3BC`, dispatcher at `0x1A3E8` and empty finish
callback at `0x1A448`. The dispatcher selects three workers:

| Kind | Worker ROM offset | Complete extent |
| --- | --- | --- |
| 60 | `0x1A2C4` | 156 bytes |
| 12 | `0x1A450` | 136 bytes |
| 23 | `0x1A4D8` | 132 bytes |

The existing selector and prepare callbacks choose the same three kinds. Begin
allocates an attachment record, records its kind and routes it through the
existing registration context. Dispatch directs an actor toward the owner on
phase zero, then calls the selected worker. The record's existing `timer` word
acts as a phase selector here; actor offset `0x58` holds the separate countdown.
Running byte one forces the completion phase. Worker results are one while
active and two when complete; an unrecognized dispatcher kind returns zero.

Kind 60 starts animation eight and a 150-step countdown, selects cue 133 or 132
from the existing interaction setting, then updates need 30. Kind 23 accumulates
the owner's optional state, starts animation 45 and a 90-step countdown, then
updates need 54 until that countdown reaches minus one. Kind 12 starts animation
14 and cue 26, updates need 52 and waits for the low byte of the existing optional
consumer's result to equal one. It stops the stored sound handle on completion.
Each worker requests animation one when completing. These descriptions follow
static dataflow and do not establish gameplay names or timing units.

The canonical owner now names the four-byte sound handle at `0xE0` as
`optional_sample`. Splitting the unused opaque array preserves every other
member offset, the 256-byte structure size and four-byte alignment. The old
array has no consumers outside its declaration. The new definitions and twelve
actual provider definitions pass target type checks; eight deliberately wrong
contracts reject, covering arity, return width, worker argument, finish return,
sound field width/offset, record timer width and the step callback type.

All seven full fixed-address bodies match, including pools and alignment.
Seven genuine source changes reject the comparisons; the empty finish control
grows its emitted extent, and the comparison retains those extra bytes. The
only assembly directives in the new C emit zero alignment. Full project gates
also check the shared header against all previously accepted sources.

The initializer's unused owner formal remains inferred from its caller protocol.
Observed table rows are not a complete selector, writer, target or backing
population. The neighboring word at `0x1A44C..0x1A450` decodes as a return-100
leaf, but has no established incoming root. It remains an inventory question
without a fabricated C owner. No new runtime execution observation is claimed;
complete executable inventory and source ownership remain unproved.
