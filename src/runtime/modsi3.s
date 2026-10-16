@ libgcc1 routines for ARM cpu.
@ Division routines, written by Richard Earnshaw, (rearnsha@armltd.co.uk)

/* Copyright (C) 1995, 1996, 1998 Free Software Foundation, Inc.

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


/* Selected from pret/agbcc da598c1d918402c42c0c0d7128ba14567f3175e9,
 * libgcc/lib1thumb.asm, L_modsi3. Preprocessor-only wrappers
 * are expanded; trailing whitespace is trimmed. ARM7 Thumb mode and
 * standalone alignment are explicit.
 * The algorithm and instruction sequence are unchanged. Assembly origin,
 * with no recovered-C credit. */
.syntax divided
.cpu arm7tdmi
.thumb
.text
.balign 4, 0
work .req r4

dividend	.req	r0
divisor		.req	r1
overdone	.req	r2
curbit		.req	r3

	.text
	.globl	__modsi3
	.type __modsi3, %function
	.align	2, 0
	.thumb_func
__modsi3:
	mov	curbit, #1
	cmp	divisor, #0
	beq	Ldiv0
	Bpl	Over1
	neg	divisor, divisor		@ Loops below use unsigned.
Over1:
	push	{ work }
	@ Need to save the sign of the dividend, unfortunately, we need
	@ ip later on.  Must do this after saving the original value of
	@ the work register, because we will pop this value off first.
	push	{ dividend }
	cmp	dividend, #0
	Bpl	Over2
	neg	dividend, dividend
Over2:
	cmp	dividend, divisor
	bcc	Lgot_result
	mov	work, #1
	lsl	work, #28
Loop1:
	@ Unless the divisor is very big, shift it up in multiples of
	@ four bits, since this is the amount of unwinding in the main
	@ division loop.  Continue shifting until the divisor is
	@ larger than the dividend.
	cmp	divisor, work
	bcs	Lbignum
	cmp	divisor, dividend
	bcs	Lbignum
	lsl	divisor, #4
	lsl	curbit, #4
	b	Loop1

Lbignum:
	@ Set work to 0x80000000
	lsl	work, #3
Loop2:
	@ For very big divisors, we must shift it a bit at a time, or
	@ we will be in danger of overflowing.
	cmp	divisor, work
	bcs	Loop3
	cmp	divisor, dividend
	bcs	Loop3
	lsl	divisor, #1
	lsl	curbit, #1
	b	Loop2

Loop3:
	@ Test for possible subtractions.  On the final pass, this may
	@ subtract too much from the dividend, so keep track of which
	@ subtractions are done, we can fix them up afterwards...
	mov	overdone, #0
	cmp	dividend, divisor
	bcc	Over3
	sub	dividend, dividend, divisor
Over3:
	lsr	work, divisor, #1
	cmp	dividend, work
	bcc	Over4
	sub	dividend, dividend, work
	mov	ip, curbit
	mov	work, #1
	ror	curbit, work
	orr	overdone, curbit
	mov	curbit, ip
Over4:
	lsr	work, divisor, #2
	cmp	dividend, work
	bcc	Over5
	sub	dividend, dividend, work
	mov	ip, curbit
	mov	work, #2
	ror	curbit, work
	orr	overdone, curbit
	mov	curbit, ip
Over5:
	lsr	work, divisor, #3
	cmp	dividend, work
	bcc	Over6
	sub	dividend, dividend, work
	mov	ip, curbit
	mov	work, #3
	ror	curbit, work
	orr	overdone, curbit
	mov	curbit, ip
Over6:
	mov	ip, curbit
	cmp	dividend, #0			@ Early termination?
	beq	Over7
	lsr	curbit, #4			@ No, any more bits to do?
	beq	Over7
	lsr	divisor, #4
	b	Loop3

Over7:
	@ Any subtractions that we should not have done will be recorded in
	@ the top three bits of "overdone".  Exactly which were not needed
	@ are governed by the position of the bit, stored in ip.
	@ If we terminated early, because dividend became zero,
	@ then none of the below will match, since the bit in ip will not be
	@ in the bottom nibble.
	mov	work, #0xe
	lsl	work, #28
	and	overdone, work
	beq	Lgot_result

	mov	curbit, ip
	mov	work, #3
	ror	curbit, work
	tst	overdone, curbit
	beq	Over8
	lsr	work, divisor, #3
	add	dividend, dividend, work
Over8:
	mov	curbit, ip
	mov	work, #2
	ror	curbit, work
	tst	overdone, curbit
	beq	Over9
	lsr	work, divisor, #2
	add	dividend, dividend, work
Over9:
	mov	curbit, ip
	mov	work, #1
	ror	curbit, work
	tst	overdone, curbit
	beq	Lgot_result
	lsr	work, divisor, #1
	add	dividend, dividend, work
Lgot_result:
	pop	{ work }
	cmp	work, #0
	bpl	Over10
	neg	dividend, dividend
Over10:
	pop	{ work }
	mov pc, lr

Ldiv0:
	push    { lr }
	bl	__div0
	mov	r0, #0			@ about as wrong as it could be
	pop	{ pc }

	.size __modsi3, .-__modsi3


.balign 4, 0
