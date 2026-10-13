#include "view_effects.h"
#include "view_motion_step.h"
static inline unsigned int view_effect_phase(const struct ResourceViewEffect *effect) {
    register unsigned int value asm("r0")=effect->phase;
    return value;
}
#define HIGH_SHORT(value) (*((short *)&(value)+1))
union ViewFixedCoordinate {
    int word;
    struct {
        unsigned short fraction;
        short integer;
    } halves;
};
/* The complete word initializes both halves before the signed high-half read. */
static inline int view_high_value(int word) {
    union ViewFixedCoordinate value;
    value.word=word;
    return value.halves.integer;
}
void transition_step_view(unsigned char view_index) {
    unsigned char mode;
    unsigned char *mode_pointer;
    struct ResourceViewEffect *effect;
    register unsigned int offset asm("r9");
    struct FramePoint delta,current;
    struct FrameObject *view=(struct FrameObject *)g_transition_view_context.views[view_index].object;
    switch(g_resource_view_motion[view_index].mode) {
        case 0:
        if(g_resource_view_motion[view_index].interpolate==1) {
            struct FrameObject *tracked=g_resource_view_motion[view_index].object;
            short *high_position=(short *)&g_resource_view_motion[view_index].position;
            delta.x=tracked->position.x-g_resource_view_motion[view_index].position.x;
            delta.y=g_resource_view_motion[view_index].object->position.y-g_resource_view_motion[view_index].position.y;
            delta.x&=0x0fffffff;
            delta.y&=0x0fffffff;
            if(delta.x<=0x1ffff)g_resource_view_motion[view_index].position.x=g_resource_view_motion[view_index].object->position.x;
            else {
                struct FrameObject *tracked_x=g_resource_view_motion[view_index].object;
                int saved_high=high_position[1];
                int tracked_high=HIGH_SHORT(tracked_x->position.x);
                g_resource_view_motion[view_index].position.x=((saved_high+tracked_high)/2)<<16;
            }
            if(delta.y<=0x1ffff)g_resource_view_motion[view_index].position.y=g_resource_view_motion[view_index].object->position.y;
            /* Sequence the actual object-pointer capture before the saved Y read. */
            else g_resource_view_motion[view_index].position.y=(tracked=g_resource_view_motion[view_index].object,((view_high_value(g_resource_view_motion[view_index].position.y)+HIGH_SHORT(tracked->position.y))/2)<<16);
        }
        else {
            g_resource_view_motion[view_index].position.x=g_resource_view_motion[view_index].object->position.x;
            g_resource_view_motion[view_index].position.y=g_resource_view_motion[view_index].object->position.y;
        }
        break;
        case 1:break;
        case 2:
        if(transition_approach_view(g_resource_view_motion[view_index].target,g_resource_view_motion[view_index].speed,view_index)==8)g_resource_view_motion[view_index].mode=3;
        break;
        case 3:
        if(--g_resource_view_motion[view_index].delay==0xffff) {
            g_resource_view_motion[view_index].mode=4;
            g_resource_view_motion[view_index].target.x=g_resource_view_motion[view_index].object->position.x;
            g_resource_view_motion[view_index].target.y=g_resource_view_motion[view_index].object->position.y;
        }
        break;
        case 4:
        if(transition_approach_view(g_resource_view_motion[view_index].target,g_resource_view_motion[view_index].speed,view_index)==8) {
            {
                register unsigned int tracking_mode asm("r0")=0;
                g_resource_view_motion[view_index].mode=tracking_mode;
            }
            g_resource_view_effects[view_index].mode=0;
        }
        break;
        case 5: {
            offset=view_index*sizeof(struct ResourceViewEffect);
            effect=(struct ResourceViewEffect *)((unsigned char *)g_resource_view_effects+offset);
            mode_pointer=&effect->mode;
            mode=*mode_pointer;
            if(mode==1) {
                if(effect->object!=view||!effect->phase) {
                    if(transition_approach_view(effect->object->position,(*(int *)((unsigned char *)g_resource_view_effects+offset+0x14)),view_index)==8) {
                        unsigned int phase=view_effect_phase(effect);
                        if(!phase) {
                            if(effect->object==view) {
                                *mode_pointer=phase;
                                view->velocity=effect->saved_velocity;
                                frame_set_variant_state(view,effect->variant);
                                g_resource_view_motion[view_index].mode=phase;
                                *mode_pointer=0;
                            }
                            if(!effect->flags) {
                                effect->flags=mode;
                                resource_activate_groups(effect->group_a,effect->group_b);
                            }
                            effect->elapsed=phase;
                        }
                        else {
                            effect->phase--;
                            g_resource_view_motion[view_index].position=effect->object->position;
                        }
                    }
                }
                else effect->phase--;
            }
            else if(mode==3) {
                if(!effect->ready) {
                    register int *counter asm("r0")=(int *)((unsigned char *)g_resource_view_effects+offset+0x18);
                    int previous=(*counter)--;
                    if(!previous) goto expired;
                }
                view_copy_point(&g_resource_view_motion[view_index].object->position,&current);
                view_subtract_point(&current,&g_resource_view_motion[view_index].position,&delta);
                g_resource_view_motion[view_index].position.x=current.x;
                g_resource_view_motion[view_index].position.y=current.y;
                {
                    if ((unsigned int)effect->phase++ << 16) {
                        effect->phase=0;
                        {
                            register unsigned int address_offset asm("r0")=offset;
                            int *parameter=(int *)((unsigned char *)g_resource_view_effects+address_offset+0x14);
                            *parameter=-*parameter;
                        }
                    }
                    g_resource_view_motion[view_index].position.y+=(*(int *)((unsigned char *)g_resource_view_effects+offset+0x14))*effect->phase;
                }
                break;
                expired: {
                    *mode_pointer=0;
                    resource_activate_groups(effect->group_a,effect->group_b);
                    audio_game_stop_sample(g_resource_view_sound);
                }
            }
            break;
        }
    }
}
asm(".align 2, 0");
