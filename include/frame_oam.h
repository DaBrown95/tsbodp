#include "frame_affine.h"

extern struct FrameOam g_oam_empty;
extern unsigned char g_oam_storage[], g_oam_auxiliary_storage[];
extern unsigned char *g_oam_auxiliary;

void frame_initialize_oam(void);
void frame_reset_oam(void);
void frame_reset_affine_slots(void);
unsigned char frame_allocate_oam(void);
void frame_release_oam(unsigned char);
void frame_enable_oam(int);
void frame_disable_oam(int);

struct FrameOamDma {
    unsigned int source, destination, control;
};
#define FRAME_OAM_DMA3 ((volatile struct FrameOamDma *)0x040000D4)
