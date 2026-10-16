#ifndef DISPLAY_PENDING_BLOCK_H
#define DISPLAY_PENDING_BLOCK_H
#include "heap.h"

/* Observed 16-byte VCount rows; the callback receives both words by address. */
struct DisplayPendingRow {
    unsigned short line, unknown02;
    unsigned int value, delta;
    void (*apply)(unsigned int *, unsigned int *);
};
/* The staged copy covers eleven rows. Reset touches twelve queued rows, but
 * publication has no local count bound; the queued tail is deliberately unsized.
 * This is a partial access view, not a complete backing-capacity declaration. */
struct DisplayPendingRows {
    unsigned short pending, count;
    struct DisplayPendingRow staging[11];
    struct DisplayPendingRow queued[0];
};
struct DisplayPendingBlock;
extern struct DisplayPendingBlock g_display_pending_block;
extern unsigned int g_display_pending_block_flag;
#define DISPLAY_PENDING_ROWS (*(struct DisplayPendingRows *)&g_display_pending_block)

extern const unsigned char g_display_default_pending_rows[];
void display_reset_queued_rows(void);
void display_queue_pending_rows(const void *, unsigned int);
void display_arm_pending_vcount(void);
void display_pending_vcount_callback(void);
void display_pending_noop(unsigned int *, unsigned int *);
void display_initialize_pending_block(void);

/* Existing IRQ APIs. The function-pointer form is compatible with IrqCallback
 * without importing the unguarded irq.h into combined startup header closures. */
void set_vcount_callback(void (*)(void));
void irq_set_vcount(unsigned int);
#endif
