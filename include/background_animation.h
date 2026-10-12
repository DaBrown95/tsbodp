/* Layout inferred from the VBlank tick and connected loader/cleanup routines. */
struct BackgroundAnimation {
 const void **frames;
 void *resource_handle;
 short countdown;
 unsigned short flags;
 unsigned char delay, last_frame;
 signed char frame;
 unsigned char transfer_enabled;
};
extern struct BackgroundAnimation g_background_animation;
extern unsigned int g_game_flags;
struct BackgroundResource;
extern const unsigned short *display_load_background_resource(unsigned int, const struct BackgroundResource *, unsigned short, unsigned short);
extern void background_animation_load(int), background_animation_configure_alpha(void);
