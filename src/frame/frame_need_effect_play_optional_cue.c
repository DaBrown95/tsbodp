#include "frame_need_effect_optional.h"

void frame_need_effect_play_optional_cue(struct FrameNeedEffectState *state)
{
    switch (state->kind) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 43:
    case 44:
    case 45:
    case 49:
    case 89:
    case 104:
    case 106:
    case 107:
    case 108:
    case 112:
        audio_play_animation_cue(36);
        break;
    case 69:
    case 71:
    case 73:
    case 105:
    case 109:
    case 110:
    case 111:
    case 114:
    case 115:
        audio_play_animation_cue(37);
        break;
    default:
        break;
    }
}

asm(".align 2, 0");
