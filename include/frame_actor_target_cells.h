#ifndef FRAME_ACTOR_TARGET_CELLS_H
#define FRAME_ACTOR_TARGET_CELLS_H

/* Owner-specific views inferred from the target-cell selector and its counter. */
struct FrameActorTargetCellOwner {
 unsigned char unknown00[0x74];
 /* Twelve candidate words followed by ten restricted-axis words. */
 unsigned int cells[22];
};
struct FrameActorOwnerKind {
 unsigned char unknown00[8];
 unsigned int kind;
};
extern unsigned char *g_frame_actor_owner_descriptors[];

/* Low two bits and upper six bits are observed cell properties. */
struct FrameGridCellProperties {
 unsigned char terrain:2, occupied:6;
} __attribute__((packed));
unsigned int frame_grid_terrain(void *, const int *);
unsigned int frame_grid_occupancy(void *, const int *);

unsigned int frame_actor_owner_cell_count(void *, unsigned int);
unsigned char *frame_grid_cell_data_pointer(void *, const int *);
unsigned char frame_grid_neighbor(void *, const int *, int *, unsigned char);
extern unsigned char g_frame_grid_neighbor_offsets[];

#endif
