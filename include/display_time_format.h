#ifndef DISPLAY_TIME_FORMAT_H
#define DISPLAY_TIME_FORMAT_H
#include "display_time.h"
#include "display_catalog_text.h"

/* Same-address role view of game options. Only the byte at +10 is read here;
 * its wider storage and the runtime meaning of nonzero remain provisional. */
struct DisplayTimeFormatOptions {
    unsigned char unknown_00[10], mode;
};
extern struct DisplayTimeFormatOptions g_display_time_format_options;
/* Unconverted BIOS division/remainder wrappers; no source coverage is implied. */
int display_bios_div(int, int);
int display_bios_remainder(int, int);
/* Returns the original output pointer. No output bound is supplied by this API. */
char *display_time_format(const struct DisplayTimeRecord *, char *, unsigned int);
#endif
