#ifndef SAVE_CONDITION_STATE_H
#define SAVE_CONDITION_STATE_H

#include "save_stream.h"
#include "resource_conditions.h"

/* Observed eight-byte ROM rows. The sentinel and index bounds are static findings. */
struct ConditionDisplayCompletion {
    unsigned int kind;
    unsigned char row, column, unknown06[2];
};
extern const struct ConditionDisplayCompletion g_condition_display_completions[];

void save_stream_write_condition_display_bits(void);
void save_stream_read_condition_display_bits(void);
void condition_finish_display_kind(unsigned int);

#endif
