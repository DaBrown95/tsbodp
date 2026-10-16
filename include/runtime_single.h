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


/* Single-precision access view adapted from the pinned fp-bit-base.c FLOAT
 * selection. Shared class and DF declarations come from runtime_fp.h.
 * This assigns no static NaN storage or allocation ownership. */
#ifndef RUNTIME_SINGLE_H
#define RUNTIME_SINGLE_H
#include "runtime_fp.h"
typedef unsigned int UHItype __attribute__((mode(HI)));
#define SF_NGARDS 7L
#define SF_GARDROUND 0x3f
#define SF_GARDMASK 0x7f
#define SF_GARDMSB 0x40
#define SF_EXPBITS 8
#define SF_EXPBIAS 127
#define SF_FRACBITS 23
#define SF_EXPMAX (0xff)
#define SF_QUIET_NAN 0x100000L
#define SF_FRAC_NBITS 32
#define SF_FRACHIGH 0x80000000L
#define SF_FRACHIGH2 0xc0000000L
#define SF_NORMAL_EXPMIN (-(SF_EXPBIAS)+1)
#define SF_IMPLICIT_1 (1LL<<(SF_FRACBITS+SF_NGARDS))
#define SF_IMPLICIT_2 (1LL<<(SF_FRACBITS+1+SF_NGARDS))
typedef struct {
    fp_class_type class;
    unsigned int sign;
    int normal_exp;
    union { USItype ll; UHItype l[2]; } fraction;
} sf_number_type;
typedef union {
    SFtype value;
    USItype value_raw;
    struct {
        USItype fraction:SF_FRACBITS __attribute__((packed));
        unsigned int exp:SF_EXPBITS __attribute__((packed));
        unsigned int sign:1 __attribute__((packed));
    } bits;
} SF_union_type;
static inline int sf_isnan(sf_number_type *x) { return x->class == CLASS_SNAN || x->class == CLASS_QNAN; }
static inline int sf_isinf(sf_number_type *x) { return x->class == CLASS_INFINITY; }
static inline int sf_iszero(sf_number_type *x) { return x->class == CLASS_ZERO; }
SFtype __pack_f(sf_number_type *);
void __unpack_f(SF_union_type *,sf_number_type *);
SFtype __make_fp(fp_class_type,unsigned int,int,USItype);
DFtype __make_dp(fp_class_type,unsigned int,int,UDItype);
DFtype __negdf2(DFtype);
DFtype __extendsfdf2(SFtype);
SFtype __truncdfsf2(DFtype);

/* The upstream FLOAT object's NaN helper addresses this existing RAM record.
 * This is an external access view, not an initializer or allocation claim. */
extern sf_number_type g_runtime_single_nan;
static inline sf_number_type *sf_nan(void) { return &g_runtime_single_nan; }
sf_number_type *_fpadd_parts_f(sf_number_type *,sf_number_type *,sf_number_type *);
SFtype __addsf3(SFtype,SFtype), __subsf3(SFtype,SFtype);
SFtype __mulsf3(SFtype,SFtype), __divsf3(SFtype,SFtype);
SItype __fpcmp_parts_f(sf_number_type *,sf_number_type *);
SItype __cmpsf2(SFtype,SFtype);
SItype __eqsf2(SFtype,SFtype), __nesf2(SFtype,SFtype);
SItype __gtsf2(SFtype,SFtype), __gesf2(SFtype,SFtype);
SItype __ltsf2(SFtype,SFtype), __lesf2(SFtype,SFtype);
SFtype __floatsisf(SItype);
SItype __fixsfsi(SFtype);
SFtype __negsf2(SFtype);
#endif
