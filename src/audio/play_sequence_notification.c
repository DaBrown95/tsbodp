#include "audio_game.h"
void audio_play_sequence_notification(unsigned char id)
{
 if(g_audio_game_options.sequences_volume) {
  struct AudioSequenceDescriptor *descriptor,*table;
  const void *sequence;
  register unsigned int parameters asm("r1");
  g_audio_control.flags|=0x80;
  table=g_audio_sequence_descriptors;
  descriptor=&table[id];
  parameters=descriptor->parameters.word;
  sequence=descriptor->sequence;
  audio_start_sequence(sequence,4,(unsigned char)(parameters>>8));
  audio_sync_game_state();
 }
}
