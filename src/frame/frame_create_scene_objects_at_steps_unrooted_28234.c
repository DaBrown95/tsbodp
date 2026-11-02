#include "frame_scene_object.h"

struct SceneObjectPixelOffset { short x, y; };
union SceneObjectStep { struct SceneObjectPixelOffset axes; unsigned int packed; };
typedef char scene_step_axes_are_four[sizeof(struct SceneObjectPixelOffset) == 4 ? 1 : -1];
typedef char scene_step_word_is_four[sizeof(union SceneObjectStep) == 4 ? 1 : -1];

union __attribute__((packed, aligned(2))) SceneStepHalfwordInput {
    unsigned short word;
};
typedef char scene_step_x_input_size[sizeof(union SceneStepHalfwordInput) == 2 ? 1 : -1];
typedef char scene_step_x_input_alignment[__alignof__(union SceneStepHalfwordInput) == 2 ? 1 : -1];

/* The incoming route and the six-formal interface remain provisional. */
void frame_create_scene_objects_at_steps_unrooted_28234(unsigned int id,
    unsigned int next_id, int count, unsigned int subtype,
    unsigned int palette, unsigned int layer)
{
    register union SceneObjectStep step asm("r10");
    int index;

    {
        const struct FrameScenePosition *positions = g_frame_scene_positions;
        const struct FrameScenePosition *next = &positions[next_id];
        const struct FrameScenePosition *prefix_origin = &positions[id];
        step.axes.x = (short)(next->x0 - prefix_origin->x0);
        step.axes.y = (short)(next->y0 - prefix_origin->y0);
    }
    {
        union SceneStepHalfwordInput x_source = { (unsigned short)step.axes.x };
        for (index = (int)((unsigned int)count - 1u); index >= 0; --index) {
            const struct FrameScenePosition *loop_origin = &g_frame_scene_positions[id];
            struct FrameObject *object =
                frame_create_scene_object(id, subtype, palette, layer);
            struct SceneObjectPixelOffset position;
            position.x = (short)((unsigned int)loop_origin->x0 +
                (unsigned int)(int)(short)x_source.word * (unsigned int)index);
            position.y = (short)((unsigned int)loop_origin->y0 +
                (unsigned int)((int)step.packed >> 16) * (unsigned int)index);
            frame_set_position(object,
                (int)((unsigned int)(int)position.x << 16),
                (int)((unsigned int)(int)position.y << 16));
            object->flags &= ~0x10u;
        }
    }
}
