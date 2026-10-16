#ifndef SCENE_LINK_STATUS_PRIVATE_H
#define SCENE_LINK_STATUS_PRIVATE_H
#include "display_scene_lifecycle.h"
#include "link_state.h"
#include "scene_request.h"
#include "display_map_fill.h"
#include "audio_game.h"
#include "display_text_fields.h"

/* Existing word fields retain the canonical request and link declarations. */
struct SceneLinkStatusNotice { unsigned short text, delay; };
struct SceneLinkStatusIndicatorResource {
 unsigned char x,y,unknown02[2];
 struct FrameVariantResource animation;
};
extern const struct SceneLinkStatusNotice g_link_status_notices[3];
/* Real provider API accepts FrameVariantResource*, and these consumers do not write it. */
extern struct SceneLinkStatusIndicatorResource g_link_status_indicator_resources[4];
extern struct FrameObject *g_link_status_indicators[4];
extern int g_link_status_visible_count,g_link_status_previous_count,g_link_status_flicker;
extern unsigned int g_link_status_previous_scene;
extern const unsigned int g_link_status_control3,g_link_status_control2,g_link_status_control0;
extern const struct BackgroundResource g_link_status_background3,g_link_status_background2,g_link_status_complete_background;
void display_enable_layers(unsigned short);
void display_clear_background_map(unsigned int);
unsigned int display_load_resource_palette(const struct BackgroundResource *,unsigned short);
void transition_run_first(unsigned short,unsigned int);
void transition_fade_black_in_record(unsigned short),transition_fade_black_out_record(unsigned short);
void link_initialize_endpoint(void),scene_stage_0803e3a8(void);
void set_word_0300217c(unsigned int),set_word_03002180_bit0(unsigned char);
/* Entry points; the larger step body remains unconverted. */
void scene_link_status_initialize(void),scene_link_status_step(void),scene_link_status_shutdown(void);
void scene_link_status_draw_notice(unsigned int),scene_link_status_create_indicator(unsigned int);

/* Target layout assertions, no emitted data or instruction traffic. */
typedef char link_status_frame312[(sizeof(struct FrameObject)==312 && __alignof__(struct FrameObject)==4)?1:-1];
typedef char link_status_variant16[(sizeof(struct FrameVariantResource)==16 && __alignof__(struct FrameVariantResource)==4)?1:-1];
typedef char link_status_notice4[(sizeof(struct SceneLinkStatusNotice)==4)?1:-1];
typedef char link_status_row20[(sizeof(struct SceneLinkStatusIndicatorResource)==20 && (unsigned int)&((struct SceneLinkStatusIndicatorResource*)0)->animation==4)?1:-1];
typedef char link_status_owner16[(sizeof(g_link_status_indicators)==16)?1:-1];
typedef char link_status_request24[(sizeof(struct SceneRequest)==24 && (unsigned int)&((struct SceneRequest*)0)->unknown_14==20)?1:-1];
#endif
