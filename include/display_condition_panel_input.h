#ifndef DISPLAY_CONDITION_PANEL_INPUT_H
#define DISPLAY_CONDITION_PANEL_INPUT_H

#include "display_condition_panel.h"
#include "input.h"

/* Alternate access view of the same world root. Only the command byte's
 * offset is established here; the unknown prefix is not a complete layout. */
struct ConditionPanelExitView {
    unsigned char unknown00[0x73f];
    unsigned char code;
};

void condition_panel_step_input(void);
/* Full-word return-request argument read at 0x03004334 on this path. */
extern unsigned int g_condition_panel_return_arg;

/* Original detail provider remains unconverted. */
void condition_panel_draw_details(unsigned int, unsigned int);

/* Established providers retain their full-word input contracts. */
unsigned int audio_play_animation_cue(unsigned int);
void scene_submit_default_request(unsigned int);

#endif
