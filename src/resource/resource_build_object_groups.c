#include "resource_builders.h"
unsigned char *resource_build_object_groups(const unsigned char *base,const unsigned char *selected,unsigned char *destination) {
 const unsigned char *groups;
 unsigned char count,index;
 unsigned short stride;
 g_resource_group_flags=*(const unsigned short *)(selected+4);
 groups=selected+8;
 selected=groups;
 count=*selected;
 if(g_resource_group_flags&1) *(unsigned short *)g_resource_object_data=count+1;
 else *(unsigned short *)g_resource_object_data=count;
 stride=resource_offset_table_bytes(*(unsigned short *)g_resource_object_data+1);
 destination+=stride;
 if(g_resource_group_flags&1) {
  *(unsigned short *)(g_resource_object_data+2)=stride;
  groups=base+8;
  destination=resource_build_object_group(groups,destination,0);
 }
 groups=selected;
 for(index=0;index<count;) {
  stride=destination-g_resource_object_data;
  if(g_resource_group_flags&1) { unsigned int offset=index+1; unsigned int bytes=offset<<1; unsigned short *offsets=(unsigned short *)(g_resource_object_data+2); *(unsigned short *)((unsigned char *)offsets+bytes)=stride; stride=offset; }
  else { unsigned int bytes=index<<1; unsigned short *offsets=(unsigned short *)(g_resource_object_data+2); *(unsigned short *)((unsigned char *)offsets+bytes)=stride; stride=index+1; }
  destination=resource_build_object_group(groups,destination,index);
  index=stride;
 }
 return destination;
}
