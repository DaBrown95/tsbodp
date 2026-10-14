#include "scene_contact_activity_five.h"
#define STATE ((struct SceneContactActivityFiveState *)g_scene_contact_state)
void scene_contact_activity_five_replace_cell(int row,int column)
{
 int i;
 for(i=0;i<64;++i) {
  struct SceneContactActivityFiveObject *object=STATE->objects[i];
  if(object) {
   int object_row=display_bios_remainder(object->cell,8);
   int object_column=display_bios_div(object->cell,8);
   if(object_row==row&&object_column==column) {
    unsigned short subtype;
    unsigned char *program;
    do {
     subtype=frame_random_bounded(g_scene_contact_activity_five_rows[STATE->option].subtype_count-1);
    }while(subtype==object->subtype);
    frame_release_object_palette((struct FrameObject *)object);
    object->subtype=subtype;
    frame_set_subtype_object_palette((struct FrameObject *)object,g_scene_contact_activity_five_cell_palettes);
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
  }
 }
}
