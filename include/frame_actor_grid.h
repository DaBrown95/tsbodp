#ifndef FRAME_ACTOR_GRID_H
#define FRAME_ACTOR_GRID_H
/* Paths are copied in reverse order; packed cell upper bits stay unspecified. */
struct FramePoint;
struct FrameActorPackedCell;
union FrameGridSavedTarget {
 unsigned int word;
 struct { unsigned char x, y; unsigned short unknown; } axes;
};
struct FrameGridSearchState {
 void *context;
 union FrameGridSavedTarget target;
 int cells[100];
 unsigned char count, status, unknown_19a[2];
};
extern struct FrameGridSearchState g_frame_grid_search;
unsigned char frame_grid_cell_to_point(void *, const int *, struct FramePoint *);
unsigned char frame_grid_search(void *, const struct FrameActorPackedCell *, const struct FrameActorPackedCell *, unsigned int, unsigned char);
unsigned int frame_grid_search_status(void);
unsigned char frame_copy_grid_path(struct FramePoint *, unsigned int);
#endif
