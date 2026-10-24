#include "frame_actor_attachment_counter_choices.h"

unsigned int frame_select_counter_attachment_choices(struct FrameNeedEffectState *owner,
                                                      unsigned char *choices)
{
    unsigned int count = 0;
    register union ResourceGameState *world asm("r1") = &g_resource_game_state;
    switch (world->scene.variant) {
    case 1:
        if (world->actor_values.value == 0) choices[count] = 19;
        else {
            register unsigned short *counter asm("r0") = &world->scene.counter.value;
            display_text_number_field_two(*counter);
            choices[count] = 68;
        }
        break;
    case 0:
        if (world->actor_values.value > 99) {
            display_text_number_field_two(100);
            count++;
            choices[0] = 69;
        }
        choices[count] = 20;
        break;
    }
    return 1;
}
