#include "view_effects.h"

void transition_set_view_mode(unsigned int mode, unsigned char view)
{
    g_resource_view_motion[view].mode = mode;
    g_resource_view_effects[view].mode = 0;

    switch (mode) {
    case 0:
        goto mode_0_exit;
    case 1:
        g_resource_view_motion[view].object = 0;
        goto mode_1_exit;
    case 2:
        goto mode_2_exit;
    case 3:
        goto mode_3_exit;
    case 4:
        goto mode_4_exit;
    case 5:
        goto mode_5_exit;
    }
    return;

mode_0_exit:
    return;
mode_1_exit:
    return;
mode_2_exit:
    return;
mode_3_exit:
    return;
mode_4_exit:
    return;
mode_5_exit:
    return;
}
