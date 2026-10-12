#include "frame_animation.h"
void frame_decode_animation_commands(struct FrameObject *base)
{
    struct FrameAnimationObject *object = (struct FrameAnimationObject *)base;
    struct FrameAnimationState *animation;
    FrameU8 *commands;
    int continue_commands;
    object->flags &= ~0x400000;
    animation = &object->animation;
    commands = animation->commands;
    continue_commands = 1;
    do {
        if (commands[0] <= 0xf2) {
            animation->frame = commands[0];
            animation->delay = commands[1];
            return;
        }
        switch (commands[0]) {
        case 0xff:
            object->flags |= 0x400000;
            return;
        case 0xfe:
            animation->delay = 1;
            return;
        case 0xfd:
            commands = animation->commands = animation->command_start + commands[1] * 2;
            goto accept_jump;
        case 0xfc: {
            int position = object->next_position.x;
            int offset;
            if (object->display.flips.mirrored_x < 0)
                offset = (signed char)-commands[1] * 65536;
            else
                offset = (signed char)commands[1] * 65536;
            object->next_position.x = position + offset;
            goto advance;
        }
        case 0xfb: {
            int position = object->next_position.y;
            int offset;
            if (object->display.flips.mirrored_y < 0)
                offset = (signed char)-commands[1] * 65536;
            else
                offset = (signed char)commands[1] * 65536;
            object->next_position.y = position + offset;
            goto advance;
        }
        case 0xfa: {
            int velocity = commands[1] * 65536;
            if (object->display.flips.mirrored_x < 0)
                velocity = -velocity;
            object->velocity.x = velocity;
            goto advance;
        }
        case 0xf9: {
            int velocity = commands[1] * 65536;
            if (object->display.flips.mirrored_y < 0)
                velocity = -velocity;
            object->velocity.y = velocity;
            goto advance;
        }
        case 0xf6:
            audio_play_animation_cue(commands[1]);
            goto advance;
        case 0xf4: {
            int random = frame_random_bounded(100);
            if (random <= 14) {
                object->requested_animation = 2;
                goto request_animation;
            } else if (random <= 29) {
                object->requested_animation = 3;
                goto request_animation;
            } else {
                commands = animation->commands = animation->command_start + commands[1] * 2;
                goto accept_jump;
            }
        }
        case 0xf3:
            object->requested_animation = 1;
request_animation:
            object->flags |= 0x10;
            object->pending_updates |= 4;
            object->flags &= ~0x400000;
advance:
            commands = animation->commands += 2;
accept_jump:
            break;
        }
    } while (continue_commands);
}
