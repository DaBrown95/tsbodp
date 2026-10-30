#include "frame.h"

/* One physical word with successive, separately defined roles. */
union FinalizerScratchWord {
    struct FrameObject *object;
    FrameU32 flags;
    int coordinate;
    int contained;
    FrameU32 mask;
    FrameU32 index;
};
typedef char finalizer_scratch_word_layout[
    (sizeof(union FinalizerScratchWord) == 4 &&
     __alignof__(union FinalizerScratchWord) == 4) ? 1 : -1];
typedef char finalizer_coordinate_pair_layout[
    (sizeof(struct FramePoint) == 8 &&
     __alignof__(struct FramePoint) == 4) ? 1 : -1];
/* Separately consumed full-word entry inputs; no whole-record read. */
struct FinalizerEntryInputs {
    FrameU32 gate;
    FrameU32 raw_flags;
};
typedef char finalizer_entry_input_layout[
    (sizeof(struct FinalizerEntryInputs) == 8 &&
     __alignof__(struct FinalizerEntryInputs) == 4) ? 1 : -1];
/* Two actual inputs consumed by the ordered commit stores. */
struct FinalizerCommitInputs {
    struct FrameObject **table;
    struct FrameObject *object;
};
typedef char finalizer_commit_inputs_layout[
    (sizeof(struct FinalizerCommitInputs) == 8 &&
     __alignof__(struct FinalizerCommitInputs) == 4) ? 1 : -1];
/* Native addresses and byte offsets occupy one target word. */
typedef char finalizer_address_word_layout[
    (sizeof(FrameU32) == 4 && sizeof(struct FrameObject **) == 4) ? 1 : -1];
void frame_finalize_object(struct FrameObject *base)
{
    register struct FrameObject *object asm("sl") = base;
    register union FinalizerScratchWord scratch;
    register struct FinalizerEntryInputs entry_inputs asm("r1");
    register unsigned int working_value asm("r2");
    {
        register struct FrameObject **objects asm("r9") = g_frame_objects;
        register FrameU32 *initial_count_source asm("r0") = &g_frame_count;
        register struct FrameObject **append_slot asm("r1");
        working_value = *initial_count_source;
        append_slot = objects + working_value;
        *append_slot = (scratch.object = object);
    }
    scratch.flags = scratch.object->flags;
    {
        register FrameU32 gate_input asm("r1") = 0x800;
        gate_input &= scratch.flags;
        entry_inputs.gate = gate_input;
    }
    if (entry_inputs.gate) {
        register FrameU32 count_value asm("r0") = working_value + 1;
        register FrameU32 *count_output asm("r1") = &g_frame_count;
        *count_output = count_value;
        return;
    } else {
        volatile struct {
            struct FramePoint lower, upper;
            int category;
            FrameU32 flags;
            unsigned int previous;
        } work;
        register unsigned int i asm("r8");
        work.upper.x = object->spatial.bounds.upper.x;
        work.upper.y = object->spatial.bounds.upper.y;
        work.lower.x = object->spatial.bounds.lower.x;
        work.lower.y = object->spatial.bounds.lower.y;
        i = working_value;
        if (working_value) {
            work.flags = scratch.flags;
            working_value = scratch.flags;
            entry_inputs.raw_flags = working_value;
            working_value = entry_inputs.raw_flags;
            working_value >>= 18;
            work.category = working_value;
            scratch.mask = 1;
            working_value &= scratch.mask;
            work.category = working_value;
scan_previous:
            {
                register struct FrameObject *other asm("ip");
                register unsigned int previous asm("r0");
                int other_category;
                unsigned char result;
                previous = i - 1;
                other = g_frame_objects[previous];
                other_category = other->flags >> 18;
                scratch.mask = 1;
                other_category &= scratch.mask;
                work.previous = previous;
                if (work.category == 1) {
                    register struct FramePoint other_upper asm("r5");
                    register struct FramePoint other_lower asm("r3");
                    register int separated asm("r9");
                    FrameU32 other_flags;
                    if (other_category != 1)
                        goto ordering_done;
                    other_upper.x = other->spatial.bounds.upper.x;
                    other_upper.y = other->spatial.bounds.upper.y;
                    other_lower.x = other->spatial.bounds.lower.x;
                    other_lower.y = other->spatial.bounds.lower.y;
                    {
                        register int separation_value asm("r0") = 0;
                        if (work.upper.y >= other_lower.y ||
                            ({
                                register int upper_x_input asm("r2") = work.upper.x;
                                upper_x_input;
                            }) <= other_lower.x)
                            separation_value = 1;
                        separated = separation_value;
                    }
                    {
                        register int boolean_result asm("r0") = 0;
                        if ((scratch.coordinate = work.upper.y,
                             scratch.coordinate >= other_upper.y) &&
                            work.upper.x <= other_upper.x &&
                            ({
                                register int lower_y_input asm("r2") = work.lower.y;
                                lower_y_input;
                            }) <= other_lower.y &&
                            (scratch.coordinate = work.lower.x,
                             scratch.coordinate >= other_lower.x))
                            boolean_result = 1;
                        scratch.contained = boolean_result;
                    }
                    other_flags = other->flags;
                    {
                        register FrameU32 priority_mask asm("r2") = 0x80000;
                        if ((other_flags & priority_mask) &&
                            !(work.flags & priority_mask)) {
                            result = 1;
                        } else {
                            priority_mask = 0x100000;
                            if ((work.flags & priority_mask) &&
                                !(other_flags & priority_mask))
                                result = 1;
                            else if (({
                                register int separated_input asm("r1") = separated;
                                entry_inputs.gate = separated_input;
                                entry_inputs.gate;
                            }) == 1 || scratch.contained == 1)
                                result = 1;
                            else
                                goto ordering_done;
                        }
                    }
                } else {
                    if (other_category != 1 || ({
                        register int category_input asm("r2") = work.category;
                        category_input;
                    }) != 0)
                        goto ordering_done;
                    result = other_category;
                }
                if (result == 1) {
                    scratch.index = work.previous;
                    {
                        register FrameU32 first_offset asm("r0") =
                            scratch.index * sizeof(g_frame_objects[0]);
                        register struct FrameObject **table_input asm("r1") = g_frame_objects;
                        register struct FrameObject **first_slot asm("r0") =
                            (struct FrameObject **)(first_offset + (FrameU32)table_input);
                        register struct FinalizerCommitInputs inputs asm("r1");
                        inputs.table = table_input;
                        {
                            register struct FrameObject *object_input asm("r2") = object;
                            inputs.object = object_input;
                        }
                        *first_slot = inputs.object;
                        scratch.index = i;
                        inputs.table[scratch.index] = other;
                    }
                    i = work.previous;
                }
            }
            scratch.index = i;
            if (scratch.index)
                goto scan_previous;
ordering_done:
            ;
        }
    }
    {
        register FrameU32 *count_output asm("r1") = &g_frame_count;
        register FrameU32 count_value asm("r0") = *count_output + 1;
        *count_output = count_value;
    }
}
