#ifndef SCENE_CONTACT_ACTIVITY_TWO_ACCESS_H
#define SCENE_CONTACT_ACTIVITY_TWO_ACCESS_H
#include "scene_contact_activity_two.h"
/* One actual aligned flags word is snapshotted and committed; this 4-byte
 * record contains no other field and is not an invented overlapping union. */
struct SceneContactActivityTwoControlWord { unsigned int bits; };
static inline struct SceneContactActivityTwoControlWord scene_contact_activity_two_read_control(struct FrameObject *object)
{ return *(const struct SceneContactActivityTwoControlWord *)&object->flags; }
static inline void scene_contact_activity_two_write_control(struct FrameObject *object,struct SceneContactActivityTwoControlWord flags)
{ *(struct SceneContactActivityTwoControlWord *)&object->flags = flags; }
/* Field-address arithmetic uses the actual 32-bit target word; the pointer
 * denotes one coordinate field, not an array of unrelated members. */
static inline int scene_contact_activity_two_row_coordinate(const void *field,unsigned int offset)
{ return *(const int *)(offset+(unsigned int)field); }
static inline unsigned char scene_contact_activity_two_rate(const void *table,unsigned int variant,unsigned int subtype)
{ return *((const unsigned char *)table+(variant*3+subtype)); }
static inline int scene_contact_activity_two_reward_share(int value,int divisor)
{ return value/divisor; }
#endif
