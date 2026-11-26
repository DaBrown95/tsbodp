/* Independently bounded word predicate; callers and unused formals unknown. */
unsigned int frame_code_in_range_2_to_35(unsigned int code)
{
    unsigned int result = 0;
    if (code >= 2u && code <= 35u)
        result = 1;
    return result;
}
asm(".align 2, 0");
