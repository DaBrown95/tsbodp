#include "scene_scroll_text.h"
void scene_scroll_text_regular_step(struct FrameObject *object){int y=object->position.y;if(y<0x240000)object->flags|=2;else if(y<0x200000)((struct SceneScrollDisplayFlags *)object)->control=1;}
asm(".align 2,0");
