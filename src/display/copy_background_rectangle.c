#include "display_menu_primary.h"
#include "display_map.h"
void display_copy_background_rectangle(unsigned int index, const struct DisplayStoredMap *source, int source_x, int source_y, int x, int y, int width, int height, unsigned short offset) {
 struct DisplayMapState *state=&g_display_map_states[index];
 unsigned short *destination=state->destination+(y*32+x);
 const unsigned short *tiles=source->tiles+(source_y*source->width+source_x);
 /* Semantic row count, held locally; the copy loop makes no calls. */
 register int remaining_rows asm("r2")=height;
 int count;
 if(remaining_rows>0)do {
  count=width;
  --remaining_rows;
  if(width>0)do {
   *destination=offset+*tiles;
   ++tiles;
   ++destination;
  }while(--count>0);
  tiles+=source->width-width;
  destination+=32-width;
 }while(remaining_rows>0);
}
asm(".align 2, 0");
