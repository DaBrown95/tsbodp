#ifndef STARTUP_GAME_ENTRY_H
#define STARTUP_GAME_ENTRY_H

#include "frame_map.h"
#include "frame_effect_pools.h"
#include "frame_oam.h"
#include "frame_random.h"
#include "display_text_raster.h"
#include "display_text_bank.h"
#include "display_palette_lifecycle.h"
#include "save_stream.h"
#include "resource_builders.h"
#include "audio_game_initialize.h"
#include "input.h"
#include "frame_actor_initialization.h"
#include "frame_map_scene.h"
#include "startup_buffer.h"
#include "game_counter.h"
#include "display_pending_block.h"

/* Shared storage and APIs already used by the scene/transition paths. */
extern unsigned int g_game_flags, g_transition_frame_period;
void configure_blending(unsigned short, unsigned short);
void irq_init(void), irq_enable_defaults(void);
void set_vblank_callback(IrqCallback);
void irq_default_vblank_callback(void);
void scene_initialize_request_queue(void), scene_step_request_handoff(void);
void display_install_tile_allocator(void), frame_install_runtime(void);
void input_init(void);
void set_word_0300217c(unsigned int);
void set_word_03002180_bit0(unsigned char);

void startup_initialize_memory(void), display_initialize(void);

/* The original provider uses SWI 05, unlike irq_wait_vblank's flag polling. */
void startup_bios_wait_vblank(void);

void startup_game_entry(void);
#endif
