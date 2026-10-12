/* Field meanings are inferred from the VBlank-driven state progression. */
#include "background_animation.h"

void background_animation_tick(void) {
 unsigned short reverse;
 if (!(g_game_flags & 0x70018) && (g_background_animation.flags & 1)) {
  if (g_background_animation.countdown <= 0) {
   reverse = g_background_animation.flags & 4;
   if (reverse) {
    if (--g_background_animation.frame < 0)
     g_background_animation.frame = g_background_animation.last_frame;
   } else {
    g_background_animation.frame++;
    if (g_background_animation.frame > g_background_animation.last_frame)
     g_background_animation.frame = 0;
   }
   g_background_animation.countdown = g_background_animation.delay;
   if (g_background_animation.frames && g_background_animation.transfer_enabled)
    display_load_background_resource(3, *(const void **)((const unsigned char *)g_background_animation.frames + (g_background_animation.frame << 2)), 0xC0, 3);
  }
  g_background_animation.countdown--;
 }
}
