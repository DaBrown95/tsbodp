#include "display_need_effect_choices.h"
#include "frame_actor_action_target.h"
#include "frame_actor_social.h"
#include "frame_actor_state.h"

static inline struct FrameActorNeedState *actor_need_state(struct FrameObject *actor)
{
    struct FrameActorNeedState *state;
    __builtin_memcpy(&state, (const unsigned char *)actor + 0x60, sizeof state);
    return state;
}

unsigned char frame_find_need_target(struct FrameObject *actor, void **target,
                                    unsigned int *action)
{
    unsigned char actions[7];
    unsigned char low_needs[8];
    unsigned char count = 0;
    unsigned char i;
    for (i = 0; i < 8; i++) {
        if (frame_actor_need_value(actor_need_state(actor), i) <= 30) {
            low_needs[count] = i;
            count++;
        }
    }
    if (count) {
        unsigned char selected = frame_random_range(0, count - 1);
        struct FrameActionSearchNode *node =
            (struct FrameActionSearchNode *)g_frame_pending_action_head;
        while (node) {
            struct FrameActionSearchNode *next = node->next;
            if (g_frame_action_search_descriptors[node->kind].enabled &&
                (unsigned char)node->check((struct FrameNeedEffectState *)node, actor)) {
                unsigned char j;
                heap_clear(actions, 0, 7);
                node->actions((struct FrameNeedEffectState *)node, actions);
                for (j = 0; j < 7; j++) {
                    unsigned char code = actions[j];
                    if (code) {
                        if (g_need_effect_action_text[code].unknown_00 == selected) {
                            *target = node->target;
                            *action = code;
                            return 1;
                        }
                    } else {
                        break;
                    }
                }
            }
            node = next;
        }
    }
    return 0;
}

asm(".align 2, 0");
