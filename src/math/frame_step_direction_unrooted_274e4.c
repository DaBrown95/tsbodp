unsigned char frame_step_direction_unrooted_274e4(unsigned char current,
                                                 unsigned char target,
                                                 signed char *step)
{
    int difference = (current - target) & 31;
    if (difference <= 16)
        *step = -1;
    else
        *step = 1;
    current += *step;
    if (current <= 31)
        return current;
    if (current == 32)
        return 0;
    return 31;
}
