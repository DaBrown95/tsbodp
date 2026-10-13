#include "frame_grid_selection.h"
void frame_need_effect_mark_attachment_running(struct FrameActorAttachmentOwner *owner,struct FrameObject *actor)
{
 struct FrameActorAttachmentRecord *record=frame_find_actor_attachment_record(owner,actor);
 if(record)record->running=1;
}
