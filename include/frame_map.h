#ifndef FRAME_MAP_H
#define FRAME_MAP_H

#include "frame.h"
#include "resource_decode.h"
#include "heap.h"

/* Partial map views inferred from the allocation and cell-access path. */
struct FrameMapRecord {
    const void *source;
    void *primary, *combined, *secondary;
    unsigned int unknown10;
    unsigned short width, height;
    unsigned char unknown18[0x900 - 0x18];
};
struct FrameMapStore {
    void *default_resource;
    struct FrameMapRecord views[2];
};
extern struct FrameMapStore g_frame_map_store;
extern struct FrameMapRecord g_frame_map_records[];
extern struct FramePoint g_frame_view_origins[];
extern struct FramePoint g_frame_default_view_origin;

void frame_set_view_origin(struct FramePoint *, unsigned char);
void frame_get_map_dimensions(struct FramePoint *);
void frame_get_alternate_map_dimensions(struct FramePoint *);
void frame_load_map_resources(unsigned int, const void *, const void *);
void frame_load_combined_map_resource(unsigned int, const void *, const void *);
unsigned short *frame_map_cell(unsigned int, unsigned int, unsigned int);
void frame_write_map_cell(unsigned int, unsigned short, unsigned short, unsigned int);
void frame_release_map_resources(void);
unsigned short display_get_mode(void);


void frame_set_map_sources(const void *, const void *);
void frame_snapshot_map_vram(void);
void frame_restore_map_vram(void);
void frame_install_map_routines(void);
/* Provisional one-argument copied ARM routines; installed bodies remain original. */
extern void (*g_frame_map_draw_routine)(unsigned int);
extern void (*g_frame_map_scroll_routine)(unsigned int);
extern unsigned char g_frame_map_draw_rom[], g_frame_map_draw_ram[];
extern unsigned char g_frame_map_scroll_rom[], g_frame_map_scroll_ram[];

#endif
