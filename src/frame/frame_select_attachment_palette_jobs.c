#include "frame_actor_attachment_palette_jobs.h"

unsigned int frame_select_attachment_palette_jobs(struct FrameNeedEffectState *owner,
                                                   unsigned char *choices)
{
    choices[0] = 9;
    if (g_frame_interaction_settings.attachment_mode == 0)
        choices[1] = 8;
    else
        choices[1] = 11;
    choices[2] = 10;
    return 1;
}
asm(".align 2, 0");
