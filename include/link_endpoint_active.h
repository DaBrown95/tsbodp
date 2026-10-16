#ifndef LINK_ENDPOINT_ACTIVE_H
#define LINK_ENDPOINT_ACTIVE_H
/* Full-word return preserves the existing controller call view. The source
 * reads the canonical active byte; complete count/protocol roles remain open. */
unsigned int link_read_endpoint_active(void);
#endif
