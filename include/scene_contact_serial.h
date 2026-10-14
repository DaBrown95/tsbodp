#ifndef SCENE_CONTACT_SERIAL_H
#define SCENE_CONTACT_SERIAL_H

/* Observed IRQ-shared byte prefix at the existing input root. These are
 * compiler-specific access views, not recovered protocol declarations. */
struct SceneContactSerialFields {
    volatile unsigned char status:8, mode:8, state2:8, state3:8;
    volatile unsigned char count:8, pending:8, unknown06:8, unknown07:8, flag8:8;
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

#define SCENE_CONTACT_SERIAL_IME (*(volatile unsigned short *)0x04000208)
#define SCENE_CONTACT_SERIAL_REG16(a) (*(volatile unsigned short *)(a))
#define SCENE_CONTACT_SERIAL_REG32(a) (*(volatile unsigned int *)(a))

void scene_contact_reset_serial_registers(void);
unsigned int scene_contact_prepare_input_counter(void);
unsigned int scene_contact_poll_input_status(void);

#endif
