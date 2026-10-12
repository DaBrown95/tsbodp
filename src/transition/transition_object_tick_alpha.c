#include "transition_object.h"
#include "background_animation.h"

void transition_object_tick_alpha(struct TransitionObject *object) {
 switch (object->state) {
 case 0:
  if (--object->countdown == -1) {
   if (object->alpha_a == object->limit) {
    transition_object_set_state(object, 1);
   } else {
    object->alpha_a++;
    object->alpha_b--;
    if (!(g_game_flags & 0x100000))
     transition_set_alpha(object->alpha_a, object->alpha_b);
    object->countdown = object->period;
   }
  }
  break;
 case 1:
  transition_set_layers(object->layer_a, object->layer_b);
  object->flags |= 2;
  break;
 case 3:
  if (--object->countdown == -1) {
   if (object->alpha_a == object->limit) {
    transition_object_set_state(object, 1);
    if (!(g_game_flags & 0x100010)) {
     background_animation_load(g_background_animation.transfer_enabled);
     background_animation_configure_alpha();
    }
   } else {
    object->alpha_a--;
    object->alpha_b++;
    if (!(g_game_flags & 0x100000))
     transition_set_alpha(object->alpha_a, object->alpha_b);
    object->countdown = object->period;
   }
  }
  break;
 }
 object->pending = 0;
}
