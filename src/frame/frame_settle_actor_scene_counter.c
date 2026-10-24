#include "frame_actor_idle.h"
#include "frame_actor_attachment_counter_choices.h"
#include "frame_actor_attachment_parameters.h"

unsigned int frame_settle_actor_scene_counter(unsigned char repeat)
{
    union ResourceGameState *world;
    struct FrameActorSceneCounter *counter_address;
    /* Native input values and arithmetic destinations; no calls cross these lives. */
    register unsigned short counter asm("r2");
    register int initial_value asm("r3");
    unsigned int result;
    {
        register union ResourceGameState *entry asm("r0") = &g_resource_game_state;
        counter_address = &entry->scene.counter;
        counter = counter_address->value;
        initial_value = entry->actor_values.value;
        world = entry;
    }
    if (initial_value >= counter) {
        register int value asm("r0") = initial_value - counter;
        world->actor_values.value = value;
        if (value > 999999)
            world->actor_values.value = 999999;
        else if (value < 0)
            world->actor_values.value = 0;
        g_attachment_parameter_ui[g_input_config.local_player].flags |= 2;
        world->scene.counter.value = 0;
        result = 1;
    } else {
        /* Unsigned subtraction defines wraparound for every signed input value. */
        register unsigned short remaining asm("r0") = counter - (unsigned int)initial_value;
        counter_address->value = remaining;
        world->actor_values.value = 0;
        result = 0;
        g_attachment_parameter_ui[g_input_config.local_player].flags |= 2;
        if (repeat) {
            world->idle.counter_reduction_tick = 9;
            goto done;
        }
    }
    world->idle.counter_reduction_tick = 0;
done:
    return result;
}
