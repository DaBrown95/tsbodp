#include "frame_actor_animation.h"
void frame_request_actor_animation(struct FrameCommandObject *object, FrameU8 animation)
{
 struct FrameActorAnimation *record;
 if (animation == object->requested_animation && !(object->pending_updates & 0x10)) return;
 switch (animation) {
 case 12: record = &g_frame_actor_animation_sets[object->subtype][2]; break;
 case 11: record = &g_frame_actor_animation_sets[object->subtype][3]; break;
 case 8: record = &g_frame_actor_animation_sets[object->subtype][2]; break;
 case 24: record = &g_frame_actor_animation_sets[object->subtype][2]; break;
 case 6:
  if (object->subtype == 31 && g_frame_actor_special_event == 1 && g_frame_world_id == 28)
   record = &g_frame_actor_animation_sets[object->subtype][2];
  else record = &g_frame_actor_animation_sets[object->subtype][0];
  break;
 case 14: record = &g_frame_actor_animation_sets[object->subtype][2]; break;
 case 10: case 27: record = &g_frame_actor_animation_sets[object->subtype][3]; break;
 case 19: case 20:
  if (object->subtype == 22 || object->subtype == 26 || object->subtype == 28)
   record = &g_frame_actor_animation_sets[object->subtype][2];
  else if (object->subtype == 19) record = &g_frame_actor_animation_sets[object->subtype][4];
  else return;
  break;
 case 40: record = &g_frame_actor_animation_sets[object->subtype][3]; break;
 case 42: record = &g_frame_actor_animation_sets[object->subtype][2]; break;
 case 45: case 46: record = &g_frame_actor_animation_sets[object->subtype][2]; break;
 case 47: record = &g_frame_actor_animation_sets[object->subtype][2]; break;
 case 50: record = &g_frame_actor_animation_sets[object->subtype][3]; break;
 case 23: case 59: record = &g_frame_actor_animation_sets[object->subtype][2]; break;
 case 65: record = &g_frame_actor_animation_sets[object->subtype][5]; break;
 case 56: record = &g_frame_actor_animation_sets[object->subtype][6]; break;
 case 89: record = &g_frame_actor_animation_sets[object->subtype][3]; break;
 case 90: record = &g_frame_actor_animation_sets[object->subtype][2]; break;
 case 92: record = &g_frame_actor_animation_sets[object->subtype][3]; break;
 case 91: record = &g_frame_actor_animation_sets[object->subtype][2]; break;
 case 93: record = &g_frame_actor_animation_sets[object->subtype][2]; break;
 case 94: record = &g_frame_actor_animation_sets[object->subtype][4]; break;
 case 95: record = &g_frame_actor_animation_sets[object->subtype][3]; break;
 case 96: record = &g_frame_actor_animation_sets[object->subtype][0]; break;
 case 98: record = &g_frame_actor_animation_sets[object->subtype][2]; break;
 case 99: record = &g_frame_actor_animation_sets[object->subtype][3]; break;
 case 100: record = &g_frame_actor_animation_sets[object->subtype][4]; break;
 case 101: record = &g_frame_actor_animation_sets[object->subtype][5]; break;
 case 102: record = &g_frame_actor_animation_sets[object->subtype][6]; break;
 case 1: default: record = &g_frame_actor_animation_sets[object->subtype][1]; break;
 }
 if (record) {
  frame_set_animation_record((struct FrameObject *)object, record->variants + g_frame_actor_direction_variants[((struct FrameObject *)object)->unknown_12[0]]);
  frame_set_animation_commands((struct FrameObject *)object, record->commands, 0);
  object->requested_animation = animation;
  object->flags |= 0x10;
  object->pending_updates |= 4;
  object->flags &= ~0x400000;
 }
}
asm(".align 2, 0");
