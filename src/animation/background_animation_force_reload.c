#include "background_animation.h"
extern void background_animation_stop(void);

void background_animation_force_reload(void) {
 background_animation_stop();
 if (g_background_animation.transfer_enabled)
  g_background_animation.flags |= 8;
}
