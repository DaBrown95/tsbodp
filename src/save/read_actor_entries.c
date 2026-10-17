#include "save_game_loading.h"
#include "resource_actor_entries.h"
#include "display_menu_choice.h"

void save_stream_read_actor_entries(void *input)
{
    /* Input has complete mutable backing through +347; the typed view is a prefix. */
    unsigned char *region = input;
    unsigned int group, index, remaining, collection_group;
    unsigned int *remaining_input;
    unsigned char packed;
    unsigned char *byte, *nibble_a, *nibble_b, *tail;

    group = 0;
    remaining_input = &remaining;
    tail = region + 0x0d;
    byte = region + 9;
    nibble_a = region + 10;
    nibble_b = region + 11;
    do {
        /* This next-group value survives the small-list reader calls. */
        register unsigned int next_group asm("r8");
        struct ConditionActorEntries *list = &((struct ActorEntryContext *)region)->lists[group];
        frame_load_save_value(&list->count, 1);
        index = 0;
        next_group = group + 1;
        if (index < list->capacity) do {
            frame_load_save_value(&list->entries[index].kind, 1);
            frame_load_save_value(&packed, 1);
            list->entries[index].unknown03 = packed >> 4;
            list->entries[index].value1 = packed << 4;
            list->entries[index].value1 >>= 4;
            frame_load_save_value(&list->entries[index].value2, 1);
        } while (++index < list->capacity);
        group = next_group;
    } while (group < 15);

    heap_clear(((struct ActorEntryContext *)region)->collection, 0, sizeof(*((struct ActorEntryContext *)region)->collection));
    remaining = 0;
    for (collection_group = 0; collection_group < 50; ++collection_group) {
        struct ActorEntryCollectionRecord *record;
        /* This second count snapshot ends before the record-reader calls. */
        register unsigned int start asm("r6");
        frame_load_save_value(remaining_input, 1);
        ((struct ActorEntryContext *)region)->collection->groups[collection_group].count = remaining;
        ((struct ActorEntryContext *)region)->collection->groups[collection_group].start = ((struct ActorEntryContext *)region)->collection->count;
        start = ((struct ActorEntryContext *)region)->collection->count;
        ((struct ActorEntryContext *)region)->collection->count = start + remaining;
        record = &((struct ActorEntryContext *)region)->collection->records[start];
        while (remaining != 0) {
            frame_load_save_value(&record->entry.kind, 1);
            frame_load_save_value(&packed, 1);
            record->entry.unknown03 = packed >> 4;
            record->entry.value1 = (unsigned char)(packed << 4) >> 4;
            frame_load_save_value(&record->entry.value2, 1);
            frame_load_save_value(&record->unknown04, 2);
            frame_load_save_value(&record->unknown08, 1);
            ++record;
            --remaining;
        }
    }
    for (collection_group = 0; collection_group < 50; ++collection_group)
        save_stream_read_bits(&((struct ActorEntryContext *)region)->collection->groups[collection_group].flags, 1);
    {
        /* The late cursor and counter survive the five byte-reader calls. */
        register unsigned char *cursor asm("r4");
        register unsigned int byte_index asm("r5");
        byte_index = 0;
        cursor = region;
        cursor += 4;
        do {
            frame_load_save_value(cursor, 1);
            ++cursor;
        } while (++byte_index < 5);
    }
    frame_load_save_value(tail, 5);
    frame_load_save_value(byte, 1);
    save_stream_read_nibbles(nibble_a, 1);
    save_stream_read_nibbles(nibble_b, 1);
    frame_load_save_value(region, 3);
    save_stream_read_actor_tail(region + 0x320);
    display_menu_load_choice((struct DisplayMenuSelectionState *)(region + 0x33c));
}
