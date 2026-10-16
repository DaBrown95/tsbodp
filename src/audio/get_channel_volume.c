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
 * Adapted from Krawall lib/mixer.c and lib/player.c.
 * Copyright (C) 2001-2005, 2013 Sebastian Kienzl.
 * Source: https://github.com/sebknzl/krawall/tree/8d338581bf0ed0afad15b66bf5979ad4c4d15ed0
 * Changes: observed game channel fields, low-byte handle view and volume names.
 * LGPL-2.1-or-later; see licenses/Krawall-LGPL-2.1.txt for the licence.
 */
#include "audio_queries.h"

unsigned int audio_get_channel_volume(unsigned int handle)
{
    return g_audio_sample_channels[(unsigned char)handle].volume;
}
