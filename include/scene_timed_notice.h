#ifndef SCENE_TIMED_NOTICE_H
#define SCENE_TIMED_NOTICE_H
#include "scene_link_menu.h"
#include "display_text_raster.h"
#include "audio_game.h"
#include "game_counter.h"
#include "input.h"
extern const unsigned int g_scene_timed_notice_control3;
extern const unsigned int g_scene_timed_notice_control0;
extern const struct BackgroundResource g_scene_timed_notice_background;
void scene_timed_notice_initialize(void);
void scene_timed_notice_step(void);
void scene_timed_notice_shutdown(void);
void scene_submit_default_request(unsigned int);
#endif
