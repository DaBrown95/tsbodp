#ifndef LINK_STATUS_POLL_PRIVATE_H
#define LINK_STATUS_POLL_PRIVATE_H
#include "link_endpoint_setup.h"
#include "irq.h"
void irq_wait_vblank(void);
unsigned int link_start_status_poll(unsigned int);
void link_wait_for_status_confirmation(void);
unsigned int link_read_status_original(void);
/* Remaining original-address IRQ service. */
void link_handshake_irq_original(void);
#endif
