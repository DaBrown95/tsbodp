#include "frame_optional_activation.h"

/* Independently bounded no-op; no incoming root or consumed input is known. */
void frame_optional_activation_empty_hook(void)
{
}
asm(".align 2, 0");
