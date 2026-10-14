#ifndef DISPLAY_PALETTE_LIFECYCLE_H
#define DISPLAY_PALETTE_LIFECYCLE_H

struct PaletteRangeJob;
struct PaletteBufferPair;

/* Observed eight-byte prefix; complete resource ownership remains provisional. */
struct PaletteSequenceConfig {
    const unsigned short *palettes;
    unsigned char first, count, duration, interval;
};

unsigned int display_create_palette_range(unsigned int, unsigned int,
    unsigned int, unsigned int);
void display_reset_palette_range(struct PaletteRangeJob *);
void display_configure_palette_range(unsigned int, unsigned int, unsigned int);
void display_enable_palette_range(unsigned int);
void display_disable_palette_range(unsigned int, unsigned int);
void display_reset_palette_ranges(void), display_step_palette_ranges(void);
void display_reset_palette_blocks(void);
void display_reset_palette_jobs(void), display_step_palette_jobs(void);
unsigned int display_create_palette_sequence(unsigned int, unsigned int,
    unsigned int, unsigned int, unsigned int, const unsigned short *,
    unsigned int);
unsigned int display_create_palette_sequence_config(
    const struct PaletteSequenceConfig *, unsigned int, unsigned int);
void display_remove_palette_block(unsigned int);
void display_initialize_palette_pair(struct PaletteBufferPair *,
    unsigned short *);
void display_initialize_palettes(void);

/* Cached halfword written by initialization. The curve consumes the incoming
   low halfword and writes a byte lookup view; valid caller domains are unproven. */
extern short g_palette_curve_parameter;
void display_configure_palette_curve(unsigned int);

#endif
