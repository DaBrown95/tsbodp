#include "scene_catalog_content.h"
unsigned char scene_catalog_has_next(unsigned char first,unsigned char count) {
 if(count==0)return 0;
 return first<((count-1)&0xfc);
}
asm(".align 2,0");
