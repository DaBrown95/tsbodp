#ifndef FRAME_ACTOR_INITIALIZATION_H
#define FRAME_ACTOR_INITIALIZATION_H

void startup_initialize_actor_resources(void);
void frame_initialize_actor_need_states(void);
void frame_initialize_need_effect_pool(void);
void frame_reset_need_effect_pool(void);
void frame_reset_need_effect_selection(void);
void frame_search_initialize_buffers(void);
/* Backing allocation retained independently of the intrusive free-list head. */
struct DisplayNeedEffectStateView;
extern struct DisplayNeedEffectStateView *g_frame_need_effect_storage;

#endif
