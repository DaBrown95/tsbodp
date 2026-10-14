#ifndef SCENE_CONTACT_SERIAL_SESSION_CONTROLLER_H
#define SCENE_CONTACT_SERIAL_SESSION_CONTROLLER_H
#include "scene_contact_serial_session.h"
#include "scene_link_menu.h"
#include "frame_actor_runtime.h"
#include "save_world_initialization.h"
#include "save_stream.h"
#include "heap.h"
#include "save_world_defaults.h"
struct SceneContactSerialMessage { unsigned short text, delay; };
struct SceneContactSerialSlotDefinition {
 unsigned char x, y, unknown02[2];
 struct FrameVariantResource resource;
};
struct SceneContactSerialPlayerInputPrefix {
 unsigned char unknown00[7], flags07;
 unsigned short value08, value0a;
 unsigned char unknown0c[37], input_index31;
};
extern struct SceneContactSerialMessage g_scene_contact_serial_messages[];
extern struct SceneContactSerialSlotDefinition g_scene_contact_serial_slot_definitions[];
extern struct SceneContactSerialPlayerInputPrefix g_scene_contact_serial_player_input;
extern unsigned char g_scene_contact_serial_animation_commands[];
extern unsigned short g_scene_contact_input_pressed[];
void scene_contact_prepare_serial_slot(unsigned int);
void scene_contact_draw_serial_session_status(unsigned int);
void scene_contact_step_serial_session(void);
void scene_contact_shutdown_serial_session(void);
void scene_contact_stop_serial_input(void);
void restore_irq_table_entry(unsigned int);
void scene_contact_commit_serial_session(void);
void scene_contact_original_serial_slot_noop(struct FrameObject *);
#endif
