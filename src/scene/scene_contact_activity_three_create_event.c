#include "scene_contact_activity_three.h"
#define STATE ((struct SceneContactActivityThreeState*)g_scene_contact_state)
static inline void observer_absolute_point(struct FramePoint *point) {
 frame_read_attachment(((struct FrameObject*)STATE->observer.address),0,point);
 point->x=(int)((unsigned int)((struct FrameObject*)STATE->observer.address)->position.x+((unsigned int)point->x<<16));
 point->y=(int)((unsigned int)((struct FrameObject*)STATE->observer.address)->position.y+((unsigned int)point->y<<16));
}
struct FrameObject *scene_contact_activity_three_create_event(void) {
 struct SceneContactActivityThreeObject *object=(void*)frame_allocate_scene_object();
 struct FramePoint point;unsigned int value;
 object->id=5;object->contact_mode=0;object->double_size=0;object->layer=1;object->palette=15;object->flags=9;
 observer_absolute_point(&point);
 frame_set_position((struct FrameObject*)object,point.x,point.y);
 value=STATE->primary->shared_slot;
 if(value<=6)object->direction=value+25;else object->direction=value-7;
 object->speed=STATE->secondary->shared_slot<<15;
 frame_set_animation_record((struct FrameObject*)object,&g_scene_contact_activity_three_event_animation);
 object->on_step=scene_contact_activity_three_step_event;
 object->outcome=0;object->phase=0;
 return (struct FrameObject*)object;
}
asm(".align 2,0");
