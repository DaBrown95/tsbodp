#include "link_endpoint_setup.h"
void scene_link_reset_setup_state(void)
{
    g_link_flags &= ~4u;
    g_frame_flags &= ~0x20u;
    g_link_setup_state.identifier = -1;
    if (!(LINK_REG16(0x04000128) & 4))
        LINK_REG16(0x04000200) &= 0xffbf;
    LINK_REG16(0x04000200) &= 0xff7f;
    LINK_REG16(0x0400012a) = 0xffff;
    g_link_setup_state.active = 0;
    g_link_setup_state.slot = 0xff;
}
