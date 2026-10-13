#include "frame_need_effect_placement.h"

void frame_need_effect_pattern_cell(int x, int y, const unsigned char *pattern,
 unsigned int direction, const struct FrameActorPackedCell *anchor,
 struct FrameActorPackedCell *output)
{
 int row, column;
 unsigned char width, height;
 int dx, dy;

 row = y;
 column = x - pattern[0];
 row -= pattern[1];
 frame_need_effect_pattern_dimensions_2f430(pattern, &width, &height);
 switch (direction) {
 case 5: dx = -row; dy = -column; break;
 case 1: dx = row; dy = ~column + width; break;
 case 7: dx = column - width + 1; dy = -row; break;
 case 3:
 default: dx = column; dy = row; break;
 }
 ((unsigned char *)output)[0] = ((const unsigned char *)anchor)[0] + dx;
 ((unsigned char *)output)[1] = ((const unsigned char *)anchor)[1] + dy;
}
