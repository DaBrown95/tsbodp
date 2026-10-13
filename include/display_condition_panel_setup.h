#ifndef DISPLAY_CONDITION_PANEL_SETUP_H
#define DISPLAY_CONDITION_PANEL_SETUP_H

#include "display_condition_panel_details.h"
#include "save_world_view_resources.h"

extern const unsigned int g_condition_panel_control0;
extern const unsigned int g_condition_panel_control1;
extern const unsigned int g_condition_panel_control2;
extern const unsigned int g_condition_panel_control3;
extern const struct BackgroundResource g_condition_panel_background3;
extern const struct BackgroundResource g_condition_panel_background2;
extern const struct BackgroundResource g_condition_panel_palette0;
extern const struct BackgroundResource g_condition_panel_palette7;
extern const struct PaletteRangeConfig g_condition_panel_ranges;

void condition_panel_initialize(void);
void transition_run_first(unsigned short, unsigned int);

#endif
