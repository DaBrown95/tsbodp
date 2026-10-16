/*
 * Adapted from Krawall lib/mixer_func.S, revision
 * 8d338581bf0ed0afad15b66bf5979ad4c4d15ed0, blob
 * 6d4975102527644490e195357d841976f588e412.
 * Source: https://github.com/sebknzl/krawall/tree/8d338581bf0ed0afad15b66bf5979ad4c4d15ed0
 * Changes: expand upstream register macros; retain named field/shift constants;
 * use .text and private labels;
 * resolve the game clip-table address externally; leave clip-table storage in
 * the original data. No algorithm or instruction sequence changes.
 *
 * This is assembly-origin source, with 12 callable entries and shared tails,
 * not recovered C. The startup copy installs this complete 1,604-byte block
 * from ROM 0xFDAA7C at RAM 0x03000604. It contains 1,592 instruction bytes,
 * two 4-byte volume words and one 4-byte clip-table pointer literal.
 * The source assumes a positive sample count divisible by four, as upstream.
 * Local labels keep all PC-relative references valid at ROM and RAM addresses;
 * callers retain the separately declared fixed RAM entry addresses.
 * LGPL-2.1-or-later; see licenses/Krawall-LGPL-2.1.txt for the licence.
 */
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
 .extern g_audio_clip_table
 .text
 .ARM
@ Channel offsets follow upstream mixer_private.h and the observed game layout.
 .equ CH_POS, 8
 .equ CH_INC, 20
 .equ CH_FRAC, 28
 .equ CH_LVOL, 30
 .equ CH_RVOL, 31
 .equ SRS, 3
 .equ SRSBITSHW, (((1 << SRS) - 1) << 16)
 .equ DEAMP, 5
@=================================================================
@ general register assignments for mix*
@=================================================================
@=================================================================
@ .LmixLeft
@=================================================================
 .align
.LmixLeft:
 stmdb sp!, {r4-r11}
 ldr r5, [r0, #CH_POS]
 ldr r6, [r0, #CH_INC]
 ldrh r7, [r0, #CH_FRAC]
 ldrb r3, [r0, #CH_LVOL]
 mov r2, r2, lsr #2
0:
 ldrb r8, [r5, r7, asr #16] @ 6
 add r7, r7, r6 @ 1
 ldrb r9, [r5, r7, asr #16] @ 6
 add r7, r7, r6 @ 1
 add r9, r8, r9, lsl #16 @ 1
 mul r8, r9, r3 @ 2
 bic r10, r8, #SRSBITSHW @ 1
 ldrb r8, [r5, r7, asr #16]
 add r7, r7, r6
 ldrb r9, [r5, r7, asr #16]
 add r7, r7, r6
 add r9, r8, r9, lsl #16
 mul r8, r9, r3
 bic r11, r8, #SRSBITSHW @ = 18
 ldmia r1, {r8, r9} @ 4
 add r8, r8, r10, lsr #SRS @ 1
 add r9, r9, r11, lsr #SRS @ 1
 stmia r1!, {r8, r9} @ 3
 add r1, r1, #8 @ 1
 subs r2, r2, #1 @ 1
 bne 0b @ 3
      @ = 50/4 = 12.5
 add r5, r5, r7, asr #16
        str r5, [r0, #CH_POS]
        strh r7, [r0, #CH_FRAC]
 ldmia sp!, {r4-r11}
 bx lr
@=================================================================
@ .LmixRight
@=================================================================
 .align
.LmixRight:
 stmdb sp!, {r4-r11}
 ldr r5, [r0, #CH_POS]
 ldr r6, [r0, #CH_INC]
 ldrh r7, [r0, #CH_FRAC]
 ldrb r3, [r0, #CH_RVOL]
 mov r2, r2, lsr #2
 add r1, r1, #8
 b 0b @ jump to .LmixLeft
@=================================================================
@ .LmixCenter
@=================================================================
 .align
.LmixCenter:
 stmdb sp!, {r4-r11}
 ldr r5, [r0, #CH_POS]
 ldr r6, [r0, #CH_INC]
 ldrh r7, [r0, #CH_FRAC]
 ldrb r3, [r0, #CH_LVOL]
 mov r2, r2, lsr #2
0:
 ldrb r8, [r5, r7, asr #16] @ 6
 add r7, r7, r6 @ 1
 ldrb r9, [r5, r7, asr #16] @ 6
 add r7, r7, r6 @ 1
 add r9, r8, r9, lsl #16 @ 1
 mul r8, r9, r3 @ 2
 bic r12, r8, #SRSBITSHW @ 1
 ldrb r8, [r5, r7, asr #16] @ 6
 add r7, r7, r6 @ 1
 ldrb r9, [r5, r7, asr #16] @ 6
 add r7, r7, r6 @ 1
 add r9, r8, r9, lsl #16 @ 1
 mul r8, r9, r3 @ 2
 bic r4, r8, #SRSBITSHW @ 1
 ldmia r1, {r8, r9, r10, r11} @ 6
 add r8, r8, r12, lsr #SRS @ 1
 add r10, r10, r12, lsr #SRS @ 1
 add r9, r9, r4, lsr #SRS
 add r11, r11, r4, lsr #SRS @ = 20
 stmia r1!, {r8, r9, r10, r11} @ 5
 subs r2, r2, #1 @ 1
 bne 0b @ 3
      @ = 55/4 = 13.75
 add r5, r5, r7, asr #16
        str r5, [r0, #CH_POS]
        strh r7, [r0, #CH_FRAC]
 ldmia sp!, {r4-r11}
 bx lr
@=================================================================
@ .LmixStereo
@=================================================================
 .align
.LmixStereo:
 stmdb sp!, {r4-r11, lr}
 ldr r5, [r0, #CH_POS]
 ldr r6, [r0, #CH_INC]
 ldrh r7, [r0, #CH_FRAC]
 ldrb r3, [r0, #CH_LVOL]
 ldrb r4, [r0, #CH_RVOL] @ load values
 mov r2, r2, lsr #2
0:
 ldmia r1, {r8, r9, r10, r11} @ 6
 ldrb r12, [r5, r7, asr #16] @ 6
 add r7, r7, r6 @ 1
 ldrb lr, [r5, r7, asr #16]
 add r7, r7, r6
 add r12, r12, lr, lsl #16 @ 1
 mul lr, r12, r3 @ 2
 bic lr, lr, #SRSBITSHW @ 1
 add r8, r8, lr, lsr #SRS @ 1
 mul lr, r12, r4 @ 2
 bic lr, lr, #SRSBITSHW @ 1
 add r10, r10, lr, lsr #SRS @ 1
 ldrb r12, [r5, r7, asr #16]
 add r7, r7, r6
 ldrb lr, [r5, r7, asr #16]
 add r7, r7, r6 @ = 14
 add r12, r12, lr, lsl #16
 mul lr, r12, r3
 bic lr, lr, #SRSBITSHW
 add r9, r9, lr, lsr #SRS
 mul lr, r12, r4
 bic lr, lr, #SRSBITSHW
 add r11, r11, lr, lsr #SRS @ = 9
 stmia r1!, {r8, r9, r10, r11} @ 5
 subs r2, r2, #1 @ 1
 bne 0b @ 3
      @ = 61/4 = 15.25
 add r5, r5, r7, asr #16
        str r5, [r0, #CH_POS]
        strh r7, [r0, #CH_FRAC]
 ldmia sp!, {r4-r11, lr}
 bx lr
@=================================================================
@ .LmixLeftHQ
@=================================================================
 .align
.LmixLeftHQ:
 stmdb sp!, {r4-r11, lr}
 ldr r5, [r0, #CH_POS]
 ldr r6, [r0, #CH_INC]
 ldrh r7, [r0, #CH_FRAC]
 ldrb r3, [r0, #CH_LVOL]
 mov r2, r2, lsr #2
 add lr, r5, #1
0:
 ldrb r8, [r5, r7, asr #16] @ 6
 ldrb r10, [lr, r7, asr #16] @ 6
 sub r10, r10, r8 @ 1
 mov r11, r7, lsl #16 @ 1
 mov r11, r11, lsr #16 @ 1
 mul r10, r11, r10 @ 2
 add r8, r8, r10, lsr #16 @ 1
 add r7, r7, r6 @ 1
 ldrb r9, [r5, r7, asr #16]
 ldrb r10, [lr, r7, asr #16]
 sub r10, r10, r9
 mov r11, r7, lsl #16
 mov r11, r11, lsr #16
 mul r10, r11, r10
 add r9, r9, r10, lsr #16
 add r7, r7, r6 @ = 19
 add r9, r8, r9, lsl #16 @ 1
 mul r8, r9, r3 @ 2
 bic r12, r8, #SRSBITSHW @ 1
 ldrb r8, [r5, r7, asr #16]
 ldrb r10, [lr, r7, asr #16]
 sub r10, r10, r8
 mov r11, r7, lsl #16
 mov r11, r11, lsr #16
 mul r10, r11, r10
 add r8, r8, r10, lsr #16
 add r7, r7, r6 @ = 19
 ldrb r9, [r5, r7, asr #16]
 ldrb r10, [lr, r7, asr #16]
 sub r10, r10, r9
 mov r11, r7, lsl #16
 mov r11, r11, lsr #16
 mul r10, r11, r10
 add r9, r9, r10, lsr #16
 add r7, r7, r6 @ = 19
 add r9, r8, r9, lsl #16
 mul r8, r9, r3
 bic r4, r8, #SRSBITSHW @ = 4
 ldmia r1, {r8, r9} @ 4
 add r8, r8, r12, lsr #SRS @ 1
 add r9, r9, r4, lsr #SRS @ 1
 stmia r1!, {r8, r9} @ 3
 add r1, r1, #8 @ 1
 subs r2, r2, #1 @ 1
 bne 0b @ 3
      @ = 98/4 = 24.5
 add r5, r5, r7, asr #16
        str r5, [r0, #CH_POS]
        strh r7, [r0, #CH_FRAC]
 ldmia sp!, {r4-r11, lr}
 bx lr
@=================================================================
@ .LmixRightHQ
@=================================================================
 .align
.LmixRightHQ:
 stmdb sp!, {r4-r11, lr}
 ldr r5, [r0, #CH_POS]
 ldr r6, [r0, #CH_INC]
 ldrh r7, [r0, #CH_FRAC]
 ldrb r3, [r0, #CH_RVOL]
 mov r2, r2, lsr #2
 add r1, r1, #8
 add lr, r5, #1
 b 0b @ jump to .LmixLeftHQ
@=================================================================
@ .LmixCenterHQ
@=================================================================
 .align
.LmixCenterHQ:
 stmdb sp!, {r4-r11, lr}
 ldr r5, [r0, #CH_POS]
 ldr r6, [r0, #CH_INC]
 ldrh r7, [r0, #CH_FRAC]
 ldrb r3, [r0, #CH_LVOL]
 mov r2, r2, lsr #2
 add lr, r5, #1
0:
 ldrb r8, [r5, r7, asr #16] @ 6
 ldrb r10, [lr, r7, asr #16]
 sub r10, r10, r8 @ 1
 mov r11, r7, lsl #16
 mov r11, r11, lsr #16
 mul r10, r11, r10 @ 2
 add r8, r8, r10, lsr #16 @ 1
 add r7, r7, r6 @ 1
 ldrb r9, [r5, r7, asr #16] @ 6
 ldrb r10, [lr, r7, asr #16] @ 6
 sub r10, r10, r9 @ 1
 mov r11, r7, lsl #16
 mov r11, r11, lsr #16
 mul r10, r11, r10 @ 2
 add r9, r9, r10, lsr #16 @ 1
 add r7, r7, r6 @ 1
 add r8, r8, r9, lsl #16 @ 1
 mul r9, r8, r3 @ 2
 bic r12, r9, #SRSBITSHW @ 1
 ldrb r8, [r5, r7, asr #16] @ 6
 ldrb r10, [lr, r7, asr #16]
 sub r10, r10, r8 @ 1
 mov r11, r7, lsl #16
 mov r11, r11, lsr #16
 mul r10, r11, r10 @ 2
 add r8, r8, r10, lsr #16 @ 1
 add r7, r7, r6 @ 1
 ldrb r9, [r5, r7, asr #16] @ 6
 ldrb r10, [lr, r7, asr #16] @ 6
 sub r10, r10, r9 @ 1
 mov r11, r7, lsl #16
 mov r11, r11, lsr #16
 mul r10, r11, r10 @ 2
 add r9, r9, r10, lsr #16 @ 1
 add r7, r7, r6 @ 1
 add r8, r8, r9, lsl #16 @ 1
 mul r9, r8, r3 @ 2
 bic r4, r9, #SRSBITSHW @ 1
 ldmia r1, {r8, r9, r10, r11} @ 6
 add r8, r8, r12, lsr #SRS @ 1
 add r9, r9, r4, lsr #SRS @ 1
 add r10, r10, r12, lsr #SRS @ 1
 add r11, r11, r4, lsr #SRS @ 1
 stmia r1!, {r8, r9, r10, r11} @ 5
 subs r2, r2, #1 @ 1
 bne 0b @ 3
 add r5, r5, r7, asr #16
        str r5, [r0, #CH_POS]
        strh r7, [r0, #CH_FRAC]
 ldmia sp!, {r4-r11, lr}
 bx lr
@=================================================================
@ .LmixStereoHQ
@=================================================================
 .align
.LmixStereoHQ:
 stmdb sp!, {r4-r11, lr}
 ldr r5, [r0, #CH_POS]
 ldr r6, [r0, #CH_INC]
 ldrh r7, [r0, #CH_FRAC]
 ldrb r3, [r0, #CH_LVOL]
 ldrb r4, [r0, #CH_RVOL]
 mov r2, r2, lsr #2
 stmdb sp!, {r0}
0:
 add lr, r5, #1
 ldrb r8, [r5, r7, asr #16] @ 6
 ldrb r10, [lr, r7, asr #16]
 sub r10, r10, r8 @ 1
 mov r11, r7, lsl #16
 mov r11, r11, lsr #16
 mul r10, r11, r10 @ 2
 add r8, r8, r10, lsr #16 @ 1
 add r7, r7, r6 @ 1
 ldrb r9, [r5, r7, asr #16] @ 6
 ldrb r10, [lr, r7, asr #16] @ 6
 sub r10, r10, r9 @ 1
 mov r11, r7, lsl #16
 mov r11, r11, lsr #16
 mul r10, r11, r10 @ 2
 add r9, r9, r10, lsr #16 @ 1
 add r7, r7, r6 @ 1
 add r12, r8, r9, lsl #16 @ 1
 ldrb r8, [r5, r7, asr #16] @ 6
 ldrb r10, [lr, r7, asr #16]
 sub r10, r10, r8 @ 1
 mov r11, r7, lsl #16
 mov r11, r11, lsr #16
 mul r10, r11, r10 @ 2
 add r8, r8, r10, lsr #16 @ 1
 add r7, r7, r6 @ 1
 ldrb r9, [r5, r7, asr #16] @ 6
 ldrb r10, [lr, r7, asr #16] @ 6
 sub r10, r10, r9 @ 1
 mov r11, r7, lsl #16
 mov r11, r11, lsr #16
 mul r10, r11, r10 @ 2
 add r9, r9, r10, lsr #16 @ 1
 add r7, r7, r6 @ 1
 add r0, r8, r9, lsl #16 @ 1
 ldmia r1, {r8, r9, r10, r11} @ 6
 mul lr, r12, r3
 bic lr, lr, #SRSBITSHW
 add r8, r8, lr, lsr #SRS
 mul lr, r12, r4
 bic lr, lr, #SRSBITSHW
 add r10, r10, lr, lsr #SRS
 mul lr, r0, r3
 bic lr, lr, #SRSBITSHW
 add r9, r9, lr, lsr #SRS
 mul lr, r0, r4
 bic lr, lr, #SRSBITSHW
 add r11, r11, lr, lsr #SRS
 stmia r1!, {r8, r9, r10, r11} @ 5
 subs r2, r2, #1 @ 1
 bne 0b @ 3
 ldmia sp!, {r0}
 add r5, r5, r7, asr #16
        str r5, [r0, #CH_POS]
        strh r7, [r0, #CH_FRAC]
 ldmia sp!, {r4-r11, lr}
 bx lr
@=================================================================
@ .LmixBias( s16 *dest, uint amount, uint lvol, uint rvol );
@=================================================================
 .align
.LmixBias:
 stmdb sp!, {r4-r7}
 mov r2, r2, lsl #7 @ *128
 mov r2, r2, lsr #SRS
 add r2, r2, r2, lsl #16 @ upper halfword
 mov r3, r3, lsl #7
 mov r3, r3, lsr #SRS
 add r3, r3, r3, lsl #16
 mov r1, r1, lsr #2
0:
 ldmia r0, {r4, r5, r6, r7} @ 6
 add r4, r4, r2 @ 1
 add r5, r5, r2 @ 1
 add r6, r6, r3 @ 1
 add r7, r7, r3 @ 1
 stmia r0!, {r4, r5, r6, r7} @ 5
 subs r1, r1, #1 @ 1
 bne 0b @ 3
     @ = 19 / 4 = 4.75/sample
 ldmia sp!, {r4-r7}
 bx lr
@=================================================================
@ .LmixClear( s16 *dst, uint amount )
@=================================================================
        .align
.LmixClear:
 stmdb sp!, { r4, r5 }
 mov r2, #0
 mov r3, #0
 mov r4, #0
 mov r5, #0
 str r2, .LvolSumLeft
 str r2, .LvolSumRight
 mov r1, r1, lsr #2
       0:
 stmia r0!, { r2-r5 }
 subs r1, r1, #1
 bne 0b
 ldmia sp!, { r4, r5 }
 bx lr
@=================================================================
@ .LvolSumLeft/Right
@=================================================================
.LvolSumLeft: .word 0
.LvolSumRight: .word 0
 .pool
@=================================================================
@ .Lmix16to8( u16 *src, s8* left, s8 *right, uint amount );
@=================================================================
 .align
.Lmix16to8:
 stmdb sp!, {r4-r11}
 ldr r8, .LvolSumLeft
 mov r8, r8, lsl #7 @ *128
 ldr r9, .LvolSumRight
 mov r9, r9, lsl #7
 mov r8, r8, lsr #SRS
 mov r9, r9, lsr #SRS
 mov r3, r3, lsr #2
 ldr r12, =g_audio_clip_table
       0:
 ldmia r0!, {r4-r7} @ 6
 @ = 6
 mov r10, r4, lsr #16 @ 1: r10 -> upper 16 bit
 sub r11, r4, r10, lsl #16 @ 1: r11 -> lower 16 bit
 sub r10, r10, r8 @ 1: remove bias
 sub r11, r11, r8 @ 1
       4:
 ldrb r10, [r12, r10, asr #DEAMP] @ EWRAM: 5 (IWRAM: 3)
 ldrb r11, [r12, r11, asr #DEAMP]
 add r4, r11, r10, lsl #8
        @ = 15
 mov r10, r5, lsr #16
 sub r11, r5, r10, lsl #16
 sub r10, r10, r8
 sub r11, r11, r8
       5:
 ldrb r10, [r12, r10, asr #DEAMP]
 ldrb r11, [r12, r11, asr #DEAMP]
 add r11, r11, r10, lsl #8
 @ = 15
 add r4, r4, r11, lsl #16 @ 1
 str r4, [r1], #4 @ 2
 @ = 3
 mov r10, r6, lsr #16
 sub r11, r6, r10, lsl #16
 sub r10, r10, r9
 sub r11, r11, r9
       6:
 ldrb r10, [r12, r10, asr #DEAMP]
 ldrb r11, [r12, r11, asr #DEAMP]
 add r6, r11, r10, lsl #8
 @ = 15
 mov r10, r7, lsr #16
 sub r11, r7, r10, lsl #16
 sub r10, r10, r9
 sub r11, r11, r9
       7:
 ldrb r10, [r12, r10, asr #DEAMP]
 ldrb r11, [r12, r11, asr #DEAMP]
 add r11, r11, r10, lsl #8
 @ = 15
 add r6, r6, r11, lsl #16
 str r6, [r2], #4
 @ = 3
 subs r3, r3, #1 @ 1
 bne 0b @ 3
     @ = 76 / 4 = 19/sample
 ldmia sp!, {r4-r11}
 bx lr
 .align
@=================================================================
@ void .Lmix16to8_patch( uint deamp ) LONG_CALL;
@=================================================================
@ this func patches the
@ ldrb r10, [r12, r10, asr #DEAMP]
@ instructions from above, changing the 5.
/*
amnt tp
11  7 65 4
xxxxx xx 0
*/
.Lmix16to8_patch:
 adr r1, 4b
 ldr r1, [r1]
 adr r2, 4b+4
 ldr r2, [r2]
 bic r1, r1, #0b111110000000
 bic r2, r2, #0b111110000000
 orr r1, r1, r0, lsl #7
 orr r2, r2, r0, lsl #7
 adr r0, 4b
 str r1, [r0]
 str r2, [r0, #4]
 adr r0, 5b
 str r1, [r0]
 str r2, [r0, #4]
 adr r0, 6b
 str r1, [r0]
 str r2, [r0, #4]
 adr r0, 7b
 str r1, [r0]
 str r2, [r0, #4]
 bx lr
 .pool
