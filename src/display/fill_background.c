extern void display_fill_background_map(unsigned int, unsigned short, unsigned short);
void display_fill_background(unsigned int index, unsigned short tile)
{
    display_fill_background_map(index, tile, 0);
}
