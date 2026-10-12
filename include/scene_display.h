#include "display.h"
extern void display_reset_background(unsigned int), display_reset(void);
extern void display_release_memory(void *);
extern void display_set_mode(unsigned short);
extern void *scene_fill_bytes(void *, int, unsigned int);
