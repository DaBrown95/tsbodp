extern void display_disable_layers(unsigned short);

void display_hide_background(unsigned int index) {
 display_disable_layers((0x01000000U << index) >> 16);
}
