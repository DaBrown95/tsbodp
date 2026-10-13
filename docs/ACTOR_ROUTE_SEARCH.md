# Actor route-search support

The connected route-search path reconstructs 17 C functions and 2,288 bytes:
11 support helpers, the central 720-byte search, two 100-byte buffer setup
and reset functions, the 76-byte reverse path extractor, and two connected
target-route and interaction consumers. Every complete
linked extent matches the fixed reference,
including literal pools and alignment. Each real source mutation is rejected.
Neither these matches nor the full-ROM equality gate establish runtime behaviour.

| ROM offset | Function | Verified bytes |
| --- | --- | ---: |
| `0x3BCF4` | `frame_grid_search` | 720 |
| `0x3BFC4` | `frame_search_initialize_buffers` | 100 |
| `0x3C028` | `frame_search_reset` | 100 |
| `0x3C08C` | `frame_copy_grid_path` | 76 |
| `0x3BAC0` | `frame_route_attachment_to_target` | 104 |
| `0x16C68` | `frame_interaction_step_16c68` | 280 |
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
the central search and both buffer helpers access it. Queue indices
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

All fifteen use the pinned default compiler. The lookup functions each retain a
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

The next coherent targets are buffer lifetime and release dependencies and
the 356-byte actor target cell selector at `0x3B75C`. The latter remains a separate failed candidate. Static
CFG closure, a matching helper and a byte-identical full-ROM build are different
claims from execution or gameplay evidence.

## Central search and full-word cost limit

The matching 720-byte search initializes each queue's supplied backing buffer
as 300 nodes with a 24-byte stride. It clears the path array and sets the context,
saved target word and status. A matching low-halfword start and target produces
one path entry and return value 2. A target cost above 99 produces status 3 and
return value 0. Otherwise the starting record enters queue zero with cost zero.

The main loop selects the minimum-priority record from queue zero, then checks
its cell against the target and its byte cost against the supplied limit. Four
four-byte direction records at `0x0807F420` provide the two byte offsets added
to the current cell. The two other bytes in each record remain unspecified.
New costs are narrowed to a byte before scoring. A neighbor matching the current
parent is skipped. An existing entry with an equal or lower priority is kept;
a more expensive entry is removed. Entries with costs at most 99 enter queue
zero, others enter queue one, and the processed current record enters queue one.
A failed neighbor insertion sets status 2 but still proceeds through the current
record's queue-one handoff, exactly as the original branches do.

The loop cap is 1,000 iterations. Exceeding it returns zero immediately, without
forcing a new status or path count. The status can otherwise become 1, 2 or 3
through cost, allocation or path-construction branches; these values are not
claimed to form a complete exclusive gameplay classification. Byte cost and
priority wrapping, queue-buffer size guarantees and input-cell upper halfwords
remain unresolved contracts. Record bytes without observed assignments remain
explicitly unknown; the source preserves the original partial initialization.

Return value 1 identifies the found branch and zero its other completion paths.
Only mode 1 requests path construction. A found result uses the current cell;
otherwise status 2 may request a chain beginning at its parent. A zero path-builder
result forces status 1 and return zero. The count is written by the same-cell
case or path builder; the initial reset clears path words without resetting that
count. Reverse extraction now matches separately; its caller buffer-capacity
guarantees remain uncertain.

The fourth argument is an unsigned word. The original stores all of `r3` and
compares its full value against a zero-extended cost byte; it does not narrow
that argument. The fifth argument is narrowed to a byte. The existing actor
route caller supplies an already loaded byte limit and remains exact after the
canonical prototype refinement. The saved target is now a four-byte union with
word and byte-coordinate views, preserving every following global offset. A
local working-record union exposes typed byte/halfword/word cell views and the
existing copied-record member; calls pass the latter directly rather than
casting between unrelated record structures.

The central source retains seven minimized C register constraints: the clear
value (`r1`), saved comparison mask (`r7`), loaded current key (`r0`), target
comparison result (`r0`), direction-record pointer (`r1`), and two parent-key
comparison values (`r1`/`r0`). Their source scopes separate the current key and
later result lifetimes. The ordinary queue pointer, working mask, state pointer,
status pointer, table base and first comparison value need no constraints after
minimization. A local direction delta is evaluated inside the coordinate
assignment to retain its original load order. The clear-value statement
expression constrains only its C argument value. There is no instruction assembly
in this function.

The 1,000-to-996 iteration-cap mutation changes one compared byte and is rejected.
An earlier 1,000-to-1,001 control and every useful failed type/lifetime trial are
also retained. The final canonical proof covers 24 affected functions spanning
2,772 bytes, including the new search, all support helpers, existing route/grid
consumers and the connected pending effect-point projector. All full extents
match and all real source controls fail. Its local receipt is
`path-central-canonical/`; ready metadata is
`actor-central-search-batch-manifest.json`. Runtime and gameplay evidence remain
unclaimed.


## Buffer setup and reset

The initializer at `0x3BFC4` requests two 7,200-byte zeroed buffers through
the accepted heap allocator. Each buffer is stored before its 300 nodes are
initialized with a 24-byte stride. The returned free-list head is published at
the corresponding index, then both links in that queue are cleared. Only the
two low target-coordinate bytes are reset afterward; the saved target's upper
halfword and other search-state fields retain their prior values. Allocation
failure handling and ownership of the two buffers remain unresolved contracts.

The reset function at `0x3C028` reinitializes the existing buffers with the same
node count and stride, publishes their free-list heads, and clears both queues.
It also zeros the low target-coordinate bytes and the 400-byte path array. It
does not clear the stored path count, status or context. This distinction is
observed in the complete instruction extents and preserved in the matching C.

Both functions use ordinary C without register constraints or assembly. The
initializer's 7,200-to-7,168 allocation-size control and the reset's
300-to-298 node-count control each change one compared byte and are rejected.
Their raw comparisons and source snapshots are included in the same canonical
receipt as the search and affected callers. No buffer-management runtime test
is claimed.

## Reverse path extraction

The 76-byte extractor at `0x3C08C` reads the stored byte count and walks the
100-word saved-cell array backward. Each complete cell word is passed to the
matching grid-to-point helper, then its two-word result is copied into the next
output point. An empty count leaves the output untouched. The function returns
one in both cases; the second full-word argument is unused. The connected
route caller supplies 30 there, but the extractor performs no capacity check.
The relationship between the 100-cell storage, the byte count and that caller's
output capacity remains an unresolved contract. Unknown cell upper bits are
preserved rather than assigned a new meaning.

The source uses ordinary C with no fixed register bindings. Its inline helper
forms the saved-cell address from a byte offset and the cell-array address;
that explicit operand order reproduces the original load scheduling. A
per-function `-fno-gcse` option prevents a redundant cached stack address that
otherwise enlarges the function. This is a compiler constraint supported by
the exact comparison, not proof of the historical compiler options. The only
assembly is an alignment directive for the original zero tail bytes.

Changing the byte-offset decrement from four to eight changes one compared byte
and is rejected. The existing 292-byte route caller remains exact and its
30-to-29 argument control also changes one byte and is rejected. Complete
positive and negative bytes, source and header snapshots, commands and pinned
toolchain checks remain in `path-reverse-canonical/`; the ready manifest is
`actor-reverse-path-batch-manifest.json`. No execution or gameplay test is claimed.


## Target-route and interaction consumers

The 104-byte function at `0x3BAC0` converts its attachment record's actor
position to integer coordinates and then a packed cell. It invokes the still
unconverted 356-byte target selector at `0x3B75C` with the record's actor,
owner's object, the packed cell and restricted-axis flag one. A nonzero byte
result converts that cell back to a fixed-point position, requests mode-four
routing with the record's status word, and requests animation six. The initial
projection result, cell-to-point result and route-start result are ignored in
the original. Failure of the target selector skips both route and animation
requests. The remaining validity and initialization preconditions are unknown.

The 280-byte function at `0x16C68` uses the same 24-byte attachment record,
reinterpreting its word at `+8` as a phase. A running byte equal to one forces
phase one. Phase zero copies the owner's direction to the actor, requests
animation 50, stores a 90-frame timer at actor `+0x58`, commits owner mode one,
and hands off spatial bounds according to direction three/five. Phase 41
waits for actor flag `0x400000`, clears pending animation and moves to phase 43.
Phase 43 adjusts need kind 22 using definition byte `+0x23` and tests the
matching need/timer helper with kind four. A zero narrowed result selects phase
one. Phase one, reached either directly or by the post-switch check, invokes
the still unconverted 284-byte neighbor producer at `0x3B640`, projects its
cell, restores actor fixed-point position, requests animation one, commits
owner mode zero and restores the matching resource projection callback at
actor `+0x98`. The neighbor call's third full-word argument is the actor address;
the inspected callee does not consume it. Both neighbor and projection results
are ignored, so no new failure behavior is invented. Return values are one
while continuing and two on this completion path. Unknown phases retain their
phase and return one.

The address-derived interaction name deliberately leaves its specific
effect-definition role unresolved. No pointer-table entry for this function
was identified by the bounded aligned/un-aligned word scan; its game reachability
is not claimed. Both sources use ordinary C, without register constraints or
assembly. They retain explicit calls into the two unmatched producer/selector
regions. A restricted-axis one-to-zero mutation changes 33 compared bytes;
phase 43-to-44 changes one. Both controls reject. Complete positive/control
bytes, source/header snapshots and toolchain checks are retained in
`actor-target-consumers-canonical/`; ready metadata is
`actor-target-consumers-batch-manifest.json`. These matches do not claim
runtime or gameplay validation.
