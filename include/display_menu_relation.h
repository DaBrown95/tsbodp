#ifndef DISPLAY_MENU_RELATION_H
#define DISPLAY_MENU_RELATION_H

/* Four-byte serialized records; values -128 mark an uninitialized entry. */
struct DisplayMenuRelationRecord {
    unsigned char flags;
    signed char value;
    unsigned char unknown_02[2];
};
/* The observed child at main-state +0x20. The first signed byte's name is
 * provisional; average and the byte threshold counter share this prefix. */
struct DisplayMenuRelationValues {
    signed char baseline;
    unsigned char unknown_01;
    short average;
    unsigned char high_count;
    unsigned char unknown_05[3];
    struct DisplayMenuRelationRecord records[24];
};
/* Partial state view. The updater scans 24 records; callers establish no
 * general bound for their incoming index. Wider state storage is unknown. */
struct DisplayMenuRelationState {
    unsigned char unknown_00[0x20];
    struct DisplayMenuRelationValues values;
};
/* ROM tables have observed eight- and four-byte strides, respectively. */
struct DisplayMenuRelationTraits {
    unsigned char unknown_00[2];
    unsigned char values[5];
    unsigned char unknown_07;
};
struct DisplayMenuRelationSeed {
    unsigned char unknown_00;
    signed char initial;
    unsigned char unknown_02[2];
};
extern const struct DisplayMenuRelationTraits g_display_menu_relation_traits[];
extern const struct DisplayMenuRelationSeed g_display_menu_relation_seeds[];

int display_menu_adjust_relation(struct DisplayMenuRelationState *, unsigned int,
                                 int);
void display_menu_prepare_relation(void *, unsigned int);
int display_menu_write_relation(struct DisplayMenuRelationState *, unsigned int,
                                int);
/* LDRSB returns a sign-extended word; callers narrow only at byte uses. */
int display_menu_read_relation(void *, unsigned int);
unsigned char display_menu_relation_flags(void *, unsigned int);
int display_menu_initial_relation(struct DisplayMenuRelationState *, unsigned int);
void display_menu_refresh_relation(void *);

#endif
