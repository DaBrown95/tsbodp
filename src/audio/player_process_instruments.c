/*
 * Adapted from Krawall's processInstruments in lib/player.c.
 * Copyright (C) 2001-2005, 2013 Sebastian Kienzl.
 * Source: https://github.com/sebknzl/krawall/tree/8d338581bf0ed0afad15b66bf5979ad4c4d15ed0
 * Changes: observed game track fields, natural instrument alignment,
 * direct volume/pan fields and signed-byte pan clipping.
 * Verified at the original ROM entry.
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
#include "audio_instrument.h"

static inline int setChannelVolH(struct AudioPlayerTrack *c)
{
    return audio_set_channel_volume(c->handle, c->volume * c->cvolume * c->i_vol >> 12);
}
static inline int setChannelPanH(struct AudioPlayerTrack *c)
{
    signed char x = c->panning + c->i_pan;
    if (x < -64) x = -64;
    if (x > 64) x = 64;
    return audio_set_channel_pan(c->handle, x);
}
static inline void stopChannel(struct AudioPlayerTrack *c)
{
    c->envelope_enabled = 0;
    audio_sample_release(c->handle);
}

void audio_player_process_instruments( struct AudioPlayerTrack *c, int amount )
{
	int i;

	for( i = amount; i; i--, c++ ) {

		if( !c->envelope_enabled )
			continue;

		const register struct AudioInstrument *ins = c->instrument;

		// ==============================
		// volume envelopes/fadeout
		// ==============================
		if( c->i_vol_status ) {
			int setVol = 0;

			// fading?
			if( c->i_vol_fadeactive ) {
				setVol = 1;
				c->i_vol_fade -= ins->volFade;
				if( c->i_vol_fade <= 0 ) {
					stopChannel( c );
					continue;
				}
			}

			// vol-envelope?
			if( c->i_vol_status >= AUDIO_ENV_ACTIVE ) {
				const struct AudioEnvelope *env = &ins->envVol;

				setVol = 1;
				c->i_vol_pos += env->nodes[ c->i_vol_node ].inc;

				// hit next node?
				if( ++c->i_vol_tick == c->i_vol_ticktarget ) {
					c->i_vol_node++;

					// sustain-node?
					if( ( env->flags & AUDIO_ENV_SUSTAIN ) &&
						( c->i_vol_node == env->sus ) &&
						( c->i_vol_status != AUDIO_ENV_ACTIVE_NOSUSTAIN ) ) {
						c->i_vol_status = AUDIO_ENV_SUSTAINING;
					}

					// max node? check for loop!
					if( c->i_vol_node == env->max ) {
						if( env->flags & AUDIO_ENV_LOOP ) {
							c->i_vol_node = env->loopStart;
							c->i_vol_tick = env->nodes[ c->i_vol_node ].coord & 0x1ff;
						}
						else {
							c->i_vol_status = AUDIO_ENV_STOPPED;
							if( ( env->nodes[ c->i_vol_node ].coord >> 9 ) == 0 ) {
								stopChannel( c );
								continue;
							}
						}
					}

					c->i_vol_pos = ( env->nodes[ c->i_vol_node ].coord >> 9 ) << 8;
					c->i_vol_ticktarget = 1 + ( env->nodes[ c->i_vol_node + 1 ].coord & 0x1ff );
				}
			}

			if( setVol ) {
				c->i_vol = ( c->i_vol_pos * c->i_vol_fade ) >> 23;
				if( !setChannelVolH( c ) ) {	// sample is already done (kramSetVolume returned false)
					stopChannel( c );
					continue;
				}
			}
		}

		// ==============================
		// panning envelopes/fadeout
		// ==============================
		// this is a little copy'n'paste. too bad :(
		if( c->i_pan_status >= AUDIO_ENV_ACTIVE ) {
			const struct AudioEnvelope *env = &ins->envPan;

			c->i_pan_pos += env->nodes[ c->i_pan_node ].inc;

			if( ++c->i_pan_tick == c->i_pan_ticktarget ) {
				c->i_pan_node++;

				if( ( env->flags & AUDIO_ENV_SUSTAIN ) &&
					( c->i_pan_node == env->sus ) &&
					( c->i_pan_status != AUDIO_ENV_ACTIVE_NOSUSTAIN ) ) {
					c->i_pan_status = AUDIO_ENV_SUSTAINING;
				}

				if( c->i_pan_node == env->max ) {
					if( env->flags & AUDIO_ENV_LOOP ) {
						c->i_pan_node = env->loopStart;
						c->i_pan_tick = 1 + ( env->nodes[ c->i_pan_node ].coord & 0x1ff );
					}
					else {
						c->i_pan_status = AUDIO_ENV_STOPPED;
					}
				}

				c->i_pan_pos = ( env->nodes[ c->i_pan_node ].coord >> 9 ) << 8;
				c->i_pan_ticktarget = env->nodes[ c->i_pan_node + 1 ].coord & 0x1ff;
			}

			c->i_pan = ( ( c->i_pan_pos >> 8 ) - 32 ) << 1;

			if( !setChannelPanH( c ) ) {
				stopChannel( c );
				continue;
			}
		}

		// ==============================
		// sample vibrato
		// ==============================
		if( ins->vibRate ) {
			// vibr-sweep's not implemented
			// vibr-type not implemented (using table set in current channel)
			unsigned short vperiod = c->periodc + ( ( ins->vibDepth * c->vibrtable[ c->i_vibrpos >> 2 ] ) >> 8 );
			audio_set_sample_step( c->handle, g_audio_player.calc_final_frequency( vperiod ) );
			c->i_vibrpos += ins->vibRate;
			c->i_vibrpos &= ( 64 << 2 ) - 1;	// =0xff
		}

	}
}
