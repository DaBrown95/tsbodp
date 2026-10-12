#include "background_animation.h"

struct BackgroundAnimationDescriptor {
 const void **frames;
 const void *palette_resource;
 const unsigned int *background_control;
 unsigned int unknown_0c;
 unsigned char last_frame, delay, flags, unknown_13;
};
extern struct BackgroundAnimationDescriptor g_background_animation_descriptors[];
extern void display_show_background(unsigned int, unsigned int);
extern unsigned int display_load_resource_palette(const struct BackgroundResource *, unsigned short);
extern void display_write_background_map(unsigned int, const unsigned short *, unsigned short, unsigned short, unsigned int, unsigned int);
extern unsigned short g_background_animation_placement[];

void background_animation_load(int kind) {
 struct BackgroundAnimationDescriptor *descriptor;
 struct BackgroundAnimationDescriptor *start;
 const void **frames;
 if ((g_background_animation.flags & 8) || (!g_background_animation.transfer_enabled && kind)) {
  g_background_animation.transfer_enabled = kind;
  g_background_animation.frame = 0;
  start = g_background_animation_descriptors;
  descriptor = start + kind;
  g_background_animation.last_frame = descriptor->last_frame;
  g_background_animation.delay = descriptor->delay;
  g_background_animation.countdown = descriptor->delay;
  g_background_animation.frames = descriptor->frames;
  if ((g_game_flags & 0x100020) != 0x100020) {
   display_show_background(3, **(const unsigned int **)((unsigned char *)g_background_animation_descriptors + 8 + kind*20));
   display_load_resource_palette(*(const void **)((unsigned char *)g_background_animation_descriptors + 4 + kind*20), 3);
   frames = g_background_animation.frames;
   frames += g_background_animation.frame;
   display_load_background_resource(3, *frames, 0xC0, 3);
   display_write_background_map(3, g_background_animation_placement, 0xC0, 3, 0, 0);
   g_background_animation.flags |= descriptor->flags;
  }
  g_background_animation.flags &= 0xFFF7;
 }
}
