# Menu relation lifecycle

Seven matching Thumb functions reconstruct the 512-byte relation core. Two
connected resource and footer transfer functions add 240 bytes, for nine
functions and 752 C bytes in this path.
The existing matching menu initializer at `0x0803E518` calls the lazy initializer
and signed-value reader. The retained, unconverted secondary menu at
`0x0803F908` calls the adjustment and reader around its selected-entry updates,
text and indicator operations. Its consequence dispatcher and indicator producer
are described in [DISPLAY_MENU_EFFECTS.md](DISPLAY_MENU_EFFECTS.md). These are
static call links, not UI or gameplay validation.

| Entry | Extent bytes | Observed role |
| --- | ---: | --- |
| `0x08035D98` | 260 | Adjust an initialized relation value, clamp and update threshold flags |
| `0x08035F78` | 48 | Initialize an entry whose signed value is -128 |
| `0x08035FA8` | 36 | Store the narrowed value, refresh the average and notify condition state |
| `0x08035FCC` | 12 | Read a signed value through the offset getter view |
| `0x08035FD8` | 8 | Read flags through the same offset getter view |
| `0x080360C8` | 100 | Derive an initial value from the seed and five trait operands |
| `0x0803612C` | 48 | Sum non-sentinel values and divide by a fixed 24 |
| `0x080407EC` | 188 | Select and load a background from relation flags |
| `0x08040F10` | 52 | Restore a footer rectangle from the retained map |

The guarded access views and APIs are in
[display_menu_relation.h](../include/display_menu_relation.h). The four-byte
record contains flags at `+0`, a signed value at `+1`, and two unknown bytes.
The adjustment and initialization state receives the main base: its records
start at `+0x28`, and the threshold counter is a byte at `+0x24`. The getter and
average views receive that base plus `0x20`, placing the records at `+8` in
those views. The average is a signed halfword at their `+2`, hence main state
`+0x22`. The average updater observes 24 records. That scan establishes the
accessed record range, not a complete state layout or bounds checking for an
arbitrary incoming index. Other bytes and wider storage remain unknown.

A signed value of -128 is the sentinel. Adjustment returns it unchanged;
otherwise it adds the signed delta, clamps to -100 through 100, and clears flag
8 when the new value is nonpositive. Upward and downward threshold crossings
at 49, -50 and -90 update bits 4, 2 and 1. Crossing 49 also increments or
decrements the narrowed byte counter. The downward branch runs for a zero
delta as well, but its crossing conditions then fail. There is no added index
validation or counter saturation.

The store receives a full signed word, narrows it at the byte assignment,
refreshes the average, and calls the published
`condition_update_actor_context`. It returns the original word argument rather
than rereading the narrowed byte. The average ignores -128 entries in its sum
but always divides by 24, including when fewer entries contribute. Its compiler
runtime call is the existing signed divide at `0x0804CD2C`; that dependency
remains explicit and is not credited by this batch.

Initial values read a four-byte-stride seed table at `0x0806A020` and an
eight-byte-stride trait table at `0x080695DC`. The local trait view begins at
main state `+0x18`, with its five byte operands at `+2` through `+6`. Index 12
uses only the signed seed. For other indices, the first four trait pairs
subtract half their absolute difference, while the fifth pair adds half their
sum. Separate signed operand locals preserve both meaningful operands for the
negative-difference branch. The names `relation`, `traits`, `seed` and
`high_count` describe these accesses and remain inferred; the evidence does
not establish original field names or a gameplay meaning for the flag bits.

The accepted sources are ordinary C with no register bindings or instruction
body transcription. Their extents include alignment and intervening literal
pools: adjustment returns at `0x08035E9A`; preparation ends at `0x08035FA8`;
the store includes padding through `0x08035FCB`; the reader and flags getter
end at `0x08035FD8` and `0x08035FE0`; the initial-value extent includes its
mid-function pools and ends at `0x0803612C`; the average includes trailing
padding through `0x0803615B`.

The matching menu initializer also calls the resource selector at
`0x080407EC`. It reads flags through the getter view at `0x03003980` and selects
resources in priority order bit 8, bit 4, bit 1, bit 2. With none of those bits,
it indexes the resource pointer table at `0x08D73658` by the current menu
definition. All branches use the existing `display_load_background` with layer
3, tile offset 258, palette 12 and zero coordinates. The four flag-selected
resource addresses remain explicit metadata rather than extracted assets.
This path establishes the selection order, not the visual meaning of the bits,
table length, or asset identity. Its return and final pool/padding end at
`0x080408A8`, the indicator producer's entry.

The retained secondary menu and adjustment path call the footer restorer at
`0x08040F10`. It passes the map pointer retained in menu word `+0x10` to the
matching `display_copy_background_rectangle`: background 1, source and
destination (27,12), size (3,2), offset `0xD116`. The nine-argument call and
resource pointer role are observed; no new tile or asset interpretation is
asserted. Its final pools/padding end at `0x08040F44`. The resource declarations
and transfer prototypes are in
[display_menu_relation_resource.h](../include/display_menu_relation_resource.h).

Fresh canonical positive proofs and actual changed-source controls pass for
all nine functions. Controls change the sentinel checks, stored value,
queried field, special seed index, fixed average divisor, resource-selection
bit or footer offset. Eight controls
reject with one differing byte; replacing the stored value with zero rejects
with 28 differing bytes. The existing 744-byte menu initializer and its control
were recompiled at that milestone without changing its `void *` preparation
and then-provisional signed-byte reader contract. The nine functions, two existing ready consequence
functions and caller proof are indexed in the ignored
`catalog-presentation/menu-secondary-ready.json` receipt: eleven new functions
and 1,276 C bytes in the combined batch.

The earlier void-pointer adjustment, reassociated initial-value arithmetic,
pointer-cursor average and serialized-slot average candidates remain intact
with their raw comparison evidence. The six-byte choice-initializer scheduling
candidate and substantially differing secondary menu remain excluded. Full-ROM
matching and runtime behavior are separate claims from these extent matches.

## Delay and world-clock coordination

A further coherent batch adds four relation helpers and their 160-byte clock
producer, five functions and 292 C bytes. Their guarded role views and
contracts are in
[display_menu_relation_events.h](../include/display_menu_relation_events.h).
The main relation records and existing APIs retain their published layouts.

| Entry | Extent bytes | Observed role |
| --- | ---: | --- |
| `0x08035FE0` | 24 | Test that a signed value differs from -128 |
| `0x08035FF8` | 32 | Decrement each nonzero record byte `+2` across 24 records |
| `0x08036018` | 20 | Clear flag 8 and store four times the requested delay in record byte `+2` |
| `0x0803602C` | 56 | Ask the existing chance helper to decide whether to set flag 8 |
| `0x0803C498` | 160 | Advance the world clock, signal a row and age relation delays |

The byte at record `+2`, still represented as `unknown_02[0]` in the earlier
shared record, now has an observed countdown role. This does not establish
its wall-clock unit or meaning in every consumer. The setter takes a full
unsigned word, multiplies it by four and narrows the product at the byte store,
clearing flag 8 before that store. It adds no clamp or validation. The decrement scans exactly
24 four-byte records through a byte cursor, preserves zero, and subtracts one
from every nonzero delay. Unlike the setter, it does not change flags.

The chance helper divides the signed value by two, narrows that half to a
signed byte, promotes it for comparison, and supplies either that value or a
minimum of five to the existing `frame_random_chance`. A nonzero result sets
flag 8. It does not check for the uninitialized sentinel or delay expiry. The
existing RNG API's name and observed byte input/return are reused; these calls
do not independently establish a probability distribution. The separate
initialized query returns a byte boolean and is statically called by the
relation access paths at `0x08036534`, `0x0803660C`, `0x08036744` and
`0x08043F08`; those callers remain unconverted.

The world producer calls the matching clock arithmetic on the eight-byte view
at `0x03003958`. A nonzero carry mask ORs 3 into flags at `+4` of a selected
56-byte record in the array at `0x03004130`. The selected row is a byte at
`0x030040E0 + 0x31`; no row-array length or index check is established. A day
carry calls the unconverted `0x0803CA6C` dependency, whose entry overwrites the
incoming argument registers before their use. Its neutral day-event contract
remains provisional. An hour carry ages the relation getter-view records at
`0x03003980` only at hours 0, 6, 12 and 18. A minute carry decrements the signed
word at game base `0x03003950 + 0x74C` if it is nonnegative and the byte at
`+0x749` is zero. Wider state and the meanings of the row flags and timer are
unknown. Callback frequency and gameplay scheduling are not tested.

The retained menu stages at `0x0803F3DC` and `0x08040E84` directly call the
chance helper; the unconverted adjustment path at `0x08040AB4` calls the delay
setter. These links connect the new helpers to the existing menu and relation
core rather than treating them as independent byte totals. The world-clock
producer connects that state to the published clock arithmetic.

All five canonical extents match and all real compiled controls reject with
one differing byte: sentinel, scan endpoint, delay multiplier, chance threshold
and row-flag mask mutations. The decrement helper's first record cursor and
chance helper's first same-size scheduling attempt remain intact and excluded;
the accepted decrement uses a delay-byte cursor and the chance source keeps a
separate promoted half. All five sources are ordinary C with no register
bindings. Raw bytes, commands, snapshots and controls are indexed in the
ignored `catalog-presentation/menu-relation-events-ready.json` receipt. No
pre-existing accepted source or shared header needs an ABI change.

The connected row-execution, footer and result-presentation path now has nine matching
C functions / 2,976 bytes, described in [DISPLAY_MENU_RESULTS.md](DISPLAY_MENU_RESULTS.md).
It connects the relation chance/delay helpers and world-clock producer to
result pairs, background transfers, cue selection and text staging. Its
serialized result views express the observed row strides without asserting
complete table bounds.

## Reader word-return refinement

The connected, source-owned footer at `0x080401B8` uses the result of
`display_menu_read_relation` directly as a signed word: its call at
`0x08040214` is followed by a word copy and comparison, without a caller-side
byte extension. The reader itself uses `LDRSB` and therefore returns a
sign-extended word. Its C return type and both declaration headers now use
`int`. This corrects the earlier byte-return inference while retaining the
four-byte record layout and byte-valued field.

The primary-result probability explicitly narrows the returned word to
`signed char`; the menu initializer narrows through its existing byte store.
Fresh exact proofs pass for the reader (12 bytes), initializer (744 bytes),
and primary-result application (364 bytes). Their actual changed-source
controls reject with 7, 1, and 1 differing bytes, respectively. This refinement
adds no coverage. The footer and percentage helpers now have matching C;
the sequence-tile producer remains unconverted. These findings do not establish
runtime behavior or wider index bounds. The ignored refinement receipt is
`catalog-presentation/relation-word-return-ready.json`.
