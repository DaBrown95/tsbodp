#include "display_palette_curve.h"

void display_configure_palette_curve(unsigned int incoming_parameter)
{
    unsigned short parameter = incoming_parameter;
    if (g_palette_curve_parameter != (short)parameter) {
        unsigned short pivot, step, accumulator;
        int index;
        if ((short)parameter > 512)
            parameter = 512;
        pivot = display_fixed_multiply((short)parameter, 0xf00);
        {
            short value = (short)pivot;
            step = display_fixed_divide(value, (short)(0x1f00 - value));
        }
        {
            int endpoint, position, maximum;
            accumulator = 0;
            index = 0;
            position = (short)pivot >> 8;
            maximum = 31;
            endpoint = maximum - position;
            if (index < endpoint) {
                int limit;
                unsigned char *output = g_palette_curve_values;
                int increment = (short)step;
                limit = endpoint;
                do {
                    unsigned char *destination = (unsigned char *)(
                        index + (unsigned int)output);
                    int current = (short)accumulator;
                    *destination = current >> 8;
                    current += increment;
                    accumulator = current;
                    ++index;
                } while (index < limit);
            }
        }
        {
            unsigned int high = (unsigned int)pivot << 16;
            short value = (int)high >> 16;
            accumulator = high >> 16;
            step = display_fixed_divide((short)(0x1f00 - value), value);
            index = 31 - ((int)high >> 24);
        }
        if (index <= 31) {
            unsigned char *output = g_palette_curve_values;
            int increment = (short)step;
            do {
                unsigned char *destination = (unsigned char *)(
                    index + (unsigned int)output);
                int current = (short)accumulator;
                *destination = current >> 8;
                current += increment;
                accumulator = current;
                ++index;
            } while (index <= 31);
        }
        g_palette_curve_parameter = parameter;
    }
}
