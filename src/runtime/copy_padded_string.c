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
 * Adapted from Newlib libc/string/strncpy.c, pret/agbcc revision
 * da598c1d918402c42c0c0d7128ba14567f3175e9.
 * Source: https://github.com/pret/agbcc/tree/da598c1d918402c42c0c0d7128ba14567f3175e9/libc/string
 * Changes: project name and unsigned-byte API, direct ANSI declaration,
 * 32-bit null detector and explicit previous-count padding-loop lifetime.
 * See licenses/Newlib-COPYING.txt.
 */
#include "save_world_defaults.h"

#define DETECT_NULL(x) (((x) - 0x01010101) & ~(x) & 0x80808080)

unsigned char *runtime_copy_padded_string(unsigned char *destination,
                                        const unsigned char *source,
                                        unsigned int count)
{
    unsigned char *dst = destination;
    const unsigned char *src = source;
    long *aligned_dst;
    const long *aligned_src;

    if (!(((long)src | (long)dst) & (sizeof(long) - 1)) &&
        count >= sizeof(long)) {
        aligned_dst = (long *)dst;
        aligned_src = (const long *)src;
        while (count >= sizeof(long) && !DETECT_NULL(*aligned_src)) {
            count -= sizeof(long);
            *aligned_dst++ = *aligned_src++;
        }
        dst = (unsigned char *)aligned_dst;
        src = (const unsigned char *)aligned_src;
    }
    while (count > 0) {
        --count;
        if ((*dst++ = *src++) == 0)
            break;
    }
    for (;;) {
        unsigned int previous = count--;
        if (!previous)
            break;
        *dst++ = 0;
    }
    return destination;
}
