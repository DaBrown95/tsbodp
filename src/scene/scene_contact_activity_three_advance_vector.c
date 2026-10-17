#include "scene_contact_activity_three.h"
void scene_contact_activity_three_advance_vector(struct FrameObject *base,int speed,unsigned int direction) {
 struct FramePoint movement;
 movement.x=frame_fixed_multiply(g_view_direction_vectors[direction].x,speed);
 movement.y=frame_fixed_multiply(g_view_direction_vectors[direction].y,speed);
 base->next_position.word.x=(int)((unsigned int)base->position.x+(unsigned int)movement.x);
 base->next_position.word.y=(int)((unsigned int)base->position.y+(unsigned int)movement.y);
}
asm(".align 2,0");
