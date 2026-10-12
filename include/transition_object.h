/* Partial frame-object view inferred from connected transition callbacks. */
struct TransitionObject {
 unsigned char unknown_00[12];
 unsigned int flags;
 unsigned char unknown_10[61];
 unsigned char state, unknown_4e, pending;
 unsigned char unknown_50[8];
 int countdown;
 unsigned short unknown_5c, delay;
 unsigned int unknown_60;
 int period;
 unsigned short limit, position_x, position_y;
 unsigned char first_kind, second_kind;
 unsigned char layer_a, layer_b, alpha_a, alpha_b;
};
extern void transition_object_set_state(struct TransitionObject *, unsigned char);
extern void background_animation_load(int);
extern void background_animation_configure_alpha(void);
extern void transition_set_alpha(unsigned short, unsigned short);
extern void transition_set_layers(unsigned char, unsigned char);

struct TransitionViewObject {
 unsigned char unknown_00[24];
 int x, y;
};
struct TransitionViewSlot {
 struct TransitionViewObject *object;
 unsigned int unknown_04, unknown_08;
};
struct TransitionViewContext {
 struct TransitionViewSlot views[4];
 unsigned char unknown_30, current_view;
};
extern struct TransitionViewContext g_transition_view_context;
extern unsigned int g_transition_view_configuration[2];
typedef void (*TransitionHandler)(unsigned short);
extern TransitionHandler g_transition_first_handlers[], g_transition_second_handlers[];
extern void transition_set_view_mode(unsigned int, unsigned char);
extern void transition_set_view_position(int, int, unsigned char);
extern void transition_configure_view(struct TransitionViewObject *, unsigned int, unsigned int, unsigned char);
extern void transition_clear_game_flags(unsigned int);
