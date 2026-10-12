#include "display.h"
#include "frame_scene_object.h"
struct FrameObject *frame_create_scene_object(unsigned int id,unsigned int subtype,unsigned int palette,unsigned int layer)
{
 struct FrameObject *object=frame_allocate_scene_object();
 object->id=id;
 object->unknown_0a=subtype;
 object->flags=25;
 object->display_layer=layer;
 object->display_palette=palette;
 object->on_step=frame_scene_object_tick;
 transition_object_set_state(object,14);
 frame_set_variant_state(object,0);
 frame_set_position(object,g_frame_scene_positions[id].x0<<16,g_frame_scene_positions[id].y0<<16);
 if(subtype!=267) frame_set_animation_record(object,&g_frame_scene_resources[subtype]);
 else {
  display_load_palette_alternate(g_frame_scene_special_palette,palette*16,16);
  if(id==110) frame_set_animation_program(object,(struct FrameSpriteResource*)&g_frame_scene_resources[subtype],g_frame_scene_commands_110,0);
  else if(id==111) frame_set_animation_program(object,(struct FrameSpriteResource*)&g_frame_scene_resources[subtype],g_frame_scene_commands_111,0);
 }
 return object;
}
