#ifndef FRAME_POOL_H
#define FRAME_POOL_H
/* These routines access only the first two intrusive node pointers. */
struct FrameObject;
struct FrameObjectList;
struct FrameObject *frame_pool_allocate_08024d50(void *,struct FrameObjectList *,unsigned int);
void frame_pool_release(void *,struct FrameObjectList *,struct FrameObject *);
struct FrameObject *frame_pool_pop(struct FrameObjectList *);
void frame_pool_push(struct FrameObjectList *,struct FrameObject *);
void frame_pool_remove(struct FrameObjectList *,struct FrameObject *);
struct FrameObject *frame_pool_initialize(void *, unsigned int, unsigned int);
unsigned int frame_pool_count(void *);
#endif
