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


@ Pool for the saved-R5 Krawall PlayExt hardware-mode adapter.
@ Source role: lib/stub.S at 8d338581bf0ed0afad15b66bf5979ad4c4d15ed0;
@ the fixed ARM provider word also matches the pinned source verbatim.
@ Licence: licenses/Krawall-LGPL-2.1.txt (upstream COPYING).
@ Data only; this does not declare a normal C calling convention for the stub.
.syntax unified
.text
.balign 4
.global audio_stub_play_extended_literal
.type audio_stub_play_extended_literal, %object
audio_stub_play_extended_literal:
    .word audio_start_sample_extended
.size audio_stub_play_extended_literal, .-audio_stub_play_extended_literal
