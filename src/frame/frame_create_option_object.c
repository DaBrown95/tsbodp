#include "frame_option_object.h"

struct FrameObject *frame_create_option_object(unsigned int kind,unsigned char direction,unsigned char option,short x,short y)
{
 struct FrameOptionObject *object=(struct FrameOptionObject *)frame_allocate_object(9);
 frame_set_position((struct FrameObject *)object,x<<16,y<<16);
 object->subtype=kind;object->kind=kind;
 object->direction=direction;object->option=option;
 frame_set_animation_record((struct FrameObject *)object,&g_frame_option_animation_sets[object->subtype].variants[0][g_frame_actor_direction_variants[object->direction]]);
 g_frame_option_definitions[object->subtype].configure((struct FrameObject *)object);
 object->on_step=frame_option_tick;
 object->oam.gfx_mode=0;object->oam.double_tile_size=0;
 object->speed=g_frame_option_definitions[object->subtype].speed;
 object->flags=0x10050655;
 object->field84=2;
 frame_update_actor_state((struct FrameObject *)object);
 if(object->direction>4)object->oam.flip_x=1;
 else object->oam.flip_x=0;
 if(object->subtype==0) { register unsigned char *counter asm("r1")=(unsigned char *)&g_resource_game_state; counter+=0x73e; (*counter)++; }
 return (struct FrameObject *)object;
}
asm(".align 2, 0");
