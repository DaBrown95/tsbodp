#include "frame_actor_needs.h"
#include "frame_actor_state.h"
#include "frame_actor_relation.h"
#include "view_math.h"
#include "audio_game.h"

static inline unsigned int narrow_subtype(unsigned int value)
{
 register unsigned int high asm("r0")=value<<16;
 return high>>16;
}

void frame_actor_state_46(struct FrameObject *object)
{
 unsigned int distance=view_point_distance(g_frame_actor_need_input.views[0].actor->position,object->position);
 unsigned int subtype=((struct FrameActorObject *)object)->subtype;
 int relation;
 register unsigned short loaded asm("r0");
 unsigned int current;
 register unsigned int narrowed asm("r3");

 if (distance<=0x1fffff && ((struct FrameActorObject *)object)->requested_animation==1)
  frame_set_actor_direction(object,frame_direction_toward(object,g_frame_actor_need_input.views[0].actor));
 /* Reload after the direction calls, only after the earlier guards pass. */
 if (distance>0x3fffff || (((struct FrameActorObject *)object)->unknown_50&1) || object->id!=7 ||
     (loaded=((struct FrameActorObject *)object)->subtype,current=loaded,narrowed=loaded,current<=17))
  return;
 {
  relation=((struct FrameActorRelationState *)&g_resource_game_state)->records[((struct FrameActorObject *)object)->actor_id-18].value;
  if (relation>29 && current<=31 &&
      (subtype==19 || subtype==21 || subtype==24 || subtype==25 || subtype==27 || subtype==31 || subtype==29 || subtype==26 || subtype==23 || subtype==20))
   goto marked;
  if (relation<0 && narrow_subtype(narrowed)<=31 &&
      (subtype==18 || subtype==19 || subtype==21 || subtype==23 || subtype==24 || subtype==25 || subtype==27 || subtype==30 || subtype==29 || subtype==26 || subtype==20)) {
marked:
   ((struct FrameActorObject *)object)->unknown_50|=1;
   return;
  }
  if (relation==-128 || (unsigned int)relation<=29)
   return;
  frame_stop_motion(object);
  frame_set_actor_direction(object,frame_direction_toward(object,g_frame_actor_need_input.views[0].actor));
  ((struct FrameActorObject *)object)->unknown_50|=1;
  if (relation>29) {
   frame_request_animation((struct FrameCommandObject *)object,65);
   frame_set_variant_state(object,62);
   audio_play_animation_cue(g_frame_actor_greetings[subtype-18].cue_record[7]);
   ((struct FrameActorStateWork *)object)->timer=60;
  } else {
   frame_request_animation((struct FrameCommandObject *)object,56);
   frame_set_variant_state(object,63);
   if (!g_frame_actor_greetings[subtype-18].cue_variant) {
    if (frame_random_range(0,2)) audio_play_animation_cue(148);
    else audio_play_animation_cue(139);
   } else {
    if (frame_random_range(0,2)) audio_play_animation_cue(147);
    else audio_play_animation_cue(138);
   }
  }
 }
}
asm(".align 2, 0");
