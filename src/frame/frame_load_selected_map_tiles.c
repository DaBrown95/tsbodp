#include "frame_map_scene.h"

/* Provisional serialized owner: 4-byte prefix, then 8-byte descriptors. */
struct FrameMapTileChunk {
    unsigned short codec, count;
    unsigned int offset;
};
struct FrameMapTileResource {
    unsigned short unknown0, chunk_tiles;
    struct FrameMapTileChunk chunks[0];
};
/* Decoded allocation must back count halfword indices after this prefix. */
struct FrameMapTileSelection {
    unsigned short count;
    unsigned short tiles[0];
};

static inline unsigned int frame_map_color_mode(unsigned int control)
{
    return (unsigned char)control >> 7;
}

static inline unsigned int frame_map_character_base(unsigned int control)
{
    return (unsigned char)(control << 4) >> 6;
}

static inline unsigned int scaled_map_chunk_bytes(unsigned int bytes,unsigned int color_mode)
{
 register unsigned int result asm("r2")=bytes<<color_mode;
 return result;
}

static inline unsigned int selected_map_destination_byte_offset(unsigned int control,unsigned int index)
{
 register unsigned int offset asm("r0")=(frame_map_character_base(control)<<14)+(index<<5);
 return offset;
}

/* Low word: unscaled width, then the existing fresh control observation.
 * High word: the actual background address. Each field is read only after its own assignment. */
struct FrameMapWidthControlWords {
    unsigned int value;
    const unsigned int *background;
};
typedef char frame_map_width_control_words_layout[
    (sizeof(struct FrameMapWidthControlWords)==8 &&
     __alignof__(struct FrameMapWidthControlWords)==4) ? 1 : -1];

/* Define both scalar address inputs before touching either tuple field.
 * Every field is assigned before its own read; no whole-object read occurs. */
struct FrameMapDmaTargetWords {
    volatile struct FrameMapDma *dma;
    const unsigned int *address;
};
typedef char frame_map_dma_target_words_layout[
    (sizeof(struct FrameMapDmaTargetWords)==8 &&
     __alignof__(struct FrameMapDmaTargetWords)==4) ? 1 : -1];

/* The same real background pointer is consumed before the scaled result phase. */
struct FrameMapScaleResultWords {
    const unsigned int *background;
    unsigned int bytes;
};
typedef char frame_map_scale_result_words_layout[
    (sizeof(struct FrameMapScaleResultWords)==8 &&
     __alignof__(struct FrameMapScaleResultWords)==4) ? 1 : -1];

/* The iterator step, selected descriptor and payload are successive decode phases. */
struct FrameMapChunkCursorWords {
    union {
        int step;
        const struct FrameMapTileChunk *descriptor;
    } cursor;
    const unsigned char *payload;
};
typedef char frame_map_chunk_cursor_words_layout[
    (sizeof(struct FrameMapChunkCursorWords)==8 &&
     __alignof__(struct FrameMapChunkCursorWords)==4 &&
     sizeof(struct FrameMapTileResource)==4 &&
     sizeof(struct FrameMapTileChunk)==8) ? 1 : -1];

/* Actual scan start and chunk sentinel, consumed before the first iteration. */
struct FrameMapInitialLoopWords {
    int scan_index;
    int chunk_sentinel;
};
typedef char frame_map_initial_loop_words_layout[
    (sizeof(struct FrameMapInitialLoopWords)==8 &&
     __alignof__(struct FrameMapInitialLoopWords)==4) ? 1 : -1];

void frame_load_selected_map_tiles(const struct FrameMapTileResource *resource,
                                  const void *selection_source,
                                  const struct FrameMapBackgroundControl *background)
{
    struct {
        unsigned int decoded_bytes;
        const struct FrameMapTileResource *source;
        const unsigned int *background;
        const struct FrameMapTileResource *layout;
    } work;
    register const void *selection_bytes asm("r4") =
        (work.source = resource, selection_source);
    struct FrameMapTileSelection *selection;
    register unsigned int chunk_bytes asm("sl");
    unsigned char *scratch;
    register int chunk_index asm("r9");
    register int chunk_last asm("r8");
    int index;

    work.background = (const unsigned int *)background;
    work.decoded_bytes = resource_decoded_size(selection_bytes);
    selection = heap_allocate(work.decoded_bytes);
    resource_decode_bytes(selection_bytes, selection);
    work.layout = work.source;
    {
        register struct FrameMapWidthControlWords width_control asm("r0");
        register struct FrameMapScaleResultWords scale_words asm("r1");
        {
            register unsigned int unscaled_width asm("r0")=work.layout->chunk_tiles;
            unscaled_width<<=5;
            width_control.value=unscaled_width;
        }
        chunk_bytes=width_control.value;
        {
            register const unsigned int *background_address asm("r1")=work.background;
            width_control.background=background_address;
        }
        {
            register const unsigned int *scale_address asm("r1")=width_control.background;
            scale_words.background=scale_address;
        }
        {
            register const unsigned int *scale_reader asm("r1")=scale_words.background;
            register unsigned int observed_control asm("r0")=*scale_reader;
            width_control.value=observed_control;
        }
        {
            register unsigned int scaled_width asm("r2")=
                chunk_bytes<<frame_map_color_mode(width_control.value);
            scale_words.bytes=scaled_width;
        }
        chunk_bytes=scale_words.bytes;
    }
    scratch = heap_allocate(chunk_bytes);
    {
        register struct FrameMapInitialLoopWords initial_words asm("r2");
        {
            register int chunk_sentinel asm("r3")=-1;
            initial_words.chunk_sentinel=chunk_sentinel;
        }
        chunk_index=initial_words.chunk_sentinel;
        chunk_last=chunk_index;
        {
            register int scan_start asm("r2")=0;
            initial_words.scan_index=scan_start;
        }
        index=initial_words.scan_index;
    }
    while (index < selection->count) {
        unsigned int tile = selection->tiles[index];
        unsigned int source_offset;
        if ((int)tile > chunk_last) {
            register const struct FrameMapTileChunk *chunk asm("r3");
            register const unsigned char *input asm("r4");
            register struct FrameMapChunkCursorWords cursor_words asm("r3");
            register unsigned int scaled_index asm("r0") =
                (unsigned int)chunk_index * sizeof(struct FrameMapTileChunk);
            register unsigned int descriptor_bytes asm("r1") =
                sizeof(struct FrameMapTileResource) + scaled_index;
            do {
                descriptor_bytes += sizeof(struct FrameMapTileChunk);
                {
                    register int step asm("r3")=1;
                    cursor_words.cursor.step=step;
                }
                chunk_index += cursor_words.cursor.step;
                {
                    register const struct FrameMapTileResource *layout_origin asm("r0")=work.layout;
                    chunk = (const struct FrameMapTileChunk *)
                        ((const unsigned char *)layout_origin + descriptor_bytes);
                    cursor_words.cursor.descriptor=chunk;
                    chunk=cursor_words.cursor.descriptor;
                }
                chunk_last += chunk->count;
            } while ((int)tile > chunk_last);
            {
                register unsigned int payload_offset asm("r0")=chunk->offset;
                register const unsigned char *payload_root asm("r1")=(const unsigned char *)work.source;
                input=payload_root+payload_offset;
                cursor_words.payload=input;
                input=cursor_words.payload;
            }
            switch (chunk->codec) {
            case 0:
                FRAME_MAP_DMA3->source = input;
                FRAME_MAP_DMA3->destination = scratch;
                {
                    unsigned int count = chunk->count;
                    register const unsigned int *control asm("r3") = work.background;
                    FRAME_MAP_DMA3->control = 0x80000000 |
                        (count * ((frame_map_color_mode(*control) + 1) << 4));
                }
                (void)FRAME_MAP_DMA3->control;
                break;
            case 1: resource_bios_swi_11(input, scratch); break;
            case 2: resource_bios_swi_13(input, scratch); break;
            case 3: resource_bios_swi_14(input, scratch); break;
            case 4:
                g_display_tile_decompress(input, scratch, &work.decoded_bytes);
                break;
            case 5: break;
            case 6:
                g_display_background_decompress(input, scratch, &work.decoded_bytes);
                break;
            }
        }
        source_offset = (unsigned int)scratch + (tile << 5) - chunk_index * chunk_bytes;
        {
            register volatile struct FrameMapDma *source_dma asm("r2")=FRAME_MAP_DMA3;
            source_dma->source=(const void *)source_offset;
            {
                register const unsigned int *background_address asm("r3")=work.background;
                register struct FrameMapDmaTargetWords target_words asm("r2");
                target_words.dma=source_dma;
                target_words.address=background_address;
                {
                register unsigned int background_control asm("r0")=*target_words.address;
                register unsigned int byte_offset asm("r0")=
                    selected_map_destination_byte_offset(background_control,index);
                {
                    register const unsigned int *video_base asm("r3")=(const unsigned int *)0x06000000;
                    target_words.address=video_base;
                }
                {
                    register volatile struct FrameMapDma *destination_dma asm("r2")=target_words.dma;
                    destination_dma->destination=(void *)((unsigned int)target_words.address+byte_offset);
                    destination_dma->control = 0x80000010;
                    (void)destination_dma->control;
                }
                }
            }
        }
        index++;
    }
    if (scratch) heap_free(scratch);
    if (selection) heap_free(selection);
}
