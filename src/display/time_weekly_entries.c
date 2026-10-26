#include "resource_actor_entries.h"
#include "display_time_daily.h"

void display_time_weekly_entries(struct ActorEntryContext *input)
{
    register struct ActorEntryContext *context asm("r5") = input;
    if ((unsigned char)condition_is_complete(1, 0, 0)) {
        unsigned int bit = 0;
        int flags = context->unknown00[9];
        unsigned int one = 1;
        for (; bit <= 7; ++bit) {
            register int test asm("r0") = flags;
            test >>= bit;
            test &= one;
            if (test) {
                register unsigned int index asm("r3") = 0;
                register struct ConditionActorEntries *list asm("r2");
                register struct ConditionActorEntry *entry asm("r1");
                {
                    register struct ConditionActorEntries *initial asm("r0") =
                        *(struct ConditionActorEntries *volatile *)
                            &context->secondary;
                    list = initial;
                }
                {
                    register unsigned char capacity asm("r0") = list->capacity;
                    if (index >= capacity) goto exhausted;
                }
                entry = list->entries;
                goto inspect;
next:
                ++index;
                {
                    register unsigned char capacity asm("r0") = list->capacity;
                    if (index >= capacity) goto exhausted;
                }
                {
                    register struct ConditionActorEntry *base asm("r0") =
                        list->entries;
                    entry = (struct ConditionActorEntry *)(index * sizeof(*entry));
                    entry = (struct ConditionActorEntry *)
                        ((unsigned int)entry + (unsigned int)base);
                }
inspect:
                {
                    register unsigned char kind asm("r0") = entry->kind;
                    if (kind != 125) goto next;
                }
                {
                    register unsigned char value asm("r0") = entry->value1;
                    if (value != bit) goto next;
                }
exhausted:
                {
                    register unsigned char capacity asm("r2") = list->capacity;
                    if (index == capacity) {
                        register unsigned int mask asm("r1") = one;
                        register unsigned char value asm("r0");
                        mask <<= bit;
                        value = context->unknown00[9];
                        value &= ~mask;
                        context->unknown00[9] = value;
                        break;
                    }
                }
            }
        }
    }
}
