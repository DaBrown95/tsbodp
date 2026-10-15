#ifndef SCENE_STARTUP_H
#define SCENE_STARTUP_H

#include "scene_environment.h"
#include "input.h"

/* Observed 56-byte player stride; flags overlap the existing single-player
 * SceneModeFlags view. No array bound or full allocation is established. */
struct SceneStartupPlayer {
    unsigned int unknown00, flags;
    unsigned char unknown08[48];
};
/* A bounded access view sharing the audio-options root, not a second object. */
struct SceneStartupLoadOptions {
    unsigned char unknown00[184];
    unsigned int selection;
};
extern struct SceneStartupPlayer g_scene_startup_players[];
extern struct SceneStartupLoadOptions g_scene_startup_load_options;
extern unsigned char g_resource_selected;
void save_world_initialize(void), save_stream_load_buffer(unsigned int);
void scene_prepare_load(void), scene_initialize_transient_slots(void);
void scene_check_initial_time_flags(void);
struct FrameSpriteResource;
unsigned short frame_initialize_transient_definition(unsigned char, unsigned char,
                                                     struct FrameSpriteResource *);
extern struct FrameSpriteResource g_scene_startup_transient2, g_scene_startup_transient3;
extern struct FrameSpriteResource g_scene_startup_transient6, g_scene_startup_transient7;
#endif
