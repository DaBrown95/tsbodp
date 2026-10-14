#ifndef FRAME_SERIALIZED_ACTOR_H
#define FRAME_SERIALIZED_ACTOR_H
struct FrameObject;
struct FrameSerializedActorPayload {
 unsigned int unknown00; short x,y;
 unsigned char actor,direction;
};
extern unsigned int g_frame_world_id;
extern unsigned char g_scene_world_state[];
struct FrameObject *frame_create_actor(unsigned int,unsigned char,int,int);
struct FrameObject *frame_create_scene_actor_resource(unsigned char,unsigned char);
#endif
