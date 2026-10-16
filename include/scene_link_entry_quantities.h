#ifndef SCENE_LINK_ENTRY_QUANTITIES_H
#define SCENE_LINK_ENTRY_QUANTITIES_H
#include "link_entry_receive.h"
#include "display_scene_lifecycle.h"

/* Same complete readonly declaration already used by the accepted linked
 * builder. Four observed rows are an access prefix, not a full ROM capacity. */
struct SceneLinkEntryCaption {
    unsigned char x, y, unknown02[2];
};
extern const struct SceneLinkEntryCaption g_scene_link_entry_captions[4];
extern const unsigned int g_scene_link_entry_text_control;
/* Exact existing API from frame_actor_palette_menu.h; this narrow declaration
 * avoids importing another unguarded frame view into this translation unit. */
void display_text_set_object_string(struct FrameObject *, const char *);
void scene_link_entry_draw_quantities(void);
#endif
