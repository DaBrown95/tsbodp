#include "scene_contact_activity_two.h"
#define STATE ((struct SceneContactActivityTwoState *)g_scene_contact_state)
void scene_contact_activity_two_draw_row(unsigned int row) {
 unsigned short tile;
 const struct BackgroundResource *resource;
 display_clear_background_rectangle(2,g_scene_contact_activity_two_rows[row].positions[STATE->entries[row].position].x,g_scene_contact_activity_two_rows[row].positions[STATE->entries[row].position].y,2,2);
 STATE->entries[row].position=frame_random_range(0,2);
 STATE->entries[row].variant=frame_random_range(0,2);
 resource=g_scene_contact_activity_two_event_resources[STATE->entries[row].variant].resource;
 tile=row*4+201;
 display_load_background(2,resource,tile,g_scene_contact_activity_two_event_resources[STATE->entries[row].variant].character_base,g_scene_contact_activity_two_rows[row].positions[STATE->entries[row].position].x,g_scene_contact_activity_two_rows[row].positions[STATE->entries[row].position].y);
}
asm(".align 2, 0");
