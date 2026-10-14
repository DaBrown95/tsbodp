#include "scene_contact_activity_five.h"
#define STATE ((struct SceneContactActivityFiveState *)g_scene_contact_state)
void scene_contact_activity_five_reset(void)
{
 STATE->score=0;
 STATE->selected_column=0;
 STATE->selected_row=0;
 STATE->root=scene_contact_activity_five_create_root();
 scene_contact_activity_five_populate();
 scene_contact_activity_five_reset_timers();
}
asm(".align 2, 0");
