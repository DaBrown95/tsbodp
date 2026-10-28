#ifndef SCENE_CATALOG_CONFIRM_H
#define SCENE_CATALOG_CONFIRM_H
#include "frame.h"
#include "scene_catalog_transfer.h"
#include "scene_request_queue.h"
#include "resource_actor_entries.h"
#include "frame_actor_action_query.h"
#include "frame_actor_need_input.h"
#include "transition_object.h"
#include "frame_random.h"
/* Same native 0x03003950 storage, interpreted through accepted access views. */
union CatalogWorldViews {
 struct SceneCatalogTransferWorld entries;
 struct FrameActorValueWorld value;
};
extern union CatalogWorldViews g_catalog_world;

/* Individually assigned words carry the observed scratch-value epochs. */
struct CatalogWordOwner {
 unsigned int low;
 unsigned int high;
};
typedef char catalog_word_owner_size[(sizeof(struct CatalogWordOwner)==8)?1:-1];
typedef char catalog_word_owner_alignment[(__alignof__(struct CatalogWordOwner)==4)?1:-1];
typedef char catalog_word_owner_low_offset[((unsigned int)&((struct CatalogWordOwner *)0)->low==0)?1:-1];
typedef char catalog_word_owner_high_offset[((unsigned int)&((struct CatalogWordOwner *)0)->high==4)?1:-1];

#endif
