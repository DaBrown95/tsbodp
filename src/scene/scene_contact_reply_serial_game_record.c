#include "scene_contact_serial_session.h"
#include "heap.h"
#include "scene_request.h"
#include "display_text_bank.h"
#include "display_text_runtime.h"

void scene_contact_reply_serial_game_record(unsigned short *length,unsigned short *buffer)
{
 union SceneContactSerialRecord *record=(void*)buffer;
 unsigned char *output=record->bytes;
 unsigned char *source=&g_scene_contact_serial_capture.bytes[16];
 record->words[0]=g_scene_contact_serial_capture.words[0];
 record->words[1]=g_scene_contact_serial_capture.words[1];
 heap_copy(output+8,source,16);
 heap_copy(output+24,source+16,8);
 heap_copy(output+32,source+24,8);
 heap_copy(output+40,source+136,24);
 heap_copy(output+64,source+160,44);
 *length=108;
 g_scene_request.unknown_10=3;
 g_scene_request.unknown_14=45;
 g_scene_contact_serial_session.status04=237;
}
