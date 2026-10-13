#include "display_need_effect_update.h"
/* The signed sentinel is formed as a word before its byte store. */
static inline void reset_frame(signed char *frame)
{
 register int value asm("r0")=-1;
 *frame=value;
}
void frame_commit_need_effect(struct FrameObject *base,unsigned int mode)
{

 unsigned char *resource,*commands;
 unsigned int appearance;
 unsigned char *kind;
 if(((struct FrameNeedEffectObject *)base)->direction==1||((struct FrameNeedEffectObject *)base)->direction==7)resource=(unsigned char *)g_need_effect_resources[((struct FrameNeedEffectObject *)base)->kind]+16;
 else if(((struct FrameNeedEffectObject *)base)->direction==3||((struct FrameNeedEffectObject *)base)->direction==5)resource=(unsigned char *)g_need_effect_resources[((struct FrameNeedEffectObject *)base)->kind]+48;
 else return;
 kind=&((struct FrameNeedEffectObject *)base)->kind;
 if(*kind==82) {
  struct FrameNeedEffectState *state,*loaded;
 register unsigned int optional asm("r3");
 register unsigned int parameter asm("r0");

  appearance=g_need_effect_game_state[40];
  loaded=((struct FrameNeedEffectObject *)base)->effect_state;
  optional=loaded->optional;
  parameter=loaded->parameter;
  state=loaded;
  if(optional!=10) {
   if(((struct FrameNeedEffectObject *)base)->direction==1||((struct FrameNeedEffectObject *)base)->direction==7)resource=g_need_effect_appearances[appearance].resource+16;
   else if(((struct FrameNeedEffectObject *)base)->direction==3||((struct FrameNeedEffectObject *)base)->direction==5)resource=g_need_effect_appearances[appearance].resource+48;
   state->mode=g_need_effect_appearances[appearance].mode;
   ((struct FrameNeedEffectObject *)base)->effect_state->parameter=appearance<<8;
   ((struct FrameNeedEffectObject *)base)->effect_state->optional=10;
  } else {
   unsigned short selection=(short)parameter>>8;
   if(((struct FrameNeedEffectObject *)base)->direction==1||((struct FrameNeedEffectObject *)base)->direction==7)resource=g_need_effect_appearances[(short)selection].resource+16;
   else if(((struct FrameNeedEffectObject *)base)->direction==3||((struct FrameNeedEffectObject *)base)->direction==5)resource=g_need_effect_appearances[(short)selection].resource+48;
   state->mode=g_need_effect_appearances[(short)selection].mode;
  }
 }
 switch(mode) {
 case 0:commands=g_need_effect_programs[*kind][0];break;
 case 1:commands=g_need_effect_programs[*kind][1];break;
 case 2:commands=g_need_effect_programs[*kind][3];break;
 case 3:commands=g_need_effect_programs[*kind][2];break;
 case 4:commands=g_need_effect_programs[*kind][4];break;
 case 5:commands=g_need_effect_programs[*kind][5];break;
 default:return;
 }
 if(commands)frame_set_animation_program(base,(struct FrameSpriteResource *)resource,commands,0);
 else {
  if(*(unsigned char **)((unsigned char *)base+0xdc)!=resource) {
   *(unsigned char **)((unsigned char *)base+0xdc)=resource;
   *((unsigned char *)base+0xda)=255;
   reset_frame((signed char *)base+0xdb);
   ((struct FrameNeedEffectObject *)base)->requested_animation=mode;
  }
  *(unsigned char **)((unsigned char *)base+0xe4)=commands;
  *(unsigned char **)((unsigned char *)base+0xe0)=commands;
  frame_set_animation_frame((struct FrameTickObject *)base,0);
 }
 if(*kind==32) {
  struct FrameNeedEffectState *state,*loaded;
 register unsigned int optional asm("r3");
 register unsigned int parameter asm("r0");

  appearance=g_need_effect_game_state[40];
  loaded=((struct FrameNeedEffectObject *)base)->effect_state;
  optional=loaded->optional;
  parameter=loaded->parameter;
  state=loaded;
  if(optional!=10) {
   state->parameter=appearance<<8;
   ((struct FrameNeedEffectObject *)base)->effect_state->optional=10;
   frame_set_animation_frame((struct FrameTickObject *)base,g_need_effect_appearances[appearance].frame);
  } else {int selection=(short)parameter; frame_set_animation_frame((struct FrameTickObject *)base,g_need_effect_appearances[selection>>8].frame);}
 }
}
asm(".align 2, 0");
