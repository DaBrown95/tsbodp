/* Names are reconstructed. Layout is supported by the original accesses. */
typedef void (*IrqCallback)(void);
struct IrqContext {
    IrqCallback vblank, hblank, vcount;
    unsigned int timer0_count, unknown_10, unknown_14;
    unsigned int timer3_serial_count, vblank_count, previous_vblank_count;
    unsigned int hblank_count, vcount_count;
};
extern struct IrqContext *g_irq_context;
extern struct IrqContext g_irq_context_storage;
extern unsigned int g_irq_table[], g_irq_defaults[];
extern unsigned char g_irq_dispatcher_rom[], g_irq_dispatcher_ram[];
extern volatile unsigned short g_irq_flags;
extern void irq_noop(void);
extern void frame_update(void);
#define REG16(a) (*(volatile unsigned short *)(a))
#define REG32(a) (*(volatile unsigned int *)(a))
