#ifndef TSBODP_TRANSITION_VIEW_CONFIGURATION_H
#define TSBODP_TRANSITION_VIEW_CONFIGURATION_H

#include "frame.h"

/* Reconstructed views of the same two-word transition dimensions. */
union TransitionViewConfiguration {
    unsigned int words[2];
    struct FramePoint point;
};
extern union TransitionViewConfiguration g_transition_view_configuration;

#endif
