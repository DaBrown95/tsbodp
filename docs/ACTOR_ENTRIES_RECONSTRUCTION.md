# Actor entry list lifecycle and condition handoff

The 25 connected source extents listed here cover 3,224 bytes of matching C,
including the newly qualified grouped reader and writer: two functions and
868 bytes beyond the previous 23-extent, 2,356-byte snapshot. Complete linked
extents, pools and alignment match at the original addresses. Every replacement
has a compiled changed-source control that rejects. The full-project matching
and progress gates also pass with the paired transfer installed.
The list setup, reset, insertion and selection paths connect to the accepted
condition lookup/removal and completion code. These are static and compiler
results; no gameplay behavior or complete executable inventory is claimed.

| Provisional name | ROM address | Bytes |
| --- | --- | ---: |
| `actor_entry_prepare` | `0802086C` | 104 |
| `actor_entry_reset` | `080208D4` | 116 |
| `actor_entry_reset_values` | `08020948` | 84 |
| `actor_entry_add` | `080200C8` | 364 |
| `actor_entry_find_capacity` | `0802099C` | 48 |
| `actor_entry_is_empty` | `08020A5C` | 20 |
| `actor_entry_is_full` | `08020A70` | 20 |
| `actor_entry_has_space` | `08020A84` | 20 |
| `actor_entry_adjust_counter` | `08020A1C` | 48 |
| `actor_entry_clear_counter` | `08020A4C` | 16 |
| `actor_entry_mark_seen` | `0800EB48` | 32 |
| `actor_entry_choose_base` | `080206EC` | 96 |
| `actor_entry_choose_195` | `0802074C` | 96 |
| `actor_entry_choose_209` | `080207AC` | 96 |
| `actor_entry_choose_201` | `0802080C` | 96 |
| `actor_entry_clear_collection_group` | `08020234` | 172 |
| `actor_entry_publish_collection_group` | `08020614` | 216 |
| `actor_entry_remove_collection_record` | `08020574` | 160 |
| `actor_entry_refresh_list` | `08020368` | 328 |
| `actor_entry_reserve_collection_record` | `080204B0` | 196 |
| `actor_entry_empty_hook` | `0800EB2C` | 4 |
| `save_stream_read_actor_tail` | `0800EB30` | 12 |
| `save_stream_write_actor_tail` | `0800EB3C` | 12 |
| `save_stream_read_actor_entries` | `0801FCF8` | 468 |
| `save_world_write_region_1fecc` | `0801FECC` | 400 |

## Shared storage evidence

The canonical four-byte `ConditionActorEntry` and eight-byte list header are
reused. Count and capacity are bytes zero and one; the entry pointer is at four.
The context initializer exposes fifteen embedded headers beginning at `1C`.
Their records are assigned successive positions in the inline storage beginning
at `94`, using the capacities in the eight-byte definitions at `080535A4`.
Context pointers at `18` and `14` select headers thirteen and fourteen.

The fixed capacities are thirteen eights, fifty and eight, totaling 162 records.
The canonical context now declares those records as one `storage[162]` array
at `94`, occupying 648 bytes through `31C`; its collection pointer and all
established context offsets are unchanged. Prepare uses `storage + offset` and
retains all 104 matching bytes. This common producer-backed array makes the
catalog's last unused cursor decrement reach element 153 after reading list
fourteen's elements 161 through 154, rather than before an eight-record C
subarray. The captured prepared pointer and continuing backing remain premises;
this is not a universal contract for arbitrary alias-list or serialized inputs.
The final eight records begin at context `2FC` and end at `31C`, immediately
before the collection pointer. Under the world-reset producer at context
base world `DC`, these are world `3D8..3F8`; its secondary list header is at
world `168`. The linked catalog now reuses the canonical list and collection
types. Its former byte-`+1` count name was capacity, and its collection policy
byte is the existing four-byte group's count. See the
[catalog bounds](SCENE_LINK_CATALOG.md#access-and-compiler-evidence) for the
unchanged-pointer, allocation and scene-ID premises. This does not establish
all later writer or serialized-state populations.

The definition table is the same table already used by
`condition_record_actor_selection`. Its shared declaration now names byte zero
`capacity`, byte two `retained` and byte three `fallback`; byte one remains
`count`. The matching refresh uses that count as the minimum regenerated list
size; the selection publisher uses it as its seed scan bound. The pointer at
four and all field types/offsets remain the same.
Thirteen definitions are used by the selection publisher and reset-value loop;
fifteen are used by setup. Those loop bounds are distinct from total table size.

Setup allocates `84C` bytes only when the pointer at `03001DAC` is null, then
copies that pointer to context `31C`. It retains the original absence of an
allocation-failure check. Reset marks every capacity slot's kind `FF`, zeroes
the fifteen counts, calls the connected refresh path for the first thirteen
headers, regenerates five bytes at context `0D` from the two-byte parameters at
`08053634`, and clears the separate allocation. Its `0800EB2C` hook already has
an empty matching C body and a rejecting byte-store control; the table now
includes those four previously owned bytes without adding credit again.
Reset finally inserts ID `8E` into the list
pointed to by game-state `F0`. Neither the complete context allocation nor its
gameplay identity is established.

The adjacent tail reader and writer now close the source-owned interval
`0800EB2C..0800EB48`: 28 bytes including the existing hook. Each new wrapper
owns 12 instruction bytes, with no literal pool or alignment. They pass a fixed
signed count of 28 to the existing byte-stream providers. The writer accepts a
read-only source pointer; no seven-word actor owner is inferred from that count.

Native grouped-reader and writer callers pass their original complete byte
base plus `0x320`. The known enclosing world paths therefore transfer bytes
`0x3FC..0x417` relative to the world root. This tail lies beyond the canonical
`0x320` context prefix and requires the actual enclosing backing. Stream cursor,
copy overlap and partial-bit-position preconditions remain those of the byte
providers. Observed direct callers do not establish all incoming targets or
valid stream populations.

The older tail-writer recipe lacked controls and canonical API qualification.
Fresh normal/strict builds subsequently verified both 12-byte wrappers; all
four count controls changing 28 to 27 reject by one byte. Their actual provider
and caller-definition checks pass ten target layout facts, and six incompatible
contracts reject. The grouped callers now have their own qualification below.

## Paired grouped transfer

The reader at `0801FCF8` owns 468 bytes: 456 instruction bytes and twelve literal
bytes. The writer at `0801FECC` owns 400 bytes: 390 instruction bytes, eight
literal bytes and two alignment bytes. Both use the canonical collection group
layout: start at byte zero, count at byte one and flags at byte two. Retained
older private headers reversed start/count; those failed sources remain evidence,
not matching coverage. The separate small-list layout still has count at zero,
capacity at one and four-byte entries selected by capacity.

Both functions require complete mutable backing of at least `0x348` bytes
through input `+0x347`, beyond the canonical `0x320` context prefix. Besides the
28-byte tail at `+0x320`, they access the twelve-byte menu-choice record at
`+0x33C`. Valid capacity-backed lists, the separate aligned `0x84C` collection,
record indices within its 160 slots and valid stream/provider state remain
source-domain preconditions. No bounds, allocation or stream checks are added.

The reader clears the full `0x84C` collection and initializes the receiving
word to zero before reading one count byte per group. Decrementing each count
to zero preserves the word's defined upper bytes for the next group. It keeps
two distinct halfword count observations: the first supplies the descriptor
start byte; the second supplies the total-count update and `12 * start + 4`
record address. That second snapshot is the genuine `r6` value and dies before
the first record-reader call. The writer instead captures the descriptor start
in `r6` before the count-byte writer call and uses it for the record address
afterward. Those lifetimes are different.

One actual complete byte base removes the reader's redundant typed root.
Truncating the large-record packed value to an unsigned byte before shifting
produces the native low-nibble shift pair. The real small-list next-group value
in `r8` survives its reader calls; the input base remains unconstrained. The
late `r4` cursor is copied from the complete base and then advanced by four,
preserving its native scope rather than hoisting it into the entry. Both
functions use a separate real `r5` counter across the final five byte calls.
These are initialized algorithm values with disjoint required lifetimes, not
instruction-body assembly or artificial memory traffic.

Fresh normal and strict builds without diagnostic flags match both entire
extents. Controls changing the first list limit from fifteen to fourteen reject
one byte in each build and omit real serialized input/output. The reader's API
unit includes its actual definition, six providers and the copy dependency;
35 target layout facts pass and nine incompatible contracts reject. The
writer's actual-definition unit passes 31 facts and rejects seven contracts.
Complete backing, valid save populations, incoming targets and runtime save
compatibility remain separate from these source and compiler results.

## Insertion and selection

Insertion searches the entire capacity for the first `FF` slot. It writes the
narrowed kind and two byte values, increments the byte count, and marks the
original word-sized ID in a bitset at `03003D4C` only when that ID is at most
148. IDs 125 and 126 become 169 for the particular list at `03003A88`.

Successful insertion into the current game-state `F0` list can complete
observed condition triples for IDs 109, 134, 124, 127, 118, 141, 145 and 126.
IDs 119 through 123 additionally count matching capacity slots with the byte
at game-state `E6`; a total above two completes `(2,2,1)`. IDs 195 through 200
write `kind + 61`, narrowed to a byte, at `43D` and set `43E` to one. These
specific accesses justify a condition handoff name, not an inventory or quest
interpretation for every record.

The capacity lookup returns the first matching index or minus one, unlike the
existing count-bounded lookup. The empty/full/space predicates normalize their
byte comparisons to zero or one. Clearing an indexed counter byte at input
`4 + index` returns its old value. The connected indexed adjustment adds a signed change to that byte, clamps the
result to zero through 250, stores its narrowed value, calls the accepted
condition threshold refresh, and returns the clamped value. Two temporary
cell-pointer scopes preserve the original recomputation around the clamp in
ordinary C.
Bounds, duplicate entries and count/capacity
consistency remain unchecked in these functions.

The four selection routines read the shared catalog at `080616CC` with stride
24. They reject a zero word at record `10`, reject ID word 317, retry mode two
when the existing chance helper with argument 50 returns nonzero, and retry
mode three when its argument 5 returns nonzero. Their bounded-random arguments
and offsets are respectively `(117,0)`, `(5,195)`, `(7,209)` and `(7,201)`;
the resulting ID is narrowed to a byte. This exposed catalog accesses beyond
the earlier 149-entry name scan. The shared array declaration is now unsized;
149 remains a caller scan limit, and the complete storage extent is unknown.
The selection-mode meaning and termination for arbitrary table contents have
not been established by runtime evidence.

## Separate record collection

The pointer at context `31C` addresses the separate `84C`-byte allocation.
Its observed layout contains a halfword count at zero, an unknown halfword at
two, 160 twelve-byte records beginning at four, and 50 four-byte group headers
beginning at `784`. Each record begins with the existing four-byte actor entry;
its two following words remain unknown. A group header supplies byte-sized
start, count and flags at offsets zero, one and two, followed by an unknown byte.
The scene marker sets flag bit zero at group `+2` without changing its four-byte
layout. The capacity test in insertion,
the `49` bounds in deletion/clearing, and the reset's `84C` clear agree on these
extents. This is evidence for this allocation, not the complete context size.

Group clearing copies any following records down with the accepted heap copy,
clears the vacated tail, reduces the later groups' starting indices, subtracts
the removed count and zeroes the selected group count. The scoped later-group
loop matches in ordinary C without register constraints. Overlapping-copy
direction is inherited from the matching heap helper.

Group publication consumes records while the active list has space. It skips
records whose catalog word at `0C`, provisionally named `category`, is six and
otherwise calls the matching actor-entry insertion path with the three entry
bytes. A second handoff inspects game-state `43C`, writes 50 and attempts an
entry with ID `195 + game[43D]`; when no slot is available it also clears `43E`.
The function then clears the collection group, including records that were not
published. Those byte accesses are preserved; a timer or notification gameplay
interpretation is provisional. Indices, count consistency and destination
capacity remain unchecked except for the observed active-list comparison.

Single-record removal now matches the complete 160-byte extent at `08020574`.
It decrements the selected group's byte count and the collection's halfword
count, shifts later twelve-byte records down, clears the vacated twelve-byte
tail with the matching heap helper, then decrements later groups' start bytes.
The record copy uses explicit byte offsets from the collection base: four is
the documented record-array offset, and twelve is the verified record stride.
A scoped count reader uses one semantic `r0` pointer lifetime constraint; the
ordinary clear-reference scope preserves the subsequent pointer recomputation.
There is no instruction-body assembly. Empty groups, selected indices and
underflow remain unchecked as in the original. A changed loop comparison
extends the shift by one record and rejects one byte. Its positive/control
proof index is `reports/audio-root/collection-remove-canonical/1791850297820779000/ready.json`.

Collection reservation now matches the complete 196-byte extent at `080204B0`
in ordinary C. It rejects a total above 159, chooses the record at group start
plus count, shifts subsequent twelve-byte records up in descending index order,
increments later group starts and both counts, then returns the reserved slot.
The separate copy-reference scope preserves the compiler's pointer lifetime
while its structure copy uses three word transfers. The selected count byte is
addressed through the typed group-zero count plus the verified four-byte group
stride. It neither initializes the returned record nor adds unchecked-group
bounds. Changing the capacity rejection from 159 to 160 rejects one byte.
The canonical proof index is
`reports/audio-root/collection-reserve-canonical/1791851836572880000/ready.json`.

## Conditional collection partition and remover bounds

For a live, disjoint collection, let `C[g]` and `S[g]` be each group's count
and start, and `N` the total. The reset clear establishes
`S[g] = sum(C[h], h < g)` and `N = sum(C) <= 160`. Valid reservation,
nonempty indexed removal and group clearing preserve those equations: each
shifts the affected suffix and adjusts all later starts by the same amount.
The reservation guard prevents growth beyond 160. This is an induction over
those named writers with valid group/index arguments and stable backing;
allocation alone, arbitrary writers and concurrent changes do not establish it.

Under that partition and stable stage 2, 3 or 4, the original selection remover
at `0x454DC` draws only initialized group IDs. The stages select groups
`23/25/24`, `46/48/47` and `39/40`, respectively. Empty groups retry before the
record draw. For a nonempty count `m <= 160`, the matched random-range helper
computes `floor(m * (random & 32767) / 32768)`, so its result is in `0..m-1`;
the product fits a signed word. Consequently `S[g] + selected < N <= 160`.
A positive selectable-count result proves that an allowed record exists under
the same stable partition and the fixed kind predicate. It does not prove
that the retry loop terminates. Stages above four leave the group output
unwritten; a test for stage greater than one is insufficient by itself.

The [serialized reader](SAVE_STREAM.md) establishes the same prefix equations
only when every incoming count prefix is at most 160. It has no such capacity
test. After a fresh clear, a first group count of 161 reaches record index 160
at collection `+0x784`, exactly the first group descriptor. This is the native
address calculation at the first descriptor overlap, not a valid C-array access
or evidence that a natural save takes that path. Slot checksum validation does
not inspect these counts. A saved-input argument therefore needs backed count
prefixes or an actual valid writer history, in addition to the checksum.
Complete writer, alias, stage and lifetime populations remain open. Neither
this conditional bound nor the failed 192-byte / two-difference remover source
adds matching-C credit.

## Definition-driven refresh

The central refresh at `08020368` now matches all 328 bytes. When the current
count exceeds the definition's retained count, it scans from the retained index
through capacity, marks occupied kinds `FF`, zeroes their two value bytes and
decrements the byte count. It then fills from the resulting count through the
definition's count bound. Four seed kinds `FE`, `FD`, `FC` and `FB` call the
accepted base/195/201/209 selectors. Other seeds copy their complete first word
when their packed condition key is `(5,6,5)`, or when the addressed condition is
active and incomplete. Otherwise those four fallback kinds choose the entry.
Every generated record clears value bytes one and two and increments the count;
an unrecognized fallback leaves its kind unchanged, as in the original.

The eight-byte seed is an alternate view of the existing definition value:
the first four bytes are `ConditionActorEntry`, followed by row, column, index
and an unknown byte. Its condition state address is game-state `+448`, with
strides 144, 24 and four respectively; the completion byte follows at `+449`.
The shared `ConditionActorDefinition` and canonical table name are reused.
Four C register bindings preserve the cleanup array, record pointer and
byte-to-word kind return lifetimes. A byte return versus a widened return
changes the old compiler's narrowing and allocation; the retained ordinary
variants and wrong matches remain local. No instruction body is embedded.
The real retained-count comparison mutation rejects one byte. Its proof index is
`reports/audio-root/actor-entry-refresh-canonical/1791851640877264000/ready.json`.

## Matching and remaining path

The historical lifecycle snapshot reported eighteen functions without fixed
register constraints. The refresh and collection-removal constraints are
recorded above; the newly qualified grouped pair is described separately. Reset
now reads the producer-backed canonical `secondary_entries` member without a fixed-register constraint. The source
quality repair preserves its complete 116-byte match and adds zero C credit.
It contains no instruction-body assembly. Zero-filled
Thumb tail alignment is explicit where present. Changed limits, sentinels,
field selection, initialization values and notification IDs each reject by one
byte, except the altered random spread in reset-values, which rejects by 32
different/missing/extra bytes. The adjustment control changes the upper-bound
test and also rejects; its separate proof index is
`reports/audio-root/actor-entry-counter-canonical/1791848102323039000/ready.json`. The original private proof index is
`reports/audio-root/actor-entry-canonical/1791847197727325000/ready.json`.
The two collection controls change the later-group bound and the catalog
category filter, rejecting by two and one bytes respectively. Their proof index
is `reports/audio-root/actor-entry-collection-canonical/1791849007996878000/ready.json`.

The connected weekly/secondary-flag routine at `0802005C`, the higher game-state
loader at `0801B704` and condition serializer at `08029D18` remain unconverted.
Useful failed bodies and raw comparisons remain in ignored local reports. The
paired transfer does not close their target domains, valid save populations or
whole-game execution. Whole-ROM equality, storage mapping and runtime behavior
remain separate claims.


## Producer-backed secondary-list member

The existing canonical `ResourceActorState` now names the four-byte
`secondary_entries` pointer at `+0xF0`, with its character prefix ending at
`F0` and suffix beginning at `F4`. The selected-actor byte remains at `+0x748`.
The producer is the existing world reset calling `actor_entry_prepare` with
world base plus `0xDC`: that initializer's context-secondary field at `+0x14`
writes the pointer at world `+0xF0`. In the defined initialized state it points
to embedded list fourteen; its backing and capacity come from the existing
context setup. The separate `0x84C` heap collection is a different pointer and
is not the new member's pointee.

Actual selected-target layout checks establish that both the old character-only
record and the refined record have size `0x74C` and alignment four. The old
record was already rounded by the Thumb target's 32-bit structure boundary;
there is no old `0x749`/alignment-one ABI change. The containing union also
remains `0x74C`/alignment four, and all old field offsets are preserved. This
field refinement does not establish the full global allocation, a universally
initialized pointer, or compatibility of every legacy world alias and save/load
writer. The observed broader clear is not a complete storage-owner proof.

Reset's final insertion now reads `g_resource_game_state.actor.secondary_entries`
at its original position after the reset-value, clear and hook calls. It keeps
the live pointer read rather than taking an earlier snapshot. The fixed `r0`
source constraint and integer-address pointer dereference are removed; the
remaining reset loops, provider calls, full-word ID 142 and changed-source
control are unchanged. This is a source-quality repair, not an additional
function or byte gain. The wider header importer closure must retain its
matching bytes and controls under the refined declaration. Matching and target
layout evidence remain separate from gameplay and universal aliasing claims.
