#include "scene_link_catalog.h"
unsigned int scene_link_catalog_try_entry(struct FrameObject *actor,unsigned int entry)
{
 unsigned int error;
 if(entry==141 && g_scene_id==9 && ((struct SceneLinkCatalogActor*)actor)->state==16)goto allowed;
 if(entry==255 || !frame_world_in_idle_exclusion_set(g_scene_id) || ((struct SceneLinkCatalogActor*)actor)->state!=16){error=1;goto denied;}
 if(entry<=117 || entry==125 || entry==141){
  unsigned char *policies=g_scene_link_catalog_world.policies;
  policies+=g_scene_id*4;
  if(policies[0x785]>24){error=4;goto denied;}
 }else if(entry!=139 && entry-195>5)goto denied_kind;
allowed:
 entry=1;
 goto prepared;
denied_kind:
 error=3;
denied:
 scene_link_catalog_draw_panel(error);
 entry=0;
prepared:
 if(entry!=1)return 0;
 transition_object_set_state(actor,22);
 frame_set_variant_state(actor,0);
 ((struct SceneLinkCatalogActor*)actor)->selected=1;
 ((struct SceneLinkCatalogActor*)actor)->selected_index=g_scene_request.scene-5;
 audio_play_animation_cue(7);
 resource_submit_scene(1,2,g_scene_id);
 return 1;
}
asm(".align 2,0");
