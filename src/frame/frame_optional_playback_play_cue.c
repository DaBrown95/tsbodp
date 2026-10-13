#include "frame_optional_playback.h"
void frame_optional_playback_play_cue(struct FrameNeedEffectState *owner)
{
 int index=frame_random_range(0,9);
 if(((struct FrameOptionalPlaybackState *)owner)->parameter==256)index=g_optional_playback_cues_256[index];
 else index=g_optional_playback_cues_other[index];
 audio_play_animation_cue(index);
}
