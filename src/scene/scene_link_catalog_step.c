#include "scene_link_catalog.h"
void scene_link_catalog_step(void)
{
 struct FrameObject *actor=g_scene_link_catalog_input.actor;
 struct EventPayload payload;
 if(g_link_flags&0x8000) {
  resource_submit_scene(1,2,g_scene_id);
  g_scene_link_catalog_input.player_count=1;
  g_scene_link_catalog_input.local_player=0;
  return;
 }
 switch(g_scene_request.unknown_10) {
 case 4:
  *(unsigned int *)payload.bytes=g_scene_link_catalog_world.value;
  transition_record_event(7,payload);g_scene_request.unknown_10=5;break;
 case 5:
  *(unsigned int *)payload.bytes=0;
  transition_record_event(8,payload);g_scene_request.unknown_10=6;break;
 case 6:
  *(unsigned int *)payload.bytes=0;
  transition_record_event(9,payload);g_scene_request.unknown_10=7;break;
 case 7:
  *(unsigned int *)payload.bytes=0;
  transition_record_event(10,payload);g_scene_request.unknown_10=8;break;
 case 8:resource_submit_scene(23,0,g_link_received_join.metadata[1]);break;
 default:
 if(g_input_local_pressed[g_scene_link_catalog_input.local_player]&0xf0) {
  switch(g_scene_request.unknown_10) {
  case 0:case 1:case 3:
   {
    unsigned int index=g_scene_request.scene;
    if(index>4) {
     if((g_input_local_pressed[g_scene_link_catalog_input.local_player])&0x80) {
      if(index-5<=3)g_scene_request.scene=index+4;
     } else if((g_input_local_pressed[g_scene_link_catalog_input.local_player])&0x40) {
      if(index-9<=3)g_scene_request.scene=index-4;
     } else if((g_input_local_pressed[g_scene_link_catalog_input.local_player])&0x20) {
      if(index!=5&&index!=9)g_scene_request.scene=index-1;
      else if(!g_scene_request.unknown_10) {
       g_scene_request.scene=2;
       g_scene_link_catalog_owners.first->unknown_0a=12;
       display_scene_refresh_item(g_scene_link_catalog_owners.first);
      }
     } else if((g_input_local_pressed[g_scene_link_catalog_input.local_player])&0x10) {
      if(index!=8&&index!=12)g_scene_request.scene=index+1;
     }
    } else {
     if((g_input_local_pressed[g_scene_link_catalog_input.local_player])&0x80) {
      if(index!=1&&index!=4)g_scene_request.scene=index+1;
     } else if((g_input_local_pressed[g_scene_link_catalog_input.local_player])&0x40) {
      if(index!=0&&index!=2)g_scene_request.scene=index-1;
     } else if((g_input_local_pressed[g_scene_link_catalog_input.local_player])&0x20) {
      if(index-2<=2)g_scene_request.scene=0;
     } else if((g_input_local_pressed[g_scene_link_catalog_input.local_player])&0x10) {
      if(index-2<=2) {
       g_scene_request.scene=5;
       g_scene_link_catalog_owners.first->unknown_0a=10;
       display_scene_refresh_item(g_scene_link_catalog_owners.first);
      } else g_scene_request.scene=2;
     }
    }
    g_scene_link_catalog_owners.first->id=g_scene_request.scene+52;
    frame_set_variant_state(g_scene_link_catalog_owners.first,58);
    display_catalog_draw_selection();audio_play_animation_cue(0);
   }
   break;
  case 2:
   {
    if((g_input_local_pressed[g_scene_link_catalog_input.local_player])&0x40) {
     if(g_scene_request.parameter<g_scene_link_catalog_quantity_limit) {
      g_scene_request.parameter++;audio_play_animation_cue(13);
     }
    } else if((g_input_local_pressed[g_scene_link_catalog_input.local_player])&0x80) {
     if(g_scene_request.parameter>1) {
      g_scene_request.parameter--;audio_play_animation_cue(13);
     }
    }
    scene_link_catalog_draw_quantity();
   }
   break;
  case 4:case 5:case 6:case 7:case 8:case 9:break;
  }
 }
 switch(g_scene_request.unknown_10) {
 case 0:
  {
   if((g_input_local_pressed[g_scene_link_catalog_input.local_player])&0x100) {
    g_scene_link_catalog_world.requested_kind=14;
    scene_submit_default_request(14);audio_play_animation_cue(4);
   } else if((g_input_local_pressed[g_scene_link_catalog_input.local_player])&0x200) {
    g_scene_link_catalog_world.requested_kind=17;
    scene_submit_default_request(17);audio_play_animation_cue(4);
   } else {
    if((g_input_pressed[g_scene_link_catalog_input.local_player])&1) {
     struct SceneLinkCatalogContext *context=g_scene_link_catalog_world.context;
     unsigned int selection=g_scene_request.scene;
     if(!(unsigned char)scene_link_catalog_try_entry(actor,context->entries[selection-5].unknown_00[0]))audio_play_animation_cue(3);
    } else if((g_input_pressed[g_scene_link_catalog_input.local_player])&10) {
     resource_submit_scene(1,2,g_scene_id);audio_play_animation_cue(2);
    }
   }
  }
  break;
 case 1:
  {
   if((g_input_pressed[g_scene_link_catalog_input.local_player])&1)scene_link_catalog_accept_entry();
   else if((g_input_pressed[g_scene_link_catalog_input.local_player])&2) {resource_submit_scene(15,1,0);audio_play_animation_cue(2);}
  }
  break;
 case 2:
  {
   if((g_input_pressed[g_scene_link_catalog_input.local_player])&1)scene_link_catalog_accept_quantity();
   else if((g_input_pressed[g_scene_link_catalog_input.local_player])&2) {
    display_fill_background(0,0);g_scene_request.unknown_10=1;
    display_text_set_background_control(g_scene_link_catalog_control1);
    g_scene_link_catalog_owners.details[0]->flags&=~1u;
    g_scene_link_catalog_owners.details[1]->flags&=~1u;
   }
  }
  break;
 case 3:
  {
   if((g_input_local_pressed[g_scene_link_catalog_input.local_player])&1) {
    struct SceneLinkCatalogContext *context=g_scene_link_catalog_world.context;
    unsigned int selection=g_scene_request.scene;
    if(context->entries[selection-5].unknown_00[0]>117) {
     display_fill_background_constant_rectangle(1,1,12,28,8,0);
     display_text_select_font(3,0,-1);
     display_text_draw_line(226,120,96,display_scene_lookup_text(450),1);
     audio_play_animation_cue(3);
    } else {
     payload.bytes[0]=context->entries[selection-5].unknown_00[0];
     payload.bytes[1]=context->entries[selection-5].unknown_00[1];
     payload.bytes[2]=context->entries[selection-5].type;
     transition_record_event(5,payload);
     g_link_received_join.entry_index=g_scene_request.scene-5;
    }
   } else if(g_input_pressed[g_scene_link_catalog_input.local_player]&2) {
    transition_record_event(11,payload);audio_play_animation_cue(2);
   }
  }
  break;
 case 9:
  if(g_input_pressed[g_scene_link_catalog_input.local_player]&3) {
   display_fill_background(0,0);g_scene_request.unknown_10=0;
   display_text_set_background_control(g_scene_link_catalog_control1);
  }
  break;
 }
 }
}
