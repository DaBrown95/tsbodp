#include "link_endpoint_active.h"
#include "link_endpoint_setup.h"

unsigned int link_read_endpoint_active(void)
{
    return g_link_setup_state.active;
}
