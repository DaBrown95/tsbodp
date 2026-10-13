#ifndef DISPLAY_NEED_EFFECT_LIFECYCLE_H
#define DISPLAY_NEED_EFFECT_LIFECYCLE_H
#include "frame_need_effect.h"
#include "frame_pool.h"
#include "frame_actor_attachment.h"
#include "heap.h"

/* A 256-byte access view; callback signatures and retained fields stay provisional. */
struct DisplayNeedEffectStateView {
    struct FrameNeedEffectState *next, *previous;
    unsigned int kind;
    struct FrameActorAttachmentRecord records[3];
    struct FrameObject *object, *auxiliary_object;
    unsigned char unknown_5c, definition_20, unknown_5e, mode;
    unsigned char definition_21, definition_22, enabled, unknown_63;
    unsigned char unknown_64[12];
    unsigned short parameter;
    unsigned char optional, unknown_73;
    unsigned char work_74[48], work_a4[40];
    unsigned int value_cc, value_d0, value_d4, value_d8;
    unsigned char value_dc, unknown_dd[7];
    void *callback_e4, *callback_e8, *callback_ec, *callback_f0;
    void *callback_f4, *callback_f8, *callback_fc;
};
struct DisplayNeedEffectDefinitionView {
    void *callback, *callback_e8, *callback_ec, *callback_f0;
    void *callback_f4, *callback_f8, *callback_fc, *callback_e4;
    unsigned char definition_20, definition_21, definition_22, unknown_23;
};
extern void *g_frame_registration;
extern unsigned int g_frame_world_id;
extern struct FrameNeedEffectState *g_frame_need_effect_free_pool;
extern struct FrameObjectList g_frame_need_effect_active_list;
void frame_unregister_need_effect(void *, struct FrameObject *);
unsigned int frame_release_need_effect_state(struct FrameNeedEffectState *);
struct FrameNeedEffectState *frame_create_need_effect_state_node(void);
void frame_reset_need_effect(struct FrameObject *);
unsigned char frame_need_effect_enabled(struct FrameObject *);
unsigned char frame_world_in_idle_exclusion_set(unsigned int);
#endif
