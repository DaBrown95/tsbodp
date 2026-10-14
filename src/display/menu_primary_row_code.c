#include "display_menu_primary.h"
#include "display_catalog_text.h"
#include "frame.h"
#include "frame_actor_relation.h"
#include "frame_random.h"

struct ConditionActorEntries;
int actor_entry_is_empty(struct ConditionActorEntries *);
extern const int g_display_menu_record_thresholds[];

/* Local access view; the world word's business meaning remains uncertain. */
struct DisplayMenuThresholdWorld {
    unsigned int unknown00;
    int value;
};

unsigned int display_menu_primary_row_code(unsigned int input)
{
    register unsigned int row asm("r5") = input;
    register unsigned int result asm("r4") = 0;
    unsigned int selected = 0;

    ((struct FrameObject *)g_display_menu_objects.unknown_00[1])->flags |= 1;
    if (g_display_menu_state.choice != 255) {
        const struct DisplayMenuTextRecord *records =
            g_display_menu_text_records[g_display_menu_state.record_group];
        register const unsigned char *entries asm("r0");
        register const unsigned char *entry_address asm("r1");
        register unsigned int entry asm("r0");

        entries = (const unsigned char *)(g_display_menu_state.choice *
            sizeof(*records) + (unsigned int)records);
        entries += 4;
        entry_address = entries + row;
        entry = *entry_address;
        if (entry != 255 && row <= 3) {
            const unsigned int *flags_address = (const unsigned int *)(
                (const unsigned char *)&records[entry] + 20);
            if (*flags_address & 0x7e00) {
                int bit = 6;
                unsigned int mask = 0x200;
                unsigned int flags = *flags_address;
                const struct DisplayMenuThresholdWorld *world =
                    (const struct DisplayMenuThresholdWorld *)&g_display_catalog_state;

                for (; bit >= 0; --bit)
                    if (flags & (mask << bit)) {
                        if (world->value >= g_display_menu_record_thresholds[bit])
                            result = row + 23;
                        else
                            result = 29;
                        selected = 1;
                    }
            } else {
                result = row + 23;
                goto done;
            }
        } else {
            result = 29;
            goto done;
        }
    } else {
        if (row == 3) {
            if ((unsigned char)actor_entry_is_empty(
                    (struct ConditionActorEntries *)g_display_catalog_state.context))
                goto needs_code;
            goto done;
        } else if (row == 4) {
            result = 21;
            selected = 1;
        }
    }

needs_code:
    if (!selected) {
        unsigned int index;
        unsigned char *state = (unsigned char *)&g_display_catalog_state;
        do {
            result = frame_random_bounded(22);
            if (result != 0 && result != 21) {
                for (index = 0; index <= 4; ++index)
                    if (result == g_display_menu_state.codes[index]) {
                        selected = 0;
                        break;
                    }
                if (index == 5) {
                    selected = 1;
                    if (g_display_menu_state.definition == 12 ||
                            state[32] == g_frame_actor_greetings[
                                g_display_menu_state.definition].cue_variant) {
                        if (result - 4 <= 1 || result == 14)
                            selected = 0;
                    }
                    if (result == 22 && state[0x740] != 42) {
                        if (state[0x740] == g_display_menu_state.definition + 18)
                            result = 28;
                        else
                            selected = 0;
                    }
                }
            }
        } while (!selected);
    }

done:
    return result;
}

asm(".align 2, 0");
