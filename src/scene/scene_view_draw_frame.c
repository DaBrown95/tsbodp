#include "save_world_view_resources.h"
#include "scene_view_frame.h"
#include "display_map_fill.h"
/* Tile additions occur before the palette OR, then wrap to a halfword. */
#define FRAME_TILE(n) ((unsigned short)((g_scene_view_resource_palette<<12)|(g_scene_view_resource_tile+(n))))
void scene_view_draw_frame(unsigned int x,unsigned int y,unsigned int width,unsigned int height) {
 unsigned int right=(unsigned char)(x+width-1);
 unsigned int bottom=(unsigned char)(y+height-1);
 unsigned int inner_x,inner_width,inner_height;
 display_fill_background_constant_rectangle(g_scene_view_resource_background,x,y,1,1,FRAME_TILE(0));
 display_fill_background_constant_rectangle(g_scene_view_resource_background,inner_x=x+1,y,inner_width=width-2,1,FRAME_TILE(1));
 display_fill_background_constant_rectangle(g_scene_view_resource_background,right,y,1,1,FRAME_TILE(2));
 display_fill_background_constant_rectangle(g_scene_view_resource_background,x,++y,1,inner_height=height-2,FRAME_TILE(3));
 display_fill_background_constant_rectangle(g_scene_view_resource_background,right,y,1,inner_height,FRAME_TILE(5));
 display_fill_background_constant_rectangle(g_scene_view_resource_background,x,bottom,1,1,FRAME_TILE(6));
 display_fill_background_constant_rectangle(g_scene_view_resource_background,inner_x,bottom,inner_width,1,FRAME_TILE(7));
 display_fill_background_constant_rectangle(g_scene_view_resource_background,right,bottom,1,1,FRAME_TILE(8));
 display_fill_background_constant_rectangle(g_scene_view_resource_background,inner_x,y,inner_width,inner_height,FRAME_TILE(4));
}
asm(".align 2,0");
