#ifndef DISPLAY_CONDITION_PANEL_LIFECYCLE_H
#define DISPLAY_CONDITION_PANEL_LIFECYCLE_H

#include "display_scene_lifecycle.h"

void condition_panel_close(void);

/* Existing transition dispatcher; its original body remains unconverted. */
void transition_run_second(unsigned short, unsigned int);

#endif
