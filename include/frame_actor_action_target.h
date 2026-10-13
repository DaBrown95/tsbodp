#ifndef FRAME_ACTOR_ACTION_TARGET_H
#define FRAME_ACTOR_ACTION_TARGET_H

/* Partial list/callback view derived from the action-target selector. */
struct FrameObject;
struct FrameActionSearchNode {
 struct FrameActionSearchNode *next;
 unsigned char unknown04[4];unsigned int kind;
 unsigned char unknown0c[0x48];void *target;
 unsigned char unknown58[0x8c];
 unsigned char (*check)(struct FrameActionSearchNode *,struct FrameObject *);
 void (*actions)(struct FrameActionSearchNode *,unsigned char *);
};
struct FrameActionSearchDescriptor {unsigned char unknown00[34],enabled,unknown23;};
struct FramePendingAction;
extern struct FramePendingAction *g_frame_pending_action_head;
extern struct FrameActionSearchDescriptor g_frame_action_search_descriptors[];
void *scene_fill_bytes(void *,int,unsigned int);

#endif
