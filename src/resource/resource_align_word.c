unsigned short resource_align_word(unsigned short bytes) { unsigned int remainder=bytes&3; if(remainder==1) remainder=3; else if(remainder==2) remainder=2; else if(remainder==3) remainder=1; return bytes+remainder; }
asm(".align 2, 0");
