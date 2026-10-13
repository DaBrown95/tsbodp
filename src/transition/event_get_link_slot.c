#include "event_record.h"
#include "link_state.h"

int event_get_link_slot(void)
{
    return (signed char)g_link_endpoint.slot;
}
