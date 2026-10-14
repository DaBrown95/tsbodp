#ifndef SCENE_CONTACT_ACTIVITY_FOUR_H
#define SCENE_CONTACT_ACTIVITY_FOUR_H

#include "scene_contact_menu.h"
#include "frame_random.h"

/* Observed row-four prefix within the 420-byte contact allocation. These
 * access views do not establish complete storage or arbitrary index bounds. */
struct SceneContactActivityFourState {
    struct FrameObject *object;
    unsigned char unknown04[8];
    short score;
    unsigned char unknown0e[10];
    struct FrameObject *first[8], *second[8], *control;
    unsigned char selections[8];
};

struct SceneContactActivityFourRow {
    struct DisplayTimeRecord clock;
    unsigned char count, interval, chance, unknown0b;
};

struct SceneContactActivityFourItem {
    unsigned char unknown00[16];
    const unsigned short *palette;
    unsigned char penalty, unknown15[3];
};

/* Whole-object-rooted flag prefix. The pinned byte mapping is checked;
 * this 216-byte access view does not describe the complete allocation. */
struct SceneContactActivityFourObjectFlags {
    unsigned char unknown00[0xd1];
    unsigned char mode:2, contact_mode:2, unknown_d1_4:1;
    unsigned char double_size:1, unknown_d1_6:2;
    unsigned char unknown_d2;
    unsigned char unknown_d3_0:4;
    signed char flag4:1;
    unsigned char flag5:1, unknown_d3_6:2;
    unsigned char unknown_d4;
    unsigned char tile_high:2, layer:2, palette:4;
};

extern const struct SceneContactActivityFourRow
    g_scene_contact_activity_four_rows[];
extern const struct SceneContactActivityFourItem
    g_scene_contact_activity_four_items[];
extern const unsigned int g_scene_contact_activity_four_background1;
extern const unsigned int g_scene_contact_activity_four_background2;
extern const struct BackgroundResource g_scene_contact_activity_four_map1;
extern const struct BackgroundResource g_scene_contact_activity_four_map2;
extern const struct BackgroundResource g_scene_contact_activity_four_map3;
extern struct FrameVariantResource g_scene_contact_activity_four_animation_a;
extern struct FrameVariantResource g_scene_contact_activity_four_animation_b;

void scene_contact_activity_four_initialize(void);
void scene_contact_activity_four_reset_items(void);
void scene_contact_activity_four_load_palettes(void);
void scene_contact_activity_four_clear_secondary(void);
unsigned int scene_contact_activity_four_complete(void);
struct FrameObject *scene_contact_activity_four_create_item(struct FramePoint,
    unsigned int, unsigned int);
void scene_contact_add_activity_score(int);

struct FrameTickObject;
void frame_set_animation_record(struct FrameObject *, struct FrameVariantResource *);
void frame_set_animation_frame(struct FrameTickObject *, unsigned char);

/* Reconstructed creators; their allocation and callback roles are bounded. */
struct FrameObject *scene_contact_activity_four_create_primary(void);
struct FrameObject *scene_contact_activity_four_create_control(void);
struct FrameObject *scene_contact_activity_four_create_auxiliary(void);

#endif
