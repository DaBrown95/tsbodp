#ifndef DISPLAY_PENDING_MUTATION_H
#define DISPLAY_PENDING_MUTATION_H
#include "display_pending_block.h"

/* Uses the original directional copy helper; its aligned backward offset is
 * preserved. */
void display_insert_pending_row(unsigned short, unsigned short,
    void (*)(unsigned int *, unsigned int *));
void display_remove_pending_row(unsigned short);

#endif
