#include "scene_contact_menu.h"
#include "scene_contact_serial_session.h"
void scene_contact_apply_need_adjustments(void)
{
    if (g_scene_previous_request.unknown_00 == 1) {
        int i = 0;
        struct SceneContactState **scene_slot = &g_scene_contact_state;
        union SceneContactSerialCapture *world = &g_scene_contact_serial_capture;
        const unsigned char *deltas = g_scene_contact_definitions[0].need_deltas;
        for (; i < 8; ++i) {
            int limit;
            int value = (int)world->words[44 + i];
            unsigned int offset = i + (*scene_slot)->scene *
                sizeof(struct SceneContactDefinition);
            const unsigned char *increment = (const unsigned char *)(offset +
                (unsigned int)deltas);
            value = (int)((unsigned int)value +
                ((unsigned int)*increment << 24));
            limit = 0x13ffffff;
            if (value <= limit) {
                ++limit;
                value = limit;
            }
            else {
                limit = 0x64000000;
                if (value > limit) value = limit;
            }
            world->words[44 + i] = (unsigned int)value;
        }
    }
}
