#include "resource_actor_entries.h"
#include "frame_scene_restore.h"
struct FrameObject *actor_entry_restore_collection_effect(struct ActorEntryCollectionRecord *record) {
 struct FrameObject *object=frame_spawn_need_effect(record->entry.kind,record->entry.value1,record->entry.value2,record->entry.unknown03,1);
 struct FramePoint position;
 struct FrameSceneSavedEffectObject *effect=(struct FrameSceneSavedEffectObject *)object;
 effect->linked=1;
 frame_grid_cell_corner(g_frame_registration,(const int *)&record->unknown04,&position);
 frame_configure_need_effect(object,((unsigned char *)&record->unknown08)[0],(short)position.x,(short)position.y);
 effect->linked=0;
 return object;
}
asm(".align 2,0");
