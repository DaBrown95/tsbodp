#include "frame_actor_needs.h"
#include "frame_actor_scene.h"
#include "frame_actor_idle.h"
void frame_cycle_idle_actor_palette(void)
{
 struct FrameObject *object=0,*entry=g_frame_primary_list.first,*next;
 while(entry) {
  next=entry->next;
  if(entry->unknown_0a==13){object=entry;break;}
  entry=next;
 }
 if(object) {
  unsigned int palette=frame_get_actor_palette_slot(object)+1;
  if(palette>6)palette=1;
  ((struct FrameActorPaletteSelection *)&g_resource_game_state)->palette=palette;
  frame_acquire_palette_slot(object,palette);
 }
}
