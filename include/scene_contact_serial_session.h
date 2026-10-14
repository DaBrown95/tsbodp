#ifndef SCENE_CONTACT_SERIAL_SESSION_H
#define SCENE_CONTACT_SERIAL_SESSION_H

#include "scene_contact_serial.h"

/* Observed partial access views at existing, overlapping state roots. */
struct SceneContactSerialSession {
    unsigned short initial00, unknown02, status04, status06;
    unsigned char matched08, unknown09[3];
    void *buffer0c;
    unsigned int word10;
};

union SceneContactSerialCapture {
    unsigned char bytes[220];
    unsigned int words[55];
};

union SceneContactSerialRecord {
    unsigned int words[27];
    unsigned char bytes[108];
};

extern struct SceneContactSerialSession g_scene_contact_serial_session;
extern union SceneContactSerialCapture g_scene_contact_serial_capture;
extern unsigned char g_scene_contact_serial_options[8];
extern const unsigned char g_scene_contact_serial_request_modes[];
extern const unsigned char *const g_scene_contact_serial_text_rows[][8];

struct BackgroundResource;
extern const struct BackgroundResource g_scene_contact_serial_initializer_palette;
extern const struct BackgroundResource g_scene_contact_serial_initializer_background;
extern const struct BackgroundResource g_scene_contact_serial_initializer_first_panel;
extern const struct BackgroundResource g_scene_contact_serial_initializer_second_panel;
extern const unsigned int g_scene_contact_serial_initializer_control3;
extern const unsigned int g_scene_contact_serial_initializer_control2;
extern const unsigned int g_scene_contact_serial_initializer_control0;

void scene_contact_initialize_serial_session(void);

/* Original direct providers; no reconstructed C credit in this group. */
void scene_contact_original_disable_background(unsigned int);
void scene_contact_original_prepare_serial_slot(unsigned int);

#endif
