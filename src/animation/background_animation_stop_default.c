#include "background_animation.h"
extern void background_animation_stop(void);

void background_animation_stop_default(void) {
 if (g_background_animation.transfer_enabled <= 1)
  background_animation_stop();
}
