#include "frame_actor_target_cells.h"

unsigned int frame_actor_owner_cell_count(void *base, unsigned int mode)
{
 struct FrameActorTargetCellOwner *owner=base;
 unsigned int selected_mode=mode;
 unsigned int count=0;

 if(selected_mode==1 || selected_mode==4) {
  unsigned int maximum=12;
  unsigned int *cell;
  register unsigned short mask asm("r3");
  if(selected_mode==1)maximum=10;
  mask=0xffff;
  cell=owner->cells;
  for(;count<maximum;cell++,count++) {
   unsigned int value;
   if(selected_mode==1)value=cell[12];
   else value=*cell;
   if(!(value&mask))break;
  }
 } else {
  unsigned char *definition=g_frame_actor_owner_descriptors[((struct FrameActorOwnerKind *)owner)->kind];
  unsigned int i;
  unsigned char *codes;
  if(!definition)return 0;
  i=0;
  codes=definition+2;
  for(;i<5;) {
   unsigned int j=0;
   unsigned int scaled=i<<2;
   unsigned int next=i+1;
   unsigned char *code=(unsigned char *)(scaled+i+(unsigned int)codes);
   for(;j<5;code++,j++)if(*code==selected_mode)count++;
   i=next;
  }
 }
 return count;
}
