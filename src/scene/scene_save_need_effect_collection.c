#include "display_need_effect_lifecycle.h"
#include "resource_condition_entries.h"
#include "frame_actor_state.h"
#include "resource_need_effect_collection.h"
union SceneNeedEffectSnapshotAxis {int value;short half[2];};
struct SceneNeedEffectSnapshotActor {
 unsigned char unknown00[18],direction,unknown13[5];
 union SceneNeedEffectSnapshotAxis x,y;
};
struct SceneNeedEffectSnapshotRecord {
 struct ConditionActorEntry entry;
 struct FrameActorPackedCell cell;
 unsigned char direction,unknown09[3];
};
union SceneNeedEffectSnapshotRecordBytes {
 struct SceneNeedEffectSnapshotRecord fields;
 struct ActorEntrySavedRecordBytes representation;
};
void scene_save_need_effect_collection(unsigned char *context,unsigned int group)
{
 union SceneNeedEffectSnapshotRecordBytes record;
 struct FramePoint point;
 struct DisplayNeedEffectStateView *state=(struct DisplayNeedEffectStateView *)g_frame_need_effect_active_list.first;
 while(state) {
  if(state->enabled) {
   record.fields.entry.kind=state->kind;
   record.fields.entry.value1=state->optional;
   record.fields.entry.value2=(short)state->parameter>>8;
   record.fields.direction=((struct SceneNeedEffectSnapshotActor *)state->object)->direction;
   point.x=((struct SceneNeedEffectSnapshotActor *)state->object)->x.half[1];
   point.y=((struct SceneNeedEffectSnapshotActor *)state->object)->y.half[1];
   frame_grid_point_to_cell(g_frame_registration,&point,&record.fields.cell);
   record.fields.entry.unknown03=state->mode;
   actor_entry_save_collection_record((struct ActorEntryContext *)context,group,&record.representation);
  }
  state=(struct DisplayNeedEffectStateView *)state->next;
 }
}
