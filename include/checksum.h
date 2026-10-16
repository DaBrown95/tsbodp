#ifndef CHECKSUM_H
#define CHECKSUM_H

/* Reflected byte checksum with polynomial0x8C and initial value0.
 * No incoming caller or historical typedef is established. */
unsigned char crc8_reflected(const unsigned char *, unsigned int);

#endif
