#ifndef FRAME_SCENE_PLAYER_UPDATE_H
#define FRAME_SCENE_PLAYER_UPDATE_H

#include "frame_scene_player.h"
#include "transition_object.h"

/* Player actor initialization and installed update callback declarations. */
struct FrameActorNeedState;
struct FrameActorNeedTickState;
extern struct FrameActorNeedState g_display_menu_result_local_needs;
extern unsigned char g_frame_actor_palette_pair_definition[];
void frame_update_actor_needs(struct FrameActorNeedTickState *,
    struct FrameActorObject *);
void frame_actor_choose_need_action(struct FrameActorNeedState *,
    struct FrameActorObject *);
void frame_set_animation_commands(struct FrameObject *, FrameU8 *, FrameU8);

void frame_scene_player_step_1dfe4(struct FrameObject *);

#endif
