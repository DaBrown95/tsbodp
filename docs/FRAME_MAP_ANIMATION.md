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

## Map-cell startup storage

The connected startup allocator
[`frame_initialize_map_cell_buffers`](../src/frame/frame_initialize_map_cell_buffers.c)
at `0802B11C` matches its full 68-byte extent: 52 instruction bytes and four
literal words. It allocates `0x2000` scratch, `0x2800` type-map and `0x4000`
cell-data bytes, then points the extra type map four bytes into the type-map
buffer. Existing base/extra decoders corroborate the pointer roles. The
allocation-size control preserves 68 bytes and rejects by one byte. This is
source/static evidence; allocation success and gameplay are not established.

## Conditional map-row-6 append

The matching [scene-25 step](../src/scene/scene_phase25_step.c), state four,
submits `(kind=1, mode=4, scene=6)`. If that queued request survives shutdown and
object-removal callbacks until the handoff copy, the observed initialization
path selects map row six and normalizes mode four to zero. This is a conditional
source route; those intervening callback writers remain open.

The 72-byte descriptor at `0x080565C4` contains these fixed stream headers:

| Field offset | Stream | Address | Advertised bytes | Codec |
| --- | --- | --- | ---: | ---: |
| `+0x28` | Cell data | `0x08ED5DF0` | 2,288 | 6 |
| `+0x2C` | Cell types | `0x08ED6048` | 1,044 | 3 |
| `+0x30` | Extra cell data | `0x08ED61E4` | 288 | 6 |
| `+0x34` | Extra cell types | `0x08ED6240` | 56 | 3 |

[`resource_decode_bytes`](../src/resource/resource_decode_bytes.c) returns the
outer header's advertised size. Codec six instead obtains its produced count
from the installed [background decoder](RESOURCE_BACKGROUND_DECODER.md), whose
input starts after that header. The codec flag for the optional delta pass is
clear in all four headers.

The existing calibrated original-instruction model produces exactly 2,288 and
288 bytes for the two fixed codec-six payloads. A coupled fixture appends the
second at the first advertised offset: 2,576 bytes total, leaving 13,808 bytes
of the `0x4000` cell-data allocation. The first output and trailing 32-byte guard
remain intact. Exact replay, sixteen independent expected fixtures and the
existing malformed-input, instruction-budget and nullable-count controls pass.
The input guards stop at the next separately referenced containers; they do not
establish exact compressed-object extents.

The type headers separately give `(1,044 - 4) / 2 = 520` primary cells and a
52-byte extra DMA payload. Its destination ends at byte `1,044 + 52 = 1,096` of
the `0x2800` type-map allocation; 56 advertised scratch bytes fit `0x2000`.
This is header and source arithmetic; actual codec-three output and DMA
execution remain separate questions.

The byte-data observations use synthetic addresses and preloaded original
instructions. Successful nonoverlapping live allocations, the installed decoder
callback, and unchanged row, base and size across intervening providers remain
premises. Wider selectors, writers, copied-code states and gameplay remain open.
This adds no C ownership, executable discovery or native runtime coverage.

## Independently bounded extra-map getter

The [getter at `0x2B2C8`](../src/frame/frame_unrooted_read_extra_map_cell_2b2c8.c)
owns 52 C extent bytes: 48 instruction bytes and the four-byte literal at
`0x2B2F8` naming pointer storage `0x03001DE0`. It ends before the existing
actor-state owner at `0x2B2FC`. No incoming caller has been established; its
two consumed unsigned-halfword coordinates and halfword result describe the
chosen interface, with historical unused formals unresolved.

It calls the actual void dimensions provider with an ordinary `FramePoint`
output, then reads the selected halfword at `(x >> 5) + (y >> 5) *
(dimensions.x >> 5)`. A local address of the existing pointer owner is captured
before index calculation; its sole pointer read follows byte scaling. This
preserves the native value lifetimes without another memory observation,
register binding, qualifier or shared-header change.

The getter, dimensions provider and existing extra-map setter pass six
normal/strict complete matches and six genuine source controls in their separate
header contexts. Five interface checks and five meaningful wrong-contract
controls corroborate the actual owners and signatures. The getter's control
changes the x-cell shift from five to four and rejects by one byte.

The actual dimensions provider bounds width by an unsigned halfword times 32;
the getter's byte-offset arithmetic therefore fits signed 32 bits. It still
requires an initialized pointer, live aligned halfword backing and an in-bounds
selected cell. The startup allocation leaves 10,236 bytes after its four-byte
prefix, conditionally enough for 5,118 halfwords; this does not prove all input,
writer, lifetime or reachable-state populations. No new runtime or gameplay
evidence is added, and this getter is separate from the unrooted range predicate
at `0x2B25C`.
