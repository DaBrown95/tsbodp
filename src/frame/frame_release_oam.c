#include "frame_oam.h"
void frame_release_oam(unsigned char index) {
 frame_disable_oam(index);
}
asm(".align 2, 0");
