/* Nothing in the ROM is known to call this; its signature is provisional. */
void frame_empty_hook_1db20(void)
{
}

/* The next independent entry starts at the following word boundary. */
asm(".align 2, 0");
