#ifndef FRAME_NEED_EFFECT_FACTORY_H
#define FRAME_NEED_EFFECT_FACTORY_H
struct FrameObject;
struct ActorEntryContext;
struct FrameNeedEffectPayload {
 unsigned int unknown00; short x,y;
 unsigned char kind,direction,optional,parameter,enabled,mode;
};
struct FrameNeedEffectFactoryWorld {
 unsigned char unknown00[0x20],kind33_selector,unknown21[0xe7-0x21],kind_latches;
};
extern unsigned char g_scene_entry_data[];
extern unsigned int g_frame_world_id;
unsigned char actor_entry_collection_group_marked(struct ActorEntryContext *,unsigned int);
struct FrameObject *frame_create_need_effect_resource(unsigned char,unsigned char);
#endif
