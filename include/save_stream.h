#ifndef SAVE_STREAM_H
#define SAVE_STREAM_H
#include "display_text_bank.h"
#include "save_transfer.h"
/* Observed 40-byte decoded view; content roles remain provisional. */
struct SaveStreamRecord {
    unsigned int unknown00;
    unsigned char unknown04[6], unknown0a[2];
    int signed24;
    unsigned char unknown10[16], pairs[2], nibbles[6];
};
/* Four records fit the observed region; unchecked slot arguments stay unchecked. */
union SaveStreamHeader {
    struct {
        unsigned char bytes[14];
        unsigned short checksum;
    } fields;
    unsigned char bytes[16];
    unsigned short words[8];
    unsigned int dwords[4];
};
struct SaveStreamState {
    union SaveStreamHeader header;
    unsigned char *buffer;
    struct SaveStreamRecord records[4];
    unsigned char valid[4];
    unsigned int selected;
    unsigned char *cursor;
    int bit_offset;
    unsigned int used, percentage;
};
/* Overlapping access view of state +0xbc, not independent storage. */
struct SaveStreamBitCursor {
    unsigned char *cursor;
    int bit_offset;
};
extern struct SaveStreamState g_save_stream_state;
extern struct SaveStreamBitCursor g_save_bit_cursor;
extern unsigned char g_save_serialized_marker;
extern const unsigned char g_save_header_template[16];
extern unsigned short g_save_saved_display_status;
extern volatile unsigned short g_save_display_status, g_save_interrupt_ack;
void frame_load_save_value(void *, int);
void frame_write_save_value(const void *, int);
void save_stream_read_bits(unsigned char *, unsigned int);
void save_stream_write_bits(const unsigned char *, unsigned int);
void save_stream_write_nibbles(const unsigned char *, unsigned int);
void save_stream_read_pairs(unsigned char *, unsigned int);
void save_stream_write_pairs(const unsigned char *, unsigned int);
void save_stream_read_nibbles(unsigned char *, unsigned int);
unsigned short save_stream_checksum(const void *, unsigned int);
void save_stream_clear_buffer(void);
void save_stream_load_record(struct SaveStreamRecord *);
void save_stream_read_record(unsigned int);
void save_stream_load_slots(void);
void save_stream_commit_slot(unsigned int);
unsigned int save_stream_validate_slot(unsigned int);
void save_stream_read_slot(unsigned int);
void save_stream_write_slot(unsigned int);
void save_stream_read_blocks(unsigned int, unsigned int, void *);
void save_stream_write_blocks(unsigned int, unsigned int, const void *);
void save_stream_begin_transfer(void);
void save_stream_end_transfer(void);
void save_stream_suspend_audio(void);
void save_stream_resume_audio(void);
unsigned char save_stream_validate_header(void);
void save_stream_initialize_header(void);
void save_stream_initialize(void);
unsigned int save_stream_update_header_option(void);
unsigned int save_stream_commit_header(void);
/* Explicit unconverted buffer serialization interface. */
void save_stream_build_buffer(void);
#endif
