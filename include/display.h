/* Inferred layouts are supported by original field widths and offsets. */
struct DisplayCommitContext {
    unsigned char unknown_00[0x38];
    unsigned short commit_pending;
};
extern struct DisplayCommitContext *g_display_commit_context;
struct WindowState {
    unsigned int flags;
    unsigned char unknown_04[6];
    short horizontal_start;
    unsigned char unknown_0c[2];
    short vertical_start;
    unsigned char unknown_10[0x16];
    short horizontal_end;
    unsigned char unknown_28[2];
    short vertical_end;
    unsigned char unknown_2c[0x10];
};
extern struct WindowState g_window_states[2];
#define DISPLAY_REG16(a) (*(volatile unsigned short *)(a))
struct BackgroundState {
    unsigned short control;
    unsigned char unknown_02[6];
    void *tilemap_source;
    unsigned int unknown_0c;
    void *tilemap_destination;
    unsigned int unknown_14;
    unsigned int flags;
    int scroll_x, scroll_y;
    unsigned char unknown_24[0x2a];
    unsigned short pa, pb, pc, pd;
    short unknown_56;
    int reference_x, reference_y;
    unsigned char unknown_60[0x0c];
};
extern struct BackgroundState g_background_states[4];
struct DisplayControlState {
    unsigned int flags;
    unsigned short control;
};
extern struct DisplayControlState g_display_control;
extern void display_cpu_copy(const void *, void *, unsigned int);
struct PaletteBufferPair {
    unsigned short *staging;
    unsigned short *destination;
};
extern struct PaletteBufferPair g_palette_buffer_pairs[2];
struct PaletteRangeJob {
    unsigned char flags;
    unsigned char unknown_01[2];
    unsigned char source_first, destination_first, destination_last, count;
    unsigned char unknown_07;
};
struct PaletteBlockJob {
    unsigned char flags;
    unsigned char unknown_01[4];
    unsigned char first;
    unsigned char unknown_06;
    unsigned char count;
    unsigned char unknown_08[12];
};
struct PaletteQueueEntry {
    unsigned short first, count;
    const void *source;
};
extern struct PaletteRangeJob g_palette_range_jobs[12];
extern struct PaletteBlockJob g_palette_block_jobs[12];
extern struct PaletteQueueEntry g_palette_queue[18];
extern unsigned int g_palette_queue_count;
extern void display_commit_palette_range(struct PaletteRangeJob *);
extern void display_commit_palette_block(struct PaletteBlockJob *);
extern void display_transfer_palette(const void *, unsigned int, unsigned int, struct PaletteBufferPair *);
extern void *display_copy_bytes(void *, const void *, unsigned int);
struct DisplayPendingBlock {
    unsigned short pending;
    unsigned short unknown_02;
    unsigned char staging[0xb0];
    unsigned char queued[0xb0];
};
extern struct DisplayPendingBlock g_display_pending_block;
extern unsigned int g_display_pending_block_flag;
#define DISPLAY_REG32(a) (*(volatile unsigned int *)(a))
struct DisplayDmaRegisters {
    unsigned int source, destination, control;
};
#define DISPLAY_DMA3 ((volatile struct DisplayDmaRegisters *)0x040000d4)
extern unsigned int g_display_allocated_tiles[32], g_display_pending_free_tiles[32];
extern void display_mark_tiles_free(unsigned short, unsigned short);
struct DisplayTileResource;
extern void display_copy_tile_resource(struct DisplayTileResource *, unsigned short);
extern unsigned int display_find_tile_run(unsigned int *, unsigned int, unsigned int);
extern unsigned char g_display_tile_allocator_rom[], g_display_tile_allocator_ram[];
extern void *display_fill_bytes(void *, int, unsigned int);
extern void display_mark_tiles_allocated(unsigned short, unsigned short);
extern void display_release_tiles_immediately(unsigned short, unsigned short);
struct DisplayTileResource {
    const unsigned char *data;
    const unsigned char *layout;
};
struct DisplayTileRecord {
    unsigned char flags, unknown_01, width, height;
    unsigned short data_offset;
};
extern int display_bios_div(int, int);
extern void display_lz77_vram(const void *, void *);
extern void (*g_display_tile_decompress)(const void *, void *, unsigned int *);
extern void display_huffman(const void *, void *);
extern void (*g_display_background_decompress)(const void *, void *, unsigned int *);
struct BackgroundResource {
    unsigned char flags, palette_bank;
};
struct BackgroundResourceCodec {
    unsigned char unknown_low : 5;
    unsigned char codec : 2;
    unsigned char unknown_high : 1;
} __attribute__((packed));
extern void display_decode_background(const struct BackgroundResource *, const void *, int, void *);
extern unsigned int display_load_resource_palette(const struct BackgroundResource *, unsigned short);
struct BackgroundCharacterBase {
    unsigned char unknown_low : 2;
    unsigned char character_base : 2;
    unsigned char unknown_high : 4;
} __attribute__((packed));
extern const unsigned short *display_load_background_resource(unsigned int,
    const struct BackgroundResource *, unsigned short, unsigned short);
extern unsigned int g_palette_queue_words[];
struct DisplayTileLayout {
    unsigned char unknown_00[6];
    unsigned short count;
    unsigned char unknown_08[4];
    unsigned short record_offsets[1];
};
extern void (*g_display_tile_decompress_table[])(const void *, void *, unsigned int *);
/* Explicit interworking handoff; the target is passed in the fourth register. */
extern void display_call_decoder(const void *, void *, unsigned int *,
                                void (*)(const void *, void *, unsigned int *));
