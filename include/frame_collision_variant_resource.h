#ifndef FRAME_COLLISION_VARIANT_RESOURCE_H
#define FRAME_COLLISION_VARIANT_RESOURCE_H

struct FrameObject;
struct CollisionObject;
struct FrameVariantResource;

/* Word-aligned payload access prefix; the factory reads bytes zero through eight. */
struct FrameCollisionVariantPayload {
    unsigned int selector_word;
    short x, y;
    unsigned char kind;
};

/* Whole-object access prefix; field roles remain provisional. */
struct FrameCollisionVariantView {
    unsigned char unknown00[8];
    unsigned short id, subtype;
    unsigned int flags;
    unsigned char unknown10[0x3c], kind, state, variant, pending_updates;
    unsigned char unknown50[0x38];
    void (*on_step)(struct FrameObject *);
    unsigned char unknown8c[0x22], mode_ae, unknownaf[0x19];
    void (*on_contact)(struct CollisionObject *, struct CollisionObject *);
    unsigned char unknowncc[5];
    unsigned char mode : 2, contact_mode : 2, unknown_d1_4 : 1;
    unsigned char double_size : 1, unknown_d1_6 : 2;
    unsigned char unknownd2[0x2e], strip_mode, sharing_flags, shared_group;
};

/* Five records/pointers are observed; complete table capacities are unknown. */
extern struct FrameVariantResource g_frame_collision_variant_animations[];
extern const void *const g_frame_collision_variant_palettes[];
struct FrameObject *frame_create_collision_variant_resource(unsigned char, unsigned char);
void frame_collision_variant_resource_step(struct FrameObject *);

#endif
