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

/* Selected body adapted from pinned pret/agbcc fp-bit-base.c.
 * Source-only SF view uses distinct names alongside the existing DF view. */
#include "runtime_single.h"
#define F_D_BITOFF (52+8-(23+7))
#define FLOAT_BIT_ORDER_MISMATCH
#define FLOAT

void
__unpack_f (SF_union_type * src, sf_number_type * dst)
{
  /* We previously used bitfields to store the number, but this doesn't
     handle little/big endian systems conveniently, so use shifts and
     masks */
  USItype fraction;
  int exp;
  int sign;

#if defined(FLOAT_WORD_ORDER_MISMATCH) && !defined(FLOAT)
  SF_union_type swapped;

  swapped.words[0] = src->words[1];
  swapped.words[1] = src->words[0];
  src = &swapped;
#endif

#ifdef FLOAT_BIT_ORDER_MISMATCH
  fraction = src->bits.fraction;
  exp = src->bits.exp;
  sign = src->bits.sign;
#else
  fraction = src->value_raw & ((((USItype)1) << SF_FRACBITS) - (USItype)1);
  exp = ((int)(src->value_raw >> SF_FRACBITS)) & ((1 << SF_EXPBITS) - 1);
  sign = ((int)(src->value_raw >> (SF_FRACBITS + SF_EXPBITS))) & 1;
#endif

  dst->sign = sign;
  if (exp == 0)
    {
      /* Hmm.  Looks like 0 */
      if (fraction == 0)
	{
	  /* tastes like zero */
	  dst->class = CLASS_ZERO;
	}
      else
	{
	  /* Zero exponent with non zero fraction - it's denormalized,
	     so there isn't a leading implicit one - we'll shift it so
	     it gets one.  */
	  dst->normal_exp = exp - SF_EXPBIAS + 1;
	  fraction <<= SF_NGARDS;

	  dst->class = CLASS_NUMBER;
#if 1
	  while (fraction < SF_IMPLICIT_1)
	    {
	      fraction <<= 1;
	      dst->normal_exp--;
	    }
#endif
	  dst->fraction.ll = fraction;
	}
    }
  else if (exp == SF_EXPMAX)
    {
      /* Huge exponent*/
      if (fraction == 0)
	{
	  /* Attached to a zero fraction - means infinity */
	  dst->class = CLASS_INFINITY;
	}
      else
	{
	  /* Non zero fraction, means nan */
	  if (fraction & SF_QUIET_NAN)
	    {
	      dst->class = CLASS_QNAN;
	    }
	  else
	    {
	      dst->class = CLASS_SNAN;
	    }
	  /* Keep the fraction part as the nan number */
	  dst->fraction.ll = fraction;
	}
    }
  else
    {
      /* Nothing strange about this number */
      dst->normal_exp = exp - SF_EXPBIAS;
      dst->class = CLASS_NUMBER;
      dst->fraction.ll = (fraction << SF_NGARDS) | SF_IMPLICIT_1;
    }
}

asm(".align 2, 0");
