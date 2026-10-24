#include "event_record.h"
#include "link_state.h"
#include "link_endpoint_setup.h"

int event_get_link_slot(void)
{
    return (signed char)g_link_setup_state.slot;
}
