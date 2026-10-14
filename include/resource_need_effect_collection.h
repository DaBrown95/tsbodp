#ifndef RESOURCE_NEED_EFFECT_COLLECTION_H
#define RESOURCE_NEED_EFFECT_COLLECTION_H

struct ActorEntryContext;
/* Twelve-byte aligned representation; not every byte is initialized by the snapshot. */
struct __attribute__((aligned(4))) ActorEntrySavedRecordBytes {
    unsigned char bytes[12];
};

void actor_entry_save_collection_record(
    struct ActorEntryContext *, unsigned int,
    const struct ActorEntrySavedRecordBytes *);
void scene_save_need_effect_collection(unsigned char *, unsigned int);

#endif
