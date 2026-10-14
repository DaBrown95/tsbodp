#include "frame_movement_redirect.h"
void frame_redirect_movement(struct FrameObject *object,unsigned int contact)
{
 unsigned int direction=((struct FrameMovementRedirectDirection *)object)->direction>>1;
 struct FramePoint displacement;
 union FrameMovementNibbleSnapshot second,first;
 if(contact==37)return;
 if(contact!=3) {
  union FrameMovementNibbleSnapshot second,first;
  unsigned int root;
  const union FrameTerrainLine *line;
  contact-=4;
  root=(unsigned int)g_frame_movement_contact_lines;
  line=(const union FrameTerrainLine *)(root+(contact<<2));
  second.word=line->bytes[1];
  {unsigned int x1=second.byte.low;first.word=line->bytes[0];displacement.x=x1-first.byte.low;}
  second.word>>=4;first.word>>=4;
  displacement.y=(int)second.word-(int)first.word;
  if(!frame_movement_direction_blocked(object,displacement))return;
 }
 if(((struct FrameMovementRedirectDirection *)object)->direction&1) {
  union FrameMovementNibbleSnapshot second,first;
  second.word=g_frame_movement_direction_lines[direction].bytes[1];
  {unsigned int x1=second.byte.low;first.word=g_frame_movement_direction_lines[direction].bytes[0];displacement.x=x1-first.byte.low;}
  second.word>>=4;first.word>>=4;
  displacement.y=(int)second.word-(int)first.word;
  if(!frame_movement_direction_blocked(object,displacement))return;
  direction=(direction+1)&3;
 }
 second.word=g_frame_movement_direction_lines[direction].bytes[1];
 {unsigned int x1=second.byte.low;first.word=g_frame_movement_direction_lines[direction].bytes[0];displacement.x=x1-first.byte.low;}
 displacement.y=second.byte.high-first.byte.high;
 if(!frame_movement_direction_blocked(object,displacement))return;
 displacement.x=(second.byte.low-first.byte.low)*0x4000;
 displacement.y=(second.byte.high-first.byte.high)*0x4000;
 if(g_frame_movement_filter[0]==0) {
  if(g_frame_movement_filter[1]==0) {
   if(!frame_movement_offset_blocked(object,displacement))return;
   displacement.x=-displacement.x;displacement.y=-displacement.y;
  }
 } else {
  if(g_frame_movement_filter[1]!=0)return;
  displacement.x=-displacement.x;displacement.y=-displacement.y;
 }
 frame_movement_offset_blocked(object,displacement);
}
