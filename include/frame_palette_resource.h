#ifndef FRAME_PALETTE_RESOURCE_H
#define FRAME_PALETTE_RESOURCE_H
struct FrameObject;
struct CollisionObject;
struct FrameVariantResource;
struct FramePaletteResourcePayload {unsigned int id;short x,y;unsigned char palette;};
struct FramePaletteResourceView {
 unsigned char unknown00[12];unsigned int flags;
 unsigned char unknown10[2],direction,unknown13[0x4c-0x13];
 unsigned char actor_id,state,unknown4e[0x88-0x4e];
 void (*on_step)(struct FrameObject *);
 unsigned char unknown8c[0xc8-0x8c];
 void (*contact[2])(struct CollisionObject *,struct CollisionObject *);
 unsigned char unknownd0;
 unsigned char mode:2,contact_mode:2,unknown_d1_4:1,double_size:1,unknown_d1_6:2;
};
extern struct FrameVariantResource g_frame_palette_resource_animation;
struct FrameObject *frame_create_palette_resource(unsigned char,unsigned char);
void frame_palette_resource_step(struct FrameObject *);
#endif
