#ifndef SCENE_ROW24_SELECTION_PRIVATE_H
#define SCENE_ROW24_SELECTION_PRIVATE_H

#include "scene_request_queue.h"
#include "input.h"
#include "audio_game.h"

/* Provisional names for the observed row24 selection path. */
unsigned char scene_row24_selection_move(unsigned int direction);
void scene_row24_selection_step(void);

/* Original08023908 consumes globals; complete data domains remain unproven. */
void scene_row24_selection_refresh_original(void);

#endif
