#ifndef VIEW_MATH_H
#define VIEW_MATH_H

/* Shared two-word points are defined in frame.h by the including subsystem. */
struct FramePoint;
extern int g_view_phase_table[];
extern unsigned short view_bios_arctan2(short,short);
int frame_sine(int);
int frame_cosine(int);
int frame_fixed_multiply(int,int);
int frame_fixed_divide(int,int);
int frame_bios_fixed_divide(int,int);
int frame_fixed_reciprocal(int);
void view_subtract_point(const struct FramePoint *,const struct FramePoint *,struct FramePoint *);
void view_copy_point(const struct FramePoint *,struct FramePoint *);
unsigned char view_direction_angle(struct FramePoint);
unsigned int view_point_distance(struct FramePoint,struct FramePoint);
int resource_scale_value(short);
extern const unsigned char g_frame_direction_lookup[];
extern const int g_frame_velocity_default[], g_frame_velocity_restricted[], g_frame_velocity_extended[];
unsigned char frame_direction_from_velocity(struct FramePoint);
void frame_make_velocity(struct FramePoint *, unsigned int, unsigned int, int);

#endif
