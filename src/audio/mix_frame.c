/*
 * Adapted from Krawall's kramWorker in lib/mixer_private.arm.c.
 * Copyright (C) 2001-2005, 2013 Sebastian Kienzl.
 * Source: https://github.com/sebknzl/krawall/tree/8d338581bf0ed0afad15b66bf5979ad4c4d15ed0
 * Changes: game-specific globals and names, explicit tick reload and an ARM/Thumb
 * long-call declaration; verified at the game's copied RAM execution address.
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the GNU Lesser General Public License as published by the Free Software
 * Foundation; either version 2.1 of the License, or (at your option) any later
 * version.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See licenses/Krawall-LGPL-2.1.txt for the licence.
 */
#include "audio_frame.h"
int audio_mix_frame(void) {
 unsigned char *left, *right;
 unsigned int remaining, count;
 remaining=audio_acquire_frame_buffers(&left,&right);
 if(remaining) {
  do {
   count=g_audio_tick_samples;
   if(count<=remaining && g_audio_tick_callback) {
    audio_mix_channels(left,right,count);
    count=g_audio_tick_samples;
    remaining -= count;
    left += count;
    right += count;
    g_audio_tick_callback();
    g_audio_tick_samples=g_audio_tick_period;
   } else {
    audio_mix_channels(left,right,remaining);
    g_audio_tick_samples-=remaining;
    break;
   }
  } while(remaining);
  return 1;
 }
 return 0;
}
