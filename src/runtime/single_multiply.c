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
_fpmul_parts ( sf_number_type *  a,
	       sf_number_type *  b,
	       sf_number_type * tmp)
{
  USItype low = 0;
  USItype high = 0;

  if (sf_isnan (a))
    {
      a->sign = a->sign != b->sign;
      return a;
    }
  if (sf_isnan (b))
    {
      b->sign = a->sign != b->sign;
      return b;
    }
  if (sf_isinf (a))
    {
      if (sf_iszero (b))
	return sf_nan ();
      a->sign = a->sign != b->sign;
      return a;
    }
  if (sf_isinf (b))
    {
      if (sf_iszero (a))
	{
	  return sf_nan ();
	}
      b->sign = a->sign != b->sign;
      return b;
    }
  if (sf_iszero (a))
    {
      a->sign = a->sign != b->sign;
      return a;
    }
  if (sf_iszero (b))
    {
      b->sign = a->sign != b->sign;
      return b;
    }

  /* Calculate the mantissa by multiplying both 64bit numbers to get a
     128 bit number */
  {
#if defined(NO_DI_MODE)
    {
      USItype x = a->fraction.ll;
      USItype ylow = b->fraction.ll;
      USItype yhigh = 0;
      int bit;

      /* ??? This does multiplies one bit at a time.  Optimize.  */
      for (bit = 0; bit < SF_FRAC_NBITS; bit++)
	{
	  int carry;

	  if (x & 1)
	    {
	      carry = (low += ylow) < ylow;
	      high += yhigh + carry;
	    }
	  yhigh <<= 1;
	  if (ylow & SF_FRACHIGH)
	    {
	      yhigh |= 1;
	    }
	  ylow <<= 1;
	  x >>= 1;
	}
    }
#elif defined(FLOAT)
    {
      /* Multiplying two 32 bit numbers to get a 64 bit number  on
        a machine with DI, so we're safe */

      DItype answer = (DItype)(a->fraction.ll) * (DItype)(b->fraction.ll);

      high = answer >> 32;
      low = answer;
    }
#else
    /* Doing a 64*64 to 128 */
    {
      UDItype nl = a->fraction.ll & 0xffffffff;
      UDItype nh = a->fraction.ll >> 32;
      UDItype ml = b->fraction.ll & 0xffffffff;
      UDItype mh = b->fraction.ll >>32;
      UDItype pp_ll = ml * nl;
      UDItype pp_hl = mh * nl;
      UDItype pp_lh = ml * nh;
      UDItype pp_hh = mh * nh;
      UDItype res2 = 0;
      UDItype res0 = 0;
      UDItype ps_hh__ = pp_hl + pp_lh;
      if (ps_hh__ < pp_hl)
	res2 += 0x100000000LL;
      pp_hl = (ps_hh__ << 32) & 0xffffffff00000000LL;
      res0 = pp_ll + pp_hl;
      if (res0 < pp_ll)
	res2++;
      res2 += ((ps_hh__ >> 32) & 0xffffffffL) + pp_hh;
      high = res2;
      low = res0;
    }
#endif
  }

  tmp->normal_exp = a->normal_exp + b->normal_exp;
  tmp->sign = a->sign != b->sign;
#ifdef FLOAT
  tmp->normal_exp += 2;		/* ??????????????? */
#else
  tmp->normal_exp += 4;		/* ??????????????? */
#endif
  while (high >= SF_IMPLICIT_2)
    {
      tmp->normal_exp++;
      if (high & 1)
	{
	  low >>= 1;
	  low |= SF_FRACHIGH;
	}
      high >>= 1;
    }
  while (high < SF_IMPLICIT_1)
    {
      tmp->normal_exp--;

      high <<= 1;
      if (low & SF_FRACHIGH)
	high |= 1;
      low <<= 1;
    }
  /* rounding is tricky. if we only round if it won't make us round later. */
#if 0
  if (low & SF_FRACHIGH2)
    {
      if (((high & SF_GARDMASK) != SF_GARDMSB)
	  && (((high + 1) & SF_GARDMASK) == SF_GARDMSB))
	{
	  /* don't round, it gets done again later. */
	}
      else
	{
	  high++;
	}
    }
#endif
  if ((high & SF_GARDMASK) == SF_GARDMSB)
    {
      if (high & (1 << SF_NGARDS))
	{
	  /* half way, so round to even */
	  high += SF_GARDROUND + 1;
	}
      else if (low)
	{
	  /* but we really weren't half way */
	  high += SF_GARDROUND + 1;
	}
    }
  tmp->fraction.ll = high;
  tmp->class = CLASS_NUMBER;
  return tmp;
}

SFtype
__mulsf3 (SFtype arg_a, SFtype arg_b)
{
  sf_number_type a;
  sf_number_type b;
  sf_number_type tmp;
  sf_number_type *res;

  __unpack_f ((SF_union_type *) & arg_a, &a);
  __unpack_f ((SF_union_type *) & arg_b, &b);

  res = _fpmul_parts (&a, &b, &tmp);

  return __pack_f (res);
}

asm(".align 2, 0");
