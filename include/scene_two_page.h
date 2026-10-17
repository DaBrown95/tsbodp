#ifndef SCENE_TWO_PAGE_H
#define SCENE_TWO_PAGE_H

#include "scene_text_bank.h"
#include "display_scene_setup.h"
#include "transition.h"

/* Two observed ROM records; valid selectors and resource backing are provisional. */
struct SceneTwoPageRow {
    const struct BackgroundResource *resource;
    unsigned int text_id;
    unsigned char font, unknown_09;
    unsigned short text_y;
};
extern const struct SceneTwoPageRow g_scene_two_page_rows[];
extern const unsigned int g_scene_two_page_default_control;

void scene_two_page_initialize(void);
void scene_two_page_step(void);
void scene_two_page_shutdown(void);

#endif
