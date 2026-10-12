#ifndef RESOURCE_GROUPS_H
#define RESOURCE_GROUPS_H
/* Offset-indexed resource groups and command records inferred from their walkers. */
#include "frame.h"
struct ResourceObjectEntry {
 struct FrameObject *object;
 unsigned int unknown_04;
 unsigned short factory;
};
struct ResourceProgramRecord { unsigned int command; };
typedef struct FrameObject *(*ResourceObjectFactory)(unsigned char, unsigned char);
typedef void (*ResourceProgramHandler)(struct ResourceProgramRecord *);
extern unsigned char *g_resource_object_data, *g_resource_program_data;
extern unsigned char g_resource_current_program;
extern unsigned short g_resource_group_flags;
extern ResourceObjectFactory g_resource_object_factories[];
extern ResourceProgramHandler g_resource_program_handlers[];
extern unsigned char g_resource_program_lengths[];
extern void resource_object_before_step(struct FrameObject *);
extern unsigned char resource_group_is_enabled(unsigned char);
extern void resource_spawn_group(unsigned char);
extern void resource_execute_group(unsigned char);
extern void resource_activate_groups(unsigned char,unsigned char);
#endif
