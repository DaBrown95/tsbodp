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


@ From Krawall lib/stub.S 8d338581bf0ed0afad15b66bf5979ad4c4d15ed0.
@ Licence: licenses/Krawall-LGPL-2.1.txt (upstream COPYING).
@ Upstream automatic =target pool is named explicitly for the separate original
@ pool extent. These three words are data, with no executable instructions.
.syntax unified
.text
.balign 4
.global audio_stub_volume_literal
.type audio_stub_volume_literal, %object
audio_stub_volume_literal:
    .word audio_set_channel_volume
.size audio_stub_volume_literal, .-audio_stub_volume_literal
.global audio_stub_pan_literal
.type audio_stub_pan_literal, %object
audio_stub_pan_literal:
    .word audio_set_channel_pan
.size audio_stub_pan_literal, .-audio_stub_pan_literal
.global audio_stub_position_literal
.type audio_stub_position_literal, %object
audio_stub_position_literal:
    .word audio_set_channel_position
.size audio_stub_position_literal, .-audio_stub_position_literal
