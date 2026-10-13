#include "frame_scene_player.h"
void frame_scene_effect_configure(struct FrameObject *,unsigned char);
void frame_scene_effect_refresh(struct FrameObject *);
void frame_scene_effect_tick(struct FrameObject *);
void frame_scene_effect_remove(struct FrameObject *);
void frame_scene_effect_interact(struct FrameObject *,struct FrameObject *);
unsigned char frame_grid_snap_point_to_center(void *,const struct FramePoint *,struct FramePoint *);
extern int g_frame_scene_effect_speeds[];
extern unsigned char g_frame_scene_effect_script[];
struct FrameSceneSavedEffect *frame_create_scene_saved_effect(unsigned char kind,int x,int y)
{
 struct FrameActorObject *object=(struct FrameActorObject *)frame_allocate_object(6);
 struct FrameSceneSavedEffect *effect=(struct FrameSceneSavedEffect *)object;
 struct FramePoint point;
 point.x=x>>16;
 point.y=y>>16;
 frame_grid_snap_point_to_center(g_frame_registration,&point,&point);
 frame_set_position((struct FrameObject *)object,point.x<<16,point.y<<16);
 object->subtype=kind;
 object->actor_id=kind;
 object->direction=4;
 frame_scene_effect_configure((struct FrameObject *)object,1);
 frame_scene_effect_refresh((struct FrameObject *)object);
 object->default_state=29;
 transition_object_set_state((struct FrameObject *)object,29);
 frame_set_variant_state((struct FrameObject *)object,0);
 effect->value=0x32000000;
 effect->owner=0;
 object->on_step=frame_scene_effect_tick;
 object->on_remove=frame_scene_effect_remove;
 object->on_interact=(void (*)(struct FrameObject *))frame_scene_effect_interact;
 object->oam.gfx_mode=0;
 object->oam.double_tile_size=0;
 object->speed=g_frame_scene_effect_speeds[object->actor_id];
 object->flags=0x1005045d;
 frame_set_subtype_object_palette((struct FrameObject *)object,
  (const void *const *)g_frame_scene_effect_script);
 frame_update_actor_state((struct FrameObject *)object);
 object->before_step=resource_object_before_step;
 return effect;
}
