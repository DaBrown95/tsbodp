#include "display_text_template.h"
#include "display_text_draw.h"
#include "display_text_resource.h"
#include "display_text_bank.h"

unsigned int display_text_draw_template(
    unsigned int incoming_tile, unsigned int incoming_count,
    const struct DisplayTextTemplateEntry *incoming_entry)
{
    unsigned short tile = incoming_tile;
    /* Keep the count conversion split around entry cursor setup. */
    unsigned int count_shift = incoming_count << 16;
    const struct DisplayTextTemplateEntry *entry = incoming_entry;
    unsigned int count = count_shift >> 16;

    if (count) {
        do {
            if (entry->width) {
                int status = display_text_load_string(
                    entry->text, g_display_text_buffer, 1024);
                const char *text = 0;
                if (status == 0)
                    text = g_display_text_buffer;
                tile = display_text_draw_all_lines(
                    tile, entry->x, entry->y, entry->width, text, entry->style);
            } else {
                int status = display_text_load_string(
                    entry->text, g_display_text_buffer, 1024);
                const char *text = 0;
                if (status == 0)
                    text = g_display_text_buffer;
                tile = display_text_draw_line(
                    tile, entry->x, entry->y, text, entry->style);
            }
            ++entry;
            /* Preserve the original sixteen-bit decrement. */
            count = (unsigned short)(count - 1);
        } while (count);
    }
    return tile;
}
asm(".align 2,0");
