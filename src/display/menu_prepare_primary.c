#include "display_menu_primary.h"
#include "display_scene_setup.h"
#include "display_catalog_text.h"
#include "display_window.h"
#include "frame_actor_relation.h"
#include "audio_game.h"
void display_menu_prepare_primary(void) {
 struct DisplaySceneRequestState *request;
 struct DisplayMenuState *menu;
 display_menu_load_relation_resource();
 display_fill_background(0,60);
 request=&g_display_scene_request_state;
 request->unknown_10=0;
 menu=&g_display_menu_state;
 display_copy_background_rectangle(1,(const struct DisplayStoredMap *)menu->unknown_0c[1],9,14,9,14,18,5,0xd116);
 display_set_background_scroll_target(0,0,-7602176,1);
 request->scene=0;
 display_enable_window(0);
 display_disable_window(1);
 if(menu->choice!=255)display_menu_restore_choice();
 if(((struct FrameActorRelationState *)&g_display_catalog_state)->records[menu->definition].unknown_02[0]) {
  display_menu_show_hint(0);
  display_menu_request_notice(1,2,g_display_menu_notice_owner);
  audio_play_animation_cue(80);
 }else {
  display_menu_populate_primary_rows();
  display_menu_draw_lines();
  display_menu_show_hint(0);
 }
}
asm(".align 2, 0");
