#include "display_time_format.h"

char *display_time_format(const struct DisplayTimeRecord *time, char *destination,
                          unsigned int text_id)
{
    const char *format;
    const char *scan;
    unsigned int ampm;
    unsigned char current;
    if (g_display_time_format_options.mode && text_id == 6225)
        format = display_scene_lookup_text(6227);
    else
        format = display_scene_lookup_text(text_id);
    scan = format;
    ampm = 0;
    current = *format;
    while (*scan) {
        if (*scan == '@') {
            ++scan;
            if (*scan == 'a' || *scan == 'A') {
                ampm = 1;
                break;
            }
        }
        ++scan;
    }
    scan = destination;
    {
        unsigned int value = current;
        while (value) {
            if (value == '@') {
                ++format;
                switch (*format) {
                case 'D':
                    if (time->day > 99)
                        *destination++ = display_bios_remainder(
                            display_bios_div(time->day, 100), 10) + '0';
                    if (time->day > 9)
                        *destination++ = display_bios_remainder(
                            display_bios_div(time->day, 10), 10) + '0';
                    *destination++ = display_bios_remainder(time->day, 10) + '0';
                    if (format[1] == 'D')
                        ++format;
                    break;
                case 'a':
                    if (time->hour <= 11)
                        *destination++ = 'a';
                    else
                        *destination++ = 'p';
                    break;
                case 'A':
                    if (time->hour <= 11)
                        *destination++ = 'A';
                    else
                        *destination++ = 'P';
                    break;
                case 'H': case 'h':
                    if (ampm) {
                        if (time->hour > 12) {
                            if (time->hour > 21)
                                *destination++ = '1';
                            else
                                *destination++ = ' ';
                            *destination++ = display_bios_remainder(
                                time->hour - 12, 10) + '0';
                        } else if (time->hour > 0) {
                            if (time->hour > 9)
                                *destination++ = '1';
                            else
                                *destination++ = ' ';
                            *destination++ = display_bios_remainder(time->hour, 10) + '0';
                        } else {
                            *destination++ = '1';
                            *destination++ = '2';
                        }
                    } else {
                        *destination++ = display_bios_div(time->hour, 10) + '0';
                        *destination++ = display_bios_remainder(time->hour, 10) + '0';
                    }
                    ++format;
                    break;
                case 'M': case 'm':
                    *destination++ = display_bios_div(time->minute, 10) + '0';
                    ++format;
                    *destination++ = display_bios_remainder(time->minute, 10) + '0';
                    break;
                case 'S': case 's':
                    *destination++ = display_bios_div(time->second, 10) + '0';
                    ++format;
                    *destination++ = display_bios_remainder(time->second, 10) + '0';
                    break;
                }
                if (!g_display_time_format_options.mode && text_id == 6227)
                    *destination++ = *format;
            } else {
                *destination++ = value;
            }
            ++format;
            value = *format;
        }
    }
    *destination = 0;
    return (char *)scan;
}
asm(".align 2, 0");
