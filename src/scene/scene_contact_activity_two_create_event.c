#include "scene_contact_activity_two.h"
struct FrameObject *scene_contact_activity_two_create_event(unsigned int index) {
 struct SceneContactActivityTwoObject *object=(void *)frame_allocate_scene_object();
 object->id=2;object->subtype=index;
 object->contact_mode=0;object->double_size=0;object->layer=1;
 object->palette=g_scene_contact_activity_two_event_resources[object->subtype].palette_slot;
 object->flags=1;
 frame_set_position((struct FrameObject *)object,16*65536,32*65536);
 frame_set_animation_record((struct FrameObject *)object,&g_scene_contact_activity_two_event_resources[object->subtype].animation);
 audio_play_animation_cue(208);
 display_set_background_rectangle_palette(1,0,2,7,4,g_scene_contact_activity_two_event_resources[object->subtype].map_palette);
 return (struct FrameObject *)object;
}
asm(".align 2, 0");
