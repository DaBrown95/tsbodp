#include "heap.h"
void *heap_clear(void *memory,int value,unsigned int bytes)
{
    unsigned char *destination=memory;
    unsigned int leading=4-((unsigned int)memory&3);
    unsigned int i,words,pattern;
    if(leading!=4) {
        if(bytes<leading) leading=bytes;
        for(i=0;i<leading;++i) destination[i]=value;
        bytes-=i;
        destination+=i;
    }
    words=bytes>>2;
    pattern=(unsigned int)value|((unsigned int)value<<8);
    pattern|=pattern<<16;
    i=0;
    if(i<words) {unsigned int *word=(void*)destination;
        do {*word++=pattern; ++i;} while(i<words);
    }
    destination+=i*4;
    leading=bytes&3;
    for(i=0;i<leading;++i) destination[i]=value;
    return memory;
}
__asm__(".align 2, 0");
