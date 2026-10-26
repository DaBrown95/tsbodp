#include "display_menu_pages.h"
#include "resource_actor_entries.h"
#include "display_time.h"

/* Observed eight-byte ROM row; complete table domains remain provisional. */
struct MenuChoiceDefinition {
    unsigned char count, unknown_01[3];
    const unsigned int *ids;
};
extern struct MenuChoiceDefinition g_menu_choice_definitions[];
extern const unsigned int g_menu_choice_actor_ids[];
extern const struct DisplayTimeRecord g_menu_choice_next_day_delta;

static inline unsigned int choice_actor_id(unsigned char actor)
{
    register unsigned int index asm("r1") = actor;
    return g_menu_choice_actor_ids[index];
}

static inline struct DisplayTimeRecord *choice_stamp(
    struct DisplayMenuSelectionState *record)
{
    register struct DisplayMenuSelectionState *base asm("r2") = record;
    return &base->stamp;
}

unsigned char display_menu_prepare_choice(void *pointer, unsigned int argument,
    void *output)
{
    struct DisplayMenuSelectionState *record = pointer;
    struct { const struct DisplayTimeRecord *pointer; } saved = {output};
    unsigned char definition = argument;

    if (record->enabled != 1) {
        union ResourceGameState *game = &g_resource_game_state;
        if (!(unsigned char)actor_entry_is_full(game->actor.secondary_entries)
            && game->scene.stage != 0) {
            union { unsigned int word; unsigned short half[2]; } bound;
            register const unsigned int **ids asm("r6");
            {
                register struct MenuChoiceDefinition *table asm("r1") =
                    g_menu_choice_definitions;
                unsigned int mode = game->scene.stage;
                register unsigned int offset asm("r2") = mode * sizeof(*table);
                bound.word = (unsigned int)(*(unsigned char *)(offset
                    + (unsigned int)table) - 1) << 16;
                {
                    register unsigned int column asm("r1") =
                        (unsigned int)table + 4;
                    ids = (const unsigned int **)(offset + column);
                }
            }
            do {
                record->text_kind = frame_random_bounded(bound.half[1]);
                record->text_kind = (*ids)[record->text_kind] - 18;
            } while (record->text_kind == definition);
            record->enabled = 1;
            record->definition = definition;
            actor_entry_add(g_resource_game_state.actor.secondary_entries,
                choice_actor_id(definition), 0, 0);
            display_time_copy_add(saved.pointer, &g_menu_choice_next_day_delta,
                choice_stamp(record));
            return 1;
        }
    }
    return 0;
}
