#include "link_status_poll_private.h"

unsigned int link_read_status_original(void)
{
    /* The three slot observations share the actual complete-object base. */
    volatile unsigned char *endpoint_bytes =
        (volatile unsigned char *)&g_link_setup_state;
    register unsigned char slot_word asm("r3") = endpoint_bytes[5];
    signed char *signed_endpoint_bytes =
        (signed char *)&g_link_setup_state;

    register int first_observation asm("r1");
    register int second_observation asm("r0");

    unsigned int result;

    first_observation = 5;
    first_observation = signed_endpoint_bytes[first_observation];
    if (first_observation == -1) {
        result = 0;
    } else {
        second_observation = 5;
        second_observation = signed_endpoint_bytes[second_observation];
        if (second_observation < (int)g_link_word_03002190) {
            result = g_link_word_0300218c;
        } else {
            g_link_setup_state.active = 0;
            {
                register unsigned char reset_value asm("r0") = 255u;
                reset_value |= slot_word;
                g_link_setup_state.slot = (unsigned char)reset_value;
            }
            g_link_flags |= 0x10000u;
            LINK_REG16(0x04000200) &= 0xff7f;
            LINK_REG16(0x0400012a) = 0xffff;
            result = 6;
        }
    }
    return result;
}
