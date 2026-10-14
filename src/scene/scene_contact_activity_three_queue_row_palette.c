#include "scene_contact_activity_three.h"
void scene_contact_activity_three_queue_row_palette(struct FrameObject *base) {
 struct SceneContactActivityThreeObject *object=(void*)base;
 display_queue_palette(g_scene_contact_activity_three_background_entries[object->palette_source].palette,object->palette*16,16);
}
asm(".align 2,0");
