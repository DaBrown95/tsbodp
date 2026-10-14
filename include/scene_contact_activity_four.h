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

extern const struct SceneContactActivityFourRow
    g_scene_contact_activity_four_rows[];
extern const struct SceneContactActivityFourItem
    g_scene_contact_activity_four_items[];
extern const unsigned int g_scene_contact_activity_four_background1;
extern const unsigned int g_scene_contact_activity_four_background2;
extern const struct BackgroundResource g_scene_contact_activity_four_map1;
extern const struct BackgroundResource g_scene_contact_activity_four_map2;
extern const struct BackgroundResource g_scene_contact_activity_four_map3;

void scene_contact_activity_four_initialize(void);
void scene_contact_activity_four_reset_items(void);
void scene_contact_activity_four_load_palettes(void);
void scene_contact_activity_four_clear_secondary(void);
unsigned int scene_contact_activity_four_complete(void);

/* Explicit original creators. The item call view groups the observed R0/R1
 * coordinate words; it is not a recovered original declaration. Selection
 * and slot remain complete incoming words. */
struct FrameObject *scene_contact_original_create_four_primary(void);
struct FrameObject *scene_contact_original_create_four_control(void);
struct FrameObject *scene_contact_original_create_four_auxiliary(void);
struct FrameObject *scene_contact_original_create_four_item(struct FramePoint,
    unsigned int, unsigned int);

#endif
