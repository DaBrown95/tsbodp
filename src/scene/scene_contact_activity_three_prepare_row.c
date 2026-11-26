#include "scene_contact_activity_three.h"

#define ROW_STATE ((struct SceneContactActivityThreeState *)g_scene_contact_state)
#define ROW_OBJECT(owner) ((struct SceneContactActivityThreeObject *)(owner))

/* The pinned Thumb compiler uses consecutive register pairs for the row cursor,
 * the random roll and phase, and the two position coordinates. */
struct RowThresholdCursor {
    const unsigned char *ptr;
    int row;
};
struct PhaseSample {
    int roll, index;
};
struct RowSelectionFrame {
    struct {
        int left, top, right, bottom;
    } bounds;
    union {
        int word;
        unsigned short low;
    } row_selected;
};
union RowScratch {
    int integer;
    unsigned char *bytes;
    const struct RowSelectionFrame *frame;
};

#define STORE_ROW_ORIGIN()                                                                  \
    do {                                                                                    \
        ROW_STATE->row_origins[ROW_OBJECT(owner)->id].x = position.x;                       \
        {                                                                                   \
            register struct SceneContactActivityThreeObject *row_owner = ROW_OBJECT(owner); \
            ROW_STATE->row_origins[row_owner->id].y = position.y;                           \
            cursor.frame = &selection_frame;                                                \
            {                                                                               \
                register unsigned short subtype asm("r7") = cursor.frame->row_selected.low; \
                row_owner->subtype = subtype;                                               \
            }                                                                               \
        }                                                                                   \
    } while (0)

void scene_contact_activity_three_prepare_row(struct FrameObject *base)
{
    int row_phase;
    register struct {
        int phase_roll;
        unsigned char *amount;
    } phase_and_amount asm("r0");
    struct RowSelectionFrame selection_frame;
    register union RowScratch cursor;
    register struct FrameObject *owner asm("r8") = base;

    register int roll asm("r3");
    register struct PhaseSample sample asm("r3");
    register int origin_index asm("r4");
    register struct FramePoint position asm("r5");
    register int amount asm("r10");
    register int palette;

    int accepted = 0;
    int palette0_available = 0;
    int palette1_available = 0;
    int palette2_available = 0;

    register union RowScratch threshold_state asm("r7");

    /* Fall back through earlier definitions until the roll passes a threshold. */
    selection_frame.row_selected.word = frame_random_range(0, ROW_STATE->option);
    sample.roll = frame_random_range(1, 100);
    {
        register const struct SceneContactActivityThreeRowDefinition *row_definitions asm("r2") =
            g_scene_contact_activity_three_row_definitions;
        register int row_index asm("r1");
        register unsigned int displacement asm("r0");
        register const unsigned char *threshold_cursor asm("r0");
        register struct RowThresholdCursor row_cursor asm("r0");
        row_index = selection_frame.row_selected.word;
        displacement =
            row_index * sizeof(*row_definitions) +
            (unsigned int)&((struct SceneContactActivityThreeRowDefinition *)0)->threshold;
        threshold_cursor = (const unsigned char *)(displacement + (unsigned int)row_definitions);
        do {
            row_cursor.ptr = threshold_cursor;
            if (sample.roll <= (int)*row_cursor.ptr)
                break;
            row_cursor.ptr -= sizeof(*row_definitions);
            threshold_cursor = row_cursor.ptr;
            row_index = selection_frame.row_selected.word;
            row_cursor.row = row_index - 1;
            row_index = row_cursor.row;
            selection_frame.row_selected.word = row_index;
            threshold_state.integer = accepted;
        } while (!threshold_state.integer);
        {
            register const struct SceneContactActivityThreeRowDefinition *amount_row asm("r1") =
                (const struct SceneContactActivityThreeRowDefinition
                     *)(selection_frame.row_selected.word * sizeof(*row_definitions) +
                        (unsigned int)row_definitions);
            amount = frame_random_range(amount_row->minimum, amount_row->maximum);
        }
    }

    {
        register int phase_roll asm("r0") = frame_random_range(1, 100);
        phase_and_amount.phase_roll = phase_roll;
    }
    roll = phase_and_amount.phase_roll;
    {
        register unsigned int observed_acceptance;
        unsigned char *amount_output;
        unsigned char *phase_output;
        unsigned char *palette_output;

        register union RowScratch scratch asm("r7");
        phase_and_amount.amount = &ROW_OBJECT(owner)->amount;
        amount_output = phase_and_amount.amount;
        scratch.bytes = &ROW_OBJECT(owner)->phase;
        phase_output = scratch.bytes;
        palette_output = &ROW_OBJECT(owner)->palette_source;
        {
            const struct SceneContactActivityThreePhaseDefinition *const phase_table[1] = {
                g_scene_contact_activity_three_phase_definitions};

            /* Keep the same roll while reducing the amount by five on each retry. */
            goto evaluate_phase;
        retry_phase:
            amount -= 5;

        evaluate_phase: {
            int working_phase = 6;
            if (amount <= phase_table[0][working_phase].threshold) {
                do {
                    --working_phase;
                    if (working_phase <= 0) {
                        break;
                    }
                } while (amount <= phase_table[0][working_phase].threshold);
            }
            {
                register int actual_phase asm("r4") = working_phase;
                sample.index = actual_phase;
                if (roll > phase_table[0][actual_phase].probability) {
                    goto retry_phase;
                }
                row_phase = sample.index;
            }
        }

            accepted = 0;
            if (ROW_STATE->values[0]) {
                palette0_available = 1;
            }
            if (ROW_STATE->values[1]) {
                palette1_available = 1;
            }
            if (ROW_STATE->values[2]) {
                palette2_available = 1;
            }
        }
        /* Draw until the selected palette has a nonzero value in the current state. */
        do {
            register struct {
                unsigned int accepted;
                union {
                    int palette;
                    unsigned int ready;
                } selector;
            } palette_test asm("r0");
            register unsigned int first_palette asm("r0");
            palette = frame_random_range(0, 2);
            first_palette = palette;
            if (first_palette == 0) {
                scratch.integer = palette0_available;
                if (scratch.integer) {
                    palette_test.accepted = 1;
                    accepted = palette_test.accepted;
                }
            }
            palette_test.selector.palette = palette;
            if (palette_test.selector.palette == 1) {
                scratch.integer = palette1_available;
                if (scratch.integer) {
                    palette_test.accepted = 1;
                    accepted = palette_test.accepted;
                }
            }
            palette_test.selector.palette = palette;
            if (palette_test.selector.palette == 2) {
                scratch.integer = palette2_available;
                if (scratch.integer) {
                    palette_test.accepted = 1;
                    accepted = palette_test.accepted;
                }
            }
            palette_test.selector.ready = accepted;
            observed_acceptance = palette_test.selector.ready;
        } while (!observed_acceptance);
        accepted = 0;
        /* Reject positions strictly inside the 64-by-64 box around any earlier origin. */
    retry_position:
        position.x = frame_random_range(16, 224);
        position.y = frame_random_range(32, 104);
        {
            register short done asm("r1");
            int observed_count;

            register struct SceneContactActivityThreeObject *count_owner asm("r1") = (void *)owner;
            observed_count = count_owner->id;

            if (observed_count) {
                register int count asm("r12");
                origin_index = 0;
                scratch.integer = observed_count;
                count = scratch.integer;
                if (origin_index < count) {
                    register const unsigned char *origin_y asm("r3") =
                        (const unsigned char *)&ROW_STATE->row_origins + sizeof(int);
                    register const unsigned char *origin_x asm("r2") =
                        (const unsigned char *)&ROW_STATE->row_origins;
                    do {
                        register int x asm("r1") = *(const int *)origin_x;
                        register int y;
                        selection_frame.bounds.left = (unsigned int)x - 32u;
                        y = *(const int *)origin_y;
                        selection_frame.bounds.top = (unsigned int)y - 32u;
                        cursor.integer = selection_frame.bounds.top;
                        selection_frame.bounds.top = cursor.integer;
                        selection_frame.bounds.right = (unsigned int)x + 32u;
                        selection_frame.bounds.bottom = (unsigned int)y + 32u;
                        if (position.x > *(const volatile int *)&selection_frame.bounds.left &&
                            position.x < selection_frame.bounds.right &&
                            position.y > selection_frame.bounds.top &&
                            position.y < *(const volatile int *)&selection_frame.bounds.bottom) {
                            goto scan_complete;
                        }
                        origin_y += sizeof(struct FramePoint);
                        origin_x += sizeof(struct FramePoint);
                        ++origin_index;
                    } while (origin_index < count);
                }
            scan_complete:
                if (origin_index != count)
                    goto evaluate_position;

                STORE_ROW_ORIGIN();

                goto write_remaining;
            }
            done = 1;
            accepted = done;
        }
    evaluate_position:
        scratch.integer = accepted;
        if (!scratch.integer)
            goto retry_position;

        STORE_ROW_ORIGIN();

    write_remaining:
        *amount_output = amount;
        *phase_output = row_phase;
        *palette_output = palette;
        ROW_OBJECT(owner)->direction = frame_random_range(0, 31);
        frame_set_position(owner, (int)(((unsigned int)position.x) << 16),
                           (int)(((unsigned int)position.y) << 16));
    }
}

/* The function extent includes the alignment after its literal pool. */
asm(".align 2, 0");
