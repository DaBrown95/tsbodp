#ifndef DISPLAY_WORD_SCAN_H
#define DISPLAY_WORD_SCAN_H

/* Test an aligned word for a zero byte. Pass a value without side effects. */
#define DISPLAY_WORD_HAS_ZERO(value) \
    (((value) + 0xfefefeffU) & ~(value) & 0x80808080U)

#endif
