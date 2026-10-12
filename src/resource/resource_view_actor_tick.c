#include "frame_actor_runtime.h"
#include "view_math.h"
#include "resource_view_actor.h"
#define ACTOR_FIELDS(o) ((struct FrameActorObject *)(o))
void resource_view_actor_tick(struct FrameObject *object)  {
    unsigned int direction,pending;
    frame_run_actor_state(object);
    direction=ACTOR_FIELDS(object)->direction;
    pending=ACTOR_FIELDS(object)->pending_updates;
    if(pending&8)frame_make_velocity(&ACTOR_FIELDS(object)->velocity,ACTOR_FIELDS(object)->flags,direction,ACTOR_FIELDS(object)->speed);
    if(pending&4)frame_set_animation_variant(object,1,g_frame_actor_direction_variants_signed[direction]);
    if(pending&0x12)  {
        if(ACTOR_FIELDS(object)->variant_state==3)  {
            frame_set_animation_variant(object,6,g_frame_actor_direction_variants_signed[direction]);
            frame_make_velocity(&ACTOR_FIELDS(object)->velocity,ACTOR_FIELDS(object)->flags,direction,ACTOR_FIELDS(object)->speed);
        }
        else  {
            frame_set_animation_variant(object,1,g_frame_actor_direction_variants_signed[direction]);
            ACTOR_FIELDS(object)->velocity.x=0;
            ACTOR_FIELDS(object)->velocity.y=0;
        }
    }
    if(direction>4)object->render_special=-1;
    else object->render_special=0;
    frame_update_actor_state(object);
    ACTOR_FIELDS(object)->pending_updates=0;
}
asm(".align 2, 0");
