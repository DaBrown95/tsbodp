# Actor route-search support

The connected route-search path reconstructs 106 C functions and 13,708 bytes:
11 support helpers, the central 720-byte search, two 100-byte buffer setup
and reset functions, the 76-byte reverse path extractor, and two connected
target-route and interaction consumers plus their eight-function job lifecycle,
and six further variant/job-73 and shared value/random functions, followed by
the nine-function variant controller and parameter-indicator closure, and its
three-function random refill/seed/reader dependency, its adjoining
attachment-neighbor producer, and five allocation, seed-coordination and
secondary-reader functions, followed by six bounded-output, signed-offset and
threshold APIs, and the secondary threshold's optional need-effect/cue consumer
plus its five parameter and retained-effect producers, parameter consumer and
two attachment-job controllers and five connected selection/setup/dispatch/capacity callbacks,
followed by six mode-two selection functions, a three-function optional activity path,
and fourteen connected completion, parameter-job and choice functions, followed by
five choice-list setup, filtering, clock classification and refresh helpers,
and eight connected choice application, completion and value readers.
Every complete
linked extent matches the fixed reference,
including literal pools and alignment. Each real source mutation is rejected.
Neither these matches nor the full-ROM equality gate establish runtime behaviour.

| ROM offset | Function | Verified bytes |
| --- | --- | ---: |
| `0x3B640` | `frame_find_attachment_neighbor` | 284 |
| `0x351B0` | `frame_random_refill` | 348 |
| `0x3530C` | `frame_initialize_random_buffer` | 28 |
| `0x35328` | `frame_refresh_random_seed` | 124 |
| `0x353A4` | `frame_set_random_seed` | 52 |
| `0x35404` | `frame_random_secondary_range` | 40 |
| `0x3542C` | `frame_random_bounded` | 36 |
| `0x35450` | `game_random_inclusive` | 36 |
| `0x35474` | `frame_random_signed_offset` | 44 |
| `0x354A0` | `frame_random_secondary_signed_offset` | 44 |
| `0x354CC` | `frame_random_chance` | 44 |
| `0x354F8` | `frame_random_secondary_chance` | 44 |
| `0x2E688` | `frame_need_effect_try_optional` | 104 |
| `0x2E6F0` | `frame_need_effect_accumulate_optional` | 80 |
| `0x2E740` | `frame_need_effect_try_actor_effect` | 144 |
| `0x2EEB8` | `frame_need_effect_set_optional_one` | 56 |
| `0x2EEF0` | `frame_need_effect_set_optional_two` | 48 |
| `0x2EF20` | `frame_need_effect_begin_optional_three` | 92 |
| `0x2EF7C` | `frame_need_effect_play_optional_cue` | 508 |
| `0x2E7D0` | `frame_need_effect_consume_optional` | 184 |
| `0x18228` | `frame_step_optional_attachment_job` | 172 |
| `0x182D4` | `frame_step_optional_animation_attachment_job` | 304 |
| `0x2F178` | `frame_need_effect_optional_one_ready` | 36 |
| `0x18430` | `frame_select_optional_attachment_kind` | 32 |
| `0x18458` | `frame_begin_optional_attachment_job` | 72 |
| `0x184A0` | `frame_dispatch_optional_attachment_job` | 44 |
| `0x2F348` | `frame_check_optional_attachment_capacity` | 76 |
| `0x2F19C` | `frame_need_effect_optional_two_ready` | 36 |
| `0x1A38C` | `frame_select_optional_attachment_kinds_1a38c` | 40 |
| `0x28764` | `frame_select_optional_attachment_kinds_28764` | 116 |
| `0x35C3C` | `frame_select_optional_attachment_kinds_35c3c` | 92 |
| `0x3A994` | `frame_select_optional_attachment_kinds_3a994` | 56 |
| `0x46200` | `frame_select_optional_attachment_kinds_46200` | 56 |
| `0x2F1C0` | `frame_need_effect_try_reset_timer` | 76 |
| `0x43490` | `frame_step_optional_activity_attachment_job` | 800 |
| `0x438CC` | `frame_dispatch_optional_activity_attachment_job` | 216 |
| `0x2F240` | `frame_need_effect_consume_optional_two` | 56 |
| `0x2F278` | `frame_need_effect_consume_optional_three` | 56 |
| `0x43348` | `frame_step_optional_attachment_kind_12` | 156 |
| `0x433E4` | `frame_step_optional_attachment_kind_45` | 172 |
| `0x439AC` | `frame_step_optional_attachment_kind_22` | 128 |
| `0x2F2B0` | `frame_need_effect_step_parameter` | 92 |
| `0x2F30C` | `frame_need_effect_optional_percentage` | 60 |
| `0x46374` | `frame_step_optional_parameter_attachment_job` | 296 |
| `0x462CC` | `frame_step_optional_attachment_kind_7` | 168 |
| `0x464C8` | `frame_select_optional_parameter_attachment_kind` | 36 |
| `0x464EC` | `frame_check_optional_parameter_attachment_kind` | 40 |
| `0x46514` | `frame_begin_optional_parameter_attachment_job` | 72 |
| `0x4655C` | `frame_dispatch_optional_parameter_attachment_job` | 44 |
| `0x43B30` | `frame_step_optional_choice_attachment_job` | 800 |
| `0x43E50` | `frame_optional_choice_begin` | 92 |
| `0x43EAC` | `frame_optional_choice_open_secondary` | 92 |
| `0x43F08` | `frame_optional_choice_build_available` | 148 |
| `0x4423C` | `frame_optional_choice_refresh` | 32 |
| `0x2CCA8` | `frame_optional_choice_classify` | 232 |
| `0x44020` | `frame_optional_choice_apply_page` | 244 |
| `0x44114` | `frame_optional_choice_install_value` | 120 |
| `0x4418C` | `frame_optional_choice_apply_special` | 176 |
| `0x4425C` | `frame_optional_choice_apply` | 104 |
| `0x443B0` | `frame_optional_choice_apply_failure` | 44 |
| `0x2C720` | `frame_optional_choice_complete` | 48 |
| `0x1BC68` | `frame_read_game_value` | 12 |
| `0x36064` | `display_menu_read_relation_average` | 8 |
| `0x35524` | `frame_seed_random_words` | 56 |
| `0x3555C` | `frame_next_random_word` | 80 |
| `0x355AC` | `frame_next_random_secondary_word` | 88 |
| `0x3CB14` | `frame_step_variant_attachment_job` | 1016 |
| `0x3D00C` | `frame_dispatch_variant_attachment_job` | 24 |
| `0x3D02C` | `frame_update_attachment_parameter` | 188 |
| `0x3D200` | `frame_read_parameter_percentage` | 20 |
| `0x2B9D8` | `frame_clear_attachment_need_countdown` | 16 |
| `0x1A660` | `frame_create_attachment_parameter_indicator` | 156 |
| `0x1A6FC` | `frame_complete_attachment_parameter_indicator` | 112 |
| `0x1A76C` | `frame_set_attachment_parameter_indicator` | 64 |
| `0x1A7AC` | `frame_attachment_parameter_indicator_tick` | 28 |
| `0x3CF84` | `frame_begin_variant_attachment_job` | 136 |
| `0x3D3D4` | `frame_begin_attachment_job_73` | 64 |
| `0x3D214` | `frame_step_attachment_job_73` | 388 |
| `0x3D414` | `frame_dispatch_attachment_job_73` | 64 |
| `0x2F20C` | `frame_gate_attachment_game_value` | 52 |
| `0x353D8` | `frame_random_range` | 44 |
| `0x3BCF4` | `frame_grid_search` | 720 |
| `0x3BFC4` | `frame_search_initialize_buffers` | 100 |
| `0x3C028` | `frame_search_reset` | 100 |
| `0x3C08C` | `frame_copy_grid_path` | 76 |
| `0x3BAC0` | `frame_route_attachment_to_target` | 104 |
| `0x16C68` | `frame_interaction_step_16c68` | 280 |
| `0x16918` | `frame_begin_target_attachment_job` | 56 |
| `0x16E04` | `frame_dispatch_attachment_job_49` | 32 |
| `0x167B8` | `frame_step_attachment_job_7` | 292 |
| `0x16950` | `frame_dispatch_attachment_job_7` | 32 |
| `0x18C8` | `frame_direction_to_need_effect_center` | 116 |
| `0x2F394` | `frame_adjust_attachment_need` | 60 |
| `0x16DBC` | `frame_begin_attachment_route_4` | 72 |
| `0x16E3C` | `frame_begin_attachment_route_3` | 72 |
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

The address-derived interaction name preserves uncertainty about its gameplay
role. Its matching dispatcher at `0x16E04` tests job kind 49 before calling it;
that dispatcher is stored in observed effect-definition rows 56 and 58. No
direct pointer-table entry for the step itself was identified. These indirect
connections are static evidence; runtime reachability remains untested. Both sources use ordinary C, without register constraints or
assembly. They retain explicit calls into the two unmatched producer/selector
regions. A restricted-axis one-to-zero mutation changes 33 compared bytes;
phase 43-to-44 changes one. Both controls reject. Complete positive/control
bytes, source/header snapshots and toolchain checks are retained in
`actor-target-consumers-canonical/`; ready metadata is
`actor-target-consumers-batch-manifest.json`. These matches do not claim
runtime or gameplay validation.


## Attachment-job initialization, dispatch and timed progression

The allocator's 24-byte record has an actor pointer at zero, an unsigned kind
word at four, the phase/timer word at eight, a running byte at twelve, and a
routing status word at sixteen. The kind label replaces `unknown04` without
changing its type or any offset: matching initializers store their entire third
argument there, and matching dispatchers compare the whole word with seven or
49. Allocation still clears it to zero. Other record bytes keep their prior
unknown views.

The 56-byte initializer at `0x16918` allocates a record, stores that full-word
kind, invokes the matching target-route requester and requests animation six.
It returns zero only if allocation failed; the requester's own target/route
failures are not propagated. The 32-byte dispatcher at `0x16950` finds the
actor's record and invokes the 292-byte timed job only when kind equals seven.
The 32-byte dispatcher at `0x16E04` similarly calls the already matching
`0x16C68` step only for kind 49. Both lookup results are dereferenced without a
null check in the original; the source retains that unresolved caller contract.
The two 72-byte initializers at `0x16DBC` and `0x16E3C` allocate a record, store
its kind, obtain owner attachment zero, request route mode four or three with
that record's status word, and request animation six. They also return one
regardless of attachment/route helper results once allocation succeeds.

The job-seven step has phases zero, three and one. A running byte equal to one
forces phase one. Phase zero points the actor toward the owner's projected
center, requests animation eight, chooses phase three and writes halfword 150
at actor `+0x5E`. Owner kinds 29/22 commit mode one and request cue 53/47.
The global option byte at `+0x20` chooses cue 133/132. Owner kinds 20/25 retain
cue 43/62's full-word result at owner `+0xE0`. Phase three applies a world-selected
need adjustment using definition byte `+0x23`; decrementing the actor halfword
through `0xFFFF` selects phase one. The change is handled on a later call rather
than by falling through immediately. Phase one commits mode two for kinds 29/22,
stops the retained sample for kinds 20/25 and requests animation one. Returns
are one while continuing and two for the phase-one completion. Unknown phases
retain their value and return one. Cue numbers and kind branches are observed;
the original gameplay meanings are not assigned.

The 116-byte direction helper projects owner point pairs at `+0xD4` and `+0xCC`,
takes their signed midpoint with truncation toward zero, subtracts the actor's
integer position and calls the matching by-value direction helper. Projection
results are ignored. A bounded work view exposes those point pairs and the
sample word at `+0xE0`; their complete allocation, coordinate units and bounds
meaning remain provisional. The 60-byte need helper tests the matching world
exclusion predicate on `0x03004334` and selects need adjustment zero or 56.
Its second argument is retained as a full word, then narrowed to a byte in each
branch before the existing need-adjustment call.

Observed 36-byte effect-definition records beginning at `0x08062E7C` store the
`0x16918` initializer at slot `+0xC` and `0x16950` dispatcher at `+0x10` for rows
18, 20 through 30, 32 through 34, 83, 101, 136 and 137. Rows 56 and 58 store
`0x16DBC` and `0x16E04` in the same slots. This establishes a static indirect
handoff into both job paths and a connection to the existing effect lifecycle;
it does not establish gameplay execution. The mode-three initializer has no
pointer reference in the bounded word scan, so its reachability stays uncertain.
The raw pointer offsets, row arithmetic and complete original comparisons are
retained locally rather than publishing table contents.

All eight new extents match under the existing agbcc profile. The need helper's
only assembly is its explicit zero tail alignment; every other new function
uses ordinary C without register constraints or assembly. Animation requests,
job kinds, the world-selected need adjustment, timer, midpoint division and
route-mode mutations provide real changed-source controls, and each rejects. The midpoint divisor-two-to-four
control changes 101 bytes; the other seven controls change one byte each.
The label refinement revalidation covers 65 affected functions spanning 9,652
bytes, including the three previously published record writers/dispatchers.
All full positive extents match and every actual source control rejects.
The snapshot and comparison receipt is `actor-attachment-jobs-canonical/`;
ready metadata is `actor-attachment-jobs-batch-manifest.json`. The unmatched
284-byte neighbor producer and 356-byte target selector remain explicit ROM
regions and receive no C coverage. No runtime test is claimed.


## Variant initialization and attachment job 73

Six further matching functions add 748 bytes. Effect-definition rows 35 and 36
store the job-73 initializer and dispatcher in slots `+0xC/+0x10`. The direct
388-byte step is called by that dispatcher rather than appearing as a word
pointer in the bounded ROM scan. Rows 10, 46, 47, 48, 94 and 103 store the
variant initializer at `+0xC`; their dispatcher is now matching C, while the configuration callback at
`0x3CF38` remains an explicit unconverted region. The raw aligned
pointer references and row arithmetic are retained in
`dependencies/attachment-job73-definition-slots.json`. These are static
connections, without runtime reachability evidence.

The variant initializer saves owner byte `+0x5E` before record allocation.
It stores the full input kind at record `+4` and selects a 32-byte row at
`0x0807F4C0`. A negative signed attachment byte at row `+0x19` uses the existing
target-route requester. Otherwise it saves the actor's position at owner
`+0x64/+0x68`, obtains the selected attachment from owner object `+0x54`, and
requests route mode five with status flag one and animation six. Its result
reports allocation success; attachment and route results are not propagated.
The table stride and signed byte are established by its loads, multiply shift
and signed comparison. Other row field names in the bounded header reflect
observed accesses in the now matching 1,016-byte controller, and stay
provisional. The initializer's ordinary integer address accumulator retains
that table/stride calculation without register bindings or instruction glue.

The job-73 initializer uses the target-route requester, animation six and actor
word timer `+0x58 = 60`. Its dispatcher dereferences the found record without a
null check, updates direction for phase zero before testing kind, and calls the
step only for full-word kind 73. The lookup precondition and the direction
update for other kinds are retained.

The step uses phases zero, 61, 89, nine and one. Phase zero faces the owner center
and calls the value gate with amount five; success requests animation 58,
commits owner mode one, selects phase 61 and plays cue 54. Failure requests
animation five and phase nine. At phase 61, actor flag `0x400000` applies need
51 using owner-definition byte `+0x23`, commits mode three, requests animation
one and writes timer 60 before selecting phase 89. Phase 89 first calls the
shared need/timer helper, then decrements the actor timer again. This second
decrement is present in the original and is preserved. When it reaches minus
one, the random result from range zero through 100 is compared with up to five
packed two-byte rows at `0x0807F670`. The first strict threshold match supplies
a negated byte amount to the value gate, cue 55, animation 67 and phase nine.
No matched threshold selects phase one. The helper's false low-byte result
also selects one. Phase nine repeats need 51 until the completion flag selects
one and requests animation one. Phase one commits mode two and returns two;
other phases return one. Cue, kind and phase numbers are observed values rather
than assigned gameplay roles.

The 52-byte value gate compares the job actor with the first pointer stored at
`0x030040E0`. Only a match tests signed game-state value `+4` against the full
signed input amount. Insufficient value returns zero; otherwise it calls the
matching clamped game-value adjustment with the negated amount and plays cue
five. Other actors return one without an adjustment. Negative amounts therefore
reach an additive adjustment through the same code. This evidence supports the
bounded game-value name but does not establish the value's original label.

The 44-byte random-range definition closes the previously named external at
`0x353D8`. Equal endpoints return directly without calling the original word
generator at `0x3555C`. Otherwise it masks the result to 15 bits, multiplies it
by the signed inclusive span, shifts right by 15 and adds the first endpoint.
The source adds no endpoint-order or overflow checks. Its underlying generator
and state/refill path remain original ROM code; no distribution or runtime
claim is made.

All six complete extents match under the existing agbcc profile. Three sources
specify only zero tail alignment; none has register constraints or instruction
assembly. Each route, timer, phase, kind, comparison or mask mutation changes
one compared byte and rejects. Thirteen previously accepted random-range
callers were reverified with their own real controls after the new definition
was introduced. Complete bytes, commands and current-header snapshots are in
`actor-attachment-job73-canonical/`; ready metadata is
`actor-attachment-job73-batch-manifest.json`. The variant configuration callback, neighbor producer and target selector
remain unconverted and receive no C coverage.


## Variant attachment controller and parameter indicator

Nine further functions add 1,624 matching C bytes. The 24-byte dispatcher finds
an attachment record and immediately passes it to the 1,016-byte controller;
there is no added null check. The aligned definition-row evidence already
recorded above connects that dispatcher to kinds 10, 46, 47, 48, 94 and 103.
The phase table embedded in the controller maps zero, six, nine, eight and one
to active bodies; other values return the unchanged result one. The unmatched
72-byte configuration selector at `0x3CF38` remains outside source coverage.

At phase zero, kind 47 tests the world exclusion predicate or the primary-actor
value gate with amount 20. A failed gate requests animation five, selects phase
eight and chooses cue 85/86 from the attachment option. A low selected need
instead requests direction four and animation 85 with cue 136/137. Otherwise
the row's optional bounds handoff runs, and a parameter other than seven reads
its current signed high-byte level. A level other than ten creates an indicator
with variant one and faces the owner center. Kinds 47 and 10 face the owner's
reversed direction; other kinds use the center calculation. The controller
requests the row animation, selects phase six, writes actor timer 90 and
commits owner mode three. Variant zero clears owner flag one. Other variants
except three play a non-255 row cue and save its handle at owner `+0xE0`.
The owner's halfword phase counter at `+0x5E` starts at 15.

Phase six uses a post-increment of that halfword: variants zero and three play
the row cue after the previous counter exceeds 28, then clear it. A selected
parameter's signed level is read before computing its fractional percentage,
updating the indicator and advancing the parameter. That row index retains one
local lifetime across those three calls. A selected adjustment need other than
eight uses definition byte `+0x23`. Completion is selected when the level rises
by one; level ten instead decrements the actor word timer and adjusts need 49.
The shared need/timer helper's false low byte selects phase one; kind 103 also
requests animation six and a mode-five route to the saved owner position. A
nonzero row wait-animation byte then overrides that selection with phase nine.
Phase nine waits for actor flag `0x400000`. Phase eight waits for that same flag,
then selects one, requests animation one and clears need countdown `+0x20`.
Phase one requests animation one and commits mode two, marks a retained
indicator state one and clears its pointer, restores owner flag one for kind
94, optionally reinstalls the resource callback and stops the saved sample.
Only this phase returns two; the remaining paths return one.

The 32-byte row keeps the same offsets. Its animation view at `+4` is now a
full word narrowed by the byte animation API. A byte-plus-padding trial produced
incorrect temporary lifetimes in the controller; the word view produced the
complete original extent with ordinary C. This is compiler/type evidence,
not independent proof of a serialized field width. The row's other observed
words are initial code `+8`, timer need `+0xC`, adjustment need `+0x10` and
parameter index `+0x14`; its cue, signed attachment and option bytes occupy
`+0x18..+0x1C`. The stored indicator pointer `+0x58`, saved position `+0x64/+0x68`
and sample handle `+0xE0` remain bounded access views, with unrelated fields
explicit. No units or original gameplay labels are assigned to these states.

The 188-byte parameter updater indexes words at `0x030039E8` and a ten-column
rate table at `0x0807F580`. For initial high-byte values zero through nine,
key bit one for the local input player multiplies the increment by eight.
Otherwise the plain increment is added. A signed high byte read after the
write detects crossing into the next level. The code then stores exactly
`(previous + 1) << 24`, refreshes actor counters, sets local UI word flag
`0x40000` in a 56-byte row at `0x03004130`, creates a completion transient and
plays sequence notification 56. The 20-byte percentage helper extracts the
low 24 bits, multiplies by 100 with word arithmetic and returns the upper byte
of that product. One semantic `r0` value lifetime is required for this leaf's
code generation. It adds no instruction assembly and supplies no runtime
proof. The word-wrap behavior and the separate signed/unsigned high-byte uses
are retained rather than unified into a speculative numeric type.

The 156-byte indicator factory allocates object kind 26 without a new failure
check, retains the owner at object `+0x90`, places it at owner position minus
`0x70000/0x310000`, installs flags `0x100009`, state zero, a variant resource and
palette, the 28-byte state callback and the resource pre-step callback. Its
variant formal is a full word; the actor-id store narrows it. The resource and
palette tables remain explicit at `0x08052DE0` and `0x08052E00`. The setter
computes an 8-bit `100 / (frame_count - 1)` divisor, calls the distinct unsigned
division backend for percentage/divisor, and changes the animation frame only
when it differs from the stored previous frame. The initial promoted operands
use the signed backend at `0x0804CD2C`; the second call uses the unsigned backend
at `0x0804CED8`. Resource validity, nonzero divisors and variant bounds remain
caller preconditions. The completion factory creates transient kind six,
group zero, index three, retaining owner and position, phase three, flags
`0x248A`, height 60, countdown one and offsets five/twenty. The indicator callback
sets flag two in state one and otherwise leaves the object alone.

All nine complete linked extents match under the existing pinned agbcc profile.
Only the percentage value has a semantic register constraint; three leaf
sources contain alignment-only directives. Every actual changed-source control
rejects, including controller timer 90 to 91, parameter level limit nine to
eight and indicator flags/height/divisor changes. The six existing attachment
header consumers remain exact with their own controls after the same-layout
animation refinement. The 128-byte map-registration source correction also
remains exact with its control and adds zero coverage. Positive/control bytes,
commands and current-header snapshots are retained under
`actor-attachment-controller-canonical/`, with ready metadata in
`actor-attachment-controller-batch-manifest.json`. The configuration selector,
target selector, wider generator initialization and
allocation/lookup guarantees remain unresolved. Full-ROM equality and static
callback mapping are separate from runtime behavior, which was not tested.


## Connected random refill, seed and reader

Three dependencies of the accepted inclusive range helper add 484 matching C
bytes: the 348-byte refill at `0x351B0`, the 56-byte seed writer at `0x35524`
and the 80-byte tempered word reader at `0x3555C`. These were reconstructed
from the fixed ROM's loads, stores, control flow and constants; no third-party
implementation body was imported. The 624-word state, 397-word tap, two loops
of 227/396 words, masks `0x80000000/0x7fffffff`, conditional `0x9908b0df` xor
and four tempering operations identify an MT-style generator. This description
is a static algorithm inference, rather than evidence of randomness quality or
runtime use beyond the inspected callers.

The partial IWRAM storage consists of a buffer-address word at `0x03001F10`,
a next-word pointer at `0x03001F14`, signed remaining count at `0x03001F18`,
seed at `0x03001F28` and last-byte destination at `0x03005A0C`. The buffer
address is kept as an ordinary word view, converted at the observed pointer
loads; no volatile qualifier is needed. The matching initializer at `0x3530C`
requests 2,500 bytes, or 625 words. That extra word permits the
second loop's final ahead-pointer read, whose value is overwritten before use.
The state must already have a valid allocation. Allocation failure handling,
initialization ordering and reentrancy are not established by these three
functions, and no new checks are inserted.

The seed writer forces an odd initial seed, writes that word and 623 further
words by repeated multiplication by 69,069 with unsigned word arithmetic. It
sets the remaining count to zero. The refill reseeds from the stored seed only
when the count is below minus one, then sets count 623 and next to the second
word. The reader decrements the signed count; a nonnegative count takes the
next state word, advances the pointer, tempers the word and stores its low byte.
A negative count returns the refill result directly. The refill returns the
first newly twisted and tempered word without updating that byte destination.
This asymmetric side effect is preserved. The signed decrement requires the
observed initialized/counting domain; arbitrary underflowing counts are not
claimed to be portable C inputs.

The refill and seed writer now use ordinary C without register bindings. The
refill's named available/threshold values and comma capture preserve the storage
address lifetime through the optional seed pass. The final twist deliberately
stores before the conditional xor and stores again on the odd-word branch.
The reader retains two semantic value/result register lifetimes, with no
instruction assembly. An ordinary version was preserved at 80 bytes but 13
differing bytes; those constraints are compiler requirements, not runtime
findings. Every positive includes the complete pool and alignment. Controls
change the first refill count 227 to 226, seed multiplier 69,069 to 69,068 and
reader shift 18 to 17; all three reject with one differing byte. Fifteen
previously accepted consumers of the canonical header also remain exact and
reject their existing controls. Raw failures, compiler allocation dumps, source
snapshots and positive/control comparisons remain in ignored local reports;
ready metadata is `frame-random-batch-manifest.json`. Full-ROM validation and
publication remain separate milestone gates; no runtime/gameplay test is
claimed here.


## Attachment-neighbor producer

The accepted interaction callback at `0x16C68` now connects to the 284-byte
neighbor producer at `0x3B640`. It reads the actor attachment position, converts
attachment and actor positions to integer coordinates and cells, and chooses
one of four numeric scan groups from their signed displacement. The group is
doubled and eight consecutive two-byte offsets at `0x0807F3F0` are tried. Only
the actor cell is used as the candidate anchor; the attachment-cell conversion
is retained even though its result is unused. These group numbers and offsets
are not given unproved compass meanings. The largest observed lookup needs the
first fourteen offset pairs; wider table boundaries remain a mapping question.
This base has its own `g_frame_attachment_neighbor_offsets` view, distinct from
the sixteen-byte grid-neighbor table copied from `0x0807F410`.

Each candidate x/y field narrows the byte offset addition to eight bits. The
code performs one lookup for occupancy and, when mask 13 is clear, a second
lookup for terrain. Null lookup results supply zero properties. Terrain bit two
selects the first acceptable candidate. Both queries remain explicit. The
third word argument is unused, and conversion/resource validity requirements
are not strengthened with invented checks. The known interaction caller ignores
the returned success flag before converting its local cell to a point; a valid
neighbor in that caller context remains an unresolved precondition.

Success transfers a full four-byte candidate representation and returns one;
failure returns zero and leaves the output alone. Only the low x/y bytes are
initialized in the candidate. The source uses a four-byte built-in memory copy
for the original word transfer, avoiding an integer interpretation of the
indeterminate upper bytes. Those bytes are deliberately opaque, and no game
meaning or initialized value is claimed for them. The ordinary C source has
no register constraints: reusing the direction variable for the doubled scan
start resolved the previous index/table allocation mismatch. Complete extent,
pool and alignment match, the occupancy mask 13 to 12 control differs by one
byte, and the connected 280-byte interaction consumer remains exact with its
control rejected. Proofs and useful earlier failures remain under ignored
`attachment-neighbor-canonical/` and its predecessor trial directories; ready
metadata is `attachment-neighbor-batch-manifest.json`. No runtime behavior was
tested. The adjoining 356-byte target selector remains unconverted.

## Seed coordination and secondary random stream

Five connected functions add 332 verified C bytes. Their sources use ordinary
C without register bindings or instruction assembly. The initializer stores
the result of canonical `resource_allocate(2500)` in the observed buffer-address
word. This proves the allocation request's size, rather than allocator success
or initialization of every allocated byte. No new failure check is inserted.

The secondary reader uses a cursor at `0x03001F1C` and signed remaining count at
`0x03001F20`. After predecrement, a negative count resets it to 623 and sets the
cursor to the shared buffer's second word. It reads and advances this cursor,
applying the same four tempering operations as the primary reader. It neither
invokes the primary refill nor updates the primary last-byte destination. The
name identifies a separate cursor; it does not claim statistically independent
randomness. Its range wrapper always advances this cursor, including for equal
endpoints, while the primary range returns immediately in that case. Both use
the observed low-fifteen-bit value and signed span/product/right shift. Valid
caller bounds and signed-overflow preconditions remain inferred.

The secondary range extent is 40 bytes at `0x35404`, including its pool and zero
alignment through `0x3542B`. The next function begins with PUSH at `0x3542C`.
An initial 44-byte estimate included four bytes of that next function; the failed
comparison and corrected boundary evidence remain local. The multiplication
operand order `value * span` gives the original allocation; the earlier reversed
expression differed in two bytes. This is a compiler finding, not a different
runtime algorithm.

The seed refresh sets both remaining counts to minus one. It mixes the stored
seed with the established IRQ context's VBlank count and the first input-current
halfword. A zero intermediate seed obtains a primary random word, takes unsigned
remainder by `0x000FFF1F`, and adds one. The original helper at `0x4CF50` uses
unsigned comparisons and subtractions; its Thumb execution symbol is
`__umodsi3` at `0x0804CF51`. The refresh then increments a full-word counter at
`0x03001F24` and combines seed shifted eight, VBlank count shifted six, counter
shifted four, and the input halfword before calling the seed writer. These roles
follow shared IRQ/input views and observed offsets; entropy quality is untested.
The explicit seed setter stores its argument, calls the seed writer, then sets
the primary remaining count to 623 and primary cursor to the second word. It
does not reset the secondary cursor or count.

The buffer's final word remains uncertain. Seed and refill paths write 624 words
at indices 0 through 623. The secondary reset and immediate second-word read
permit 624 reads, at indices 1 through 624, before wrapping again. Index 624 is
inside the observed 625-word allocation, but its initialization and intended
content have not been established. The source preserves the original counter
and allocation; no fabricated writer or default value closes this gap. Allocation
ordering, reader preconditions and runtime behavior remain separate questions.
The matching allocator alias at `0x27864` is the ordinary heap allocator: its
shared first-fit allocation body splits and unlinks blocks without clearing
payload memory. That rules out automatic zeroing by this inspected allocation
path as an explanation for the extra word; it does not establish another writer
or its runtime contents.

All five full extents match. Controls alter allocation size 2,500 to 2,496,
refresh divisor `0xFFF1F` to `0xFFF1E`, seed/secondary remaining 623 to 622, and
range mask `0x7FFF` to `0x3FFF`. Every control rejects; four differ by one byte,
while the changed allocation compiles to 24 bytes with 18 compared differences.
All 27 previously accepted consumers of the shared random header, spanning
6,692 bytes, remain exact and reject their actual controls, including the
1,372-byte transient emitter. Saved source/header bundles, actual preprocessing
dependencies, complete positive/control bytes and useful failures remain under
ignored `secondary-rng-1791885100/`; the integration manifest is
`frame-random-secondary-batch-manifest.json`. This batch supplies compiler and
static mapping evidence without a runtime/gameplay experiment.

## Bounded output and threshold API closure

Three direct reader consumers add 116 verified C bytes and close dependencies
used by actor selection, animation, need effects and audio coordination. Both
bounded-output functions narrow the incoming limit to 16 bits, mask their
respective reader's word with `0x7FFF`, scale by limit plus one using unsigned
word arithmetic, and narrow the result to 16 bits. The primary function keeps
its established unsigned-short return. The secondary function keeps the existing
word-returning `game_random_inclusive` API with explicit narrowing in its body;
that name remains an inferred gameplay label. The latter is a consumer of the
secondary cursor, rather than evidence for statistical independence or valid
initialization of the buffer's extra word.

The threshold predicate at `0x354CC` also narrows its argument to 16 bits, then
returns one when the limit is greater than or equal to the masked sample scaled
by 101 and shifted right 15. This produces an inclusive sample from 0 through
100. It does not establish conventional percentage semantics or distribution
quality; a zero limit can still return one. The formal argument is now declared
once in the guarded random header. Older callers' byte-argument declarations
had obscured this observed width.

Eight of nine already accepted threshold callers match unchanged under the
16-bit formal. The optional need-effect advance explicitly narrows its
parameter-derived expression to a byte before the call, preserving the observed
caller conversion. Omitting that cast with the corrected formal changes three
shift bytes. With the cast, all nine callers and their actual controls pass;
their 3,356 bytes are existing coverage. All 194 existing functions in the
changed header closure, spanning 37,736 bytes, remain exact and reject their
actual source controls. No arbitrary
parameter-domain or runtime claim follows from the corrected prototype.

Both bounded wrappers retain a single scoped r0 binding for the reader's returned
working value; no intervening call crosses that lifetime. Ordinary alternatives
remain at 36 bytes with 14 differing bytes. The threshold predicate is ordinary C
without bindings or instruction assembly. Every complete extent, literal pool
and alignment matches. Controls change the bounded limit addition from one to
two and the threshold multiplier from 101 to 100; each differs by one byte.
Private widened-header comparisons, canonical positives and controls, source
bundles and useful failures are retained under ignored `secondary-rng-1791885100/`;
the integration manifest is `frame-random-api-batch-manifest.json`. Whole-ROM
equality and gameplay behavior remain separate claims.

## Paired signed-offset and secondary threshold functions

Three further direct reader consumers close the adjoining 88-byte offset gap
and the 44-byte secondary threshold wrapper. Each signed-offset function first
narrows its formal argument to unsigned 16 bits, retains that value through the
reader call, then interprets it as a signed 16-bit radius. It scales the masked
low-fifteen-bit sample by twice that radius plus one using unsigned word
multiplication and a logical right shift, subtracts the radius, and narrows the
result to signed 16 bits. The name describes the observed signed output. Valid
radius bounds, intended range and distribution are not established for arbitrary
16-bit inputs. The two functions use the already matched primary and secondary
readers respectively.

The source retains a mutable word-sized radius until after the call, then applies
the signed narrowing. This natural C lifetime matches both complete 44-byte
extents without register constraints. A separately initialized short variable
gave 44 bytes with 20 differences because the compiler fused sign extension
with doubling and kept the original unsigned limit for the final subtraction.
Unsigned word multiplication and final short narrowing preserve the observed
machine arithmetic; the target's signed conversion rules remain part of the
pinned compiler profile.

The secondary threshold wrapper uses the same inclusive 0 through 100 comparison
as the primary predicate and advances the secondary reader. Its mapped direct
caller at `0x2E688` is now reconstructed in the connected optional path below.
No mapped direct caller of either signed-offset function was found
in the inspected inventory, whose coverage is incomplete. The paired reader and
adjacent API structure supply the static subsystem boundary, rather than a claim
that every wrapper is used during gameplay.

All three sources use ordinary C, match their full extents and reject real
controls. Radius scaling two to three produces 48-byte candidates with 22
compared differences; threshold multiplier 101 to 100 differs by one byte.
All 197 existing random-header consumers, spanning 37,852 bytes, remain exact
and reject their actual source controls under the extended header.
Complete raw proofs, the initial type/lifetime failures and source snapshots
remain under ignored `secondary-rng-1791885100/`; ready integration metadata is
`frame-random-paired-batch-manifest.json`. The unresolved extra secondary state
word and runtime behavior remain unchanged questions.

## Optional need-effect and cue handoff

The 104-byte secondary-threshold consumer reuses the published need-effect state
view: kind word `+8`, associated object `+0x54`, enabled byte `+0x62`, parameter
halfword `+0x70` and optional byte `+0x72`. It returns zero when disabled, already
optional, or the secondary threshold does not return one. Its kind indexes
four-byte ROM rows at `0x08064370`; each row's byte `+2` is interpreted as
the threshold here. The connected increment producer below reads the signed
halfword at `+0`. Row count, byte `+3` and arbitrary index safety remain
unestablished.

On success the function sets optional to one and parameter to 25,600, selects a
cue, and examines an object-pointer slot at associated object `+0x90`. A nonnull
slot is passed to the matching state setter with state one and then cleared.
The producers below establish this path's retained actor-effect use of the
selector-specific slot; its broader lifetime remains uncertain. The state
object pointer is loaded again after
the call, preserving the original side-effect ordering. A named unsigned-short
amount before the two stores reproduces their original register scheduling;
the source needs no register binding. Direct constant-store and early-return
alternatives remain locally at 104/11 and 104/62 differences.

The cue helper at `0x2EF7C` selects canonical `audio_play_animation_cue(36)` for
kinds 1 through 8, 43, 44, 45, 49, 89, 104, 106, 107, 108 and 112. It selects
cue 37 for kinds 69, 71, 73, 105, 109, 110, 111, 114 and 115; other kinds do
nothing. Ordinary C switch labels generate the original 115-entry jump table,
including its linked target addresses. The complete extent is 508 bytes through
`0x2F177`; an initial CFG estimate of 506 omitted two zero alignment bytes before
the next PUSH at `0x2F178`. Standalone alignment-only source glue expresses those
bytes separately from the C body. No instruction body or address table is
embedded in the claimed reconstruction.

Both complete extents match. Real controls change amount 25,600 to 25,599 and
cue 36 to 35, producing 51 and one compared byte differences respectively.
The secondary-threshold predicate, optional-advance function, cue player and
object state setter remain exact across 552 existing bytes, with all four
actual source controls rejected. Saved raw table evidence, type/lifetime
trials and canonical source comparisons are in ignored local reports; ready
metadata is `frame-need-optional-batch-manifest.json`. These findings establish
the static cue/optional connection and compiler equality. Trigger rates, object
slot validity and gameplay behavior have not been tested.

## Optional parameter and retained-effect producers

The existing allocator clears optional and parameter, while the existing
424-byte spawn function copies its narrowed optional, parameter and enabled
arguments into the state. A nonzero parameter argument is shifted by eight.
The spawn function's provisionally named initializer at `0x4CCF4` is the
explicit BX-R1 transfer veneer: it dispatches the definition callback rather
than implementing another ordinary C initializer. These static paths do not
establish a default for every retained field or identify every callback writer.

The increment producer at `0x2E6F0` requires enabled and an optional byte other
than one. It changes optional to two, reads the current parameter as signed 16
bits and the ROM row's signed halfword increment, and compares their word-sized
sum with 25,599. A sum above that limit stores 25,600. Otherwise it adds the
increment to the unsigned old parameter and stores the low halfword; no lower
bound is imposed. The same four-byte ROM row supplies the chance byte to the
secondary predicate. Only two aligned references to its exact base were found
in the inspected image. The table remains an explicit original ROM data region,
and no reconstructed writer or guessed count is introduced.

A named table base and separate signed parameter/row reads recover the original
load order. A small word-sized inline addition helper retains the original ADD
operand order without register constraints; direct expressions were one byte
away despite identical arithmetic. The full 80-byte extent matches. Changing
the saturation store from 25,600 to 25,599 gives a 72-byte candidate and 29
compared differences, which the control rejects.

The 144-byte producer at `0x2E740` operates when the actor equals the published
player-pointer view. It tests the primary chance predicate using signed
parameter one plus 15, narrowed to unsigned 16 bits. On success it requests
state one for any old slot object, clears the slot, and stores the return of
`frame_create_actor_effect(owner, 200, 8, 1)` in owner `+0x90`. It chooses cue
153 or 154 from game byte `+0x20` and stores 40 at actor byte `+0x51`, represented
by the existing provisional default-state view. This directly identifies the
retained slot as an actor-effect pointer in this path. The existing attachment
updater also creates actor effects there by optional mode and requests their
teardown when invisible or no longer needed. Allocation failure and stale-slot
behavior are not established by the matching C alone.

The mode-one and mode-two setters store optional one or two and the supplied
parameter halfword, then request state one for a retained effect and clear the
slot. Mode one additionally invokes the matching cue selector. Their formals
use an inferred halfword parameter type; the observed stores discard high bits,
but do not independently prove every original caller's declaration. The
mode-three entry stores optional three and 12,800, searches for one object with
ID five and subtype 41, and invokes that object's need-state callback at `+0xF0`
with its state pointer and two zero words before clearing the retained effect.
The typed callback view preserves the existing transfer through the R3 veneer;
the callback role and its unchecked validity remain provisional.

All five complete extents match and reject real source changes. Besides the
saturation control, cue 153 to 152 and optional-state mutations each differ by
one byte. Both prior optional functions remain exact with their controls under
the refined four-byte row layout; allocator, spawn, attachment updater and
actor-effect creation/tick dependencies also remain exact and reject their
controls. Raw comparisons and failed type/lifetime attempts are retained in
ignored `need-optional-state-followup/`; integration metadata is
`frame-need-optional-state-batch-manifest.json`.

## Optional parameter consumption and attachment jobs

The 184-byte consumer at `0x2E7D0` forms a low-halfword cost from signed parameter
one multiplied by four plus 43. Pressed input mask one for the local player adds
25 to that halfword. The source captures the observed modulo-word arithmetic
with an unsigned conversion before multiplication. It proceeds only when the
optional byte is one and the parameter, interpreted as signed 16 bits, is
strictly greater than the signed 16-bit cost. It subtracts that signed cost from
the unsigned old halfword, stores the low result, adjusts the actor's need 18
by byte `+35` of its 36-byte definition row, updates the indicator with the low
byte of `100 - (signed_parameter >> 8)`, and returns zero. Otherwise it clears
optional and parameter and returns one. Arbitrary parameter ranges, definition
counts and indicator validity remain unestablished; no additional bounds or
allocation-failure branch is introduced.

Separate signed and unsigned views preserve the two original halfword loads.
A named mask result, saved optional pointer and shared zero for the failure
stores reproduce the input operation, pointer setup order and single zero
materialization. These are ordinary C lifetimes. Four temporary register
constraints used while closing the last differences were all removed, with
complete equality retained. Prior 184/8 and 184/5 candidates and the failed
pointer/type variants remain in ignored reports. The complete extent includes
two source-expressed zero alignment bytes after the return.

The 172-byte controller at `0x18228` starts by facing the actor opposite the
associated object's direction. A successful retained-effect attempt moves the
job to phase one; otherwise it creates an indicator in need-state work `+0x58`,
requests animation 45, enters phase five and saves cue 19's sample handle at
`+0xE0`. Phase five calls the matched parameter consumer and observes its low
return byte. A nonzero record byte `+0x0C` also requests phase one. Completion
stops the sample, requests animation one, requests indicator teardown if
present, clears the indicator and returns two; an active job returns one.
These fields use the existing bounded job-work and attachment-record views.
They do not redefine the retained actor-effect pointer at object `+0x90`.

The adjacent 304-byte controller at `0x182D4` calls the secondary optional
predicate, requests animation 58 and enters phase six. An animation-completion
flag starts cue 61, animation one and an actor countdown of 90. Phase 55
decrements that countdown and, at minus one, stops the saved sample, enters
phase 56 and starts animation/cue 21. Phase 56 adjusts need four and finishes
on the same animation flag. Only record byte `+0x0C` equal to one requests its
separate completion path, which stops the saved sample and plays cue 146 or
145 according to the game selector. The signed countdown and selector names
remain provisional. The complete extent ends with two zero alignment bytes
before the distinct entry at `0x18404`; a CFG estimate of 282 bytes omitted
parts of its complete contiguous body and literals. The preceding controller's
94-byte CFG estimate likewise does not cover its 172-byte linked extent.

All three complete extents match as ordinary C without register constraints,
with alignment-only glue kept explicit. Changed cost 43 to 44, animation 45 to
44 and countdown 90 to 91 each produce one differing byte and are rejected.
Canonical comparisons, current header snapshots and failed candidates remain
in ignored `need-optional-state-followup/`; ready metadata is
`frame-need-optional-jobs-batch-manifest.json`. Runtime cancellation, ownership,
sample validity and gameplay effects have not been tested.

## Optional attachment callback selection and capacity

One observed 36-byte definition row at `0x62EA0`, row one relative to the
published table base `0x62E7C`, connects the matching optional jobs. Its pointer
at `+4` selects attachment kind 29 or 45, `+12` begins that attachment job,
`+16` dispatches it, and `+28` checks capacity. The accepted allocator copies
these pointers to need-state `+0xE8`, `+0xF0`, `+0xF4` and `+0xE4`, respectively.
The row's initial callback and its other callbacks remain explicit original
dependencies. This single row does not establish a bound for the whole table.

The 36-byte predicate at `0x2F178` returns one exactly when optional is one and
the parameter halfword, read as signed 16 bits, is nonnegative. The 32-byte
selector at `0x18430` observes the predicate's low byte and writes kind 45 on
success or 29 otherwise. These attachment kinds differ from the definition's
row index. Both functions return words, and the inferred signatures preserve
the caller's observed narrowing rather than assuming a byte return ABI.

The 72-byte setup at `0x18458` requests an attachment record and returns zero
on allocation failure. On success it stores the complete supplied kind word,
reads attachment position zero from the associated object, begins an actor
route with arguments four and one using the record's status word as output,
requests animation six and returns one. A positive success branch retains the
original null-case placement; an equivalent early-return candidate differed
in its branch layout. The 44-byte dispatcher at `0x184A0` obtains the existing
record and sends kind 29 to the animation/countdown job and kind 45 to the
parameter-consumption job. Other kinds return zero. The record lookup has no
null check in the original path, and this replacement introduces none.

The 76-byte capacity callback at `0x2F348` counts nonnull actor pointers in the
three 24-byte records starting at need-state `+0x0C`. It rejects a count greater
than or equal to the byte at state `+0x5D`. The accepted allocator copies that
byte from definition `+0x20`, so its capacity role is supported by both its
producer and this comparison. It also rejects an actor with a nonzero observed
attachment count when state byte `+0x60` is one; otherwise it returns one. The
capacity and mode bytes retain their bounded existing field views. No default
capacity, allocation policy or valid actor domain is inferred beyond these
accesses. A nearby 40-byte helper at `0x18408` repeats the second predicate but
has no resolved inbound reference; its matching private trial contributes no
public coverage.

All five complete extents match as ordinary C without register constraints.
The predicate, selector and capacity callback include their original zero
tail alignment. Changed comparison, selected kind, animation, dispatch case
and capacity relation each reject a real source mutation. The three published
job consumers remain exact and reject their controls under the extended
prototype header. Table-word search results, callback-copy evidence, raw
comparisons and failed candidates remain in ignored reports; the ready batch
is `frame-need-optional-dispatch-batch-manifest.json`. Other optional-mode
predicates and the initial callback's callers remain useful connected targets.

## Mode-two selectors and optional activity

The 36-byte predicate at `0x2F19C` checks optional two and compares the signed
parameter halfword with a full signed-word threshold. All five reconstructed
direct selectors call it with 10,240, observe its low return byte and conditionally
write attachment kind twelve. They return one rather than an output count;
unwritten output bytes retain their old contents. Their writable buffer bounds
are unknown, and the replacements introduce no terminator or clearing pass.

| Selector | Other observed output selection |
| --- | --- |
| `0x1A38C` | Kinds 60 and 23, followed by optional twelve |
| `0x28764` | Optional-one ready selects 45; otherwise periods zero/one/two select 33 followed by 28/32/30, while period three writes 31 |
| `0x35C3C` | Optional-one ready selects 45; otherwise periods zero through two select 33 and period three selects 31 |
| `0x3A994` | Optional-one ready selects 45; otherwise 53 |
| `0x46200` | Optional-one ready selects 45; otherwise 59 |

The first period selector leaves its append index zero on the period-three
path, so optional twelve overwrites the 31 it just wrote. This observed behavior
is preserved. The other period selector retains its explicit default-zero
branch even though the accepted period helper returns zero through three.
The clock pointer is the established view at `0x03003958`. Pointer-word searches
place all five selectors at observed definition `+4` positions, copied to
state `+0xE8` by the accepted allocator. The names retain address suffixes where
the broader object role is uncertain; arithmetic row positions do not define
the complete table's extent. For the 53/59 selectors, advancing the count in
each branch reproduces the original register lifetime naturally. An equivalent
single count initialization produced a 52-byte candidate instead of 56 and
remains excluded. No register constraints are needed.

The 76-byte helper at `0x2F1C0` proceeds only when enabled and the actor equals
the established player pointer. It calls the primary chance API with fifteen
minus signed parameter zero, narrowed to the API's unsigned halfword. The
accepted parameter reader returns a signed byte promoted to a word, so this
subtraction itself has a bounded domain. Success clears the associated
object's word at `+0x58`, using the existing need-effect timer view. The name
describes that observed store; timer units, object ownership and the original
return declaration remain provisional. Its caller explicitly observes a byte
result.

The 800-byte controller at `0x43490` connects the helper to need updates,
conditions, animation, samples and the published optional producers. A record
byte `+0x0C` equal to one first forces phase one. Phase zero faces the actor
opposite the associated object and enters phase six. When condition `(0,4,0)`
is complete, kinds 28/30/32 gate game value 20 or 40 and, on success, call the
optional predicate and increment producer; kinds 31/33 gate ten or twenty.
The larger amounts apply in world 28. A failed gate requests animation five,
plays cue 86 or 85 and enters phase eight, which waits for the animation flag
before requesting phase one. The inline failure helper is ordinary semantic
C shared by those branches.

Phase six requests animation 61, publishes need-effect state three, plays cue
166, sets the actor's halfword countdown to 300 and enters phase 54. That phase
plays cue 22 when the old countdown's low five bits are zero and decrements it.
At its 65,535 underflow sentinel, a failed timer-reset attempt enters phase 25,
sets 150, starts animation 23/cue 20 and publishes need-effect state zero.
Success instead starts optional three and enters phase nine. Phase 25 adjusts
need seven by the definition's byte `+35`; its timeout enters phase nine and
sets triple `(0,1,0)`. Phase nine requests phase one for a later invocation.
Phase one stops the saved sample, publishes state zero, requests animation one
and returns two. Phase ten can also return two on the animation flag without
that cleanup sequence. Other paths return one. These distinct completion paths
and the halfword wrap are preserved rather than treated as one generic exit.

The controller's unsigned phase switch retains eight explicit cases in the
observed zero-through-54 jump-table range; other phases take the original
default path. Its nested kind switch covers 28 through 33, with 29 falling
through without work. Ordering source cases ten before nine closed the last
24 differing bytes in the initial natural-C candidate. The complete extent
includes generated switch tables, literals and tail alignment, without embedded
instruction bodies or comparison masks.

The 216-byte direct dispatcher at `0x438CC` obtains an unchecked attachment
record. Kinds 28/30/31/32 enter the controller; twelve, 45 and 22 select
the connected child handlers at `0x43348`, `0x433E4` and `0x439AC`. Other kinds
return zero. Its complete 12-through-45 switch table matches. This wrapper
does not pass kind 33, although the controller preserves that original nested
case; no runtime-unreachability conclusion follows from this one caller.

All nine complete extents match ordinary C and reject real controls. Eight
previously accepted optional job/callback consumers remain exact with their
controls under the current shared headers. Raw branch/table evidence, source
snapshots and failed candidates remain in ignored reports; ready metadata is
`frame-need-optional-selection-batch-manifest.json`. The dispatcher children are completed below; callers of the initial definition
callbacks remain connected targets. Runtime actor, output-buffer, sample and cancellation
validity remain untested.


## Optional completion, parameter jobs and choice control

Fourteen further ordinary-C functions cover 2,176 bytes. The activity
wrapper's three child handlers now connect both optional-mode consumers to
animation, need adjustment and sample cleanup. Kind twelve starts animation
14/cue 26 and phase four, adjusts need 52 by the definition byte `+35`, and
waits for the mode-two consumer. Kind 22 starts animation 24/cue 33 and phase
11, then waits for the mode-three consumer. Each enters phase one when the
record's running byte is exactly one; phase one stops the saved sample,
requests animation one and returns two. Other paths return one.

Kind 45 differs: any nonzero running byte requests phase one. Its phase zero
tries the retained actor effect before creating an indicator, then faces the
actor opposite the associated object, starts animation 45/cue 19 and enters
phase five. That phase uses the previously matching parameter consumer.
Cleanup stops the saved sample, requests animation one and indicator state one when an
indicator exists, clears its pointer and returns two. This ordering is distinct
from the earlier job at `0x18228`, which faces the actor before trying the effect.

The mode consumers at `0x2F240` and `0x2F278` load the same halfword both
unsigned and signed. Matching modes two and three subtract 51 and 128
respectively only when the signed value is strictly greater than that amount;
they then return word zero. Otherwise they clear both the mode byte and
parameter and return word one. This includes negative signed parameter values.
The child callers explicitly observe the low byte; no timer units or general
parameter-validity claim follows from these constants.

The percentage callback at `0x2F30C` starts with byte 100. Mode two reads the
parameter's high byte and returns `100 - value` when it is below 100, otherwise
zero. Mode one with a positive signed parameter returns 50; other cases retain
100. Comparing and subtracting the named result preserved the original shared
constant, whereas the initial constant-expression form differed in 41 bytes.
Observed definition words at field `+24` of rows 109, 110, 114 and 115 identify
this callback. The accepted allocator copies that field to state `+0xFC`.
These row numbers are address arithmetic against the established 36-byte
stride, not a complete table-bound assertion.

A second complete callback chain selects attachment kind 55 when signed
parameter one, converted to an unsigned word, is at most one; otherwise it
selects kind seven. Its eligibility callback permits kind seven and all other
kinds except 55 when that unsigned parameter is above nine. The matching source
retains a switch so the original separate seven/55 tests remain explicit.
The begin callback allocates a record, stores the full kind word, obtains the
associated object's attachment-zero point, starts route four with the record's
status byte, requests animation six and returns one; allocation failure returns
zero. The unchecked dispatcher enters the kind-seven or kind-55 child and
returns zero for other kinds. Exact pointer words at arithmetic row 138 fields
`+4/+8/+12/+16` connect this chain. The allocator copies them to state
`+0xE8/+0xEC/+0xF0/+0xF4`; broader callback and object ownership remain unknown.

The kind-seven job starts direction seven, animation eight, phase three and
an actor word countdown of 90. It chooses cue 133 or 132 from the interaction
mode, adjusts the attachment need using definition byte `+35`, and enters phase
one when the word countdown reaches minus one. Its kind-55 sibling starts an
indicator and animation 45/cue 19 unless the low-need predicate selects the
animation-85 path. Phase 52 adjusts need 18 and calls the new 92-byte parameter
step; phase eight waits for the animation flag before clearing the need
countdown. Phase one stops the sample, clears the indicator and returns two.

The parameter step deliberately treats the signed reader's result as an
unsigned word. Values above nine, including negative signed values, return one
without updating the indicator. Otherwise it publishes the current percentage,
advances the parameter and returns one only when a fresh read equals the old
value plus one. Its first formal is unused in the observed body. Existing
reader, indicator and update declarations are reused rather than duplicated.

The 800-byte choice controller at `0x43B30` preserves its full zero-through-19
jump table. Nine explicit cases perform work; phase one takes the default body
and is recognized by the final status test, returning two rather than one.
Unlike the activity children, this body has no upfront running-byte cancellation
check. It starts the optional attempt and game-value gate, waits for animation
flags, and opens the original choice helpers. A signed result word at
`0x03004370 + 12` is compared as unsigned against zero, one, two, three and
all-ones values in its nested switches. Cancellation outside the excluded worlds
and world 28 adds game value one before requesting animation 30 and phase 18.
Phase 19 decrements the actor halfword counter from its earlier value 30 and
uses the 65,535 sentinel to enter that same exit path.

Its selection, page and count accesses use three one-byte aliases at
`0x030021F1`, `0x030021F0` and `0x030021F2`. This storage is distinct from the
published scene request/choice counters at `0x03005A00`. The page advances by four,
narrows to a byte, and resets to
zero when it reaches the observed count. These aliases preserve the original
literal addresses; they do not establish separate storage ownership or buffer
capacity. A phase-17 switch and direct selection-byte assignment before the
state-word switch closed the initial 796-byte/285-difference candidate using
ordinary C with no register bindings. The complete 800-byte extent includes
two zero tail-alignment bytes omitted by the provisional 798-byte CFG extent.

The choice helpers were explicit original dependencies at that milestone;
the following batches reconstruct setup, application and completion. The page
builder at `0x43F9C` remains unconverted. Broader input contracts are provisional.
All fourteen accepted extents have changed-source controls,
including a real halfword-countdown edit in the choice controller. Current
activity-header consumers are reverified after its comment-only clarification.
Failed source variants, complete candidate/expected bytes and callback evidence
remain in ignored reports; publication metadata is
`frame-need-optional-completion-batch-manifest.json`. This is static and compiler
matching evidence, with runtime interaction, UI, sample and cancellation
behaviour still untested.


## Optional choice-list and clock-classifier closure

Five further C replacements cover 596 bytes. The 800-byte choice job calls the
92-byte initial setup, 92-byte secondary setup and 32-byte refresh wrapper at
their original addresses. Initial setup records the available-list count in
the byte at `0x030021F2`; both setup paths write the scene text halfwords at
`0x030059F0`, clear only request bytes +4, +1 and +2 at `0x03005A00`, then call
the original stage helper with two. The excluded-world branch writes titles
488 and 489, while its other branch leaves the second halfword unchanged.
Secondary setup writes 492, 495 and 493 and writes the fourth halfword to 497
only when condition `(4,0,0)` is complete and `(4,0,1)` is incomplete. It does
not invent a default value for that preserved fourth entry. Refresh delegates
to the still-unconverted page builder at `0x43F9C`, discards its result, and
performs the same request-byte handoff. The three list-control bytes at
`0x030021F0/1/2` remain distinct from the request storage at `0x03005A00`.

The 148-byte available-list producer initializes 24 observed bytes at
`0x030021D8` by reading, ORing with 255 and writing each byte. A packed byte
bitfield expresses that observed operation and one-byte stride; this is a
compiler matching view, not proof of the original source type or allocation.
It then visits indices zero through 23, calls the classifier with a word output
and two separate byte outputs, and appends qualifying indices. Initialized
relation entries qualify except index 13 when condition group `(4,4)` is
complete; an uninitialized relation entry qualifies only at index five. The
word and two byte temporary objects are separate C locals, matching the stack
out-argument addresses without padding or register constraints. Early plain
byte and aggregate-output variants remain preserved as failed comparisons.
The observed writer span and maximum append count do not establish wider
buffer ownership or arbitrary-input safety.

The 232-byte classifier indexes the established pointer table at `0x08D7162C`
with `(unsigned char)(index + 12)` and rejects a null slot. It reads
the eight-byte clock at game-state +8, the stage word at +0x440 and selected
actor byte at +0x740. These are a bounded overlay of existing scene storage;
the byte formerly called `current_world` by a separate scene view is also this
clock's hour at +0xA. No shared scene layout is changed by this overlay.
When the narrowed index equals selected actor minus 18, hours nine through 16
produce word 50; otherwise it returns the stage-indexed byte at `0x0805FBA4`,
weekday plus one, and first-hour byte nine. Other slots produce the current
hour/weekday table byte and, unless it is 50, advance the signed hour until
the table value changes. Hour rollover increments the weekday byte and takes
its unsigned remainder by seven through the actual `__umodsi3` body at
`0x4CF50`. Table bounds, termination for malformed tables and the meaning of
50 remain unproven. Inferred names describe these observed operations only.

Signed-byte hour iteration and pointer-first row address arithmetic closed the
classifier's main mismatch. Three semantic compiler constraints remain: a
short-lived unsigned table offset in r0, table base in r1, and table-slot pointer
in callee-saved r5. The offset's two unsigned shifts compute exactly
`((unsigned char)(index + 12)) * 4`; they do not copy an instruction body.
The first two constrained values end before calls, while the r5 pointer survives
the weekday and remainder calls. Removing each constraint was tested and
retained as a failed full comparison. There is no instruction assembly in the
body; explicit zero alignment is separate source glue.

All five extents have real source controls and fresh public-header proofs. The
existing 800-byte choice caller is reverified after the helper-status comment
change. The page builder remains excluded: a natural cached-limit form is
132 bytes with three differing bytes, while earlier pointer forms differed
more substantially. Application and completion are reconstructed below.
Publication metadata is
`frame-optional-choice-list-batch-manifest.json`; raw complete disassemblies,
source variants, candidate/expected bytes and controls remain private. Whole-ROM
and source-byte equality do not establish UI, clock, relationship or gameplay
behaviour.

## Optional choice application and completion

Eight further complete C extents cover 756 bytes and connect the previously
reconstructed 800-byte job controller to scene requests and actor creation.
The 104-byte apply helper reads a signed cost word from the table at
`0x0804EF50`, using the game-state stage at +0x440 and a 24-byte row stride.
Its current job caller supplies kinds zero, two and three. It compares the
signed game-value reader against that cost, then either installs the choice
and sets timer 19/animation 31, or invokes the failure request and sets selection
four, timer 18 and animation 30. No arbitrary stage or kind bounds are established.
The 12-byte reader returns the signed word at game-state +4 through the existing
`FrameActorValueWorld` view; its broader game role remains provisional.

The 120-byte installer switches on the narrowed kind. Zero, two and three set
text IDs 1148, 1147 and 1146 and create scene objects with values 263, 264 and
265. Other kinds preserve the text and request object. All paths activate the
request. The 44-byte failure helper writes text 500, creates value 112, and
activates the same request. These paths reuse the published scene factory and
request storage at `0x03005A00`; they do not infer defaults for preserved fields.

The 244-byte page application reads a signed byte from the available list,
calls the classifier with a word and two separate byte outputs, and adjusts
the corresponding relation value by one. Unless the classifier word is 50,
it computes a narrowed halfword interval from the returned bytes and current
clock. The raw comparison is between the returned last byte and the clock's
signed day halfword, with no normalization added. Interval values through 90,
91 through 179, and the remaining halfword values choose text 1149, 1150 and
1151 for substitution field zero. It then stores classifier word plus 1092
as the first text halfword, creates a scene object using the signed list byte
plus 239, and activates the request. The day, hour and minute widths, wrapping
halfword conversion and reload of the list byte are preserved.

The relation-state pointer survives its adjustment call. The clock view uses
that pointer's 32-bit address minus 16, which is the observed game-state base.
Integer address arithmetic avoids subtracting outside the relation object's
C array. Capturing the last byte before deriving this pointer and evaluating
the first byte before the hour subtraction reproduces the original lifetimes
with ordinary C. Earlier reordered expressions and uncached global-address
forms remain useful failed comparisons. No register bindings are required.

The 176-byte special path requires condition `(4,0,2)` and unsigned game-state
byte +0xE0 greater than 29 for its first test, then condition `(4,0,3)` and the
signed relation average greater than 39 for its second test. Failed tests set
text 1143 or 1144. If both pass and `(4,0,1)` is incomplete, it sets text 1145,
completes that condition and decrements byte +0xE0 by 30. It always activates
the request. The byte's `budget` name describes the observed threshold and
decrement only. The eight-byte average getter reuses `DisplayMenuRelationMetrics`
at relation-state base plus 0x20 and returns its sign-extended halfword +2;
no duplicate relation layout is introduced.

The 48-byte completion helper initializes a null result, requests two integer
coordinates, and creates an actor with direction zero only when the narrowed
target-query result equals one. Its returned `FrameObject *` corrects the older
provisional void declaration. The existing job discards that pointer, and all
six previously accepted importers of the changed header are reverified with
their actual source controls: 1,396 bytes, including that 800-byte caller.

All eight new providers have fresh current-header positive and negative proofs.
Their changed thresholds, timer, text IDs, selected source word and average
increment are rejected. The sources use ordinary C, with zero tail alignment
kept explicit where needed. The page builder remains an explicit original
132-byte region, with its strongest candidate still three bytes different.
Publication metadata is `frame-optional-choice-apply-batch-manifest.json`;
raw disassemblies, useful source failures and full candidate/expected/control
bytes are retained privately. UI, clock, relationship and gameplay behaviour
remain untested.
