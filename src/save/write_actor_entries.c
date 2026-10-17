#include "save_game_serialization.h"
#include "resource_actor_entries.h"
#include "display_menu_choice.h"

/* The incoming storage extends through +0x347; ActorEntryContext is only its prefix. */
void save_world_write_region_1fecc(void *input)
{
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
        unsigned int next_group;
        struct ConditionActorEntries *list = &((struct ActorEntryContext *)region)->lists[group];
        frame_write_save_value(&list->count, 1);
        index = 0;
        next_group = group + 1;
        if (index < list->capacity) do {
            frame_write_save_value(&list->entries[index].kind, 1);
            packed = (list->entries[index].unknown03 << 4) | list->entries[index].value1;
            frame_write_save_value(&packed, 1);
            frame_write_save_value(&list->entries[index].value2, 1);
        } while (++index < list->capacity);
        group = next_group;
    } while (group < 15);

    for (collection_group = 0; collection_group < 50; ++collection_group) {
        struct ActorEntryCollectionRecord *record;
        /* The start snapshot survives the count write and supplies the record address. */
        register unsigned int start asm("r6");
        remaining = ((struct ActorEntryContext *)region)->collection->groups[collection_group].count;
        start = ((struct ActorEntryContext *)region)->collection->groups[collection_group].start;
        frame_write_save_value(remaining_input, 1);
        record = &((struct ActorEntryContext *)region)->collection->records[start];
        while (remaining != 0) {
            frame_write_save_value(&record->entry.kind, 1);
            packed = (record->entry.unknown03 << 4) | record->entry.value1;
            frame_write_save_value(&packed, 1);
            frame_write_save_value(&record->entry.value2, 1);
            frame_write_save_value(&record->unknown04, 2);
            frame_write_save_value(&record->unknown08, 1);
            ++record;
            --remaining;
        }
    }
    for (collection_group = 0; collection_group < 50; ++collection_group)
        save_stream_write_bits(&((struct ActorEntryContext *)region)->collection->groups[collection_group].flags, 1);
    {
        /* The real cursor and counter survive the five byte-writer calls. */
        register unsigned char *cursor asm("r4");
        register unsigned int byte_index asm("r5");
        byte_index = 0;
        cursor = region;
        cursor += 4;
        do {
            frame_write_save_value(cursor, 1);
            ++cursor;
        } while (++byte_index < 5);
    }
    frame_write_save_value(tail, 5);
    frame_write_save_value(byte, 1);
    save_stream_write_nibbles(nibble_a, 1);
    save_stream_write_nibbles(nibble_b, 1);
    frame_write_save_value(region, 3);
    save_stream_write_actor_tail(region + 0x320);
    display_menu_save_choice((struct DisplayMenuSelectionState *)(region + 0x33c));
}
asm(".align 2, 0");
