extern void display_configure_background(unsigned int, unsigned int);
extern void display_enable_layers(unsigned short);

void display_show_background(unsigned int index, unsigned int control) {
 display_configure_background(index, control);
 display_enable_layers((0x01000000U << index) >> 16);
}

/* Original zero-filled alignment, separate from the C instruction body. */
asm(".align 2, 0");
