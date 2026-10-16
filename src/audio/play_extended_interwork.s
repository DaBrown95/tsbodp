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
 * Lesser General Public License in COPYING for more details.
 */


@ Hardware-mode adapter for the Krawall PlayExt stub role.
@ Adapted from lib/stub.S at 8d338581bf0ed0afad15b66bf5979ad4c4d15ed0.
@ Licence: licenses/Krawall-LGPL-2.1.txt (upstream COPYING).
@ This reconstructs the original saved-R5 variant, not the pinned source's
@ later mixed Thumb/ARM tail sequence. Exact historical source identity is open.
@ Native protocol: R0-R3 reach ARM unchanged; provider-entry SP is caller SP-8.
@ The provider consequently sees saved caller R5/LR as stack words0/1.
@ On ordinary Thumb-caller return this adapter restores caller R5/SP/return PC.
@ It is NOT a transparent forwarding wrapper for six ordinary C arguments.
@ No C prototype is declared for this ROM entry; incoming caller domain is open.
.equ original_entry, 0x0804c87c
.equ original_literal, 0x0804c8a4
.equ original_load_pc, (original_entry + 6) & -4
.syntax unified
.thumb
.text
.balign 4
.global audio_play_extended_interwork
.type audio_play_extended_interwork, %function
.thumb_func
audio_play_extended_interwork:
    push {r5, lr}
    ldr r5, [pc, #(original_literal - original_load_pc)]
    bl .Lcall_arm_r5
    pop {r5, pc}
.Lcall_arm_r5:
    bx r5
.size audio_play_extended_interwork, .-audio_play_extended_interwork
