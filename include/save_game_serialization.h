#ifndef SAVE_GAME_SERIALIZATION_H
#define SAVE_GAME_SERIALIZATION_H
#include "save_stream.h"
#include "display_time.h"
#include "display_menu_relation.h"
#include "save_stream_fields.h"

/* Observed prefix/child offsets; these views do not establish full record sizes. */
struct SaveStreamWorldRecord {
    unsigned char bytes[16], pairs[2], nibbles[6];
    unsigned char region18[8];
    struct DisplayMenuRelationValues region20;
    int region88[6];
    unsigned char regiona0[32];
};
struct SaveStreamSixNibbles {
    unsigned char first, unknown01, values[5];
};
struct SaveStreamNibbleState { unsigned char values[8], tail; };
struct SaveStreamGameStateView {
    unsigned int unknown00;
    int unknown04;
    struct DisplayTimeRecord clock;
    unsigned char unknown10[0xcc], unknowndc[0x64a];
    unsigned char byte726, unknown727[7], byte72e, unknown72f[17];
    unsigned char byte740, byte741, byte742, unknown743;
    unsigned short short744;
    unsigned char byte746, bit747, unknown748, bit749;
};
struct SaveStreamGameRowView {
    unsigned int unknown00, flags;
    unsigned char unknown08[48];
};
extern struct SaveStreamGameStateView g_save_world_view;
extern unsigned char g_save_selection_prefix[], g_save_world_event;
extern struct SaveStreamGameRowView g_save_world_rows[];
extern struct SaveStreamNibbleState g_save_nibble_bytes;
extern unsigned int g_save_flag_words[4];
void save_stream_serialize_game_state(void);
void save_stream_write_world_record(struct SaveStreamWorldRecord *);
void save_stream_write_six_nibbles(struct SaveStreamSixNibbles *);
void save_stream_write_nibble_state(void);
void save_stream_write_flag_words(void);
void save_stream_write_relation_values(struct DisplayMenuRelationValues *);
void save_stream_write_six_value_words(const int *);
struct FrameActorNeedState;
void frame_save_actor_needs(struct FrameActorNeedState *);
/* Explicit unconverted input serializers; their full contracts remain unknown. */
void save_world_write_region_1fecc(void *);
void save_world_write_module_29d18(void);
#endif
