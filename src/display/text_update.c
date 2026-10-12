#include "display_text.h"
void display_text_update(struct FrameObject *object, const char **text)
{
    unsigned int limit = 0x7fffffff;
    void *work_buffer;
    unsigned char *pixels;
    display_scene_set_text_size(object, *text);
    work_buffer = heap_allocate(120);
    pixels = heap_allocate_zeroed(
        (((struct DisplayTextObject *)object)->oam.double_tile_size + 1) * 1920);
    display_text_set_buffers(work_buffer, pixels,
        ((struct DisplayTextObject *)object)->oam.double_tile_size);
    display_text_draw(0, 0, 0, 240, text, 0, &limit);
    if (((struct DisplayTextObject *)object)->height <= 8) {
        ((struct DisplayTextObject *)object)->oam.size = 1;
        DISPLAY_TEXT_DMA->source = (unsigned int)pixels;
        DISPLAY_TEXT_DMA->destination = 0x06010000 +
            (((struct DisplayTextObject *)object)->index << 5);
        DISPLAY_TEXT_DMA->control =
            (((struct DisplayTextObject *)object)->columns << 6) | 0x80000000;
        (void)DISPLAY_TEXT_DMA->control;
    } else {
        unsigned char *source;
        unsigned char *destination;
        int column, row;
        ((struct DisplayTextObject *)object)->oam.size = 2;
        source = pixels;
        destination = (void *)(0x06010000 +
            (((struct DisplayTextObject *)object)->index << 5));
        for (column = 0;
             column < ((struct DisplayTextObject *)object)->columns; ++column) {
            for (row = 4; row > 0; --row) {
                DISPLAY_TEXT_DMA->source = (unsigned int)source;
                DISPLAY_TEXT_DMA->destination = (unsigned int)destination;
                DISPLAY_TEXT_DMA->control = 0x80000010;
                (void)DISPLAY_TEXT_DMA->control;
                source += 32;
                DISPLAY_TEXT_DMA->source = (unsigned int)source;
                DISPLAY_TEXT_DMA->destination = (unsigned int)(destination + 128);
                DISPLAY_TEXT_DMA->control = 0x80000010;
                (void)DISPLAY_TEXT_DMA->control;
                source += 32;
                destination += 32;
            }
            destination += 128;
        }
    }
    heap_free(pixels);
    heap_free(work_buffer);
}
