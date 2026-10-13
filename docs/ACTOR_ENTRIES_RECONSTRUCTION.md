# Actor entry list lifecycle and condition handoff

Eighteen connected replacements add 1,804 bytes of matching C. Their complete
linked extents, pools and alignment match at the original addresses. Every
replacement has an actual compiled changed-source control that rejects. The
list setup, reset, insertion and selection paths connect to the previously
accepted condition lookup/removal and condition completion code. These are
static and compiler results; no gameplay behavior is claimed.

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

## Shared storage evidence

The canonical four-byte `ConditionActorEntry` and eight-byte list header are
reused. Count and capacity are bytes zero and one; the entry pointer is at four.
The context initializer exposes fifteen embedded headers beginning at `1C`.
Their records are assigned successive positions in the inline storage beginning
at `94`, using the capacities in the eight-byte definitions at `080535A4`.
Context pointers at `18` and `14` select headers thirteen and fourteen.

The definition table is the same table already used by
`condition_record_actor_selection`. Its shared declaration now names byte zero
`capacity`, byte two `retained` and byte three `fallback`; byte one remains
`count`. Static accesses in the unconverted refresh routine motivate the latter
two names. The pointer at four and all field types/offsets remain the same.
Thirteen definitions are used by the selection publisher and reset-value loop;
fifteen are used by setup. Those loop bounds are distinct from total table size.

Setup allocates `84C` bytes only when the pointer at `03001DAC` is null, then
copies that pointer to context `31C`. It retains the original absence of an
allocation-failure check. Reset marks every capacity slot's kind `FF`, zeroes
the fifteen counts, calls the connected refresh path for the first thirteen
headers, regenerates five bytes at context `0D` from the two-byte parameters at
`08053634`, and clears the separate allocation. The observed `0800EB2C` hook
remains an original no-op body. Reset finally inserts ID `8E` into the list
pointed to by game-state `F0`. Neither the complete context allocation nor its
gameplay identity is established.

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
start and count fields. The capacity test in the unconverted insertion routine,
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

## Matching and remaining path

Ordinary C reproduces sixteen functions. The collection removal constraint is
recorded above. Reset uses one semantic `r0` binding
for the game-state base so the compiler retains the original base literal plus
`F0` address calculation. It contains no instruction-body assembly. Zero-filled
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

The central definition-driven refresh at `08020368` remains unconverted. Static
analysis shows a retained-slot cleanup, seed records and random fallback
selection, including a packed `(5,6,5)` condition marker. A revised 328-byte
trial matches the selection/condition handoff but still differs in the cleanup
loop; it receives no coverage credit. Collection insertion at `080204B0` and secondary-flag reconciliation at
`0802005C` remain connected targets. Useful
failed bodies and raw comparisons remain in ignored local reports. Whole-ROM
equality, partial storage mapping and runtime behavior remain separate claims.
