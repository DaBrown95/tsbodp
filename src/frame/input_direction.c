#include "input.h"
InputU8 input_direction(InputU8 player)
{
    return g_input_direction_table[(g_input_current[player] & 0xf0) >> 4];
}
