#include "scene_contact_serial_words.h"

unsigned int scene_contact_dispatch_serial_notice(unsigned int kind,
        unsigned short *length, unsigned short *buffer)
{
    switch (kind) {
    case 0x40:
    case 0x43:
        break;
    case 0x41:
        scene_contact_original_notice_41(length, buffer);
        break;
    case 0x42:
        scene_contact_original_notice_42(length, buffer);
        break;
    case 0x80:
        scene_contact_reply_serial_game_word(length, buffer);
        break;
    case 0x81:
        scene_contact_original_notice_81(length, buffer);
        break;
    case 0x82:
        scene_contact_reply_serial_state_word(length, buffer);
        break;
    case 0x83:
        scene_contact_original_notice_83(length, buffer);
        break;
    default:
        return 0;
    }
    return 1;
}
asm(".align 2, 0");
