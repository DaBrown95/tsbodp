#include "frame_scene_player.h"
extern struct FrameVariantResource **g_frame_scene_effect_animations[];
void frame_scene_effect_refresh(struct FrameObject *base) {
 struct FrameActorObject *object=(struct FrameActorObject *)base;
 frame_set_animation_record(base,&g_frame_scene_effect_animations[object->actor_id][object->requested_animation][g_frame_actor_direction_variants[object->direction]]);
}
