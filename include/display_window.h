#ifndef DISPLAY_WINDOW_H
#define DISPLAY_WINDOW_H

/* Word coordinates overlay the signed integer halves used by the VBlank path. */
union DisplayWindowFixedPoint {
    int position;
    struct { unsigned short fraction; short integer; } halves;
};
struct DisplayWindowRectangle {
    unsigned char unknown_00[8];
    union DisplayWindowFixedPoint left, top;
    unsigned char unknown_10[0x14];
    union DisplayWindowFixedPoint right, bottom;
    unsigned char unknown_2c[0x10];
};
extern const unsigned short g_display_window_enable_masks[];
void display_disable_window(unsigned int);
void display_configure_window(unsigned int, unsigned short, unsigned short);
void display_set_window_rectangle(unsigned int, int, int, int, int);

#endif
