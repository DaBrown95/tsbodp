#include "display_text_resource.h"

int display_text_load_string(unsigned int id, char *output, unsigned int input_capacity)
{
    char *destination = output;
    unsigned int capacity = input_capacity;
    const unsigned char *source;
    unsigned int count, bit;
    unsigned char bits;
    if (!g_display_text_resource) return 1;
    source = g_display_text_resource + g_display_text_offsets[id];
    count = 0;
    bit = 0;
    bits = *source++;
    do {
        unsigned int node = 256;
        do {
            if ((bits >> bit) & 1) node = g_display_text_nodes[node - 256].one;
            else node = g_display_text_nodes[node - 256].zero;
            ++bit;
            if (bit == 8) {
                bit = 0;
                bits = *source++;
            }
        } while (node > 255);
        destination[count++] = node;
        if (!destination[count - 1]) return 0;
    } while (count != capacity);
    return 2;
}
