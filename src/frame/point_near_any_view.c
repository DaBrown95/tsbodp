#include "frame_actor_distance.h"
#include "frame_actor_needs.h"
#include "frame_actor_state.h"
#include "frame_map.h"

/* Each word is assigned before its own read; the pairs share native lifetimes. */
struct PointBoundWords { int bound, coordinate; };
struct PointCountWords {
 unsigned int value;
 unsigned char *count_address;
};
struct PointXWords { int value, origin_x; };
typedef char point_word_layout[
 (sizeof(struct PointBoundWords)==8 && __alignof__(struct PointBoundWords)==4 &&
  sizeof(struct PointCountWords)==8 && __alignof__(struct PointCountWords)==4 &&
  sizeof(struct PointXWords)==8 && __alignof__(struct PointXWords)==4) ? 1 : -1];

unsigned int frame_point_near_any_view(int fixed_x,int fixed_y)
{
 register int incoming_x asm("r0")=fixed_x;
 register int incoming_y asm("r1")=fixed_y;
 struct { struct FramePoint origin,input,integer; } work;
 register unsigned int found asm("r8");
 unsigned int views;
 unsigned char index;
 unsigned int count;

 work.input.x=incoming_x;
 work.input.y=incoming_y;
 found=0;
 {
  register struct PointCountWords count_words asm("r0");
  {
   register struct FrameActorNeedInput *input_base asm("r0")=&g_frame_actor_need_input;
   count_words.count_address=(unsigned char *)input_base;
  }
  count_words.count_address+=sizeof(g_frame_actor_need_input.views);
  {
   register unsigned int count_value asm("r0")=*count_words.count_address;
   count_words.value=count_value;
   views=count_words.value;
  }
 }
 count=1;
 if(views)count=views;
 index=0;
 if(found<count) {
  register const struct FramePoint *origin_view asm("r9")=&work.origin;
  register struct FramePoint *integer_view asm("r6")=&work.integer;
  register int height asm("r10");
  /* The low word holds height before the loop, then the converted X. */
  register struct PointXWords x_words asm("r3");
  {
   register int height_input asm("r3")=260;
   x_words.value=height_input;
   height=x_words.value;
  }
  do {
   frame_get_view_origin(&work.origin,index);
   {
    register unsigned char *input_address asm("r0")=(unsigned char *)&work;
    input_address+=sizeof(work.origin);
    frame_point_to_integer((const struct FramePoint *)input_address,integer_view);
   }
   {
    register int origin_x asm("r4")=work.origin.x;
    x_words.origin_x=origin_x;
   {
    register int lower_x asm("r0")=x_words.origin_x;
    lower_x-=100;
    {
     register int integer_x asm("r3")=work.integer.x;
     x_words.value=integer_x;
    }
    if(x_words.value>=lower_x) {
     register int origin_y asm("r2")=origin_view->y;
     /* The low word becomes lower Y, right X, then upper Y. */
     register struct PointBoundWords bounds asm("r0");
     {
      register int lower_y asm("r0")=origin_y;
      lower_y-=100;
      bounds.bound=lower_y;
     }
     {
      register int integer_y asm("r1")=integer_view->y;
      bounds.coordinate=integer_y;
     }
     if(bounds.coordinate>=bounds.bound) {
      bounds.bound=100;
      bounds.bound+=240;
      bounds.bound+=origin_x;
      if(x_words.value<=bounds.bound) {
       bounds.bound=origin_y+height;
       if(bounds.coordinate<=bounds.bound)found=1;
      }
     }
    }
   }
   }
   index++;
  }while(index<count);
 }
 return found;
}
