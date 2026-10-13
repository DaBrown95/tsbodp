#include "frame_actor_palette_menu.h"

void display_text_set_object_string(struct FrameObject *object, const char *text)
{
    display_text_update(object, &text);
}

asm(".align 2, 0");
