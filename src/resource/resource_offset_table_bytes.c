unsigned short resource_offset_table_bytes(unsigned short count) { if(count&1)count++; count*=2; return count; }
asm(".align 2, 0");
