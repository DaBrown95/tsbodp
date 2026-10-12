unsigned char frame_world_in_idle_exclusion_set(unsigned int world)
{
 switch(world) {
 case 16:case 17:case 18:case 21:case 23:case 24:case 25:
 case 39:case 40:case 46:case 47:case 48:return 1;
 default:return 0;
 }
}
asm(".align 2, 0");
