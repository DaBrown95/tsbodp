#ifndef SCENE_ROW24_SELECTION_PRIVATE_H
#define SCENE_ROW24_SELECTION_PRIVATE_H

#include "scene_request_queue.h"
#include "input.h"
#include "audio_game.h"

/* Provisional names for the observed row24 selection path. */
unsigned char scene_row24_selection_move(unsigned int direction);
void scene_row24_selection_step(void);

/* Refresh at 0x08023908 consumes globals; complete data domains remain unproven. */
void scene_row24_selection_refresh_original(void);

/* Canonical object slots, world values and display provider declarations. */
#include "display_scene_lifecycle.h"
#include "display_catalog_text.h"
#include "frame_contact_action.h"

void frame_set_variant_state(struct FrameObject *, unsigned char);
void transition_object_set_state(void *, unsigned char);
void transition_run_first(unsigned short, unsigned int);
void transition_run_second(unsigned short, unsigned int);

/* Fixed scalar controls and observed serialized resource/table prefixes.
 * Unsized tables do not establish a complete incoming scene domain. Resource
 * backing, including palette payload +2, remains a caller/asset precondition. */
extern const unsigned int g_scene_row24_selection_control0;
extern const unsigned int g_scene_row24_selection_control1;
extern const unsigned int g_scene_row24_selection_control2;
extern const unsigned int g_scene_row24_selection_control3;
extern const struct BackgroundResource g_scene_row24_selection_background2;
extern const unsigned int g_scene_row24_selection_first_text_ids[];
extern const unsigned int g_scene_row24_selection_second_text_ids[];
extern const unsigned char g_scene_row24_selection_value_permutation[];

/* These matched helper bodies consume globals; nominal signatures and complete
 * incoming caller domains remain provisional. */
void scene_row24_selection_prepare_original(void);
void scene_row24_selection_draw_content_original(void);

void scene_row24_selection_initialize(void);
void scene_row24_selection_shutdown(void);

/* Canonical text/condition/resource owners shared with the remaining row24
 * helpers. These declarations do not establish complete resource domains. */
#include "display_text_draw.h"
#include "scene_contact_menu.h"
#include "resource_conditions.h"
extern const unsigned int g_scene_row24_selection_descriptor_text_ids[];

/* Label creation consumes globals; line drawing receives actual word homes
 * and a NUL-terminated text cursor. Original names/types remain provisional. */
void scene_row24_selection_create_labels(void);
void scene_row24_selection_draw_lines(unsigned int *, int, int *, const char *);

#endif
