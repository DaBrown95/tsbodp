#ifndef SCENE_SCROLL_TEXT_H
#define SCENE_SCROLL_TEXT_H
#include "frame.h"
#include "scene_audio_options.h"
#include "transition_object.h"
/* Observed sixteen-byte RAM view; complete allocation ownership is unproven. */
struct SceneScrollTextState {struct FrameObject *latest,*held;short x,y;unsigned char stopped,unknown_0d[3];};
/* Alternate byte access view of the existing object at +0xd1. */
struct SceneScrollDisplayFlags {unsigned char unknown_00[0xd1];unsigned char low:2;unsigned char control:2;unsigned char high:4;};
extern struct SceneScrollTextState g_scene_scroll_text_state;
extern const unsigned int g_scene_scroll_control3,g_scene_scroll_control2;
extern const struct BackgroundResource g_scene_scroll_background3,g_scene_scroll_background2;
extern const struct BackgroundResource *const g_scene_scroll_text_backgrounds[];
extern const unsigned short g_scene_scroll_palette[];
void resource_bios_swi_0b(const void *,void *,unsigned int);
void transition_configure_alpha(unsigned short,unsigned short);
void transition_set_alpha(unsigned short,unsigned short);
struct FrameObject *display_scene_create_label(unsigned int,const char **);

void frame_set_variant_state(struct FrameObject *,unsigned char);
struct FrameObject *display_allocate_text_object(const char **);
void frame_set_centered_integer_position(struct FrameObject *,short,int);
/* Row-thirteen callbacks, followed by their sequential text/object path. */
void scene_scroll_text_initialize(void),scene_scroll_text_step(void),scene_scroll_text_shutdown(void);
void scene_scroll_text_append(void);
void scene_scroll_text_end_step(struct FrameObject *);
void scene_scroll_text_regular_step(struct FrameObject *);
void scene_scroll_text_hold_step(struct FrameObject *);
void scene_scroll_text_confirm(void),scene_scroll_text_cancel(void),scene_scroll_text_vertical(void),scene_scroll_text_horizontal(void),scene_scroll_text_update(void);
#endif
