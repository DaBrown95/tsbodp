# Actor route-search support

The connected support path reconstructs 11 C functions and 908 bytes. Every
complete linked extent matches the fixed reference, including literal pools and
alignment. Each real source mutation is rejected. The central search routine at
`0x3BCF4` (720 bytes) and reverse path extraction at `0x3C08C` (76 bytes) remain
unconverted; these helper matches do not establish a reconstructed pathfinder or
runtime behaviour.

| ROM offset | Function | Verified bytes |
| --- | --- | ---: |
| `0x24D18` | `frame_pool_initialize` | 56 |
| `0x24E04` | `frame_pool_count` | 20 |
| `0x3C0EC` | `frame_search_release_node` | 52 |
| `0x3C120` | `frame_search_append` | 76 |
| `0x3C16C` | `frame_search_score` | 64 |
| `0x3C1AC` | `frame_search_take_minimum` | 108 |
| `0x3C218` | `frame_search_find` | 60 |
| `0x3C254` | `frame_search_find_any` | 68 |
| `0x3C298` | `frame_search_remove_cell` | 104 |
| `0x3C300` | `frame_search_cell_cost` | 68 |
| `0x3C344` | `frame_search_build_path` | 232 |

## Static layout and connection evidence

The central search calls these queue, score, lookup, cost and parent-chain
helpers. Two queue views at `0x03007310` have first and last node pointers;
free-list heads at `0x03007320` and backing-buffer pointers at `0x03007328` are
two-element arrays. The last array is retained explicitly in the header because
the central setup accesses it; the matching helpers do not use it. Queue indices
come from parameters or stored node bytes. Their observed two-queue use does not
prove arbitrary indices safe.

A node is 24 bytes: intrusive next/previous pointers precede a 16-byte copied
record. Allocation requests exactly 24 bytes, append copies all four payload
words, and minimum extraction copies them back. The record has the following
partial view:

| Record offset | View | Evidence |
| --- | --- | --- |
| `+0` | packed cell word | Lookup compares its low halfword; path construction copies all four bytes. |
| `+4` | packed parent word | Used as another cell lookup key and tested byte by byte. |
| `+8` | cost byte | Written by scoring. |
| `+9` | unknown byte | Preserved by record copies. |
| `+0xA` | heuristic halfword | Written as the sum of two absolute coordinate differences. |
| `+0xC` | priority byte | Written as heuristic plus full input cost, then narrowed; minimum selection compares this byte. |
| `+0xD` | queue byte | Written at insertion and used to select the owner queue at release. |
| `+0xE..0xF` | unknown bytes | Preserved by record copies. |

Names are provisional. The low two cell bytes are treated as x/y by comparisons
and distance calculation; the upper halfword remains unspecified. Scoring reads
target bytes at global search state `+4/+5` and applies signed-byte coordinate
differences before the absolute values. The existing four-byte unknown area was
refined to those two bytes and an unknown halfword without changing its extent
or later offsets. The central search stores the complete target word there;
that does not establish the upper halfword's meaning.

Minimum extraction chooses the first strictly smallest priority in list order,
updates the last pointer when removing the tail, and releases through the
accepted generic intrusive-pool routine. Its original code reads the first
node's next pointer before testing the first node for null. The matching C
preserves that ordering; callers must supply a nonempty queue. Pool counting
accepts an address containing the first link and follows next pointers until
zero. Pool initialization clears `count * stride` bytes and pushes each stride
into a free list. These are ordinary intrusive-node views, with explicit casts
to the existing generic pool prefix.

Cell cost calls the matching occupancy and terrain queries. It returns 100 if
occupancy has any bit in `0xD`, occupancy has bit `0x10`, or terrain lacks bit
`2`; otherwise it returns 1. The two occupancy tests remain separate source
branches to reproduce the original control flow. No specific obstacle or
terrain class name is established.

The path builder follows parent cells through both queues and writes complete
cell words into the existing 100-word path array. It compresses repeated x or y
coordinates along a parent chain. A parent with either low byte zero terminates
the traversal. An unresolved parent ends the loop without incrementing the
stored count for that last write. The `following` node retains its value between
iterations exactly as the original does. No new bounds check, cycle guard or
sentinel interpretation has been added; valid chain lengths, the meaning of
zero-axis coordinates and the caller's preconditions remain uncertain. The
builder stores an 8-bit count and returns whether that count is nonzero.

## Compiler and verification evidence

All eleven use the pinned default compiler. The lookup functions each retain a
semantic unsigned-word `r1` binding for a widened halfword and its explicit
mask. Removing those lifetimes changes the output. Cell removal needs two
unsigned comparison intermediates bound to `r1` and `r0`; the input, loaded
halfwords, key and mask use ordinary C after minimizing an initially larger set
of constraints. These bindings constrain C values, with no instruction assembly
or original byte bodies. The two lookup sources contain only an alignment
assembly directive to preserve their original two zero tail bytes.

The path builder's final return is expressed with a label to preserve the
original literal-pool placement and branches. The ordinary target-field view
lets scoring match without register constraints. Header refinement also leaves
`frame_find_actor_route` (292 bytes) and `frame_grid_search_status` (20 bytes)
exact, with their existing real mutations rejected.

Mutations change allocation size, release return value, the strict priority
comparison, stored cost, lookup mask, queue bound, removal mask, blocked cost,
pool clear value, initial count and the path-builder continuation condition.
Ten controls differ by one or two compared bytes; the scoring mutation changes
54 bytes because it also changes register scheduling. Both affected consumer
controls reject. Complete positive and changed-source bytes, compiler/linker
commands, hashes and source snapshots remain in the ignored local report tree
under `path-search-support-canonical/`; the integration manifest is
`actor-search-support-batch-manifest.json`. Useful failed natural-C and compiler
lifetime trials remain alongside those proofs.

The next coherent targets are the 720-byte central search, its 76-byte reverse
path extraction, queue-buffer setup dependencies, and the 356-byte actor target
cell selector at `0x3B75C`. The latter remains a separate failed candidate. Static
CFG closure, a matching helper and a byte-identical full-ROM build are different
claims from execution or gameplay evidence.
