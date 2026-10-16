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


@ Adapted from pinned Krawall lib/stub.S 8d338581bf0ed0afad15b66bf5979ad4c4d15ed0.
@ kramSetVolSTUB: upstream assembly-origin interworking glue.
@ Changes: canonical names, split pool ownership, GNU syntax directives, and
@ explicit PC-relative pool placement at the original fixed addresses.
@ Licence: licenses/Krawall-LGPL-2.1.txt (upstream COPYING).
@ The assembler requires a local PC-relative operand for a disjoint pool.
.equ original_entry, 0x0804c890
.equ original_literal, 0x0804c8b0
.equ original_pc, (original_entry + 4) & -4
.syntax unified
.thumb
.text
.balign 4
.global audio_set_sample_volume
.type audio_set_sample_volume, %function
.thumb_func
audio_set_sample_volume:
    ldr r3, [pc, #(original_literal - original_pc)]
    bx r3
.size audio_set_sample_volume, .-audio_set_sample_volume
