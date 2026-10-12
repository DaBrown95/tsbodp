#include "resource_groups.h"

unsigned char resource_group_is_enabled(unsigned char group) {
 if (group && (!(g_resource_group_flags & 1) || group != 1)) return 1;
 return 0;
}
asm(".align 2, 0");
