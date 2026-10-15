#ifndef LINK_SERIAL_HANDSHAKE_H
#define LINK_SERIAL_HANDSHAKE_H
#include "link_endpoint_setup.h"
#include "irq.h"
/* Literal-backed word access views; complete storage ownership is provisional. */
extern unsigned int g_link_word_03007350, g_link_last_serial_vblank;
void link_serial_handshake(void);
unsigned int link_serial_timeout(void);
/* Original boundaries: address-only installed handler and ignored-result call. */
void link_serial_interrupt(void);
void link_original_start_connection(void);
#define HANDSHAKE_RECEIVE(i) LINK_REG16(0x04000120+2*(i))
#define HANDSHAKE_CONTROL LINK_REG16(0x04000128)
#define HANDSHAKE_SEND LINK_REG16(0x0400012a)
#define HANDSHAKE_TIMER LINK_REG16(0x0400010e)
#endif
