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

/* Selected from pret/agbcc da598c1d918402c42c0c0d7128ba14567f3175e9,
 * libgcc/fp-bit-base.c, L_eq_df. Reuses the existing double-only
 * runtime types. Only upstream symbol wrappers are expanded; trailing
 * whitespace is trimmed and standalone zero alignment follows its Makefile.
 * The comparison result is signed and is not a Boolean. */
#include "runtime_fp.h"
#define CMPtype SItype
CMPtype
__eqdf2 (FLO_type arg_a, FLO_type arg_b)
{
  fp_number_type a;
  fp_number_type b;

  __unpack_d ((FLO_union_type *) & arg_a, &a);
  __unpack_d ((FLO_union_type *) & arg_b, &b);

  if (isnan (&a) || isnan (&b))
    return 1;			/* false, truth == 0 */

  return __fpcmp_parts_d (&a, &b) ;
}
asm(".align 2, 0");
