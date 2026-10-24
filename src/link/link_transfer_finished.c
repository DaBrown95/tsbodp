#include "irq.h"
#include "link_serial_handshake.h"
#include "link_event_receive.h"

static inline unsigned char link_wait_expired(unsigned int current,
                                              unsigned int reference)
{
    if ((int)(current - reference) > 300)
        return 1;
    else
        return 0;
}

static inline unsigned char link_elapsed_expired(int elapsed,
                                                unsigned int threshold)
{
    if (elapsed > (int)threshold)
        return 1;
    else
        return 0;
}

unsigned char link_transfer_finished(void)
{
    register volatile unsigned int *phases asm("r6") = &g_link_flags;
    /* This address is used only before link_apply_received_events. */
    register unsigned int *start asm("r12") = &g_link_last_serial_vblank;

    for (;;) {
        if (!(*phases & 0x40)) {
            register volatile struct IrqContext *clock asm("r4") = g_irq_context;
            register unsigned int *reference_slot asm("r2") = start;
            register unsigned int reference asm("r3") = *reference_slot;
            unsigned int work;
            unsigned int observed_flags;

            do {
                int elapsed = (int)(clock->vblank_count - reference);
                work = 300;
                if (link_elapsed_expired(elapsed, work)) {
                    observed_flags = g_link_flags;
                    work = 0x8000;
                    g_link_flags = observed_flags | work;
                    return 1;
                }
                observed_flags = g_link_flags;
                work = 0x40;
            } while (!(observed_flags & work));
        }
        if (!(*phases & 0x10)) {
            /* The flag, mask and control phases end before the apply call. */
            register volatile unsigned int *early_flags asm("r3") = &g_link_flags;
            register unsigned int transfer_mask asm("r5") = 0x20;
            register volatile unsigned short *serial_control asm("r4") =
                (volatile unsigned short *)0x04000128;
            register volatile unsigned int *second_flags = early_flags;

            do {
                if (!(*early_flags & transfer_mask) &&
                    (*(volatile int *)&g_link_setup_state.identifier) == -1) {
                    *early_flags |= 8;
                    *early_flags |= transfer_mask;
                    if ((signed char)g_link_setup_state.slot == 0) {
                        REG16(0x0400012a) = 0xc0de;
                        *serial_control |= 0x80;
                        REG16(0x0400010e) = 0xc0;
                    }
                }
                {
                    register struct IrqContext **irq_slot asm("r0") = &g_irq_context;
                    volatile struct IrqContext *clock = *irq_slot;
                    unsigned int current = clock->vblank_count;
                    register unsigned int *reference_slot asm("r2") = start;
                    if (link_wait_expired(current, *reference_slot)) {
                        *early_flags |= 0x8000;
                        return 1;
                    }
                }
            } while (!(*second_flags & 0x10));
        }
        *phases &= ~0x10u;
        *phases &= ~0x20u;
        if (*phases & 0x200)
            break;
    }

    link_apply_received_events();
    g_link_flags &= ~0x40u;
    g_link_flags &= ~0x200u;
    ++g_link_word_03007354;
    if ((signed char)g_link_setup_state.slot == 0) {
        REG16(0x0400012a) = 0xbeef;
        REG16(0x04000128) |= 0x80;
        REG16(0x0400010e) = 0xc0;
    }
    g_link_last_serial_vblank = g_irq_context->vblank_count;
    return 0;
}
