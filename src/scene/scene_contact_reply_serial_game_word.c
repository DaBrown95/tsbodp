#include "scene_contact_serial_words.h"

void scene_contact_reply_serial_game_word(unsigned short *length, unsigned short *buffer)
{
    ((union SceneContactSerialPayloadWord *)buffer)->word = g_scene_contact_serial_game_word;
    *length = 4;
}
