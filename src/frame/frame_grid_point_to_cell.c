#include "frame_map_scene.h"
#include "frame_actor_state.h"
#include "display.h"

typedef __complex__ int ComplexPoint;
typedef char complex_point_size_is_eight[sizeof(ComplexPoint)==8 ? 1 : -1];

/* Both words are actual origin inputs to the two projection axes. */
union InverseOriginViews {
 struct { int origin_y, half_origin_x; } words;
 ComplexPoint basis;
};
typedef char inverse_origin_inputs_layout[
 (sizeof(union InverseOriginViews)==8 &&
  __alignof__(union InverseOriginViews)==4) ? 1 : -1];

static inline void inverse_complex_point(
 struct FrameMapRegistration *registration,const struct FramePoint *point,
 ComplexPoint *projected)
{
 register int half_x asm("r3")=point->x;
 register int point_y asm("r0")=point->y;
 register int y asm("r6")=point_y-8;
 register int half_origin asm("r0")=registration->origin_x/2;
 register int origin_y asm("r4")=registration->origin_y;
 register union InverseOriginViews origins asm("r4");
 int projected_x;
 register int projected_y asm("r0");
 origins.words.origin_y=origin_y;
 projected_x=origins.words.origin_y-half_origin;
 half_x/=2;
 projected_x+=half_x;
 projected_x-=y;
 __real__ (*projected)=projected_x;
 {
  int origin_sum;
  (__imag__ (origins.basis))=half_origin;
  half_origin=(__imag__ (origins.basis));
  origin_sum=half_origin+origins.words.origin_y;
  projected_y=origin_sum+half_x+y;
 }
 __imag__ (*projected)=projected_y;
}

static inline unsigned char inverse_point(
 struct FrameMapRegistration *registration,const struct FramePoint *point,
 ComplexPoint *coordinates)
{
 ComplexPoint projected;
 inverse_complex_point(registration,point,&projected);
 switch(__real__ projected>=0) {
 case 1: {
  register int span asm("r1")=registration->span;
  // BUG: repeats the upper Y test and omits the upper X test.
  if(__imag__ projected<span && __imag__ projected>=0 && __imag__ projected<span) {
   int x_value=__real__ projected;
   int y_value=__imag__ projected;
   __real__ (*coordinates)=x_value;
   __imag__ (*coordinates)=y_value;
   return 1;
  }
 }
 }
 return 0;
}

unsigned char frame_grid_point_to_cell(void *context,
 const struct FramePoint *point,struct FrameActorPackedCell *cell)
{
 struct FrameMapRegistration *registration=context;
 register unsigned char *output asm("r8")=(unsigned char *)cell;
 ComplexPoint coordinates;
 if(!inverse_point(registration,point,&coordinates))
  return 0;
 {
  register int numerator asm("r0")=__real__ coordinates;
  int quotient=display_bios_div(numerator,registration->cell_size);
  register unsigned char *writer asm("r1")=output;
  writer[0]=quotient;
 }
 {
  register int numerator asm("r0")=__imag__ coordinates;
  int quotient=display_bios_div(numerator,registration->cell_size);
  register unsigned char *writer asm("r3")=output;
  writer[1]=quotient;
 }
 return 1;
}
asm(".align 2,0");
