/* GBA BLDCNT and BLDY; source names are reconstructed. */
void configure_blending(unsigned short control, unsigned short brightness)
{
    *(volatile unsigned short *)0x04000050 = control | 0x80;
    if (brightness > 16)
        brightness = 16;
    *(volatile unsigned short *)0x04000054 = brightness;
}
