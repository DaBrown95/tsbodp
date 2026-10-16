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

/* Selected ordinary-C FLOAT body adapted from pret/agbcc
 * da598c1d918402c42c0c0d7128ba14567f3175e9, libgcc/fp-bit-base.c.
 * SF identifiers are distinct from the existing DF view; no field initializer
 * or NaN storage allocation is added. Zero alignment follows its Makefile. */
#include "runtime_single.h"
#define FLOAT
#define FLOAT_BIT_ORDER_MISMATCH
#define INLINE __inline__
#define CMPtype SItype
#define MAX_SI_INT ((SItype) ((unsigned) (~0)>>1))
static INLINE sf_number_type *
_fpdiv_parts (sf_number_type * a,
	      sf_number_type * b)
{
  USItype bit;
  USItype numerator;
  USItype denominator;
  USItype quotient;

  if (sf_isnan (a))
    {
      return a;
    }
  if (sf_isnan (b))
    {
      return b;
    }

  a->sign = a->sign ^ b->sign;

  if (sf_isinf (a) || sf_iszero (a))
    {
      if (a->class == b->class)
	return sf_nan ();
      return a;
    }

  if (sf_isinf (b))
    {
      a->fraction.ll = 0;
      a->normal_exp = 0;
      return a;
    }
  if (sf_iszero (b))
    {
      a->class = CLASS_INFINITY;
      return a;
    }

  /* Calculate the mantissa by multiplying both 64bit numbers to get a
     128 bit number */
  {
    /* quotient =
       ( numerator / denominator) * 2^(numerator exponent -  denominator exponent)
     */

    a->normal_exp = a->normal_exp - b->normal_exp;
    numerator = a->fraction.ll;
    denominator = b->fraction.ll;

    if (numerator < denominator)
      {
	/* Fraction will be less than 1.0 */
	numerator *= 2;
	a->normal_exp--;
      }
    bit = SF_IMPLICIT_1;
    quotient = 0;
    /* ??? Does __divsf3 one bit at a time.  Optimize.  */
    while (bit)
      {
	if (numerator >= denominator)
	  {
	    quotient |= bit;
	    numerator -= denominator;
	  }
	bit >>= 1;
	numerator *= 2;
      }

    if ((quotient & SF_GARDMASK) == SF_GARDMSB)
      {
	if (quotient & (1 << SF_NGARDS))
	  {
	    /* half way, so round to even */
	    quotient += SF_GARDROUND + 1;
	  }
	else if (numerator)
	  {
	    /* but we really weren't half way, more bits exist */
	    quotient += SF_GARDROUND + 1;
	  }
      }

    a->fraction.ll = quotient;
    return (a);
  }
}

SFtype
__divsf3 (SFtype arg_a, SFtype arg_b)
{
  sf_number_type a;
  sf_number_type b;
  sf_number_type *res;

  __unpack_f ((SF_union_type *) & arg_a, &a);
  __unpack_f ((SF_union_type *) & arg_b, &b);

  res = _fpdiv_parts (&a, &b);

  return __pack_f (res);
}

asm(".align 2, 0");
