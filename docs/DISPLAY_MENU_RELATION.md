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
were recompiled without changing its `void *` preparation and signed-byte
reader contracts. The nine functions, two existing ready consequence
functions and caller proof are indexed in the ignored
`catalog-presentation/menu-secondary-ready.json` receipt: eleven new functions
and 1,276 C bytes in the combined batch.

The earlier void-pointer adjustment, reassociated initial-value arithmetic,
pointer-cursor average and serialized-slot average candidates remain intact
with their raw comparison evidence. The six-byte choice-initializer scheduling
candidate and substantially differing secondary menu remain excluded. Full-ROM
matching and runtime behavior are separate claims from these extent matches.
