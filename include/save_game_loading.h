#ifndef SAVE_GAME_LOADING_H
#define SAVE_GAME_LOADING_H
#include "save_game_serialization.h"

/* Incoming word is unused by the accepted body; the original caller passes 3. */
void save_stream_load_buffer(unsigned int);
/* Restores the game-state fields and derives the pending condition columns. */
void save_stream_load_game_state(void);
void save_stream_read_world_record(struct SaveStreamWorldRecord *);
void save_stream_read_relation_values(struct DisplayMenuRelationValues *);
void save_stream_read_six_value_words(int *);
void save_stream_read_six_nibbles(struct SaveStreamSixNibbles *);
void save_stream_read_nibble_state(void);
void save_stream_read_flag_words(void);
struct FrameActorNeedState;
void frame_load_actor_needs(struct FrameActorNeedState *);
void save_stream_read_actor_entries(void *);
#endif
