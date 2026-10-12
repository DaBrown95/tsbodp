#ifndef FRAME_ACTOR_EFFECT_H
#define FRAME_ACTOR_EFFECT_H
/* FrameObject, FrameOam and variant-resource types come from the actor view.
 * The four word bounds are a bounded partial view; units remain provisional. */
struct FrameActorEffectObject {
 unsigned char unknown00[8]; unsigned short id,subtype; unsigned int flags;
 unsigned char unknown10[60]; unsigned char kind,state,unknown4e[22];
 struct FrameObject *owner; unsigned int cue_handle;
 unsigned char completion_mode,unknown6d[27];
 void (*on_step)(struct FrameObject *); unsigned char unknown8c[12];
 void (*before_step)(struct FrameObject *);
 int lower_x,lower_y,upper_x,upper_y;
 unsigned char unknownac[36]; struct FrameOam oam;
 unsigned char unknownd8[41]; unsigned char sharing_flags;
};
extern struct FrameVariantResource g_frame_actor_effect_resources[];
extern int g_frame_actor_effect_palettes[];
extern unsigned int g_frame_actor_effect_cues[];
void frame_acquire_palette_slot(struct FrameObject *,int);
void frame_actor_effect_tick(struct FrameObject *);
struct FrameObject *frame_create_actor_effect(struct FrameObject *,unsigned char,unsigned int,unsigned char);
#endif
