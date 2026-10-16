#include "frame_render.h"
#include "frame_pool.h"
#include "heap.h"
#include "resource_decode.h"

extern unsigned char g_frame_sort_rom[], g_frame_sort_ram[];
extern unsigned char g_frame_collision_rom[], g_frame_collision_ram[];

void frame_install_runtime(void)
{
    g_frame_queue.backing_buffer = heap_allocate_zeroed(40960);
    g_frame_shared_display = heap_allocate_zeroed(572);
    g_frame_queue.free_list = frame_pool_initialize(
        g_frame_queue.backing_buffer, 128, 320);
    resource_bios_swi_0b(g_frame_sort_rom, g_frame_sort_ram, 0x04000047);
    resource_bios_swi_0b(g_frame_collision_rom, g_frame_collision_ram, 0x040000A0);
    g_frame_round_bias = 0;
}

asm(".align 2, 0");
