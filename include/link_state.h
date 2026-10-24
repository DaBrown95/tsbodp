#ifndef TSBODP_LINK_STATE_H
#define TSBODP_LINK_STATE_H
/* Shared flags and poll interface. Endpoint field users include
 * link_endpoint_setup.h for the existing canonical storage owner. */
extern volatile unsigned int g_link_flags;
extern unsigned int g_link_recording;
extern unsigned char link_transfer_finished(void);

#endif
