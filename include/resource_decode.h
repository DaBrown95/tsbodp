#ifndef RESOURCE_DECODE_H
#define RESOURCE_DECODE_H

/* Header fields inferred from the decoded-size and codec dispatch accesses. */
struct ResourceStream {
    unsigned int unknown0 : 4;
    unsigned int codec : 4;
    unsigned int size : 24;
};
unsigned int resource_decoded_size(const void *);
unsigned int resource_decode_bytes(const void *, void *);
extern void (*g_display_tile_decompress)(const void *, void *, unsigned int *);
extern void (*g_display_background_decompress)(const void *, void *, unsigned int *);

/* Observed SWI numbers. Providers are explicit glue with zero C coverage. */
void resource_bios_swi_0b(const void *, void *, unsigned int);
void resource_bios_swi_11(const void *, void *);
void resource_bios_swi_13(const void *, void *);
void resource_bios_swi_14(const void *, void *);
/* In-place halfword prefix reconstruction. */
void resource_decode_delta(void *, unsigned int);

void resource_decode_delta_alternate(void *, unsigned int);
unsigned int resource_decode_alternate(const void *, void *);
void resource_install_decoders(void);

/* These copied ARM bodies remain unconverted. */
extern unsigned char g_resource_tile_decoder_rom[], g_resource_tile_decoder_ram[];
extern unsigned char g_resource_background_decoder_rom[], g_resource_background_decoder_ram[];
void resource_bios_swi_0c(const void *, void *, unsigned int);
void resource_bios_swi_12(const void *, void *);
void resource_bios_swi_15(const void *, void *);

#endif
