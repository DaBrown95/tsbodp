#ifndef STARTUP_BUFFER_H
#define STARTUP_BUFFER_H
#include "heap.h"

/* Byte-addressable allocation storage; no structured element format inferred. */
extern unsigned char *g_startup_buffer_03005e5c;
void startup_allocate_buffer_03005e5c(void);
#endif
