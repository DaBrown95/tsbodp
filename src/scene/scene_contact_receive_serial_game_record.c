#include "scene_contact_serial_session.h"
#include "heap.h"
#include "scene_request.h"
#include "display_text_bank.h"
#include "display_text_runtime.h"

void scene_contact_receive_serial_game_record(unsigned short *length,unsigned short *buffer)
{
 union SceneContactSerialRecord *input=(void*)buffer;
 g_scene_contact_serial_session.matched08=(g_scene_contact_serial_game_word==input->words[0]);
 display_text_copy_bytes(g_scene_contact_serial_session.buffer0c,input,108);
 g_scene_request.unknown_10=2;
 g_scene_request.unknown_14=45;
 g_scene_contact_serial_session.status04=236;
}
