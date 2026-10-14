#include "scene_contact_activity_three.h"
#define STATE ((struct SceneContactActivityThreeState*)g_scene_contact_state)
void scene_contact_activity_three_get_observer_point(struct FramePoint *point) {
 frame_read_attachment(((struct FrameObject*)STATE->observer.address),0,point);
 point->x=(int)((unsigned int)((struct FrameObject*)STATE->observer.address)->position.x+((unsigned int)point->x<<16));
 point->y=(int)((unsigned int)((struct FrameObject*)STATE->observer.address)->position.y+((unsigned int)point->y<<16));
}
asm(".align 2,0");
