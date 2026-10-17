#include "frame_collision_response.h"
void frame_scene_player_collision(struct CollisionObject *first,struct CollisionObject *second){struct FrameObject *object=(struct FrameObject*)first,*other=(struct FrameObject*)second;unsigned int limit=(unsigned int)((struct FrameCollisionRadius*)object)->radius<<16;if(view_point_distance(object->next_position.word,other->next_position.word)<=limit){other->velocity.x=0;other->velocity.y=0;other->next_position.word=other->position;frame_resolve_actor_contact(object,other);}}
asm(".align 2,0");
