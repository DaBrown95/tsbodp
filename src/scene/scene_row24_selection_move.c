#include "scene_row24_selection_private.h"

unsigned char scene_row24_selection_move(unsigned int direction)
{
    unsigned char selection = (unsigned char)g_scene_request.scene;

    switch (direction) {
    case 0:
        if (selection != 0 && selection != 4)
            selection = (unsigned char)(selection - 1);
        break;
    case 1:
        if (selection != 3 && selection != 7)
            selection = (unsigned char)(selection + 1);
        break;
    case 2:
        if (selection > 3)
            selection = (unsigned char)(selection - 4);
        break;
    case 3:
        if ((unsigned char)(selection - 4) > 3)
            selection = (unsigned char)(selection + 4);
        break;
    }
    return selection;
}

/* Own only the final two zero alignment bytes before08023908. */
asm(".align 2, 0");
