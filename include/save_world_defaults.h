#ifndef SAVE_WORLD_DEFAULTS_H
#define SAVE_WORLD_DEFAULTS_H
#include "heap.h"
#include "frame_game_value.h"
/* Observed clear span, not a complete storage ownership contract. */
struct SaveWorldDefaultState { unsigned char bytes[1876]; };
union ResourceGameState;
struct ActorEntryContext;
struct SceneContactSerialPlayerInputPrefix;
extern union ResourceGameState g_resource_game_state;
extern struct SceneContactSerialPlayerInputPrefix g_scene_contact_serial_player_input;
extern const unsigned char g_save_world_default_name[];
void actor_entry_prepare(struct ActorEntryContext *);
void save_world_reset_defaults(void);
/* Explicit original providers; these declarations confer no C credit. */
void save_world_original_reset_hook(void);
/* Counted string copy with zero padding; returns the original destination. */
unsigned char *runtime_copy_padded_string(unsigned char *,const unsigned char *,unsigned int);
#endif
