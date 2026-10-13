#include "display_menu_primary.h"
#include "display_catalog_text.h"
#include "resource_conditions.h"

unsigned int display_menu_fallback_indicator(unsigned char actor)
{
    struct DisplayCatalogState *state = &g_display_catalog_state;
    unsigned int mode = *(unsigned int *)((unsigned char *)state + 0x440);
    if (mode == 3) {
        /* Loaded flag byte only; this extent has no calls. */
        register unsigned char flags asm("r2") = g_condition_display_bits[13];
        unsigned int first = flags & 16;
        unsigned char second = flags & 32;
        second = second != 0;
        if (first) {
            if (second) {
                if (actor == 12) {
                    if (*(signed char *)((unsigned char *)state + 0x69) > 69)
                        return 115;
                    return 114;
                }
                if (actor == 13) return 116;
                return 113;
            }
            if (actor == 12) {
                if (*(signed char *)((unsigned char *)state + 0x69) > 29)
                    return 111;
                return 110;
            }
            return 108;
        }
        if (second) {
            if (actor == 13) return 112;
            return 109;
        }
    } else if (mode == 4 && (g_condition_display_bits[14] & 32)) {
        if (actor == 15) return 118;
        return 117;
    }
    return 255;
}
asm(".align 2, 0");
