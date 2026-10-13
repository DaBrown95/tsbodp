#include "frame_actor_group.h"
void frame_compose_actor_group_alternate_palette(const void *data, void *output)
{
 unsigned short *palette = output;
 const unsigned char *definition = data;
 const unsigned char *rows = (const unsigned char *)g_actor_group_alternate_palette_rows;
 palette[0] = g_actor_group_alternate_palette_rows[0];
 heap_copy((unsigned char *)palette + 2, rows + (definition[1] * 32 + 2), 12);
 heap_copy((unsigned char *)palette + 14, rows + (definition[3] * 32 + 14), 12);
 heap_copy((unsigned char *)palette + 26, rows + (definition[4] * 32 + 26), 6);
}
asm(".align 2, 0");
