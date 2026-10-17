#ifndef SCENE_PREVIOUS_PARAMETER_RETURN_H
#define SCENE_PREVIOUS_PARAMETER_RETURN_H

#include "display_scene_lifecycle.h"
#include "display_catalog_text.h"
#include "audio_game.h"
#include "resource_commands.h"

/* Existing provider signatures; no new provider implementation or type change. */
void display_configure_tile_allocation(unsigned char);
void transition_run_first(unsigned short, unsigned int);
void transition_run_second(unsigned short, unsigned int);

/* Fixed ROM resource/control prefixes; full asset extents remain unproved. */
extern const unsigned int g_scene_previous_parameter_return_control0;
extern const unsigned int g_scene_previous_parameter_return_control3;
extern const struct BackgroundResource g_scene_previous_parameter_return_background3;
extern const struct BackgroundResource g_scene_previous_parameter_return_palette;

/* Scene phase row26; original names and gameplay meaning are provisional. */
void scene_previous_parameter_return_initialize(void);
void scene_previous_parameter_return_step(void);
void scene_previous_parameter_return_shutdown(void);

#endif
