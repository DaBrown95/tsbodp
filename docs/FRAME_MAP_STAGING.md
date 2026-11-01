# Copied ARM map staging

[`frame_stage_map_tiles`](../src/frame/frame_stage_map_tiles.c) owns 320 bytes
at ROM `0x0800B564`, linked for RAM `0x03007160`: 316 instruction bytes and one
four-byte literal. The installer copies 336 bytes, also including the first
sixteen bytes of the separately owned transfer routine. Source extents, copied
extents and runtime observations remain separate; this match adds 320 C bytes.

For each active map record, the function derives a cell and bounded staging
rectangle from the selected origin. Each cell selects a 32-byte payload and
copies four two-word groups to the four staging bands. Three source loads
advance the pointer; the final load does not. Row and record traversal, fresh
resource reads, signed coordinate division and unchecked input/backing
requirements follow the original bytes. Types, names, complete view-index
bounds and historical source spelling remain provisional.

Whole payload inputs define both words before their scalar projections and
partial output assignments. This removes eight otherwise emitted transfers.
The count and source-pointer inputs retain their native phases. Keeping the row
loop in one source function avoids the distinct caller/formal/result values
introduced by the failed helper representation. Actual primary-base, cell-byte
offset, coordinate and uncapped-row inputs restore the native address and
comparison producers without added observations or padding.

The last address was the key remaining allocation difference. One ordinary
pointer receives all three real staging-band destinations. Its three definitions
and three deaths remain one pseudo through allocation. Earlier source-pointer
conflicts therefore still constrain its final lifetime, selecting IP after the
source pointer's last use. Three independent address quantities instead let the
last address reuse R3. A hard-register declaration alone did not preserve this
history. The unchanged compiler and all original linked bytes judge the result.

The canonical default ARM profile, real seven-to-six row-cap control and full
ROM source control are separate acceptance gates. No assembly bytes, runtime
observations or independent executable-inventory closure are added. The wider
336-byte installation and the tile decoder's overlapping 24-byte copy retain
their existing mapping and incoming-entry uncertainties.

## Updater alias operands

The normal Thumb entry of
[`frame_update_map_view`](../src/frame/frame_update_map_view.c) masks its view
argument to eight bits. Of its eighteen direct global-store instructions, only
the origin pair at `0x08039B84/86`, with index four, can overwrite the drawer
and scroll slots at `0x03001FC8/CC`.

Native signed shifts first bound each coordinate to `[-32768,32767]`. The
[dimensions helper](../src/frame/frame_get_map_dimensions.c) writes distinct
stack words and derives dimensions from unsigned halfwords shifted by five,
or the fixed screen size. Signed clamps therefore produce X in
`[-240,32767]` and Y in `[-160,32767]`. The other direct global-store starts
lie in `0x03005F6C..0x03007068`; byte-index arithmetic neither wraps nor aliases the
two slots through an IWRAM mirror.

Consequently, this writer's own slot stores cannot supply direct game-ROM or
work-RAM operands: branch mode/alignment masking leaves address region `00`
or `FF`, outside work RAM `02/03` and Game Pak ROM `08..0D`. This assumes the
normal entry and fixed helper returns, a valid stack physically disjoint from
the slots and global data (including IWRAM mirrors), and no asynchronous
mutation during the checked flow. It makes no claim about BIOS/open-bus
behavior or later execution after these operands.

This resolves one named writer's direct-operand question. Other writers,
arbitrary interior entrances, reaching callback values and copied-code
integrity remain open. The 97 callback and 21 dispatch observations are
unchanged. No C bytes, executable entry or global target-domain closure are
added.
