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
/* according to the demo, fpcmp returns a comparison with 0... thus
   a<b -> -1
   a==b -> 0
   a>b -> +1
 */

int
__fpcmp_parts_f (sf_number_type * a, sf_number_type * b)
{
#if 0
  /* either sf_nan -> unordered. Must be checked outside of this routine. */
  if (sf_isnan (a) && sf_isnan (b))
    {
      return 1;			/* still unordered! */
    }
#endif

  if (sf_isnan (a) || sf_isnan (b))
    {
      return 1;			/* how to indicate unordered compare? */
    }
  if (sf_isinf (a) && sf_isinf (b))
    {
      /* +inf > -inf, but +inf != +inf */
      /* b    \a| +inf(0)| -inf(1)
       ______\+--------+--------
       +inf(0)| a==b(0)| a<b(-1)
       -------+--------+--------
       -inf(1)| a>b(1) | a==b(0)
       -------+--------+--------
       So since unordered must be non zero, just line up the columns...
       */
      return b->sign - a->sign;
    }
  /* but not both... */
  if (sf_isinf (a))
    {
      return a->sign ? -1 : 1;
    }
  if (sf_isinf (b))
    {
      return b->sign ? 1 : -1;
    }
  if (sf_iszero (a) && sf_iszero (b))
    {
      return 0;
    }
  if (sf_iszero (a))
    {
      return b->sign ? 1 : -1;
    }
  if (sf_iszero (b))
    {
      return a->sign ? -1 : 1;
    }
  /* now both are "normal". */
  if (a->sign != b->sign)
    {
      /* opposite signs */
      return a->sign ? -1 : 1;
    }
  /* same sign; exponents? */
  if (a->normal_exp > b->normal_exp)
    {
      return a->sign ? -1 : 1;
    }
  if (a->normal_exp < b->normal_exp)
    {
      return a->sign ? 1 : -1;
    }
  /* same exponents; check size. */
  if (a->fraction.ll > b->fraction.ll)
    {
      return a->sign ? -1 : 1;
    }
  if (a->fraction.ll < b->fraction.ll)
    {
      return a->sign ? 1 : -1;
    }
  /* after all that, they're equal. */
  return 0;
}

asm(".align 2, 0");
