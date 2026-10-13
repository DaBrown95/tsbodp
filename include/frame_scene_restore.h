#ifndef FRAME_SCENE_RESTORE_H
#define FRAME_SCENE_RESTORE_H

struct FrameObject;
struct FramePoint;
struct ActorEntryContext;
struct ActorEntryCollectionRecord;
/* Partial effect view used while restoring a saved packed-cell record. */
struct FrameSceneSavedEffectObject {unsigned char unknown00[0x83],linked;};
void actor_entry_mark_scene_collection(struct ActorEntryContext *,unsigned int);
void actor_entry_restore_scene_collection(struct ActorEntryContext *,unsigned int);
struct FrameObject *actor_entry_restore_collection_effect(struct ActorEntryCollectionRecord *);
struct FrameObject *frame_spawn_need_effect(int,int,int,int,int);
extern void *g_frame_registration;
unsigned char frame_grid_cell_corner(void *,const int *,struct FramePoint *);
unsigned char frame_configure_need_effect(struct FrameObject *,int,int,int);

#endif
