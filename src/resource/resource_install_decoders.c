#include "resource_decode.h"
void resource_install_decoders(void) {
 resource_bios_swi_0b(g_resource_tile_decoder_rom, g_resource_tile_decoder_ram,0x04000084);
 g_display_tile_decompress=(void*)g_resource_tile_decoder_ram;
 resource_bios_swi_0b(g_resource_background_decoder_rom,g_resource_background_decoder_ram,0x040000D4);
 g_display_background_decompress=(void*)g_resource_background_decoder_ram;
}
asm(".align 2,0");
