#include "background_animation.h"
extern unsigned char resource_is_active(void *);
extern void resource_release(void *);
extern void display_background_disable(unsigned int);

void background_animation_stop(void) {
 g_background_animation.flags &= 0xFFF0;
 if (resource_is_active(g_background_animation.resource_handle))
  resource_release(g_background_animation.resource_handle);
 display_background_disable(3);
}
