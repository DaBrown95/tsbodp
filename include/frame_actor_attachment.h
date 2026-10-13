#ifndef FRAME_ACTOR_ATTACHMENT_H
#define FRAME_ACTOR_ATTACHMENT_H
struct FrameObject;
struct FramePoint;
struct FrameActorAttachmentView {unsigned char unknown00[0x138];struct FrameObject *slots[2];};
unsigned char frame_attach_actor(struct FrameObject *,struct FrameObject *);
void frame_detach_actor(struct FrameObject *,struct FrameObject *);
unsigned char frame_count_actor_attachments(struct FrameObject *);
unsigned int frame_actor_attachment_status(struct FrameObject *,struct FrameObject *);
unsigned char frame_grid_snap_point_to_center(void *,const struct FramePoint *,struct FramePoint *);
struct FrameActionTargetOwner {unsigned char unknown00[0x64];void *owner;};
struct FrameActionOwnerCallbacks {
 unsigned char unknown00[0xe4];unsigned char (*check)(void *,struct FrameObject *);
 unsigned char unknowne8[8];unsigned char (*use)(void *,struct FrameObject *,unsigned char);
};
struct FrameActorAttachmentRecord {
 struct FrameObject *actor;unsigned int kind;int timer;
 unsigned char running,unknown0d[3];unsigned int status,unknown14;
};
struct FrameActorAttachmentOwner {
 unsigned char unknown00[12];struct FrameActorAttachmentRecord records[3];
 unsigned char unknown54[0xa0];unsigned int (*step)(struct FrameObject *,struct FrameObject *);
};
void frame_finish_actor_attachment(struct FrameActorAttachmentRecord *);
#endif
