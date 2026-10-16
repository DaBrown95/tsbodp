/*
 * Krawall, XM/S3M Modplayer Library
 * Copyright (C) 2001-2005, 2013 Sebastian Kienzl
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License in licenses/Krawall-LGPL-2.1.txt for more details.
 */

/*
 * Adapted from Krawall lib/directsound_asm.S, revision
 * 8d338581bf0ed0afad15b66bf5979ad4c4d15ed0, blob
 * c2f82e5d2971b5405c9b88009063984ade358b29.
 * Source: https://github.com/sebknzl/krawall/tree/8d338581bf0ed0afad15b66bf5979ad4c4d15ed0
 * Changes: game full-word stamp increment and full-buffer timer reload;
 * first-IRQ timer tail replaced by its existing unconditional return;
 * omit later upstream toggle/front-branch/backup/undo behavior; use private
 * labels, named constants and an external stamp address in .text.
 * This hardware IRQ is assembly glue, not recovered C.
 * LGPL-2.1-or-later; see licenses/Krawall-LGPL-2.1.txt for the licence.
 */
 .text
 .arm
 .extern g_audio_stamp
 .equ DM1CNT_H, 0x040000C6
 .equ DM2CNT_H, 0x040000D2
 .equ TM1, 0x04000104
 .equ DMABUFFERSIZE, 1104

@ Timer-1 IRQ: advance the complete-buffer stamp and restart both active DMAs.
.Laudio_timer_irq:
 ldr r0, =g_audio_stamp
 ldr r1, [r0]
 add r1, r1, #1
 str r1, [r0]

@ Reset DMA1; skip the DMA2 reset when its start bit is clear.
 ldr r0, =DM1CNT_H
 ldrh r1, [r0]
 bic r1, r1, #(1 << 15)
 strh r1, [r0]
 orr r1, r1, #(1 << 15)
 strh r1, [r0]
 ldr r0, =DM2CNT_H
 ldrh r1, [r0]
 tst r1, #(1 << 15)
 beq .Lreprogram
 bic r1, r1, #(1 << 15)
 strh r1, [r0]
 orr r1, r1, #(1 << 15)
 strh r1, [r0]

@ The first interrupt reprograms timer 1, then replaces this first load with
@ the already present BX LR at .Lreturn. Later IRQs return at this location.
.Lreprogram:
 ldr r0, =TM1
 ldr r1, [r0]
 bic r2, r1, #(1 << 23)
 str r2, [r0]
 ldr r2, =(65536 - DMABUFFERSIZE)
 mov r1, r1, lsr #16
 add r1, r2, r1, lsl #16
 str r1, [r0]
 ldr r1, .Lreturn
 adr r0, .Lreprogram
 str r1, [r0]
.Lreturn:
 bx lr
 .pool
