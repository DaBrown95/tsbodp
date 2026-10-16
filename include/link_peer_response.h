#ifndef LINK_PEER_RESPONSE_H
#define LINK_PEER_RESPONSE_H
#include "link_endpoint_setup.h"
/* Response count and mask access views follow the canonical handshake storage.
 * The complete protocol and incoming prototype population remain provisional. */
unsigned int link_peer_responses_complete(void);
#endif
