#include "link_peer_response.h"

unsigned int link_peer_responses_complete(void)
{
    if ((g_link_word_0300218c == 2 && g_link_byte_03007338 == 3) ||
        (g_link_word_0300218c == 3 && g_link_byte_03007338 == 7) ||
        (g_link_word_0300218c == 4 && g_link_byte_03007338 == 15))
        return 1;
    return 0;
}
asm(".align 2,0");
