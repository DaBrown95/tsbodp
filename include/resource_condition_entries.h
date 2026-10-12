#ifndef RESOURCE_CONDITION_ENTRIES_H
#define RESOURCE_CONDITION_ENTRIES_H

/* Partial list view at game-state +F0; its gameplay role remains provisional. */
struct ConditionActorEntry {
    unsigned char kind, value1, value2, unknown03;
};
struct ConditionActorEntries {
    unsigned char count, capacity, unknown02[2];
    struct ConditionActorEntry *entries;
};

int condition_query_actor(struct ConditionActorEntries *, int);
void condition_update_actor(struct ConditionActorEntries *, int, unsigned char);

#endif
