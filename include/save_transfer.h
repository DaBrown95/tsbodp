#ifndef SAVE_TRANSFER_H
#define SAVE_TRANSFER_H

/* Twelve-byte parameter rows selected by values 4 and 64; roles are static. */
struct SaveTransferParameters {
    unsigned int byte_size;
    unsigned short blocks, wait_control;
    unsigned char address_bits, unknown09[3];
};
/* Nonstorage views of the observed RAM pointer and original constant rows. */
#define SAVE_TRANSFER_PARAMETERS \
    (*(const struct SaveTransferParameters **)0x030074e4)
#define SAVE_TRANSFER_PARAMETERS_4 \
    ((const struct SaveTransferParameters *)0x08d7074c)
#define SAVE_TRANSFER_PARAMETERS_64 \
    ((const struct SaveTransferParameters *)0x08d70758)

/* Observed fixed MMIO views. DMA pointer registers themselves are volatile. */
#define SAVE_TRANSFER_IME (*(volatile unsigned short *)0x04000208)
#define SAVE_TRANSFER_WAITCNT (*(volatile unsigned short *)0x04000204)
#define SAVE_TRANSFER_DMA_SOURCE (*(const void *volatile *)0x040000d4)
#define SAVE_TRANSFER_DMA_DESTINATION (*(void *volatile *)0x040000d8)
#define SAVE_TRANSFER_DMA_CONTROL (*(volatile unsigned int *)0x040000dc)
#define SAVE_TRANSFER_DMA_STATUS (*(volatile unsigned short *)0x040000de)

unsigned short save_transfer_configure_4c8f4(unsigned short);
void save_transfer_dma_copy(const void *, void *, unsigned short);
/* The word input is explicitly narrowed to a halfword before block checking. */
unsigned short save_transfer_read_4c9bc(unsigned int, void *);
/* Connected write/retry providers remain explicit and unconverted. */
unsigned short save_transfer_write_4ccb0(unsigned short, const void *);

#endif
