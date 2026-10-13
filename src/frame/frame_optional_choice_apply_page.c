#include "frame_optional_choice_apply.h"

void frame_optional_choice_apply_page(unsigned char index,
                                      struct FrameActorAttachmentRecord *job)
{
    unsigned int value;
    unsigned char first, last;
    struct DisplayMenuRelationState *relation;
    signed char *entry;

    job->timer = 19;
    frame_request_animation((struct FrameCommandObject *)job->actor, 31);
    entry = (signed char *)&g_optional_choice_values[index];
    frame_optional_choice_classify(*entry, &value, &first, &last);
    relation = &g_display_menu_relation_state;
    display_menu_adjust_relation(relation, *entry, 1);
    if (value != 50) {
        int hours;
        unsigned short amount;
        unsigned int saved_last = last;
        struct FrameOptionalChoiceWorldState *world =
            (struct FrameOptionalChoiceWorldState *)((unsigned int)relation - 16);

        if (saved_last == world->clock.day) {
            hours = first;
            hours--;
            hours -= world->clock.hour;
        } else {
            int current;
            hours = first;
            current = world->clock.hour;
            current -= 23;
            hours -= current;
        }
        amount = hours * 60 - (world->clock.minute - 60);
        if (amount <= 90)
            display_text_copy_field_zero(display_scene_lookup_text(1149));
        else if ((unsigned short)(amount - 91) <= 88)
            display_text_copy_field_zero(display_scene_lookup_text(1150));
        else
            display_text_copy_field_zero(display_scene_lookup_text(1151));
    }
    g_need_effect_choice_text[0] = value + 1092;
    g_actor_scene_request.object = frame_create_scene_object(
        193, *(signed char *)&g_optional_choice_values[index] + 239, 15, 0);
    frame_activate_actor_scene_request();
}
