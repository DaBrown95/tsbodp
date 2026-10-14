#include "scene_contact_activity_five.h"
#define STATE ((struct SceneContactActivityFiveState *)g_scene_contact_state)
void scene_contact_activity_five_reset_timers(void)
{
 int i;
 for(i=0;i<8;++i)STATE->pending_column_shifts[i]=0;
 g_scene_request.unknown_14=0;
 STATE->settle_row=7;
}
