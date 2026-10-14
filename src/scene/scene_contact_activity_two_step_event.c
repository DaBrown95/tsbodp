#include "scene_contact_activity_two_access.h"
#define STATE ((struct SceneContactActivityTwoState *)g_scene_contact_state)
void scene_contact_activity_two_step_event(struct FrameObject *base)
{
    struct FrameActorObject *object = (struct FrameActorObject *)base;
    struct FramePoint velocity, point, lower, upper;
    int row;
    object->speed = (int)((unsigned int)object->speed - 0x2000u);
    if (object->speed < 0) object->speed = 0;
    velocity.x = frame_fixed_multiply(g_view_direction_vectors[object->direction].x, object->speed);
    velocity.y = frame_fixed_multiply(g_view_direction_vectors[object->direction].y, object->speed);
    object->next_position.x = (int)((unsigned int)object->position.x + (unsigned int)velocity.x);
    object->next_position.y = (int)((unsigned int)object->position.y + (unsigned int)velocity.y);
    if (object->next_position.y <= 0x3fffff)
        object->next_position.y = (int)(((64u - (unsigned int)(object->next_position.y >> 16)) << 16) + 0x400000u);
    else if (object->next_position.y > 0x700000)
        object->next_position.y = (int)(0x700000u - (((unsigned int)(object->next_position.y >> 16) - 112u) << 16));
    else goto check_horizontal;
    object->direction = g_scene_contact_activity_two_reflections[object->direction];
    object->speed = (int)((unsigned int)object->speed - 0x1000u);
    ++STATE->event_hits;
    audio_play_animation_cue(209);
    goto update_position;
check_horizontal:
    if (object->next_position.x > 0xe80000) {
        object->speed = 0;
        object->next_position.x = 0xe80000;
        object->on_step = scene_contact_activity_two_step_completed_event;
        frame_set_animation_record((struct FrameObject *)object,
            &g_scene_contact_activity_two_event_resources[object->subtype].animation_finish);
        --STATE->score;
        audio_play_animation_cue(201);
        audio_game_stop_sample(STATE->sound_handle);
        scene_contact_activity_two_draw_score();
    } else if (object->speed == 0) {
        unsigned int x_root;
        const void *table;
        audio_game_stop_sample(STATE->sound_handle);
        point.x = (short)(object->next_position.x >> 16);
        point.y = (short)(object->next_position.y >> 16);
        row = 0;
        x_root = (unsigned int)g_scene_contact_activity_two_rows;
        table = (const void *)(x_root + sizeof(int));
        for (; row < 7; ++row) {
            lower.x = (int)((unsigned int)scene_contact_activity_two_row_coordinate((const void *)x_root, row * sizeof(struct SceneContactActivityTwoRow) + STATE->entries[row].position * sizeof(struct FramePoint)) << 3);
            lower.y = (int)((unsigned int)scene_contact_activity_two_row_coordinate(table, row * sizeof(struct SceneContactActivityTwoRow) + STATE->entries[row].position * sizeof(struct FramePoint)) << 3);
            upper.x = (int)((unsigned int)lower.x + 16u);
            upper.y = (int)((unsigned int)lower.y + 16u);
            lower.x = (int)((unsigned int)lower.x - 8u);
            lower.y = (int)((unsigned int)lower.y - 8u);
            upper.x = (int)((unsigned int)upper.x + 8u);
            upper.y = (int)((unsigned int)upper.y + 8u);
            if (point.x > lower.x && point.x < upper.x && point.y > lower.y && point.y < upper.y)
                break;
        }
        if (row < 7) {
            const unsigned char *table = (const unsigned char *)g_scene_contact_activity_two_rates;
            if (scene_contact_activity_two_rate(table, STATE->entries[row].variant, object->subtype)) {
                struct FrameObject *row_object;
                const struct SceneContactActivityTwoScore *score;
                int reward;
                STATE->selected_row = row;
                object->on_step = scene_contact_activity_two_step_row_result;
                row_object = STATE->entries[row].object;
                frame_set_animation_record(row_object,
                    &g_scene_contact_activity_two_rows[row].animation_hit);
                ((struct SceneContactActivityTwoRowObject *)row_object)->phase = 12;
                row_object->flags |= 16;
                {
                    unsigned int score_root = (unsigned int)g_scene_contact_activity_two_scores;
                    score = (const struct SceneContactActivityTwoScore *)(STATE->option * sizeof(struct SceneContactActivityTwoScore) + score_root);
                }
                reward = score->base_reward;
                reward = scene_contact_activity_two_reward_share(reward, scene_contact_activity_two_rate(table, STATE->entries[row].variant, object->subtype));
                if (reward == score->base_reward)
                    audio_play_animation_cue(205);
                else audio_play_animation_cue(204);
                reward += STATE->event_hits;
                reward *= g_scene_contact_activity_two_rows[row].weight;
                scene_contact_add_activity_score(reward);
            } else {
                struct FrameObject *row_object = STATE->entries[row].object;
                frame_set_animation_record(row_object,
                    &g_scene_contact_activity_two_rows[row].animation_result);
                ((struct SceneContactActivityTwoRowObject *)row_object)->phase = 12;
                row_object->flags |= 16;
                audio_play_animation_cue(206);
                object->direction = 8;
                object->speed = 0x80000;
                audio_play_animation_cue(200);
            }
        } else {
            object->on_step = scene_contact_activity_two_step_completed_event;
            frame_set_animation_record((struct FrameObject *)object,
                &g_scene_contact_activity_two_event_resources[object->subtype].animation_miss);
            audio_play_animation_cue(202);
        }
    }
update_position:
    object->position.x = object->next_position.x;
    object->position.y = object->next_position.y;
}
asm(".align 2, 0");
