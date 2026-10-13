#ifndef LINK_EVENT_RECEIVE_H
#define LINK_EVENT_RECEIVE_H
#include "event_record.h"
#include "link_state.h"
#include "scene_request.h"
#include "frame_random.h"
#include "display_text_runtime.h"

/* Partial, overlapping receive views. The twelve-byte records and word-fill
 * view share a base. Join +0x14 and +0x54 also expose the pair/vector views;
 * these declarations do not establish separate storage or complete bounds. */
struct LinkReceivedJoin {
    int identifier;
    unsigned int values[4];
    unsigned char unknown14[100], metadata[4];
};
struct LinkReceivedPair { struct EventPayload first, second; };
extern struct EventRecord g_link_received_events[];
extern unsigned int g_link_received_words[];
extern unsigned char g_link_received_sequence[], g_link_peer_count;
extern unsigned short g_link_received_input[];
extern struct LinkReceivedJoin g_link_received_join;
extern struct LinkReceivedPair g_link_received_pairs[];
extern struct EventPayload g_link_received_vectors[];
extern unsigned int g_scene_id;

void link_apply_received_events(void);
void resource_submit_scene(unsigned int, unsigned int, unsigned int);
void display_cpu_copy(const void *, void *, unsigned int);
/* Original providers remain unconverted. */
void link_stage_080042a4(void), link_stage_0800450c(void);
#endif
