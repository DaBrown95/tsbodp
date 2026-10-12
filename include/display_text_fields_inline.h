#ifndef DISPLAY_TEXT_FIELDS_INLINE_H
#define DISPLAY_TEXT_FIELDS_INLINE_H
static __inline unsigned char *display_text_field_address(unsigned char *base,
                                                         unsigned int slot)
{
    return base + (slot << 6);
}
#endif
