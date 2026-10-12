#ifndef RESOURCE_VIEW_EFFECTS_H
#define RESOURCE_VIEW_EFFECTS_H

/* FrameObject and FramePoint are defined by the including frame view. */
/* Forty-byte view effect records inferred from the two configuration handlers. */
struct ResourceViewEffect {
    struct FrameObject *object;
    struct FramePoint saved_velocity;
    unsigned char unknown0c[8];
    int parameter,duration;
    unsigned short phase,elapsed;
    unsigned char ready,unknown21,group_a,group_b,mode,variant,flags,done;
};
extern struct ResourceViewEffect g_resource_view_effects[];

#endif
