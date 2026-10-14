#ifndef FRAME_SCENE_TRIGGER_H
#define FRAME_SCENE_TRIGGER_H

/* Partial object and serialized payload views for factory slot 11. */
struct FrameObject;
struct CollisionObject;
struct SceneTriggerView {
 unsigned char unknown00[8];unsigned short id;unsigned char unknown0a[9],player;
 unsigned char unknown14[0x4d-0x14],state,unknown4e[0x64-0x4e];
 unsigned short selector;unsigned char unknown66[0x88-0x66];
 void (*on_step)(struct FrameObject *);
 unsigned char unknown8c[0xaf-0x8c],bound_count;
 signed char left,right,top,bottom,bound_kind;
 unsigned char unknownb5[0xc8-0xb5];
 void (*on_contact)(struct CollisionObject *,struct CollisionObject *);
};
struct SceneTriggerPayload {unsigned int id;short x,y;unsigned char width,height,selector;};
struct FrameObject *frame_allocate_scene_object(void);
void frame_set_position(struct FrameObject *,int,int);
void frame_scene_trigger_contact(struct CollisionObject *,struct CollisionObject *);
void frame_scene_trigger_noop(struct FrameObject *);
void resource_submit_scene(unsigned int, unsigned int, unsigned int);
struct FrameObject *frame_create_scene_trigger(unsigned char, unsigned char);

#endif
