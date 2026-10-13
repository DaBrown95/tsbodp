#ifndef FRAME_SCENE_ACTOR_SCHEDULE_H
#define FRAME_SCENE_ACTOR_SCHEDULE_H

struct FrameObject;
struct FramePoint;
struct DisplayTimeRecord;
/* The scheduler scans ids 18..41; the presence writers test only id > 17. */
extern unsigned char g_frame_scene_actor_presence[];
extern int g_frame_scene_actor_schedule_timer;
extern unsigned char g_frame_scene_actor_eligibility_enabled;
void frame_reset_scene_actor_schedule(void);
void frame_actor_note_spawn(unsigned int);
void frame_actor_note_remove(unsigned int);
void frame_set_scene_actor_eligibility(unsigned char);
void frame_refresh_scene_actor_schedule(unsigned int, const struct DisplayTimeRecord *);
unsigned char frame_scene_actor_find_exit(struct FrameObject *, struct FramePoint *);

#endif
