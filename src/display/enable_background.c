extern void display_enable_layers(unsigned short);

void display_enable_background(unsigned int index)
{
    display_enable_layers((0x01000000U << index) >> 16);
}
