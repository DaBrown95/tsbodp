#include "resource_builders.h"
unsigned char *resource_copy_arena_header(const struct ResourceArenaHeader *source,const void *unused) {
 unsigned short index;
 g_resource_arena->count=source->count;
 for(index=0;index<g_resource_arena->count;index++) g_resource_arena->records[index]=source->records[index];
 { unsigned short bytes=source->bytes; g_resource_arena->bytes=bytes; return (unsigned char *)g_resource_arena+bytes; }
}
