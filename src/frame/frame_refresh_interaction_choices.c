#include "display_need_effect_choices.h"
#include "frame_actor_action_target.h"

int frame_refresh_interaction_choices(void)
{
    unsigned char choices[7];
    int result = 0;
    struct FrameActionSearchNode *node =
        (struct FrameActionSearchNode *)g_frame_pending_action_head;
    while (node) {
        struct FrameActionSearchNode *next = node->next;
        if (g_frame_action_search_descriptors[node->kind].enabled) {
            unsigned char i;
            unsigned char *selection;
            heap_clear(choices, 0, 7);
            node->actions((struct FrameNeedEffectState *)node, choices);
            i = 0;
            selection = node->unknown58 + 4;
            goto scan;
advance:
            i++;
scan:
            if (i <= 6) {
                unsigned char code = choices[i];
                if (code) {
                    if (code == 12 || code == 27 || code == 45 || code == 22) {
                        result = 1;
                        *selection = code;
                    } else {
                        goto advance;
                    }
                }
            }
        }
        node = next;
    }
    return result;
}
