#include "audio_game.h"

void audio_select_sequence(unsigned char id)
{
    if (g_audio_game_options.sequences_volume) {
        register struct AudioVBlankControl *active __asm__("r5") = &g_audio_control;
        if (id != active->sequence_id || (active->flags & 2)) {
            const void *sequence;
            register unsigned int parameters __asm__("r4");
            register struct AudioSequenceDescriptor *descriptor __asm__("r0");
            active->flags |= 0x80;
            {
                register struct AudioSequenceDescriptor *table __asm__("r1") = g_audio_sequence_descriptors;
                descriptor = (struct AudioSequenceDescriptor *)((id << 3) + (unsigned int)table);
            }
            sequence = descriptor->sequence;
            parameters = descriptor->parameters.word;
            audio_start_sequence(sequence, descriptor->parameters.bytes[0], (unsigned char)(parameters >> 8));
            audio_sync_game_state();
            active->flags &= 0xfd;
            (void)g_audio_scene_word;
            active->pacing = 8;
            {
                register struct AudioVBlankControl *control __asm__("r2") = &g_audio_control;
                if (!(control->flags & 1)) control->sequence_id = id;
            }
        }
    } else g_audio_control.sequence_id = id;
}
