#include "frame_need_effect_header_tick.h"
void frame_tick_header_attachment_jobs(struct FrameNeedEffectState *owner)
{
    struct FrameActorAttachmentRecord *first;
    if (frame_need_effect_attachment_count(owner) == 2) {
        struct FrameActorAttachmentRecord *second;
        unsigned int header;
        first = frame_need_effect_nth_attachment(
            owner, 1);
        second = frame_need_effect_nth_attachment(
            owner, 2);
        if (first->actor->id == 7) header = ((unsigned char *)first->actor)[0x0a];
        else header = ((unsigned char *)second->actor)[0x0a];
        if ((display_menu_relation_flags(g_need_effect_game_state + 0x30, header - 18) & 8) &&
                first->timer == 43 && second->timer == 43) {
            frame_request_animation((struct FrameCommandObject *)first->actor, 18);
            frame_request_animation((struct FrameCommandObject *)second->actor, 18);
            first->timer = 39;
            second->timer = 39;
            if (g_need_effect_game_state[0x20] == 0) audio_play_animation_cue(150);
            else audio_play_animation_cue(149);
        }
        if (first->timer == 40 || second->timer == 40) {
            first->timer = 1;
            second->timer = 1;
        }
    } else if (frame_need_effect_attachment_count(owner) == 1) {
        first = frame_need_effect_nth_attachment(
            owner, 1);
        if (first->timer == 43)
            frame_request_animation((struct FrameCommandObject *)first->actor, 50);
    }
}
asm(".align 2,0");
