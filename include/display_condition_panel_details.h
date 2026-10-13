#ifndef DISPLAY_CONDITION_PANEL_DETAILS_H
#define DISPLAY_CONDITION_PANEL_DETAILS_H
#include "display_map_fill.h"

#include "display_condition_panel.h"

/* Six text-ID words per observed row; the table's full extent is unknown. */
extern const unsigned int g_condition_panel_text_ids[][6];

void condition_panel_draw_details(unsigned int, unsigned int);

/* Existing rectangle and animation providers retain their observed contracts. */
struct FrameTickObject;
void frame_set_animation_frame(struct FrameTickObject *, unsigned char);

#endif
