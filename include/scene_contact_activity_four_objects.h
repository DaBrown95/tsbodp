#ifndef SCENE_CONTACT_ACTIVITY_FOUR_OBJECTS_H
#define SCENE_CONTACT_ACTIVITY_FOUR_OBJECTS_H

#include "scene_contact_activity_four_event.h"

/* Whole-object-rooted prefix within the observed 320-byte allocation.
 * The state byte at +4E and signed timer word at +58 have distinct roles. */
struct SceneContactActivityFourControlObject {
    unsigned char unknown00[0x4e], state;
    unsigned char unknown4f[9];
    int timer;
};

extern struct FrameVariantResource
    g_scene_contact_activity_four_primary_animation;
extern struct FrameVariantResource
    g_scene_contact_activity_four_control_animation;
extern struct FrameVariantResource
    g_scene_contact_activity_four_control_failed_animation;
extern struct FrameVariantResource
    g_scene_contact_activity_four_auxiliary_animation;

struct FrameObject *scene_contact_activity_four_create_primary(void);
struct FrameObject *scene_contact_activity_four_create_control(void);
struct FrameObject *scene_contact_activity_four_create_auxiliary(void);
void scene_contact_activity_four_step_control_object(struct FrameObject *);

/* Specific one-object callback views. The auxiliary body remains original. */
void scene_contact_activity_four_step_primary_object(struct FrameObject *);
void scene_contact_original_step_four_auxiliary(struct FrameObject *);

#endif
