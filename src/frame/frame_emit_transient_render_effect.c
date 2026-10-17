#include "frame_transient_emission.h"
void frame_emit_transient_render_effect(struct FrameTransientEffect *emitter)
{
    unsigned int direction_limit;
    struct FrameRenderEffect *effect;
    struct FramePoint origin,second;
    unsigned int radius;
    direction_limit=(emitter->owner->flags&0x20000000)?8:4;
    {
        struct FrameRenderEffect *allocated=(struct FrameRenderEffect *)frame_pool_allocate_08024d50(g_frame_render_effect_free_pool,(struct FrameObjectList *)&g_frame_render_effect_head,sizeof(*effect));
        if(++g_frame_render_effect_count>g_frame_render_effect_maximum)g_frame_render_effect_maximum=g_frame_render_effect_count;
        effect=allocated;
    }
    radius=emitter->unknown34;
    if(emitter->flags&0x200) {
        origin.x=((struct FrameRenderObject *)emitter->owner)->display.hardware.x;
        origin.y=((struct FrameRenderObject *)emitter->owner)->display.hardware.y;
    }
    else if((unsigned char)(emitter->phase-4)<=1) {
        int dx,dy,weight;
        if(!frame_read_attachment(emitter->owner,1,&origin)||!frame_read_attachment(emitter->owner,2,&second)) {
            frame_pool_release(g_frame_render_effect_free_pool,(struct FrameObjectList *)&g_frame_render_effect_head,(struct FrameObject *)effect);
            --g_frame_render_effect_count;
            return;
        }
        if(emitter->owner->unknown_12[0]>direction_limit) {
            origin.x=emitter->owner->next_position.word.x-origin.x*65536;
            second.x=emitter->owner->next_position.word.x-second.x*65536;
        }
        else {
            origin.x=emitter->owner->next_position.word.x+origin.x*65536;
            second.x=emitter->owner->next_position.word.x+second.x*65536;
        }
        origin.y=emitter->owner->next_position.word.y+origin.y*65536;
        second.y=emitter->owner->next_position.word.y+second.y*65536;
        dx=second.x-origin.x;
        dy=second.y-origin.y;
        weight=frame_random_secondary_range(0,65535);
        second.x=frame_fixed_multiply(dx,weight);
        second.y=frame_fixed_multiply(dy,weight);
        origin.x+=second.x;
        origin.y+=second.y;
        origin.x>>=16;
        origin.y>>=16;
    }
    else if(emitter->flags&0x1000) {
        unsigned char valid;
        if(emitter->flags&0x10000)valid=frame_part_attachment_position(emitter->owner,emitter->mode,emitter->unknown43,&origin);
        else valid=frame_read_attachment(emitter->owner,emitter->unknown43,&origin);
        if(!valid) {
            frame_pool_release(g_frame_render_effect_free_pool,(struct FrameObjectList *)&g_frame_render_effect_head,(struct FrameObject *)effect);
            --g_frame_render_effect_count;
            return;
        }
        origin.x>>=16;
        origin.y>>=16;
    }
    else if(emitter->flags&0x2000) {
        origin.x=((struct FrameTransientIntegerPoint *)&emitter->position)->x;
        origin.y=((struct FrameTransientIntegerPoint *)&emitter->position)->y;
    }
    else {
        origin.x=emitter->owner->next_position.halves.x_pixel;
        origin.y=emitter->owner->next_position.halves.y_pixel;
    }
    effect->origin.x=frame_random_secondary_range(origin.x-radius,origin.x+radius)*65536;
    effect->origin.y=frame_random_secondary_range(origin.y-radius,origin.y+radius)*65536;
    effect->countdown=emitter->height;
    effect->sprite.attributes.gfx_mode=0;
    effect->sprite.attributes.double_tile_size=0;
    if(emitter->flags&0x200)effect->sprite.attributes.layer=0;
    else if(emitter->flags&0x100)effect->sprite.attributes.layer=((struct FrameRenderObject *)emitter->owner)->display.oam.layer;
    else if(emitter->flags&0x4000)effect->sprite.attributes.layer=((struct FrameRenderObject *)emitter->owner)->display.oam.layer+1;
    else if(emitter->flags&0x400)effect->sprite.attributes.layer=((struct FrameRenderObject *)emitter->owner)->display.oam.layer-1;
    else effect->sprite.attributes.layer=2;
    effect->sprite.attributes.palette=emitter->kind;
    effect->tile_first=emitter->index;
    effect->resource=emitter->resource;
    if(emitter->flags&4)effect->animation_delay=3;
    else if(effect->countdown>=effect->resource->sequence->frame_count)effect->animation_delay=effect->countdown/effect->resource->sequence->frame_count;
    else effect->animation_delay=1;
    effect->frame=-1;
    effect->animation_ticks=0;
    effect->motion_mode=emitter->phase;
    effect->flags=emitter->flags;
    effect->sprite.attributes.size=emitter->unknown42;
    effect->sprite.attributes.shape=0;
    effect->indices=(unsigned short *)emitter->frames;
    effect->amplitude=emitter->offset_x;
    if(effect->flags&0x10)effect->phase_step=frame_random_secondary_range(-40,40);
    else effect->phase_step=emitter->offset_y;
    if(effect->flags&0x800)effect->phase=frame_random_secondary_range(0,255);
    else effect->phase=0;
    switch(effect->motion_mode) {
        case 0:
        effect->velocity.x=0;
        effect->velocity.y=0;
        effect->direction=emitter->owner->unknown_12[0];
        break;
        case 1: {
            const int *velocity;
            /* The byte address stays live across the two multiply calls. */
            register unsigned char *direction asm("r5");
            int rate;
            if(effect->flags&1) {
                effect->direction=g_frame_transient_cardinal_directions[emitter->direction];
                direction=&effect->direction;
                effect->unknown30=rate=emitter->rate;
                velocity=g_frame_transient_velocity_cardinal;
            }
            else if(effect->flags&0x20000) {
                effect->direction=g_frame_transient_extended_directions[emitter->direction];
                direction=&effect->direction;
                effect->unknown30=rate=emitter->rate;
                velocity=g_frame_velocity_extended;
            }
            else {
                effect->direction=g_actor_reverse_directions[emitter->direction];
                direction=&effect->direction;
                effect->unknown30=rate=emitter->rate;
                velocity=g_frame_velocity_default;
            }
            effect->velocity.x=frame_fixed_multiply(velocity[*direction*2],rate);
            {
                unsigned int offset=*direction*8;
                /* Advance from the x component to the y component. */
                ++velocity;
                effect->velocity.y=frame_fixed_multiply(
                    *(const int *)(offset+(unsigned int)velocity),
                    effect->unknown30);
            }
            effect->unknown34=effect->unknown30;
            break;
        }
        case 2:
        effect->direction=frame_random_secondary_range(0,7);
        effect->unknown30=emitter->rate;
        effect->unknown34=effect->unknown30;
        effect->velocity.x=frame_fixed_multiply(g_frame_velocity_default[effect->direction*2],effect->unknown30);
        effect->velocity.y=frame_fixed_multiply((g_frame_velocity_default+1)[effect->direction*2],effect->unknown30);
        break;
        case 3:
        effect->direction=emitter->direction;
        effect->unknown30=emitter->rate;
        effect->velocity.x=frame_fixed_multiply(g_frame_velocity_default[effect->direction*2],effect->unknown30);
        effect->velocity.y=frame_fixed_multiply((g_frame_velocity_default+1)[effect->direction*2],effect->unknown30);
        effect->unknown34=effect->unknown30;
        effect->motion_mode=1;
        break;
        case 4:
        effect->velocity.x=0;
        effect->velocity.y=0;
        effect->direction=emitter->owner->unknown_12[0];
        break;
        case 5:
        effect->direction=frame_random_secondary_range(0,7);
        effect->unknown30=emitter->rate;
        effect->unknown34=effect->unknown30;
        effect->velocity.x=frame_fixed_multiply(g_frame_velocity_default[effect->direction*2],effect->unknown30);
        effect->velocity.y=frame_fixed_multiply((g_frame_velocity_default+1)[effect->direction*2],effect->unknown30);
        break;
    }
}
asm(".align 2, 0");
