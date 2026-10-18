#include "frame_need_effect_object_restore.h"

void frame_restore_need_effect_object(struct FrameNeedEffectState *owner)
{
    struct FrameNeedEffectRestoreObject *object =
        (struct FrameNeedEffectRestoreObject *)owner->object;

    if (!(object->flags & 2)) {
        switch (owner->kind) {
        case 125:
            if (owner->optional <= 7) {
                register unsigned char *flags asm("r2") =
                    (unsigned char *)&g_resource_game_state;
                flags += 0xe5;
                *flags &= ~(1u << owner->optional);
            }
            {
                struct FrameNeedEffectRestoreObject *current_object =
                    (struct FrameNeedEffectRestoreObject *)owner->object;
                frame_create_option_object(1, current_object->direction,
                                           owner->optional,
                                           current_object->position.halves.x_pixel,
                                           current_object->position.halves.y_pixel);
            }
            break;
        case 126:
            frame_create_option_object(2, object->direction, owner->optional,
                                       object->position.halves.x_pixel,
                                       object->position.halves.y_pixel);
            break;
        case 139:
            frame_spawn_saved_scene_effect(object->position.word.x,
                                           object->position.word.y);
            break;
        }
        transition_object_set_state(owner->object, 1);
    }
}
asm(".align 2, 0");
