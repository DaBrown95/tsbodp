#ifndef DISPLAY_PALETTE_CURVE_H
#define DISPLAY_PALETTE_CURVE_H

#include "display_palette_lifecycle.h"

/* Byte lookup view; valid indices and complete storage ownership are unproven. */
extern unsigned char g_palette_curve_values[];

/* Current ABI model: signed low halfwords in word registers, signed word result.
   The helpers retain the observed eight fractional bits and low-half result. */
int display_fixed_multiply(short, short);
int display_fixed_divide(short, short);

#endif
