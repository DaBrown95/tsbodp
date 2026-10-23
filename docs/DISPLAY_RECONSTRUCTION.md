# Display transfer and tile allocation evidence

These names and layouts are inferred from static accesses and callers. Matching
means compiled and linked bytes at the pinned USA/Europe revision 0 addresses;
no runtime or gameplay claim follows from these matches.

The VBlank wrapper calls the window register commit at `0x080486b8`, pending
block copy at `0x08046f84`, palette job commit at `0x080117e4`, queued palette
flush at `0x08011834`, and background register commit at `0x0800d3b0`. All five have exact C replacements.

`display_commit_windows` reads two 60-byte records at `0x03007460`; its four
signed coordinates come from offsets `0x0a`, `0x0e`, `0x26`, `0x2a`. It writes
WIN0/1 horizontal and vertical bounds after checking the commit context's
halfword at offset `0x38`, then clears the pending flag. The coordinate names
follow the hardware register destinations, not a recovered original type.

`display_flush_pending_block` copies `0xb0` bytes from offset `0xb4` to offset
`4` within the record at `0x03002250`, then clears its pending halfword and the
word at `0x03007388`. The connected VCount path below establishes the staged
row callback role; the full backing layout remains uncertain.

The pending-display module at `0x08046DD0..0x080470C0` now has complete
source-extent ownership: thirteen C bodies, 752 bytes, with no gaps or
overlaps. The [row view](../include/display_pending_block.h),
[mutation APIs](../include/display_pending_mutation.h) and
[scroll/IRQ providers](../include/display_pending_scroll.h) keep pools and
alignment within their independently compared extents.

Sixteen-byte rows contain a scanline halfword, two mutable state words and a
callback at offset 12. The VCount handler passes the two state-word addresses,
then advances or wraps at a null next callback. The default ROM row at
`0x0807FC1C` names the four-byte no-op at `0x08047080`. The default-reset
wrapper queues this row and calls the existing flag-polling VBlank wait.
The separate disable routine clears IE bit 2, acknowledges IF bit 2 and clears
DISPSTAT bit 5. Adjacent BG2/BG3 horizontal-scroll callbacks capture the prior
high state halfword, add the delta, wait for HBlank and write that prior value.
Their compatible ABI does not establish membership in the queued target domain.

The queue copies caller-supplied rows without a local count guard. Insertion
accepts an arbitrary callback, shifts rows and leaves the inserted state words
as carried storage; removal shifts after an unbounded line-equality search.
Both use the independently reconstructed [directional copy helper](HEAP_RECONSTRUCTION.md#directional-copy-used-by-pending-display-rows),
including its original backward-offset edge. The staged copy covers eleven
rows; reset writes twelve queued rows. The final reset record overlaps the
first twelve bytes of the tile-allocation bitmap at `0x030023B8`. These are
actual accesses, not safe caller counts, backing-capacity or exhaustive writer
proofs. Incoming aliases, counts, indices and callback targets remain open.

The latest [bounded route](RUNTIME_OBSERVATIONS.md#pending-display-storage-follow-up)
completes 128 selected renderer returns and counts 1,403 pending calls; eight
sampled tuples and 1,395 counted duplicates use index zero/default target
`0x08047081`. One BL/veneer/BX arrival pair confirms that transfer before the
target instruction retires. Actual guard checks, thirteen controls, seven
reporter negatives, byte-identical cold replay and displaced-watch state
agreement support this finite observation. Every source extent retains its
changed-source control. Bitmap aliases are data, and arbitrary writer, index,
count and target domains remain open; no C credit follows from the route.

The separate [controlled insertion fixture](RUNTIME_OBSERVATIONS.md#controlled-pending-row-copy-and-consumption)
starts from genuine initialization and calls the native insertion, flush and
VCount APIs. Inserting line 2, then line 1, with the ROM's default callback
shifts the first inserted row through the copy helper's backward-offset edge.
Its callback becomes `0x04708108` and its line becomes 512. Flush stages the
malformed row; two valid callbacks retire, then the consumer loads its malformed
target. The fixture stops before the indirect call. The count remains one and
does not bound callback traversal. Baseline, single-insertion, calibration,
budget and cold-replay checks pass. This closes one concrete writer-to-load
chain, without establishing a natural insertion caller, a valid malformed
target, hardware IRQ delivery or the complete writer/target domain.

Palette jobs have two observed layouts. The twelve range records are 8 bytes
at `0x030032f0`; the twelve block records are 20 bytes at `0x03003170`. Bit 1
marks a pending DMA3 transfer and bit 2 chooses the second 8-byte buffer pair
at `0x030018d0`. Byte fields encode source/destination indexes and halfword
counts. `display_commit_palette_jobs` traverses both arrays; the block commit
and range commit clear bit 1 before issuing DMA3. The range commit supports
a split transfer when source and destination starts differ. The staging and
destination pointer names reflect transfer direction; the palette name also
follows the connected resource palette loader and its 16/256-entry counts.

The frame release path calls `display_release_tile_bytes` at `0x08047924`.
Its mode selects 32- or 64-byte allocation units. It marks a deferred free
bitmap at `0x03002438`; the frame update calls `display_commit_tile_frees` at
`0x0804796c`, ANDs its 32 words into the allocation bitmap at `0x030023b8`,
and resets the deferred mask to all ones. Sentinel tile index `0xffff` is
ignored. The bit manipulation routines process aligned groups of eight when
possible and preserve partial first/last bytes. Immediate free modifies the
allocation bitmap directly; marking allocated ORs the same range into it.

The reset/configuration routines initialize these 128-byte masks. Modes 3
through 5 reserve the first half of the allocation mask. The allocator entry
at `0x080477b8` invokes a copied ARM search routine at `0x03007390`, marks the
returned range allocated, and optionally copies a tile resource. The installer
at `0x08047724` uses CpuSet to copy 50 words from `0x0800b77c` to that RAM
address. The validated 200-byte copy includes the first word of the following
frame-copy source at ROM `0xB840`; copy length is not a function boundary.
The copied ARM search routine now has an exact 196-byte semantic C replacement,
compiled in ARM mode and linked at its RAM execution address. Its installer
continues to copy the original 200-byte extent, including the separately explicit
word from the next region. The signed remaining count, zero/full-byte fast paths,
and bit-by-bit backtracking follow the original search behavior, including its
unaligned-byte fast paths. Four C register-bound locals preserve the ARM compiler
allocation; the labels express the run search without instruction assembly.
The pinned ARM compiler uses `-O2 -mthumb-interwork -fomit-frame-pointer`.
The caller supplies zero as the initial tile index; the failure sentinel is
`0xffff`. The standalone linked proof and a compiled changed-bound control
are preserved, independently of whole-ROM and runtime claims.

Background resource loading connects scene resource descriptors to the same
palette and display work. The descriptor begins with a flags byte and palette
bank byte. Flags 1/2 select a 512-byte full palette or 32-byte bank palette;
bit 4 describes character data, bit 3 an embedded dimension-prefixed map, and
bit 7 chooses 64-byte rather than 32-byte tile offsets. Codec bits 5-6 select
CpuSet, BIOS service `0x15`, BIOS service `0x12`, or an indirect callback stored
at `0x030036c0`. The old inferred LZ77/Huffman names were corrected after
checking the wrappers: `0x0804C8E4` issues service `0x15`, while `0x0804C8D8`
issues service `0x12`. Neutral service names keep this static evidence separate
from format identification.
The corrected declarations and all four calling sources were recompiled at
their pinned addresses: 100, 184, 124 and 100 bytes remain exact. Their actual
changed-source controls reject by three, one, one and one bytes respectively;
the new receipts are indexed locally by
`reports/agents/display_audio/background_motion/scene/redraw/bios-rename-proof.json`.
The background state's control bits 2-3 select the character base, shifted
by 14 into VRAM. These bit positions are verified by exact compiler matches;
the descriptor's semantic flags and dimensions remain inferred.

Each accepted replacement has a changed-source negative control. Raw expected
and generated bytes, linked objects, command records and useful failed source
attempts are retained in ignored `reports/agents/display_audio/` directories.
This document intentionally does not contain original instruction bodies.

The background configure routine at `0x0800d594` writes a full 32-bit control
word at offset 0 of each 108-byte state. Its low half is later sent to BGxCNT;
a named union preserves both observed widths. Bits 8-12 select the screen
base in 2 KiB units and bits 2-3 select the character base in 16 KiB units.
It initially points the map buffer and DMA destination at that screen base
and sets the pending-map bit. The display layer enable/disable routines at
`0x0800d68c`/`0x0800d670` update the display control's volatile 16-bit bitfield
and set bit 1 in the commit flags. The bitfield is inferred from the duplicate
halfword load before the store in both matching compiler outputs.

The now matching background commit at `0x0800d3b0` processes all four states.
Bits `0x10`, `0x40` select affine parameters/reference points and scroll
coordinates; the commit-context pending halfword gates these writes. Bit
`0x20` schedules BGxCNT, and the `0x30` condition schedules a CpuSet map copy.
The affine reference high halves retain only the low 12 bits. The display
control commit preserves DISPCNT bit 7 while applying the staged control.
Two C register-bound locals keep the preserved scroll pointer and reference
mask in the same registers as the compiler output; they contain no instruction
bodies. Integer MMIO address calculation preserves the compiler's evaluation
order for the vertical scroll write.

Frame updates also connect to tile uploads at `0x08047824` and `0x080478a0`.
The first reads an object's frame index at `0xdb`, resource pointer at `0xdc`,
byte count at `0xfc`, first tile at `0xfe`, and one signed flag bit at `0xd1`.
The latter takes the equivalent layout/source/index/count information as
arguments. Their shared descriptor codec helper at `0x0800a8fc` reads a
halfword offset table beginning at offset `0x0c`, then checks descriptor bits
`0x20` (BIOS service `0x15`) and `0x40` (custom callback). Raw uploads use
CpuFastSet; the
object's flag selects whether the byte count is halved first. Both calculate
the destination as `0x06010000 + first_tile * 32`. The custom callback slot is
`0x03003360`. The matching
[decoder installer](../src/resource/resource_install_decoders.c) writes
`0x030036D0` there; later assignments and copied-code writers remain open.

The initial tile resource copy at `0x0804766c` traverses the same offset table,
adds 12 to each relative offset, reads descriptor dimensions at bytes 2/3 and
source offset at halfword 4, and accumulates half the dimension product via the
BIOS divide wrapper. The original accumulation and CpuSet count expression
are preserved even where their higher-level units are unclear. A register-bound
C pointer to the callback slot preserves its load order before call arguments.
The calls continue through the explicit, unconverted interworking helper; its
bytes are outside C coverage. These uploads and the allocator form a connected
frame-display path, rather than independent utility matches.

`display_step_backgrounds` at `0x0800d17c` connects the synchronized transition
updates to register commits. It interpolates the position toward a target over
a halfword countdown, or applies the velocity vector when that count is zero.
It copies position into scroll coordinates, then applies sinusoidal offsets
through `display_offset_background` at `0x0800d4f0`. Scale motion clamps at its
limits and reverses the step; angle motion updates a phase. A dirty matrix bit
triggers sine/cosine fixed-point multiplication and reference centering around
120 by 80. It then clears matrix-dirty and sets affine-commit. Expanded state
fields at offsets `0x24` through `0x6a` follow these operations and their widths.
The countdown is explicitly re-read for both divisions, preserving observed
RAM loads; it is not assumed constant across calls.

The matrix wave adapters now own both complete 20-byte slots at `0x080272a8`
and `0x080272bc`, including two zero alignment bytes each. They convert the
phase to an unsigned byte, call the existing matching `frame_sine` or
`frame_cosine`, then arithmetic-shift by eight and narrow to signed 16 bits.
The source preserves the selected target's negative-shift and narrowing behavior;
for example, -1608 shifted by eight yields -7 before narrowing. Fresh normal and
strict pairs match; changing the shift to seven rejects each by one byte.
Target API checks compile the actual wrapper/provider `int(int)` definitions
alongside the background updater. All six direct providers of that updater now
have source, including the separately counted signed-division library assembly.
This does not close the renderer/finalizer or establish gameplay coverage.

The background map initializer at `0x0800d6c8` calls the character fill routine,
then fills the staged screen map with a tile/palette halfword through CpuSet.
A four-byte table at `0x0804f808` supplies the screen-block count indexed by
BGxCNT bits 14-15. The character-fill candidate at `0x0800d730` is still
unconverted. Character upload at `0x0800d7a4` uses the state's character
base pointer and doubles first/count for 256-color tiles before CpuSet.
The incrementing map rectangle at `0x0800d890` writes 16-bit tile indexes
across rows with a 32-entry stride; `0x0800d864` selects the background's map
destination. These provide a connected map initialization/upload/edit path.
The general dimension-prefixed map upload at `0x0800cefc` now has
[matching C](../src/display/background_map.c), described below.

The queued palette flush at `0x08011834` traverses 8-byte records at
`0x03003260`, using a halfword count at `0x03003160`, then resets the count.
Its transfer at `0x080119c8` copies a halfword range into the staging buffer
and immediately sends that range to the destination with DMA3. The selected
buffer pair is the second record at `0x030018d0`. The queue record carries
first/count halfwords and a source pointer; the addressing expression follows
the observed 8-byte stride. These close the queued palette path from VBlank
through staging copy and hardware transfer. The immediate transfer and flush
have separate compiled mutation controls.

The palette block lifecycle now has matching producers and management at
`0x080118dc` (create), `0x08011b90` (find free record), `0x08011bf8` (reset),
and `0x08011c18` (step active records). The 20-byte record fields follow its
initialization stores: duration/remaining at bytes 1/2, delay/interval at 3/4,
first/last/count at 5/6/7, palette count/index at 8/9, and palette pointers at
12/16. The free search returns 12 when all slots are active; the creator does
not add a bounds guard. The active count at `0x03003350` is updated by free
selection/reset. The manager preserves its observed `visited <= active_count`
condition. These static names do not establish safe behavior for exhausted
records. The per-record RGB interpolation at `0x08011c60` remains unconverted,
with its semantic candidate and raw comparison evidence retained locally.

The matching palette range step at `0x08011a74` rotates a range forward or
backward when its byte countdown expires. Flag `0x10` reverses at endpoints;
flag `0x20` selects direction. It schedules a transfer with flag 2 and reloads
the interval. Byte fields 1/2 are therefore named interval/delay, while byte 7
stores the original count in the producer. The allocation counter at
`0x03003164` increments without an observed limit in `0x08011a10`. The immediate
palette loader at `0x080116f8` selects the first buffer pair and calls the now
matching transfer. The scene-linked range descriptor loader at `0x08011634` now matches. Its
halfword count/header and four-byte entries are inferred from static accesses;
entry fields are first/count/delay/flags. It captures the initial zero index
for delay initialization, creates each job and sets its bit in the enabled-range
mask at `0x030032e0`. No bounds check is added to the observed counter path.

The scene resource group path now reaches the matching factory walker at
`0x0800a964`. The table root at `0x03002ed8` points to a halfword offset directory;
each selected group has a byte count and another halfword offset directory.
Each entry stores an object pointer at offset 0 and a factory index at 8. The
walker invokes the indexed function pointer in the ROM table at `0x0804f278`
only when the entry is empty, records the group/slot in object bytes `0x10/0x11`,
installs the default before-step callback at `0x08001ae0` when absent, and sets
object flag `0x80000000`. These names follow the connected scene group activator
at `0x0800ad98` and the existing frame object layout. Three C register-bound
locals preserve offset evaluation and factory-table scheduling without embedding
instructions. The interworking transfer helper remains explicit original glue.
Factory table targets and their higher-level roles remain provisional.

The renderer's dimensions lookup at `0x0800a938` reads the first two words from
12-byte records at `0x0804f1e8`, indexed with a 48-byte group stride and 12-byte
variant stride. The third word's meaning is not inferred here. Its dimension
name follows the connected frame renderer callers, rather than table adjacency.
The frame allocation coordinator's pixel accessor at `0x0800186c` reads the
resource/layout at object `0xdc`, frame index at `0xdb`, then the shared relative
frame offset table and halfword data offset. It returns a byte pointer into the
resource's data. An integer address accumulator preserves the original pointer
addition order; the inferred record layout is the same one used by the matching
tile upload functions. Descriptor accessors with no mapped callers remain
unconverted pending a connected use.

The connected palette producer at `0x08011718` appends a source pointer at
record offset 4 followed by first/count halfwords at offsets 0/2, then increments
the word queue count at `0x03003160`. The VBlank flush reads its low halfword
before clearing the word. Its byte-address accumulator and C register-bound
count pointer preserve the observed store order. The variant setter at
`0x08000be8` chooses this producer or the immediate second-buffer loader at
`0x08011708` according to the frame update flags. Both have matching C and
compiled mutation controls, connecting object palette selection to the same
VBlank queue and DMA transfer already reconstructed.

The scene/map producer at `0x0800da20` connects resource loading at `0x0800cd4c`
to the dimension-prefixed map writer at `0x0800cefc` when the resource supplies
a map. It returns that map pointer and preserves the two 16-bit tile/palette
arguments and destination coordinates. The general writer now has its own
complete match and changed-source control.

The constant rectangle writer at `0x0800d828` writes a fixed tile across signed
width/height ranges with a 32-entry screen-map stride. Its background selector at
`0x0800d7fc` uses the state's map destination at offset `0x10`. Its incoming tile
argument is a complete word; the provider explicitly consumes the low halfword
before selecting the background state. The later connected view-coordinator
proof corrected the earlier narrow formal without changing this 44-byte extent. Together they
complement the previously matching incrementing tile rectangle writer. The
palette rectangle selector at `0x0800d8e0` reaches the matching 92-byte C writer
at `0x0800d90c`, which preserves the low 12 map-entry bits and substitutes
the palette-bank bits. Both have independently verified matching C and actual
changed-source controls. Rectangle writers and the resource wrapper own
the two zero alignment bytes before the following entries, alongside their
58-byte instruction extents where applicable.

The target setter at `0x0800dd80` writes signed scroll coordinates to offsets
`0x34/0x38`, truncates its duration argument to the halfword at `0x3c`, and sets
flag 1. The already matching background frame step reads those same fields
for interpolation, connecting the producer and consumer. These names follow
that shared field use; the setters' game-level event meanings remain provisional.

`display_load_background_resource_dma` at `0x0800ce14` is the 232-byte alternate
resource transfer entry, paired with the 56-byte `display_load_background_dma`
coordinator at `0x0800da5c`. Unlike the palette-loading entry at `0x0800cd4c`, its
first stage advances over the embedded palette: flag 1 selects 512 bytes, flag
2 selects 32 bytes. Flag 4 uploads the length-prefixed block through DMA3, with
halfword count and enable bit `0x80000000`, including the original control
readback. Its remaining map header, tile-size selection and codec dispatch
agree with the existing resource decoder path. The coordinator supplies a map
to the matching `display_write_background_map` when the resource entry returns
one.

The C uses an inline character-bank address helper and register-bound locals
for the compiler's original address formation. These remain ordinary typed C
calculations, with no original instruction bodies or output changes. The full
232-byte comparison owns its two literal pools and its original return; the
coordinator owns all 56 bytes. Independently compiled changes to the DMA enable
bit and the coordinator's map-null condition reject the replacements. Local
failed variants and raw positive/control comparisons are retained under the
ignored display-agent reports. These are compiler and static-link findings;
no additional runtime or gameplay claim is made.

## Dimension-prefixed background map writer

`display_write_background_map` at `0x0800CEFC` owns its complete 640-byte
extent: 634 instruction bytes, four literal bytes and two alignment bytes.
It uses the existing four 108-byte background records and their canonical
map destination, control and flag fields. The display control prefix is
identified by its target 32-bit integer address, avoiding pointer arithmetic
before the background array.

The text path selects the native 32-by-32 screen blocks using the map dimensions
and BGxCNT size bits. The affine path reads and modifies partial halfwords
and writes paired bytes. Its paired iteration advances two source and destination bytes
but decrements the column count once, exactly as the native routine does.
Consequently a conventional width-times-height backing assumption is insufficient.
Defined inputs require index 0–3, aligned readable dimensions, backing for every
actual source read, destination read/modify/write and formed cursor, including
neighboring bytes touched by partial stores. Tile-offset carry and OR behaviour
follow the native routine; arbitrary offsets need not preserve that neighbor.
Text dimensions at most 64 and affine width at most the selected stride prevent
the corresponding unsigned
stride underflow; they do not establish the remaining backing requirements.

A short R0 row-address value is consumed before the later map-height and flags
loads. It crosses no call or competing R0 lifetime. The other register variables
retain the actual destination, stride and row lifetimes; no extra access or
instruction body is introduced. The writer and all five actual callers match
in separate normal and strict compilation contexts. Their twelve genuine
changed-source controls reject; changing the writer's dirty flag from `0x20`
to `0x10` changes one output byte. Target layout and API checks pass, and six
wrong contracts reject. These are static and compiler results; resource/input
populations, copied-RAM map workers and gameplay remain open.

The copied pass at ROM `0x0800b0e8`, installed by `0x0800109c` at
`0x03002a20`, now has 640 bytes of matching ARM C named
`frame_dispatch_collisions`. The scheduler at `0x08000618` invokes that copied
entry with an unsigned object count and an object-pointer table. The complete
extent ends in a return at RAM `0x03002c9c` and has no literal pool; its 640-byte
copy extent is also the independently compared function boundary here. The
installer and indirect caller establish the static RAM mapping, while the
byte comparison uses the RAM execution address and the physical ROM bytes.

The pass tests each object's bounds against later objects in the table and
calls the per-bound callbacks on overlap. Object offsets `0x22/0x26` supply
signed X/Y positions, `0xaf` supplies the bounds count, and `0xd3` bit `0x10`
mirrors horizontal endpoints. Six-byte records begin at `0xb0`; their four
coordinate bytes are interpreted as signed left/right/top/bottom endpoints,
followed by a signed kind byte whose zero value skips the record. The C keeps
an explicit two-halfword coordinate access view because the original performs
one unsigned and one signed halfword load, then extracts the four signed
bytes. The halfword packing uses an unsigned shift, preserving negative
endpoint bit patterns without shifting a negative signed C value.

Callback pointers begin at `0xc8`. The first-bound callback runs at most once for each later object even when
several of its bounds overlap; distinct first-bound callbacks can each run
once for that object. The later object's matching callback can run for each
overlap. The code rechecks active
flag `4` after callbacks and stops a bounds scan when the first object sets
flag `0x400`. Shared flag `0x20000` suppresses a pair; for a nonzero first-bound
index, the later object's flag `0x400` also suppresses the pair. Those bit
meanings follow this control flow and remain provisional beyond it. The
original byte index truncation and count-minus-one condition are retained;
no new bounds limit or empty-input guard is claimed.

The compiler profile is ARM `-O2 -mthumb-interwork -fomit-frame-pointer`.
Register-bound C values preserve offset, coordinate and rectangle lifetimes;
there is no instruction assembly in this replacement. A changed overlap test
from `<` to `<=` produces different linked bytes and rejects the replacement.
All failed layout, eligibility and reload variants, plus the complete positive
and changed-source raw comparisons, are retained locally. Existing collider
writer names and the higher-level meaning of the kind byte still require
connected evidence. This is static mapping and compiler evidence; no new
runtime or gameplay claim is made.

## Phase-15 menu display state

The phase-15 menu uses the partial state at `0x03002198`. Its existing code,
parameter and position arrays retain offsets 20, 25 and 30; the observed repeat
delay is an unsigned byte at offset 44. The C view has size 48 and alignment
four, ending at the next named catalog state. This does not establish an
original allocation boundary or the complete storage behind either owner.

The executor uses that real byte member and the existing window APIs. Three
text callers include their proper line-height, field-copy and window headers.
The new callbacks and affected layout importers retain complete matching
normal/strict outputs and meaningful changed-source controls; prototype-only
import reach is checked again by the fresh full gate. No instruction body or
output patch supplies the match.

The 736-byte step contains five two-byte compiler-emitted alignment spans.
The word at ROM `0xE40A40` carries `0x0803E8AF`; its bit-cleared value falls
inside one such span.
It now has a [source-backed compressed-map data role](WHOLE_ROM_INVENTORY.md#phase-15-pointer-shaped-map-word):
the original decoder model consumes its four bytes from scene-resource row 23's
`combined0` input. That data use and the source-owned padding at `0x03E8AE`
do not exclude other aliases or an alternate execution entry.

## Fixed transient tile input

The matching [phase-25 object initializer](../src/scene/scene_phase25_initialize_objects.c)
passes resource `0x08069510` to
[`frame_initialize_transient_definition`](../src/display/initialize_transient_definition.c).
Its two words identify data `0x08FD90B4` and layout `0x08FD93D4`.
The ten frame records have a summed pixel area of 2,240. The allocator receives
that area and requests 35 tiles, corresponding to 1,120 expected VRAM bytes.
Successful allocation causes
[`display_copy_tile_resource`](../src/display/copy_tile_resource.c) to traverse
all ten records; frames one through nine have custom-decoder flag `0x40`.

Frame one has dimensions 16 by 16 and data offset `0x80`, so its callback input
is `0x08FD9134` and its expected output is 128 bytes. The next frame starts at
`0x08FD91A4`, providing a conservative 112-byte input guard. This is a direct
sprite callback input, without an outer generic-stream header or four-byte skip.
The caller supplies a nonnull count-word address and ignores the callback's R0
result. Its destination is `0x06010000 + first_tile * 32 + 128`, after the raw
first frame.

The unchanged original-instruction model produces 128 bytes in 742 steps,
consumes the 112-byte input guard and preserves the trailing output guard.
Exact replay, five existing expected fixtures and three rejection controls pass.
All five backward-copy load sites execute, with ten reads of bytes already
written by decoder instructions. The five long-command parser observations have
length three and distances 4, 9, 38, 76 and 72; this fixed frame does not take
the extended-repeat branch. That branch has a separate expected fixture.
The model preloads the original parser instructions; it does not sample live
RAM code or execute the actual VRAM allocation.

A subsequent [controlled emulator fixture](RUNTIME_OBSERVATIONS.md#controlled-installed-tile-decoder-fixture)
uses the game's ordinary boot-installed code and the fixed input. It reproduces
the same 128 bytes in a chosen VRAM span, with actual parser-word readbacks,
guards and replay. Its private CPU/data setup and suspended events remain
separate from natural scene execution and the actual allocator.

This is a conditional source and native-instruction route to the installed tile
decoder. The queued scene request, phase/input selection, successful live VRAM
allocation, resource/layout views, callback and copied-code state must remain
valid. It does not establish natural scene execution, complete writer domains
or a matching C replacement for the 504-byte decoder.
