#include "frame_movement.h"
void frame_apply_movement_contact(struct FrameObject *object,unsigned int contact)
{
 unsigned int terrain;
 if(frame_movement_is_contact(contact)) {
  switch(((struct FrameMovementResponse *)object)->response) {
  case 0:break;
  case 1:
   object->next_position.word.x=object->position.x;object->next_position.word.y=object->position.y;
   frame_set_variant_state(object,2);break;
  case 2:
   ((struct FrameMovementDirection *)object)->direction=g_frame_movement_reverse_directions[((struct FrameMovementDirection *)object)->direction];
   ((struct FrameMovementPending *)object)->pending|=16;
   object->velocity.x=-object->velocity.x;object->velocity.y=-object->velocity.y;
   object->next_position.word.x=object->position.x;object->next_position.word.y=object->position.y;break;
  case 3:
   object->next_position.word.x=object->position.x;object->next_position.word.y=object->position.y;
   frame_redirect_movement(object,contact);break;
  case 4:
   object->next_position.word.x=object->position.x;object->next_position.word.y=object->position.y;
   frame_set_variant_state(object,5);break;
  }
 }
 terrain=frame_map_terrain_at((struct FramePoint){(short)(object->next_position.word.x >> 16),(short)(object->next_position.word.y >> 16)});
 ((struct FrameMovementResponse *)object)->terrain=terrain;
 if(terrain&1)object->flags|=0x4000;
 else object->flags&=~0x4000;
}
asm(".align 2, 0");
