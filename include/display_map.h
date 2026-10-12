#ifndef DISPLAY_MAP_H
#define DISPLAY_MAP_H

/* A narrow view of the 108-byte background record. Names remain inferred. */
struct DisplayStoredMap {
    unsigned short width, height;
    unsigned short tiles[1];
};
struct DisplayMapState {
    unsigned int control;
    const struct DisplayStoredMap *stored_map;
    unsigned short *map;
    unsigned short *buffer;
    unsigned short *destination;
    void *characters;
    unsigned int flags;
    unsigned char unknown_1c[0x50];
};
extern struct DisplayMapState g_display_map_states[4];
extern void display_copy_map_rectangle(int, int, int, int, int,
    const unsigned short *, int, int, int, unsigned short *);

extern void display_write_incrementing_background_map(unsigned int, int, int,
    int, int, unsigned short);

#endif
