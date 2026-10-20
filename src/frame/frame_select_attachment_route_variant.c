#include "frame_actor_variant_lifecycle.h"

unsigned int frame_select_attachment_route_variant(struct FrameNeedEffectState *base,
                                                  unsigned char *output)
{
    /* Capture the owner before the long-lived byte-output destination. */
    register struct FrameNeedEffectState *owner asm("r4") = base;
    register unsigned char *code asm("r6") = output;
    unsigned char variant = 0;
    struct FrameAttachmentRouteVariant *table;
    unsigned int initial_kind, initial_owner_kind;
    /* The entry reads precede the persistent table handoff. */
    {
        register struct FrameAttachmentRouteVariant *initial_table asm("r0") =
            g_frame_attachment_route_variants;
        initial_kind = initial_table->kind;
        initial_owner_kind = owner->kind;
        table = initial_table;
    }
    if (initial_kind != initial_owner_kind) {
        do {
            if (++variant > 5)
                goto done;
        } while (table[variant].kind != owner->kind);
    }
    /* This address dies at the selection store. */
    {
        register unsigned char *selected_address asm("r0") =
            &owner->unknown_58[6];
        *selected_address = variant;
    }
done:
    /* Keep the word-field base and the row offset as their actual values. */
    {
        unsigned int byte_offset = (unsigned int)variant * sizeof(table[0]);
        register unsigned int *code_field asm("r1") = &table[0].initial_code;
        byte_offset += (unsigned int)code_field;
        *code = *(unsigned int *)byte_offset;
    }
    return 1;
}
