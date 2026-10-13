# Need-effect allocation, handoff and teardown

Seven connected C replacements cover 616 bytes, including their literal pools
and observed alignment, at their original Thumb addresses:

| Function | ROM offset | Bytes |
| --- | --- | ---: |
| `frame_need_effect_remove` | `0x2E1E8` | 56 |
| `frame_need_effect_before_step` | `0x2E220` | 48 |
| `frame_reset_need_effect` | `0x2E250` | 52 |
| `frame_need_effect_enabled` | `0x2E284` | 72 |
| `frame_allocate_need_effect_state` | `0x2E2CC` | 248 |
| `frame_release_need_effect_state` | `0x2EB40` | 92 |
| `frame_create_need_effect_state_node` | `0x2F3D0` | 48 |

The published `frame_spawn_need_effect` installs the removal and handoff
callbacks and invokes the state constructor. The published interaction family
uses the same state kind, object and three attachment records. These callers
establish the path; no execution or gameplay test is claimed.

The pool-node allocator requests exactly 256 bytes from the existing intrusive
pool functions. Its active-list access covers the head and tail at
`0x03005868`; that head is already accessed as `g_frame_pending_action_head`
elsewhere. The new list name describes this caller's role, not an exclusive
storage type. The free-list head is at `0x03001E34`. A separate 256-byte access
view retains unknown fields and generic callback pointers rather than expanding
the existing partial shared state layout into a speculative universal type.
The constructor's raw store and 36-byte descriptor index preserve the complete
incoming kind word. Its former byte parameter declaration is therefore refined
to a word; the published 424-byte spawn caller still matches with its actual
negative control.

Construction clears the object pointer, byte `+0x63`, optional byte and parameter,
the 48-byte and 40-byte work ranges, four retained words and a byte at `+0xDC`.
It copies descriptor bytes `+0x20` through `+0x22` to state bytes `+0x5D`, `+0x60`
and `+0x61`. The seven callback slots at state `+0xE4` through `+0xFC` receive
descriptor words in the observed order `+0x1C`, `+4`, `+8`, `+0x0C`, `+0x10`,
`+0x14`, `+0x18`. Finally, it clears the same three 24-byte attachment records
used by the interaction/status sources. Their signatures and remaining fields
stay provisional. No descriptor kind bound or failure handling is invented.

The constructor uses two short `r0` address locals for serialized callback reads;
no constrained value survives an external call. The table, kind and record offset
use ordinary compiler allocation. The final descriptor cursor consumes the offset
only after earlier slots have been copied. These are C address calculations and
stores; no original instruction body or output transformation is embedded.

The handoff copies state words `+0xD4`, `+0xD8`, `+0xCC`, `+0xD0` into object
words `+0x9C` through `+0xA8`. Its local volatile object access view preserves
four observed reads of the state pointer between stores. This qualifier describes
the required access sequence, not a claim about the original typedef, asynchronous
hardware or an established non-aliasing invariant. The advancing byte cursor is a
semantic inline helper. The word meanings remain neutral.

Removal checks object byte `+0x82` (the existing provisional `mode` field), calls
the unconverted registration-removal function when it equals one, then reloads
the state pointer before releasing it. Release sends an auxiliary object at
state `+0x58` to state one, detaches each non-null actor in the three records,
repairs the active-list tail when needed and returns the node to the pool.
The registration function at `0x3B4F0` remains unconverted and its wider context
is uncertain. Reset clears the phase, object state, two byte arrays and flags.
The enabled predicate excludes subtype 141 in world nine and otherwise tests
the accepted world exclusion helper and state bytes `+0x62`/`+0x63`.

Every new public source matches the complete linked extent. Each real source
mutation fails: removal mode, handoff word, reset range length, subtype guard,
constructor work length, attachment loop count and pool allocation size. The
424-byte spawn and all seven interaction sources were freshly verified against
the refined header, with their actual controls. Failed contracts, ordinary field
views, cursor variants and raw expected/actual bytes remain in ignored local
`reports/agents/display_audio/interaction/`; accepted-only metadata is
`need-effect-lifecycle-ready.json`. The update, commit and larger tick functions
remain unconverted next targets. Whole-ROM equality is a separate integration
claim made by the full build gate.
