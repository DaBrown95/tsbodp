#ifndef CONDITION_ACTOR_H
#define CONDITION_ACTOR_H

/* Partial selection and counter views inferred from condition handoff code. */
struct ConditionActorValue {
    unsigned char value, unknown01[3], row, column, entry, unknown07;
};
struct ConditionActorDefinition {
    unsigned char unknown00, count, unknown02[2];
    struct ConditionActorValue *values;
};
struct ConditionActorGroup {
    unsigned char unknown00[4];
    unsigned char *values;
};
struct ConditionActorSelectionContext {
    unsigned char unknown00[0x1c];
    struct ConditionActorGroup groups[13];
};
extern struct ConditionActorDefinition g_condition_actor_definitions[];
void condition_record_actor_selection(struct ConditionActorSelectionContext *,
                                     unsigned char, unsigned char, unsigned char);
struct ConditionCounter {
    unsigned char unknown00[3];
    signed char value;
};
struct ConditionActorCounters {
    unsigned char unknown00[0x88];
    struct ConditionCounter counters[6];
};
void condition_finish_actor_context(void *);
#endif
