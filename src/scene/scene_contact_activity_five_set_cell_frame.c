#include "scene_contact_activity_five.h"
#define STATE ((struct SceneContactActivityFiveState *)g_scene_contact_state)
void scene_contact_activity_five_set_cell_frame(struct FrameObject *base)
{
 struct SceneContactActivityFiveObject *object=(struct SceneContactActivityFiveObject *)base;
 unsigned char *program;
 switch(object->subtype) {
 case 0:program=g_scene_contact_activity_five_cell_program;break;
 case 1:program=g_scene_contact_activity_five_cell_program;break;
 case 2:program=g_scene_contact_activity_five_cell_program;break;
 case 3:program=g_scene_contact_activity_five_cell_program;break;
 case 4:program=g_scene_contact_activity_five_cell_program;break;
 default:program=0;break;
 }
 frame_set_animation_program((struct FrameObject *)object,(struct FrameSpriteResource *)(g_scene_contact_activity_five_cell_animations+(object->subtype<<4)),program,0);
}
asm(".align 2,0");
