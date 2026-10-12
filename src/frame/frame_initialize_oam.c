#include "frame_oam.h"
void frame_initialize_oam(void) {
 g_oam_previous=g_oam_storage;
 frame_reset_oam();
 frame_reset_affine_slots();
 g_oam_auxiliary=g_oam_auxiliary_storage;
}
asm(".align 2, 0");
