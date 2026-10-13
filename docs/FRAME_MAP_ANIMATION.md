# Animated map object paths

Six connected semantic C replacements cover 1,400 original extent bytes. The
observed factory table at `0x0804F278` has slot one `0x08018821` and slot two
`0x080174FD`. These are the serialized-resource entries for two map animation
objects. Both callbacks call the same rectangle writer, which updates both the
visible map and its extra cell-type map. Names and field meanings remain
provisional; these are compiler and static claims, without gameplay evidence.

| Original ROM extent | Reconstructed function | Bytes |
| --- | --- | ---: |
| `0x174FC` | `frame_create_map_animation` | 268 |
| `0x17608` | `frame_map_animation_tick` | 532 |
| `0x18820` | `frame_create_map_animation_simple` | 188 |
| `0x188DC` | `frame_map_animation_simple_tick` | 148 |
| `0x18970` | `frame_map_animation_write_rectangle` | 176 |
| `0x2B270` | `frame_write_extra_map_cell` | 88 |

The pointer-sweep entry `0x17740` is an internal block of the callback at
`0x17608`. The branch at `0x17716` reaches it with live object, endpoint and
current-byte addresses, without a new prologue. Other paths fall through it or
join its cleanup at `0x17804`. The full 532-byte replacement contains its
interspersed literal pool at `0x1773C` and ends before the independent prologue
at `0x1781C`. The rectangle writer has a 174-byte ELF function symbol followed
by two original zero alignment bytes; its complete replacement is 176 bytes.
The map-cell setter ends before the independent getter at `0x2B2C8`.

## Payloads, object fields and initialization

Both serialized payloads start with a 32-bit ID word and signed halfword
coordinates at `+4/+6`. The slot-two constructor passes the complete ID word to
`frame_allocate_object`, whose existing implementation narrows its object ID.
The slot-one constructor uses `frame_allocate_scene_object`, checks its result
and stores the narrowed payload ID itself. The slot-two constructor has no
allocation-result check, matching the original behavior. Coordinates become
fixed-point position arguments by shifting the signed values by sixteen bits.

The shared role view retains the common ID, flags, owner-group/slot and
`kind/state/variant/pending` bytes. Its position view names the signed high
halfwords at object `+0x1A/+0x1E`; it does not imply a different object allocation
size. Work bytes are local to this object family:

| Object offset | Inferred local role |
| --- | --- |
| `+0x64` | Direction/repeat control, called `reverse` |
| `+0x65` | Completion removes the object when nonzero |
| `+0x66` | State-zero eligibility byte |
| `+0x67` | A started-state byte tested by the query and cleared on a direction handoff |
| `+0x68` | A latch used with the signal and the common pending bit |
| `+0x69` | Per-frame signal, producer remains unidentified |
| `+0x6A` | Current-index step for the reversible path |
| `+0x6B` | Reset period |
| `+0x6C/+0x6D/+0x6E` | Current, first and final byte indices |
| `+0x6F` | Narrowed sequence span |
| `+0x70` | Byte countdown |
| `+0x71` | State-zero polarity |
| `+0x72/+0x73/+0x74` | Map index and rectangle width/height |
| `+0x75` | Enables an observed sample-handle query |
| `+0x88` | Installed one-object step callback |

Slot two reads eight-byte definition records at `0x08052898`, indexed by its
payload kind byte. The first four record bytes are opaque; the constructor uses
width, height and index step at `+4/+5/+6`. The table is in ROM and is declared
readonly. A captured kind and step reproduce the original reuse across object
stores; the mutable-table predecessor reloads the definition and fails. The
kind bound has not been proved and receives no invented guard.

Slot one receives width and height directly. Its span is narrowed once after
width times height, then narrowed again after multiplying by the payload frame
count. The constructor initializes current from first, copies the period to the
countdown and installs its callback. Slot two derives the final index from the
span and first index, and chooses its starting index from the direction byte.

## Callbacks and map transfers

The simple callback marks state one for removal. In state four it decrements the
byte countdown. Expiration is the narrowed value 255, after which it reloads the
period and writes one rectangle. Reaching the final index either requests state
one or restores first; the repeat control decides whether to return to state
zero. State zero is explicit and performs no action.

The reversible callback treats states zero, one and four itself. State zero
uses the eligibility and polarity bytes to request state four. State one reads
the owner's serialized payload, activates its two resource groups and sets the
removal flag. State four handles its signal/latch/pending interaction, advances
or rewinds the sequence at countdown expiration and activates those same
resource groups at an endpoint. A saved completion byte remains live across
the group activation and state change; its observed zero is also the value used
to clear the started byte. Other states call the existing actor-state dispatcher.
Every path then clears the same pending and signal bytes. Explicit local
addresses preserve their identity across the calls; they are ordinary C
pointers, without register bindings or volatile qualifiers.

The sample-query boundary uses the word at `0x0300197C` as a handle for the
existing `audio_game_sample_active` wrapper. Its result is discarded here. The
wrapper and underlying channel query are freshly reproved; this does not
establish where this word is produced or prove that this callback plays audio.
The signal producer and the broader meaning of the eligibility/latch fields
also remain open.

The rectangle writer captures both signed integer coordinates in an ordinary
`FramePoint`. The aggregate keeps their required lifetimes through the two
external calls. For each cell it captures the map index, narrows the coordinates
to unsigned halfwords, calls `frame_write_map_cell`, then calls the new extra
cell-type setter. It moves X by 32 and wraps the current byte after each cell,
reloads X from the object after each row and moves Y by 32. Row is a byte;
column is a word explicitly narrowed to a byte after increment. The latter
source form reproduces the original byte wrap and allocation. All binding and
alternate ABI experiments remain failed private predecessors.

The extra cell-type setter obtains the existing map dimensions. Its destination
is the extra type-map pointer at `0x03001DE0`, indexed by the unsigned coordinate
quotients with a cell size of 32. Its source uses the cell-count offset at
`0x03001DE8` and the supplied unsigned halfword index. It adds the existing
header word at `0x030043F8` before narrowing the stored halfword. These reuse
canonical existing map symbols and types; no shared-header ABI changed.

## Verification limits

All six replacements compile and link to their complete original extents,
including literal pools and alignment. Each has a real changed-source negative
control. Twenty-two existing allocation, owner-payload, group activation,
actor-state, map and sample-query providers are freshly checked with their own
controls and current literal header closures. This is a finite connected proof
boundary; it is not new source credit for those providers.

The generic actor-state dispatcher still covers additional object states. The
resource factory and program-handler tables retain their existing unresolved
index bounds. The flagged projection branch of `resource_object_before_step`
still calls the explicit unconverted helper at `0x08048BF8`; it is not newly
reconstructed here. Whole-ROM integration is checked by the publication gates,
separately from these static connections and from runtime behavior.
