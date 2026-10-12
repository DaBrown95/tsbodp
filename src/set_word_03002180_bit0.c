/* Observed behaviour: nonzero low byte clears bit 0, zero sets it. */
void set_word_03002180_bit0(unsigned char enabled)
{
    if (enabled)
        *(unsigned int *)0x03002180 &= ~1u;
    else
        *(unsigned int *)0x03002180 |= 1u;
}
