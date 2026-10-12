#ifndef DISPLAY_SCENE_LIFECYCLE_H
#define DISPLAY_SCENE_LIFECYCLE_H
#include "frame_scene_motion.h"
#include "display_scene_setup.h"
/* Same RAM pointer slots, viewed as frame objects for the resource handoff. */
extern struct FrameObject *g_display_scene_frame_objects[];
extern struct FrameObject *display_allocate_text_object(const char **);
extern void display_text_update(struct FrameObject *, const char **);
extern int frame_schedule(struct FrameObjectList *, FrameU8);
extern void display_release_object_list(struct FrameObjectList *);
extern void display_reset(void), display_scene_stage_080117bc(void);
extern void display_scene_clear_object_slots(void), display_scene_close(void);
extern void display_scene_clear_detail_background(void);
extern struct FrameObject *display_scene_create_label(unsigned int, const char **);
extern void display_scene_refresh_item(struct FrameObject *);
extern void display_scene_retire_object_slot(unsigned int);
extern void display_allocate_object_tiles(struct FrameObject *, struct DisplayTileResource *);
extern void display_release_tile_bytes_immediately(FrameU16, FrameU32, FrameU8);
#endif
