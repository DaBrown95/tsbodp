#include "scene_startup.h"

void scene_check_initial_time_flags(void);
struct FrameSpriteResource;
unsigned short frame_initialize_transient_definition(unsigned char,unsigned char,struct FrameSpriteResource*);
extern struct FrameSpriteResource g_scene_startup_transient2,g_scene_startup_transient3,g_scene_startup_transient6,g_scene_startup_transient7;
void scene_check_initial_time_flags(void) {
 struct SceneTimeTriggers *time=(struct SceneTimeTriggers*)g_scene_world_state;
 if(display_time_compare(&time->time,&time->first,6)==2 && display_time_compare(&time->time,&time->second,6)==1)g_scene_context.flags|=1;
}
asm(".align 2,0");
