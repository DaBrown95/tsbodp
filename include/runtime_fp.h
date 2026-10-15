/* This is a software floating point library which can be used instead of
   the floating point routines in libgcc1.c for targets without hardware
   floating point. 
 Copyright (C) 1994, 1995, 1996, 1997, 1998 Free Software Foundation, Inc.

This file is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2, or (at your option) any
later version.

In addition to the permissions in the GNU General Public License, the
Free Software Foundation gives you unlimited permission to link the
compiled version of this file with other programs, and to distribute
those programs without any restriction coming from the use of this
file.  (The General Public License restrictions do apply in other
respects; for example, they cover modification of the file, and
distribution when not linked into another program.)

This file is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; see the file COPYING.  If not, write to
the Free Software Foundation, 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */

/* As a special exception, if you link this library with other files,
   some of which are compiled with GCC, to produce an executable,
   this library does not by itself cause the resulting executable
   to be covered by the GNU General Public License.
   This exception does not however invalidate any other reasons why
   the executable file might be covered by the GNU General Public License.  */

/* This implements IEEE 754 format arithmetic, but does not provide a
   mechanism for setting the rounding mode, or for generating or handling
   exceptions.

   The original code by Steve Chamberlain, hacked by Mark Eichin and Jim
   Wilson, all of Cygnus Support.  */


/* Double-only source view adapted from pinned fp-bit-base.c. No NaN storage ownership is assigned here. */
#ifndef RUNTIME_FP_H
#define RUNTIME_FP_H
#define NGARDS 8L
#define GARDROUND 0x7f
#define GARDMASK  0xff
#define GARDMSB   0x80
#define EXPBITS 11
#define EXPBIAS 1023
#define FRACBITS 52
#define EXPMAX (0x7ff)
#define QUIET_NAN 0x8000000000000LL
#define FRAC_NBITS 64
#define FRACHIGH  0x8000000000000000LL
#define FRACHIGH2 0xc000000000000000LL

#include "runtime_integer.h"
typedef UDItype fractype;
typedef USItype halffractype;
typedef DFtype FLO_type;
typedef DItype intfrac;
#define LSHIFT(a) { a = (a & 1) | (a >> 1); }
#define NORMAL_EXPMIN (-(EXPBIAS)+1)
#define IMPLICIT_1 (1LL<<(FRACBITS+NGARDS))
#define IMPLICIT_2 (1LL<<(FRACBITS+1+NGARDS))
typedef enum { CLASS_SNAN, CLASS_QNAN, CLASS_ZERO, CLASS_NUMBER, CLASS_INFINITY } fp_class_type;
typedef struct {
    fp_class_type class;
    unsigned int sign;
    int normal_exp;
    union { fractype ll; halffractype l[2]; } fraction;
} fp_number_type;
/* The ABI stores a double's high word first, unlike the DI fraction pair. */
typedef union {
    FLO_type value;
    fractype value_raw;
    halffractype words[2];
    struct {
        fractype fraction:FRACBITS __attribute__((packed));
        unsigned int exp:EXPBITS __attribute__((packed));
        unsigned int sign:1 __attribute__((packed));
    } bits;
} FLO_union_type;
extern fp_number_type g_runtime_double_nan;
static inline fp_number_type *nan(void) { return &g_runtime_double_nan; }
static inline int isnan(fp_number_type *x) { return x->class == CLASS_SNAN || x->class == CLASS_QNAN; }
static inline int isinf(fp_number_type *x) { return x->class == CLASS_INFINITY; }
static inline int iszero(fp_number_type *x) { return x->class == CLASS_ZERO; }
FLO_type __pack_d(fp_number_type *);
void __unpack_d(FLO_union_type *, fp_number_type *);
fp_number_type *_fpadd_parts(fp_number_type *, fp_number_type *, fp_number_type *);
FLO_type __adddf3(FLO_type, FLO_type), __subdf3(FLO_type, FLO_type);
FLO_type __muldf3(FLO_type, FLO_type), __divdf3(FLO_type, FLO_type);
int __fpcmp_parts_d(fp_number_type *, fp_number_type *);

#endif
