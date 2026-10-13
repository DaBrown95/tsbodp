#ifndef FRAME_ACTOR_GRID_H
#define FRAME_ACTOR_GRID_H
/* Cells are copied in reverse order; the search algorithm remains unconverted. */
struct FramePoint;
struct FrameActorPackedCell;
struct FrameGridSearchState {
 void *context;
 /* Only the low two bytes of the saved target word are interpreted here. */
 unsigned char target_x, target_y;
 unsigned short unknown_06;
 int cells[100];
 unsigned char count, status, unknown_19a[2];
};
extern struct FrameGridSearchState g_frame_grid_search;
unsigned char frame_grid_cell_to_point(void *, const int *, struct FramePoint *);
unsigned char frame_grid_search(void *, const struct FrameActorPackedCell *, const struct FrameActorPackedCell *, unsigned char, unsigned char);
unsigned int frame_grid_search_status(void);
unsigned char frame_copy_grid_path(struct FramePoint *, unsigned int);
#endif
