#ifndef RESOURCE_ACTOR_ENTRIES_H
#define RESOURCE_ACTOR_ENTRIES_H
#include "resource_condition_entries.h"
#include "condition_actor.h"
#include "resource_commands.h"
#include "resource_conditions.h"
#include "heap.h"
#include "display_catalog_text.h"
/* Partial context through +31C; the complete context allocation is unknown. */
struct ActorEntryCollectionRecord {
 struct ConditionActorEntry entry;
 unsigned int unknown04, unknown08;
};
struct ActorEntryCollectionGroup {
 unsigned char start, count, flags, unknown03;
};
struct ActorEntryCollection {
 unsigned short count, unknown02;
 struct ActorEntryCollectionRecord records[160];
 struct ActorEntryCollectionGroup groups[50];
};
struct ActorEntryContext {
    unsigned char unknown00[0x14];
    struct ConditionActorEntries *secondary, *active;
    struct ConditionActorEntries lists[15];
    unsigned char unknown94[0x31c - 0x94];
    struct ActorEntryCollection *collection;
};
extern unsigned char g_actor_entry_initial_values[][2];
extern void *g_actor_entry_buffer;
extern struct ConditionActorEntries g_actor_entry_alias_list;
extern unsigned int g_actor_entry_seen_words[];
/* Alternate view of each eight-byte definition value: entry plus condition key. */
struct ActorEntrySeed {
 struct ConditionActorEntry entry;
 unsigned char row, column, index, unknown07;
};
unsigned short frame_random_bounded(unsigned short);
unsigned char frame_random_chance(unsigned char);
void actor_entry_prepare(struct ActorEntryContext *);
void actor_entry_reset(struct ActorEntryContext *);
void actor_entry_reset_values(struct ActorEntryContext *);
unsigned int actor_entry_add(struct ConditionActorEntries *, unsigned int,
                            unsigned char, unsigned char);
int actor_entry_find_capacity(struct ConditionActorEntries *, int);
int actor_entry_is_empty(struct ConditionActorEntries *);
int actor_entry_is_full(struct ConditionActorEntries *);
int actor_entry_has_space(struct ConditionActorEntries *);
int actor_entry_adjust_counter(void *, int, int);
unsigned char actor_entry_clear_counter(void *, int);
void actor_entry_mark_seen(unsigned int *, unsigned int);
unsigned char actor_entry_choose_base(void);
unsigned char actor_entry_choose_195(void);
unsigned char actor_entry_choose_209(void);
unsigned char actor_entry_choose_201(void);
void actor_entry_refresh_list(struct ActorEntryContext *, unsigned int);
/* Original no-op hook; its role remains provisional. */
void actor_entry_empty_hook(void *);
void resource_set_triple(unsigned int, unsigned int, unsigned int);
void actor_entry_clear_collection_group(struct ActorEntryContext *, unsigned int);
void actor_entry_publish_collection_group(struct ActorEntryContext *, unsigned int);
void actor_entry_remove_collection_record(struct ActorEntryContext *, unsigned int,
                                          unsigned int);
struct ActorEntryCollectionRecord *actor_entry_reserve_collection_record(
 struct ActorEntryContext *, unsigned int);
#endif
