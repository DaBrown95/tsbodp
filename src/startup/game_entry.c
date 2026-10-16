#include "startup_game_entry.h"

void startup_game_entry(void)
{
    REG16(0x04000204) &= 0xffe3;
    REG16(0x04000204) |= 0x4014;
    configure_blending(63, 16);
    startup_initialize_memory();
    irq_init();
    heap_initialize();
    display_text_initialize();
    display_text_initialize_buffer();
    save_stream_initialize();
    scene_initialize_request_queue();
    display_install_tile_allocator();
    frame_install_runtime();
    display_initialize();
    display_initialize_palettes();
    resource_install_decoders();
    startup_initialize_actor_resources();
    frame_initialize_oam();
    frame_initialize_effect_pools();
    startup_allocate_buffer_03005e5c();
    frame_install_map_routines();
    frame_initialize_map_cell_buffers();
    frame_initialize_random_buffer();
    input_init();
    game_initialize_counter_slots();
    resource_allocate_arena();
    g_game_flags = 0;
    set_word_0300217c(5);
    set_word_03002180_bit0(1);
    audio_game_initialize_default();
    irq_enable_defaults();
    set_vblank_callback(irq_default_vblank_callback);
    display_initialize_pending_block();
    g_transition_frame_period = 2;
    for (;;) {
        struct IrqContext *context;
        unsigned int current;
        int elapsed;
        scene_step_request_handoff();
        do {
            startup_bios_wait_vblank();
            context = g_irq_context;
            current = context->vblank_count;
            elapsed = current - context->previous_vblank_count;
            if (elapsed < 0)
                elapsed = -elapsed;
        } while ((unsigned int)elapsed < g_transition_frame_period);
        context->previous_vblank_count = current;
    }
}
