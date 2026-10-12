#ifndef FRAME_ACTOR_SCENE_H
#define FRAME_ACTOR_SCENE_H
/* Bounded global view inferred from the two actor scene selectors. */
union ResourceGameState;
struct FrameObject;
extern union ResourceGameState g_resource_game_state;
struct FrameActorSceneState {
 unsigned char unknown_00[0x440];
 unsigned int stage;
 unsigned char unknown_444[0x300];
 unsigned short counter;
 unsigned char unknown_746[2];
 unsigned char selected_actor, variant, unknown_74a[2];
 int timer;
 unsigned char ready;
};
extern unsigned char g_scene_mode_bytes[4];
extern unsigned int g_resource_scene_arg;
extern unsigned char g_actor_scene_request_active;
struct FrameActorSceneResult { unsigned short id; };
extern struct FrameActorSceneResult g_actor_scene_result_id;
struct FrameActorSceneRequest {
 unsigned int unknown_00;
 unsigned char active, unknown_05[3];
 struct FrameObject *object;
};
extern struct FrameActorSceneRequest g_actor_scene_request;
void resource_submit_scene(unsigned int,unsigned int,unsigned int);
void frame_advance_actor_scene_counter(void);
struct FrameObject *frame_create_scene_object(unsigned int,unsigned int,unsigned int,unsigned int);
void frame_activate_actor_scene_request(void);
void display_scene_stage_08027dc0(unsigned int);
#endif
