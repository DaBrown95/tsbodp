#include "scene_link_entry_setup.h"
#include "display_scene_lifecycle.h"
#include "display_catalog_text.h"

/* Read-only access prefix: each observed caption coordinate occupies four bytes. */
struct SceneLinkEntryCaption {
    unsigned char x, y, unknown02[2];
};
extern const struct SceneLinkEntryCaption g_scene_link_entry_captions[4];
extern const unsigned int g_scene_link_entry_text_control;

void scene_link_entry_build_objects_original(void)
{
    const char *text;
    unsigned int created;
    int i;

    g_display_scene_frame_objects[0] = frame_create_scene_object(106,
        g_display_scene_catalog[g_scene_request.scene].id, 1, 1);
    created = 0;
    if (!(g_game_flags & 0x20)) {
        const struct SceneLinkEffectOffer *offer = g_link_entry_effect_state.records;
        struct FrameObject **slot = &g_display_scene_frame_objects[1];
        int remaining = 3;
        do {
            unsigned int kind = offer->kind;
            if (kind != 42) {
                *slot++ = frame_create_scene_object(created + 107,
                    kind + 239, created + 3, 1);
                ++created;
            }
            ++offer;
        } while (--remaining >= 0);
    }
    g_display_scene_frame_objects[4] = frame_create_scene_object(110, 267, 6, 1);
    g_display_scene_frame_objects[5] = frame_create_scene_object(111, 267, 6, 1);
    display_text_number_field_zero(0);
    display_text_select_font(0, 0, 0);
    if (!(g_game_flags & 0x20)) {
        for (i = 0; i <= 3; ++i) {
            text = display_scene_lookup_text(0x184c);
            g_display_scene_frame_objects[6 + i] = display_allocate_text_object(&text);
            g_display_scene_frame_objects[6 + i]->flags |= 1;
            frame_set_position(g_display_scene_frame_objects[6 + i],
                (g_scene_link_entry_captions[i].x + 2) * 524288,
                g_scene_link_entry_captions[i].y * 524288);
        }
    } else {
        register const struct SceneLinkEntryCaption *coordinate asm("r4");
        i = 0;
        if (i < g_link_received_join.metadata[0]) {
            coordinate = g_scene_link_entry_captions;
            for (; i < g_link_received_join.metadata[0]; ++i) {
                if (i != g_link_received_join.identifier) {
                    text = display_scene_lookup_text(0x184c);
                    g_display_scene_frame_objects[6 + i] = display_allocate_text_object(&text);
                    g_display_scene_frame_objects[6 + i]->flags |= 1;
                    frame_set_position(g_display_scene_frame_objects[6 + i],
                        (coordinate->x + 2) * 524288,
                        coordinate->y * 524288);
                } else {
                    text = display_scene_lookup_text(0x184c);
                    g_display_scene_frame_objects[6 + i] = display_allocate_text_object(&text);
                    g_display_scene_frame_objects[6 + i]->flags |= 1;
                    frame_set_position(g_display_scene_frame_objects[6 + i],
                        160 * 65536,
                        (coordinate->y * 8 - 96) * 65536);
                }
                ++coordinate;
            }
        }
    }
    display_text_set_background_control(g_scene_link_entry_text_control);
}
