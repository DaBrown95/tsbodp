#ifndef LINK_ENDPOINT_SETUP_H
#define LINK_ENDPOINT_SETUP_H
#include "event_record.h"
#include "frame_random.h"
#include "resource_decode.h"
/* Observed access prefix only; names, ownership and complete capacity remain provisional. */
struct LinkEndpointSetupPrefix {
 int identifier;
 unsigned char active,slot,unknown06[2];
 unsigned int (*callback)(void);
 struct EventRecord *first,*second;
 struct EventRecord queue[2];
 struct EventRecord *first_records[4],*second_records[4];
 struct EventRecord first_storage[4],second_storage[4];
};
extern struct LinkEndpointSetupPrefix g_link_setup_state;
extern unsigned int g_link_word_0300733c,g_link_clock_03002178;
extern unsigned int g_link_word_0300734c,g_link_word_03007344,g_link_word_03007354,g_link_word_03007348;
extern unsigned int g_link_word_03002190,g_link_word_03002184,g_link_word_0300218c,g_link_recording;
extern unsigned char g_link_peer_count,g_link_byte_03007340,g_link_byte_03007338;
extern unsigned char g_link_byte_030072fc;
extern unsigned int g_frame_flags;
void link_initialize_endpoint(void),scene_stage_0803e3a8(void);
extern volatile unsigned int g_link_flags;
extern struct EventRecord g_link_received_events[],g_event_record;
void link_set_tick_callback(unsigned int (*)(void));
unsigned int link_tick_clock(void);
void link_reset_random_bytes(void);
void link_start_connection(void);
unsigned int link_current_random_byte(void);
unsigned int link_saved_random_byte(void);
void link_snapshot_random_byte(void);
#define LINK_REG16(a) (*(volatile unsigned short *)(a))
#endif
