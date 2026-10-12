#include "resource_groups.h"

void resource_activate_groups(unsigned char objects, unsigned char program) {
 if (resource_group_is_enabled(objects)) resource_spawn_group(objects);
 if (resource_group_is_enabled(program)) resource_execute_group(program);
}
