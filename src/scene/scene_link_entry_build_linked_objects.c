#include "link_event_receive.h"
#include "display_scene_lifecycle.h"
#include "display_catalog_text.h"
#include "display_text_fields.h"

/* Read-only four-byte caption access prefix, shared with the first builder. */
struct SceneLinkEntryCaption {
    unsigned char x, y, unknown02[2];
};
extern const struct SceneLinkEntryCaption g_scene_link_entry_captions[4];
extern const unsigned int g_scene_link_entry_text_control;

void scene_link_entry_build_linked_objects(void)
{
    const char *text;
    int i;

    g_display_scene_frame_objects[0] = frame_create_scene_object(106,
        g_display_scene_catalog[g_scene_request.scene].id, 1, 1);
    frame_set_variant_state(g_display_scene_frame_objects[0], 11);
    frame_set_position(g_display_scene_frame_objects[0], 44 * 65536, 103 * 65536);
    g_display_scene_frame_objects[10] = frame_create_scene_object(112, 238, 7, 3);
    g_display_scene_frame_objects[4] = frame_create_scene_object(110, 267, 6, 1);
    frame_set_variant_state(g_display_scene_frame_objects[4], 11);
    frame_set_position(g_display_scene_frame_objects[4], -4 * 65536, 118 * 65536);
    g_display_scene_frame_objects[5] = frame_create_scene_object(111, 267, 6, 1);
    frame_set_variant_state(g_display_scene_frame_objects[5], 11);
    frame_set_position(g_display_scene_frame_objects[5], -4 * 65536, 138 * 65536);
    display_text_number_field_zero(0);
    display_text_select_font(0, 0, 0);
    for (i = 0; i < g_link_received_join.metadata[0]; ++i) {
        if (i != g_link_received_join.identifier) {
            text = display_scene_lookup_text(0x184c);
            g_display_scene_frame_objects[6 + i] = display_allocate_text_object(&text);
            g_display_scene_frame_objects[6 + i]->flags |= 1;
            frame_set_position(g_display_scene_frame_objects[6 + i],
                (g_scene_link_entry_captions[i].x + 2) * 524288,
                g_scene_link_entry_captions[i].y * 524288);
        } else {
            text = display_scene_lookup_text(0x184c);
            g_display_scene_frame_objects[6 + i] = display_allocate_text_object(&text);
            g_display_scene_frame_objects[6 + i]->flags |= 1;
            frame_set_position(g_display_scene_frame_objects[6 + i],
                160 * 65536,
                (g_scene_link_entry_captions[i].y * 8 - 96) * 65536);
        }
    }
    display_text_set_background_control(g_scene_link_entry_text_control);
}
