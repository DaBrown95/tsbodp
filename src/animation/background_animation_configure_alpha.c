extern void transition_configure_alpha(unsigned short, unsigned short);
extern void transition_set_alpha(unsigned short, unsigned short);

void background_animation_configure_alpha(void) {
 transition_configure_alpha(2, 16);
 transition_set_alpha(8, 8);
}

/* Original zero-filled alignment, separate from the C instruction body. */
asm(".align 2, 0");
