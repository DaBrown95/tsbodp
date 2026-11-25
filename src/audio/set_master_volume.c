/*
 * Adapted from Krawall lib/mixer.c (kramSetMasterVol).
 * Copyright (C) 2001-2005, 2013 Sebastian Kienzl.
 * Source: https://github.com/sebknzl/krawall/tree/8d338581bf0ed0afad15b66bf5979ad4c4d15ed0
 * Changes: contextual routine/symbol names and standalone declarations.
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the GNU Lesser General Public License as published by the Free Software
 * Foundation; either version 2.1 of the License, or (at your option) any later
 * version.
 * This library is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See licenses/Krawall-LGPL-2.1.txt for the licence.
 */
/* Revision 1 only. Revision 0's build of this routine has a blanked final
 * store that no C source reproduces; see the README. */
void audio_patch_mix_shift(unsigned int) __attribute__((long_call));
extern signed char g_audio_clip_table[];

void audio_set_master_volume(unsigned int vol)
{
	int i, v, x;

	if ((vol >> 16) == 0) {
		/* No explicit mix shift requested: default to 5. */
		audio_patch_mix_shift(5);
	}
	else {
		audio_patch_mix_shift((vol >> 16));
	}

	vol &= 0xff;

	/* Fill the clip table around its centre. */
	v = 0;
	for (i = 0; i < 1024; i++) {
		x = v >> 7;
		g_audio_clip_table[i] = (x > 127) ? 127 : x;
		g_audio_clip_table[-i] = (x > 128) ? -128 : -x;
		v += vol;
	}
	x = v >> 7;
	/* i is 1024 here; a constant -1024 index trips a GCC 3.0.2 bug. */
	g_audio_clip_table[-i] = (x > 128) ? -128 : -x;
}
