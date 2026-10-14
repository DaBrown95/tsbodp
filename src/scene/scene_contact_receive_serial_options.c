#include "scene_contact_serial_session.h"
#include "heap.h"
#include "scene_request.h"
#include "display_text_bank.h"
#include "display_text_runtime.h"

void scene_contact_receive_serial_options(unsigned short *length,unsigned short *buffer)
{
 unsigned char mode;
 g_scene_contact_serial_session.word10=0;
 mode=((unsigned char*)buffer)[8];
 heap_copy(g_scene_contact_serial_options,buffer,8);
 g_scene_request.unknown_10=1;
 g_scene_request.unknown_14=45;
 g_scene_request.mode=g_scene_contact_serial_request_modes[mode];
 g_scene_contact_serial_session.status04=235;
}
