#include "event_record.h"

void transition_record_event(unsigned int kind, struct EventPayload payload) {
 struct EventRecord record;
 unsigned int payload_word;
 g_event_sequence++;
 memory_fill(&record, 0, 12);
 record.kind = kind;
 switch (kind) {
 case 1: case 4: case 6: case 11: case 12: case 13:
  break;
 case 3:
  record.payload.halfwords[0] = ~*(volatile unsigned short *)0x04000130;
  break;
 case 2:
  __builtin_memcpy(&payload_word, &payload, sizeof payload_word);
  record.payload.halfwords[0] = payload_word;
  break;
 case 5:
  record.payload.bytes[1] = payload.storage.bytes[0];
  record.payload.bytes[2] = payload.storage.bytes[1];
  record.payload.bytes[3] = payload.storage.bytes[2];
  record.payload.bytes[0] = event_get_link_slot();
  break;
 case 7:
  __builtin_memcpy(&payload_word, &payload, sizeof payload_word);
  record.payload.word = payload_word;
  break;
 case 8:
  *(struct EventPayload *)&record.payload = g_event_vector_a;
  break;
 case 9:
  *(struct EventPayload *)&record.payload = g_event_vector_b;
  break;
 case 10:
  *(struct EventPayload *)&record.payload = g_event_vector_c;
  break;
 }
 record.sequence = g_event_sequence;
 memory_copy(&g_event_record, &record, 12);
 g_game_flags |= 0x40;
}
