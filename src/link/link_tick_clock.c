#include "link_endpoint_setup.h"
unsigned int link_tick_clock(void) {unsigned int result=++g_link_clock_03002178;if(result<=10)result=1;else {result=0;g_link_clock_03002178=result;}return result;}
