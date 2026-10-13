#include "frame_need_effect_placement.h"

unsigned int frame_need_effect_pattern_dimensions(const unsigned char *pattern,
 unsigned char *width, unsigned char *height)
{
 unsigned char max_x = 0, max_y = 0, found = 0, x = 0, y;
 const unsigned char *actions = pattern + 2;
 unsigned char origin_x = pattern[0], origin_y = pattern[1];
 for (; x <= 4; x++) {
  for (y = 0; y <= 4; y++) {
   unsigned int offset = x + (unsigned int)(y * 5);
   if ((unsigned char)(actions[offset] - 1) <= 2) {
    found = 1;
    if (x > max_x) max_x = x;
    if (y > max_y) max_y = y;
   }
  }
 }
 if (found == 0) {
  for (x = 0; x <= 4; x++) {
   for (y = 0; y <= 4; y++) {
    unsigned int offset = x + (unsigned int)(y * 5);
    if (actions[offset] == 4) {
     if (x > max_x) max_x = x;
     if (y > max_y) max_y = y;
    }
   }
  }
 }
 max_x -= origin_x;
 max_y -= origin_y;
 *width = max_x + 1;
 *height = max_y + 1;
 return 1;
}
