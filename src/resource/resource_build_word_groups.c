#include "resource_builders.h"
extern unsigned char *g_resource_word_data;
unsigned char *resource_build_word_groups(const unsigned char *base,const unsigned char *selected,unsigned char *destination) {
 const unsigned char *base_groups,*selected_groups;
 unsigned char base_count,index;
 if(g_resource_group_flags&1) {
  base_groups=base+*(const unsigned short *)base;
  base_count=*base_groups;
 }else {base_groups=0;base_count=0;}
 selected_groups=selected+*(const unsigned short *)selected;
 base_count+=*selected_groups;
 *(unsigned short *)g_resource_word_data=base_count;
 destination+=resource_offset_table_bytes(base_count+1);
 if(g_resource_group_flags&1) {
  for(index=0;index<*(const unsigned short *)base_groups;index++) {
   { unsigned char *data=g_resource_word_data;unsigned int relative=destination-data;unsigned int bytes=index<<1;unsigned short *offsets=(unsigned short *)(data+2);*(unsigned short *)((unsigned char *)offsets+bytes)=relative; }
   destination=resource_build_word_group(base_groups,destination,index);
  }
  base_count=*base_groups;
 }else base_count=0;
 for(index=0;index<*(const unsigned short *)selected_groups;index++) {
  { unsigned char *data=g_resource_word_data;unsigned int relative=destination-data;unsigned int bytes=(index+base_count)<<1;unsigned short *offsets=(unsigned short *)(data+2);*(unsigned short *)((unsigned char *)offsets+bytes)=relative; }
  destination=resource_build_word_group(selected_groups,destination,index);
 }
 return destination;
}
