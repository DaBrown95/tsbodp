#ifndef SCENE_CONTACT_SERIAL_H
#define SCENE_CONTACT_SERIAL_H

/* Observed IRQ-shared byte prefix at the existing input root. These are
 * compiler-specific access views, not recovered protocol declarations. */
struct SceneContactSerialFields {
    volatile unsigned char status:8, mode:8, state2:8, state3:8;
    volatile unsigned char count:8, pending:8, unknown06:8, unknown07:8, flag8:8;
    unsigned int captured0c, unknown10, captured14;
    unsigned short first_parameter, second_parameter;
    volatile unsigned short receive_remaining:16, transmit_remaining:16;
    volatile unsigned short receive_index:16, transmit_index:16;
    void *first_buffer, *second_buffer;
};

union SceneContactInputPrefix {
    /* Existing initialized prefix before the notice handler at +0x2C. */
    unsigned char bytes[44];
    struct SceneContactSerialFields fields;
};

typedef unsigned int (*SceneContactNoticeHandler)(unsigned int,
    unsigned short *, unsigned short *);

struct SceneContactInputSetup {
    union SceneContactInputPrefix prefix;
    SceneContactNoticeHandler handler;
};

extern struct SceneContactInputSetup g_scene_contact_input_setup;
extern const unsigned int g_scene_contact_serial_initial_word;
extern const unsigned int g_scene_contact_serial_second_word;

#define SCENE_CONTACT_SERIAL_IME (*(volatile unsigned short *)0x04000208)
#define SCENE_CONTACT_SERIAL_REG16(a) (*(volatile unsigned short *)(a))
#define SCENE_CONTACT_SERIAL_REG32(a) (*(volatile unsigned int *)(a))

void scene_contact_reset_serial_registers(void);
unsigned int scene_contact_prepare_input_counter(void);
unsigned int scene_contact_poll_input_status(void);
void scene_contact_install_serial_irq(SceneContactNoticeHandler, unsigned int,
                                     unsigned int);
void scene_contact_handle_serial_irq(void);
void scene_contact_begin_serial_notice(void);

/* Complete serial bodies; the IRQ consumes only the result low byte. */
unsigned int scene_contact_receive_serial_word(unsigned int);
unsigned int scene_contact_transmit_serial_word(void);

unsigned int scene_contact_store_serial_word(unsigned int);
unsigned int scene_contact_emit_serial_word(void);

#include "scene_contact_serial_words.h"

void set_irq_table_entry(unsigned int, unsigned int);

#endif
