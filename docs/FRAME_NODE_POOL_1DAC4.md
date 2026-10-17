# Unrooted node-pool lifecycle

Three adjacent routines reproduce 92 complete extent bytes:

| Routine | ROM offset | Instructions | Literals | Full span |
| --- | ---: | ---: | ---: | ---: |
| Initialize | `0x1DAC4` | 40 | 4 | 44 |
| Shut down | `0x1DAF0` | 24 | 4 | 28 |
| Allocate | `0x1DB0C` | 16 | 4 | 20 |

They share a twelve-byte state at `0x03001B88`: backing pointer at zero,
active head at four and free head at eight. The existing list helpers access
only the first head word. An explicit union preserves their eight-byte active
list view, whose unused last member overlaps the separate free head. The free
head itself is one word, not another complete eight-byte list.

Initialization clears the state, allocates 4,608 bytes and builds 128 nodes
with stride 36. Allocation passes the free and active heads to the existing
pool provider, which returns null when empty; otherwise it pops a free node,
clears its 36 bytes, links it into the active head and returns it. Shutdown
unconditionally frees the backing and clears words in order zero, eight, four.
It neither traverses active nodes nor calls a destructor.

Only each node's first two link pointers have identified roles. Bytes eight
through thirty-five have no established payload type; the generic provider's
`FrameObject *` prefix view does not establish complete actor backing.
Initialization requires successful allocation, and shutdown requires a live
allocation: the native code adds no allocation-failure or null-free guard.
Reinitialization, outstanding-node and later-writer domains remain open.

Normal and strict compiler output and changed-source controls are checked
against each complete span, including all three literal words. Actual new
source definitions and their shared layout and callable types receive separate
checks. These establish matching source and consistent project interfaces;
they add no execution observations.

No indexed incoming call or canonical ROM pointer establishes a caller for
these entries. The chosen no-argument interfaces and void initialization and
shutdown results remain provisional. Their common state connects the three
routines; proximity to attachment jobs 42/94 establishes no gameplay identity.
The three following `BX LR`/zero words at `0x1DB20`, `0x1DB24` and `0x1DB28`
remain unresolved and outside this 92-byte ownership claim.
