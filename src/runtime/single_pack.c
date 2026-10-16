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

SFtype
__pack_f ( sf_number_type *  src)
{
  SF_union_type dst;
  USItype fraction = src->fraction.ll;	/* wasn't unsigned before? */
  int sign = src->sign;
  int exp = 0;

  if (sf_isnan (src))
    {
      exp = SF_EXPMAX;
      if (src->class == CLASS_QNAN || 1)
	{
	  fraction |= SF_QUIET_NAN;
	}
    }
  else if (sf_isinf (src))
    {
      exp = SF_EXPMAX;
      fraction = 0;
    }
  else if (sf_iszero (src))
    {
      exp = 0;
      fraction = 0;
    }
  else if (fraction == 0)
    {
      exp = 0;
    }
  else
    {
      if (src->normal_exp < SF_NORMAL_EXPMIN)
	{
	  /* This number's exponent is too low to fit into the bits
	     available in the number, so we'll store 0 in the exponent and
	     shift the fraction to the right to make up for it.  */

	  int shift = SF_NORMAL_EXPMIN - src->normal_exp;

	  exp = 0;

	  if (shift > SF_FRAC_NBITS - SF_NGARDS)
	    {
	      /* No point shifting, since it's more that 64 out.  */
	      fraction = 0;
	    }
	  else
	    {
	      /* Shift by the value */
	      fraction >>= shift;
	    }
	  fraction >>= SF_NGARDS;
	}
      else if (src->normal_exp > SF_EXPBIAS)
	{
	  exp = SF_EXPMAX;
	  fraction = 0;
	}
      else
	{
	  exp = src->normal_exp + SF_EXPBIAS;
	  /* IF the gard bits are the all zero, but the first, then we're
	     half way between two numbers, choose the one which makes the
	     lsb of the answer 0.  */
	  if ((fraction & SF_GARDMASK) == SF_GARDMSB)
	    {
	      if (fraction & (1 << SF_NGARDS))
		fraction += SF_GARDROUND + 1;
	    }
	  else
	    {
	      /* Add a one to the guards to round up */
	      fraction += SF_GARDROUND;
	    }
	  if (fraction >= SF_IMPLICIT_2)
	    {
	      fraction >>= 1;
	      exp += 1;
	    }
	  fraction >>= SF_NGARDS;
	}
    }

  /* We previously used bitfields to store the number, but this doesn't
     handle little/big endian systems conveniently, so use shifts and
     masks */
#ifdef FLOAT_BIT_ORDER_MISMATCH
  dst.bits.fraction = fraction;
  dst.bits.exp = exp;
  dst.bits.sign = sign;
#else
  dst.value_raw = fraction & ((((USItype)1) << SF_FRACBITS) - (USItype)1);
  dst.value_raw |= ((USItype) (exp & ((1 << SF_EXPBITS) - 1))) << SF_FRACBITS;
  dst.value_raw |= ((USItype) (sign & 1)) << (SF_FRACBITS | SF_EXPBITS);
#endif

#if defined(FLOAT_WORD_ORDER_MISMATCH) && !defined(FLOAT)
  {
    UHItype tmp = dst.words[0];
    dst.words[0] = dst.words[1];
    dst.words[1] = tmp;
  }
#endif

  return dst.value;
}

asm(".align 2, 0");
