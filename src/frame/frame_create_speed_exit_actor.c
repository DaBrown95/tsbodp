#include "frame_actor_runtime.h"
#include "frame_actor_state.h"
#include "frame_actor_speed_exit.h"
struct FrameObject *frame_create_speed_exit_actor(unsigned char direction,int x,int y)
{
 struct FrameObject *object=frame_allocate_object(13);
 frame_set_position(object,x,y);
 ((struct FrameActorObject *)object)->subtype=13;
 ((struct FrameActorObject *)object)->actor_id=13;
 ((struct FrameActorObject *)object)->direction=direction;
 frame_set_animation_record(object,&g_frame_actor_exit_resources[g_frame_actor_exit_variants[((struct FrameActorObject *)object)->direction]]);
 transition_object_set_state(object,0);
 frame_set_variant_state(object,7);
 object->on_step=frame_speed_exit_tick;
 ((struct FrameSpeedExitCallbacks *)object)->scratch=0;
 ((struct FrameSpeedExitCallbacks *)object)->on_interact=frame_speed_exit_interact;
 ((struct FrameActorObject *)object)->oam.gfx_mode=0;
 ((struct FrameActorObject *)object)->oam.double_tile_size=0;
 frame_acquire_palette_slot(object,((struct FrameActorExitPalette *)&g_resource_game_state)->palette);
 ((struct FrameActorObject *)object)->speed=0;
 object->flags=0x10040255;
 frame_update_actor_state(object);
 if(((struct FrameActorObject *)object)->direction>4) ((struct FrameActorObject *)object)->oam.flip_x=1;
 else ((struct FrameActorObject *)object)->oam.flip_x=0;
 return object;
}
asm(".align 2, 0");
