#include "display_menu_pages.h"
#include "display_menu_effects.h"
#include "frame_transient_effect.h"
#include "audio_game.h"

extern unsigned short frame_random_bounded(unsigned short);

static inline void place_menu_change(struct FrameTransientEffect *effect)
{
    effect->position.x = 208 << 16;
    effect->position.y = 32 << 16;
    effect->flags |= 8;
    effect->rate = 0x8000;
}

void display_menu_show_change(unsigned int kind)
{
    struct FrameTransientEffect *effect;
    if (kind == 6) {
        effect = frame_create_transient_effect(5, 0, 6);
        place_menu_change(effect);
    } else if (kind == 7) {
        effect = frame_create_transient_effect(6, 0, 7);
        place_menu_change(effect);
    } else if (kind == 4) {
        effect = frame_create_transient_effect(7, 0, 4);
        audio_play_animation_cue(17);
        effect->position.x = frame_random_bounded(240) << 16;
        effect->position.y = frame_random_bounded(100) << 16;
        effect->rate = 0;
    } else if (kind == 5) {
        effect = frame_create_transient_effect(8, 0, 5);
        audio_play_animation_cue(18);
        effect->position.x = frame_random_bounded(240) << 16;
        effect->position.y = frame_random_bounded(100) << 16;
        effect->rate = 0;
    } else
        effect = 0;
    if (effect) {
        effect->phase = 3;
        effect->flags |= 0x2182;
        effect->height = 60;
        effect->enabled = 1;
        effect->countdown = 1;
        effect->unknown34 = 0;
        effect->direction = 0;
        effect->offset_x = 5;
        effect->offset_y = 20;
        effect->owner = g_display_menu_objects.hint;
    }
}
asm(".align 2, 0");
