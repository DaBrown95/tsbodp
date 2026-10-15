#include "scene_contact_activity_one.h"
#define STATE ((struct SceneContactActivityOneState*)g_scene_contact_state)
void scene_contact_activity_one_reward(void) {
 int total,cue;
 scene_contact_activity_one_accumulate_count(STATE->counts[0],4);
 scene_contact_activity_one_accumulate_count(STATE->counts[1],8);
 scene_contact_activity_one_accumulate_count(STATE->counts[2],12);
 scene_contact_activity_one_accumulate_count(STATE->counts[3],16);
 total=STATE->counts[0]*5;total+=STATE->counts[1]*10;total+=STATE->counts[2]*20;total+=STATE->counts[3]*30;
 cue=220;if(total<=79){cue=218;if(total>49)cue=219;}
 total=save_world_scale_percent(STATE->score,(unsigned short)total);
 STATE->score+=total+total*(STATE->option+1);
 if(((struct FrameActorObject*)STATE->primary)->requested_animation==7){STATE->score-=30;cue=221;}
 else if(((struct FrameActorObject*)STATE->primary)->requested_animation==8){STATE->score-=50;cue=221;}
 if(STATE->score<=0)STATE->score=1;
 scene_contact_add_activity_score(STATE->score);audio_play_animation_cue(cue);
 STATE->score=0;STATE->counts[0]=0;STATE->counts[1]=0;STATE->counts[2]=0;STATE->counts[3]=0;
}
asm(".align 2,0");
