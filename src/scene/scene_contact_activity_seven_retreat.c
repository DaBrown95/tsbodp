#include "scene_contact_activity_seven.h"
void scene_contact_activity_seven_retreat(struct FrameObject *base,unsigned int animation,unsigned int state) {
 struct FrameActorObject *object=(void *)base;
 STATE->presses=0;
 if(object->previous_frame==0) {
 frame_request_animation((struct FrameCommandObject *)object,animation);
 frame_set_variant_state(base,state);
 if(!audio_game_sample_active(STATE->sample)) {
 /* The observed load remains even though both selections name the same cue. */
 if(GAME->gender==1)STATE->sample=audio_play_animation_cue(226);
 else STATE->sample=audio_play_animation_cue(226);
 }
 } else {
 frame_set_animation_frame((struct FrameTickObject *)object,object->previous_frame-1);
 TIMER(object)=20;
 }
}
asm(".align 2,0");
