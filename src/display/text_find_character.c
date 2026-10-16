/*
 * Newlib distribution notice:
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */
/*
 * Adapted from Newlib libc/string/strchr.c, pret/agbcc revision
 * da598c1d918402c42c0c0d7128ba14567f3175e9.
 * Source: https://github.com/pret/agbcc/tree/da598c1d918402c42c0c0d7128ba14567f3175e9/libc/string
 * Changes: project name, direct ANSI declaration, 32-bit null detector,
 * and the original terminal zero alignment. See licenses/Newlib-COPYING.txt.
 */
#include "display_text_fields.h"

#define DETECT_NULL(x) (((x) - 0x01010101) & ~(x) & 0x80808080)

char *display_text_find_character(const char *text, int input)
{
    const unsigned char *s = (const unsigned char *)text;
    unsigned char c = (unsigned char)input;
    unsigned long mask, j;
    unsigned long *aligned;

    if (!((long)s & (sizeof(long) - 1))) {
        mask = 0;
        for (j = 0; j < sizeof(long); j++)
            mask = (mask << 8) | c;
        aligned = (unsigned long *)s;
        while (!DETECT_NULL(*aligned) && !DETECT_NULL(*aligned ^ mask))
            aligned++;
        s = (unsigned char *)aligned;
    }
    while (*s && *s != c)
        s++;
    if (*s == c)
        return (char *)s;
    return 0;
}
asm(".align 2, 0");
