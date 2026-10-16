#include "scene_timed_notice.h"
void scene_timed_notice_shutdown(void)
{
    transition_run_second(63, 0);
}
asm(".align 2, 0");
