#include "scene_contact_serial_session.h"
#include "heap.h"
#include "scene_request.h"
#include "display_text_bank.h"
#include "display_text_runtime.h"

void scene_contact_reply_serial_text_rows(unsigned short *length,unsigned short *buffer)
{
 unsigned char *start=(void*)buffer;
 unsigned char *output;
 int row;
 *start=8;
 output=start+1;
 for(row=0;row<8;++row) {
  const unsigned char *source=g_scene_contact_serial_text_rows[display_text_selected_bank()][row];
  while(*source)*output++=*source++;
  *output++=*source;
 }
 if((unsigned int)output&1)*output++=0;
 *length=output-start;
}
