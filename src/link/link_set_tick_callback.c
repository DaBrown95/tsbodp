#include "link_endpoint_setup.h"
void link_set_tick_callback(unsigned int (*callback)(void)) {g_link_setup_state.callback=callback;}
