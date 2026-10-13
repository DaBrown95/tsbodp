#include "display_actor_interaction.h"

static inline unsigned int needs_above_limit(struct FrameActorNeedState *needs, unsigned int kind)
{
    register unsigned int result asm("r1");
    if (needs) {
        unsigned char value = frame_actor_need_value(needs, kind);
        result = 1;
        if (value > 99) goto done;
        result = 0;
    } else result = 1;
done:
    return result;
}
static inline unsigned int tick_timer(int *timer)
{
    register unsigned int result asm("r1") = 1;
    if (timer) result = --*timer != -1;
    return result;
}
unsigned int frame_step_attachment_need_timer(struct FrameActorAttachmentRecord *record,
                                              struct FrameActorNeedState *needs,
                                              unsigned int kind, int *timer)
{
    unsigned int result = 1;
    if (record->running == 1) result = 0;
    else if (kind <= 7) {
        result = needs_above_limit(needs, kind);
        if (result == 1) result = tick_timer(timer);
        else result = 1;
    }
    return result;
}
asm(".align 2, 0");
