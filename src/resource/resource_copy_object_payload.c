void resource_copy_object_payload(const unsigned char *source,unsigned char *destination,unsigned char bytes) {
 unsigned char index;
 destination+=8;
 for(index=0;index<bytes;index++)*destination++=*source++;
}
