#ifndef DISPLAY_MAP_FILL_H
#define DISPLAY_MAP_FILL_H

/* The original provider accepts a word and consumes its low halfword locally. */
void display_fill_background_constant_rectangle(unsigned int, int, int, int, int,
                                                unsigned int);

#endif
