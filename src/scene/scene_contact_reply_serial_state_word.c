#include "scene_contact_serial_words.h"

void scene_contact_reply_serial_state_word(unsigned short *length, unsigned short *buffer)
{
    *length = 2;
    *buffer = g_scene_contact_serial_notice_state.word10;
}
