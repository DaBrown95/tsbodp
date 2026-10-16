#ifndef STARTUP_MEMORY_H
#define STARTUP_MEMORY_H

/* Linker-span words retain the initialized RAM image installed by reset. */
extern const unsigned int g_startup_iwram_span_begin, g_startup_iwram_span_end;
extern const unsigned int g_heap_span_begin, g_heap_span_end;

struct StartupDma3 {
    unsigned int source, destination, control;
};
#define STARTUP_DMA3 ((volatile struct StartupDma3 *)0x040000d4)

void startup_initialize_memory(void);
void startup_clear_unused_ram(void);
void startup_clear_display_memory(void);
void startup_clear_vram(void);
void startup_clear_oam(void);
void startup_clear_palette_memory(void);

#endif
