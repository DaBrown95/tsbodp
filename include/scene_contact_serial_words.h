#ifndef SCENE_CONTACT_SERIAL_WORDS_H
#define SCENE_CONTACT_SERIAL_WORDS_H

/* Partial output/access views; inferred names do not recover original types. */
union SceneContactSerialPayloadWord {
    unsigned int word;
    unsigned short halves[2];
};

struct SceneContactSerialNoticeStatePrefix {
    unsigned char unknown00[16];
    unsigned int word10;
};

/* The first word overlaps the existing game-state root. */
extern unsigned int g_scene_contact_serial_game_word;
extern struct SceneContactSerialNoticeStatePrefix g_scene_contact_serial_notice_state;

unsigned int scene_contact_fold_serial_word(unsigned short);
unsigned int scene_contact_dispatch_serial_notice(unsigned int,
                                                  unsigned short *,
                                                  unsigned short *);
void scene_contact_reply_serial_game_word(unsigned short *, unsigned short *);
void scene_contact_reply_serial_state_word(unsigned short *, unsigned short *);

/* Complete direct children; receiving branches do not write their length output. */
void scene_contact_receive_serial_game_record(unsigned short *, unsigned short *);
void scene_contact_receive_serial_options(unsigned short *, unsigned short *);
void scene_contact_reply_serial_game_record(unsigned short *, unsigned short *);
void scene_contact_reply_serial_text_rows(unsigned short *, unsigned short *);

#endif
