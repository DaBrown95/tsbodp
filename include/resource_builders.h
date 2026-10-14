#ifndef RESOURCE_BUILDERS_H
#define RESOURCE_BUILDERS_H
#include "resource_groups.h"
/* Arena header fields are observed halfwords followed by pairs of words. */
struct ResourceArenaPair { unsigned int first,second; };
struct ResourceArenaHeader {
 unsigned short bytes,count;
 struct ResourceArenaPair records[0];
};
extern struct ResourceArenaHeader *g_resource_arena;
extern unsigned char *g_resource_word_data;
extern unsigned char g_resource_selected;
extern void *resource_allocate(unsigned int);
extern unsigned short resource_offset_table_bytes(unsigned short);
extern unsigned short resource_align_word(unsigned short);
extern void resource_copy_object_payload(const unsigned char *,unsigned char *,unsigned char);
extern unsigned char *resource_copy_arena_header(const struct ResourceArenaHeader *,const void *);
extern void resource_allocate_arena(void);
extern unsigned char *resource_build_object_group(const unsigned char *,unsigned char *,unsigned char);
extern unsigned char *resource_build_word_group(const unsigned char *,unsigned char *,unsigned char);
extern unsigned char *resource_build_program_group(const unsigned char *,unsigned char *,unsigned char);
extern unsigned char *resource_build_object_groups(const unsigned char *,const unsigned char *,unsigned char *);
extern unsigned char *resource_build_word_groups(const unsigned char *,const unsigned char *,unsigned char *);
extern unsigned char *resource_build_program_groups(const unsigned char *,const unsigned char *,unsigned char *);
#endif
