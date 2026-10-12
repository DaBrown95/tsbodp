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

/* Names identify the observed SWI numbers; wrapper bodies remain original. */
void resource_bios_swi_0b(const void *, void *, unsigned int);
void resource_bios_swi_11(const void *, void *);
void resource_bios_swi_13(const void *, void *);
void resource_bios_swi_14(const void *, void *);
/* Connected second-pass body remains unconverted. */
void resource_decode_delta(void *, unsigned int);

#endif
