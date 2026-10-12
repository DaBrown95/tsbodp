/* 8.8 fixed-point wave state inferred from the bounded alpha update. */
struct TransitionAlphaWave {
 short value, step, minimum, maximum;
};
extern struct TransitionAlphaWave g_transition_alpha_a, g_transition_alpha_b;
