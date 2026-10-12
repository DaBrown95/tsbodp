#include "frame_actor_runtime.h"
#include "frame_actor_state.h"

void frame_run_actor_state(struct FrameObject *object) {
 switch(((struct FrameActorObject *)object)->state) {
case 0: break;
case 1: object->flags=(object->flags&~1u)|0x82; break;
case 7: frame_actor_state_7(object); break;
case 8: frame_actor_state_8(object); break;
case 9: frame_actor_state_9(object); break;
case 13: frame_actor_state_13(object); break;
case 16: frame_actor_state_16(object); break;
case 24: frame_actor_state_24(object); break;
case 26: frame_actor_state_26(object); break;
case 17: frame_actor_state_17(object); break;
case 19: frame_actor_state_19(object); break;
case 22: frame_actor_state_22(object); break;
case 23: frame_actor_state_23(object); break;
case 25: frame_actor_state_25(object); break;
case 37: frame_actor_state_37(); break;
case 27: frame_actor_state_27(object); break;
case 28: frame_actor_state_28(object); break;
case 34: frame_actor_state_34(object); break;
case 31:case 32:case 33: frame_actor_state_31_32_33(object); break;
case 35: frame_actor_state_35(object); break;
case 36: frame_actor_state_36(object); break;
case 38: frame_actor_state_38(); break;
case 39: frame_actor_state_39(object); break;
case 40: frame_actor_state_40(object); break;
case 42: frame_actor_state_42(object); break;
case 41: frame_actor_state_41(object); break;
case 43: frame_actor_state_43(object); break;
case 44: frame_actor_state_44(object); break;
case 45: frame_actor_state_45(object); break;
case 46: frame_actor_state_46(object); break;
case 47: frame_actor_state_47(object); break;
 }
}
asm(".align 2, 0");
