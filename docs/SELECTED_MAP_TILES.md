# Selected-map tile loader

[`frame_load_selected_map_tiles`](../src/frame/frame_load_selected_map_tiles.c)
owns ROM `0x39CF0..0x39E78`: **392 C extent bytes**, including literal pools
and alignment. Names and serialized record interpretations remain provisional.
The census accounts for 334 instruction, 52 referenced-data and six alignment
bytes. The three alignment halfwords match the compiler's directives, but
remain in the census's unclassified-role set; current emitted provenance does
not exclude historical alternate entries.

The routine decodes a selection into an allocation, derives a chunk width from
the resource and background control, then walks the selected halfword tile
indices. The chunk cursor advances until its accumulated boundary covers the
tile. Codec cases select DMA, BIOS decoders or the existing decoder callbacks;
case 5 retains its original empty branch. A final DMA copies each selected tile
to its computed background destination. Allocation/free paths, fresh control
observations and the original source-offset arithmetic remain unchanged.

The source gives actual successive values explicit owners: unscaled width and
control, background address and scaled width, initial scan and sentinel,
descriptor step/pointer and payload, and DMA destination inputs. Every field
is assigned before its own read. There is no whole read of a partly initialized
object, added observation or pressure-only value. No unset-value BUG exception
is needed.

The descriptor byte offset progresses independently of the numeric chunk
counter. This preserves the native recurrence while the two real counters use
their native R9/R8 lifetimes. The background/scale object retains the R2 shift
producer; the initial-state object retains the R3 sentinel. These relations
also preserve the shared outer-loop guard. Register declarations contain no
instruction templates or embedded instruction data.

The pinned compiler's default Thumb flags reproduce all 392 linked bytes at
the original entry. Changing the final DMA control from `0x80000010` to
`0x8000000F` changes the original extent's byte 388. The maintained component
controls, full-ROM equality and whole-ROM changed-source control pass.

This removes one known source-backlog row. It establishes no new runtime
execution, complete callback population or executable-inventory closure.
Serialized backing, selector/writer domains and historical interfaces remain
separate questions; see [remaining work](COMPLETION_BLOCKERS.md).
