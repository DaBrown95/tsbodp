#ifndef TSBODP_DISPLAY_H
#define TSBODP_DISPLAY_H

/* Inferred layouts are supported by original field widths and offsets. */
struct DisplayCommitContext {
    unsigned char unknown_00[0x38];
    unsigned short commit_pending;
};
extern struct DisplayCommitContext *g_display_commit_context;
/* Two coordinate records follow each window's commit flags. */
union DisplayWindowFixedPoint {
    int position;
    struct { unsigned short fraction; short integer; } halves;
};
struct DisplayWindowAxis {
    unsigned short flags, duration;
    union DisplayWindowFixedPoint current[2];
    int step[2], target[2];
};
struct WindowState {
    unsigned int flags;
    struct DisplayWindowAxis axes[2];
};
extern struct WindowState g_window_states[2];
#define DISPLAY_REG16(a) (*(volatile unsigned short *)(a))
struct BackgroundState {
    union { unsigned int control_word; unsigned short control; } registers;
    union {
        unsigned char unknown_04[4];
        const unsigned short *map_pointer;
    } map_storage;
    void *tilemap_source;
    void *tilemap_buffer;
    void *tilemap_destination;
    void *character_destination;
    unsigned int flags;
    int scroll_x, scroll_y;
    int position_x, position_y, velocity_x, velocity_y, target_x, target_y;
    unsigned short scroll_duration;
    short scale, scale_step, minimum_scale, maximum_scale;
    unsigned short angle, angle_step;
    short center_x, center_y;
    unsigned short pa, pb, pc, pd;
    short unknown_56;
    int reference_x, reference_y;
    unsigned short phase_x, phase_y;
    short phase_step_x, phase_step_y, amplitude_x, amplitude_y;
};
extern struct BackgroundState g_background_states[4];
struct DisplayControlState {
    unsigned int flags;
    volatile unsigned int control : 16;
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
    unsigned char interval, delay;
    unsigned char source_first, destination_first, destination_last, count;
    unsigned char original_count;
};
struct PaletteBlockJob {
    unsigned char flags;
    unsigned char duration, remaining, delay, interval;
    unsigned char first, last, count, palette_count, palette_index;
    unsigned char unknown_0a[2];
    const unsigned short *palettes, *target;
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
extern unsigned int display_find_tile_run(const unsigned char *, int, unsigned int);
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
extern void display_bios_swi_15(const void *, void *);
extern void *(*g_display_tile_decompress)(const void *, void *, unsigned int *);
extern void display_bios_swi_12(const void *, void *);
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
extern void display_configure_background(unsigned int, unsigned int);
extern void display_enable_layers(unsigned short);
extern void display_disable_layers(unsigned short);
extern unsigned char display_tile_resource_codec(const struct DisplayTileLayout *, unsigned short);
extern void display_cpu_copy_fast(const void *, void *, unsigned int);
struct DisplayTileObject {
    unsigned char unknown_00[0xd1];
    unsigned char unknown_d1_low : 5;
    signed char double_tile_size : 1;
    unsigned char unknown_d1_high : 2;
    unsigned char unknown_d2[9];
    unsigned char frame_index;
    struct DisplayTileResource *resource;
    unsigned char unknown_e0[0x1c];
    unsigned short bytes, first_tile;
};

struct DisplayPoint { int x, y; };
extern int display_divide(int, int);
extern int display_matrix_sine(int), display_matrix_cosine(int);
extern int display_fixed_multiply(short, short);
extern int display_scroll_sine(int), display_scroll_cosine(int);
extern void display_add_point(struct DisplayPoint *, const struct DisplayPoint *, struct DisplayPoint *);
extern void display_offset_background(unsigned int);
extern const unsigned char g_display_screen_block_counts[4];
extern void display_fill_background_tile(unsigned int, unsigned short, unsigned short);
extern void display_write_incrementing_map_rectangle(void *, int, int, int, int, unsigned short);

extern unsigned int g_palette_block_count;
extern void *display_set_bytes(void *, int, unsigned int);
extern unsigned int display_find_palette_block(void);
extern void display_step_palette_block(struct PaletteBlockJob *);
extern void display_step_palette_blocks(void);
extern void display_reset_palette_block(struct PaletteBlockJob *);
extern unsigned int display_create_palette_block(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, const unsigned short *);

struct PaletteRangeConfigEntry { unsigned char first, count, delay, flags; };
struct PaletteRangeConfig { unsigned short count, unknown_02; struct PaletteRangeConfigEntry entries[1]; };
extern unsigned int g_palette_range_count, g_palette_range_enabled_mask;
extern unsigned int display_next_palette_range(void);
extern void display_load_palette_ranges(const struct PaletteRangeConfig *);
extern void display_load_palette(const void *, unsigned int, unsigned int);
extern void display_step_palette_range(struct PaletteRangeJob *);
extern const unsigned char g_display_sprite_dimensions[];
extern void display_sprite_dimensions(unsigned int, unsigned int, struct DisplayPoint *);
extern const unsigned char *display_object_tile_pixels(struct DisplayTileObject *);
extern void display_load_palette_alternate(const void *, unsigned int, unsigned int);
extern void display_queue_palette(const void *, unsigned int, unsigned int);
extern void display_write_background_map(unsigned int, const unsigned short *, unsigned short, unsigned short, unsigned int, unsigned int);
extern void display_write_constant_map_rectangle(void *, int, int, int, int, unsigned short);
extern void display_write_map_palette_rectangle(void *, int, int, int, int, unsigned short);
extern const unsigned short *display_load_background_resource_dma(unsigned int,
    const struct BackgroundResource *, unsigned short);

#endif /* TSBODP_DISPLAY_H */
