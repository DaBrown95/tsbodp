#include "scene_contact_activity_four_auxiliary.h"

#define STATE ((struct SceneContactActivityFourEventState *)g_scene_contact_state)

void scene_contact_activity_four_step_auxiliary_object(struct FrameObject *argument)
{
    register struct FrameObject *object asm("r4");
    unsigned int selected;

    object = argument;
    selected = STATE->current;
    if (!(g_scene_contact_state->flags & 2)) {
        if (g_input_pressed[0] & 0x280) {
            if (!selected)
                selected = 7;
            else
                selected--;
        } else if (g_input_pressed[0] & 0x140) {
            if (selected > 6)
                selected = 0;
            else
                selected++;
        }
        if (STATE->current != selected) {
            STATE->current = selected;
            if (!(selected & 3) || (selected & 3) == 3)
                frame_set_animation_frame((struct FrameTickObject *)object, 0);
            else
                frame_set_animation_frame((struct FrameTickObject *)object, 1);
            {
                unsigned int selected = STATE->current;
                register unsigned int shifted asm("r3");
                struct SceneContactAuxiliaryFlagPrefix *view =
                    (struct SceneContactAuxiliaryFlagPrefix *)object;

                shifted = selected >> 1;
                if (selected > 3)
                    view->flags.flag4 = -1;
                else
                    view->flags.flag4 = 0;
                {
                    register struct SceneContactAuxiliaryFlagByte
                        *flags asm("r2");

                    flags = &view->flags;
                    if (((shifted & 3) - 1) <= 1)
                        flags->flag5 = 1;
                    else
                        flags->flag5 = 0;
                }
            }
        }
    }
}

asm(".align 2,0");
