#include "resource_commands.h"
#include "resource_conditions.h"
#include "scene.h"
struct ConditionPlayerSelection { unsigned char unknown00[0x440];unsigned int row; };
extern void condition_select_actor(void *,unsigned int);
extern void condition_refresh_scene(unsigned int);
void condition_select_row(unsigned int row)
{
    if(g_scene_request.unknown_00==8) {
        if(g_scene_request.scene==5)resource_submit_scene(1,4,g_condition_row_scenes[row].scene);
        else resource_submit_scene(1,7,g_condition_row_scenes[row].scene);
        condition_refresh_scene(row);
    } else {
        condition_select_actor(g_scene_entry_data,row);
        g_scene_request.parameter=g_condition_row_scenes[row].scene;
        resource_scene_event(0x1a);
        condition_refresh_scene(row);
    }
    g_scene_mode_bytes[0]=g_condition_row_scenes[row].mode;
    ((struct ConditionPlayerSelection *)&g_resource_game_state)->row=row;
    condition_publish_row_displays(row);
}
