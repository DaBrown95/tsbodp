#include "save_stream.h"
#include "frame_actor_runtime.h"
/* Values use 24 fractional bits. Tail flags select and remember need actions. */
struct FrameActorNeedState {
 int values[8], countdown;
 FrameU32 selected, started;
};
#include "frame_actor_need_input.h"
extern struct FrameActorNeedState *g_frame_actor_need_states;
extern int g_frame_actor_need_delta_player[], g_frame_actor_need_delta_npc[];
extern int g_frame_actor_need_adjustments[][8], g_frame_actor_need_multipliers[];
struct FrameActorNeedUi { FrameU32 changed; FrameU8 unknown_04[52]; };
extern struct FrameActorNeedUi g_frame_actor_need_ui[];
extern struct FrameActorNeedState g_frame_actor_need_defaults;
int frame_random_range(int, int);
int frame_fixed_multiply(int, int);
void frame_copy_bytes(void *, const void *, int);
unsigned int frame_low_need_mask(struct FrameActorNeedState *, unsigned int);
unsigned int frame_empty_need_mask(struct FrameActorNeedState *);
int frame_actor_need_delta(struct FrameActorNeedState *, unsigned int, struct FrameObject *);
void frame_adjust_actor_needs(struct FrameActorNeedState *, unsigned int, FrameU8);
void frame_reset_actor_needs(struct FrameActorNeedState *);
void frame_load_actor_needs(struct FrameActorNeedState *);
void frame_save_actor_needs(struct FrameActorNeedState *);

/* The tick preserves each RAM read across its repeated rate calls. */
struct FrameActorNeedTickState {
 volatile int values[8];
 int countdown;
 FrameU32 selected, started;
};
extern FrameU8 g_frame_actor_needs_paused;
void frame_update_actor_needs(struct FrameActorNeedTickState *, struct FrameActorObject *);

/* Cue selection byte; its original gameplay setting remains uncertain. */
struct FrameActorCueOptions { FrameU8 unknown_00[32], variant; };
extern struct FrameActorCueOptions g_frame_actor_cue_options;
void frame_handle_actor_empty_needs(struct FrameActorNeedState *, struct FrameActorObject *);
