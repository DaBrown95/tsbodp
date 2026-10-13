#ifndef FRAME_SEARCH_H
#define FRAME_SEARCH_H
#include "frame_actor_grid.h"
#include "frame_actor_target_cells.h"
#include "frame_pool.h"
/* Provisional search view: cell and parent retain their complete packed words. */
struct FrameSearchRecord {
 unsigned int cell, parent;
 unsigned char cost, unknown_09;
 unsigned short heuristic;
 unsigned char priority, queue, unknown_0e[2];
};
struct FrameSearchNode {
 struct FrameSearchNode *next, *previous;
 struct FrameSearchRecord record;
};
struct FrameSearchQueue { struct FrameSearchNode *first, *last; };
extern struct FrameSearchQueue g_frame_search_queues[2];
extern struct FrameSearchNode *g_frame_search_free_nodes[2];
extern struct FrameSearchNode *g_frame_search_node_buffers[2];
unsigned int frame_search_release_node(struct FrameSearchNode *);
struct FrameSearchNode *frame_search_append(const struct FrameSearchRecord *, unsigned int);
void frame_search_score(struct FrameSearchRecord *, unsigned int);
unsigned int frame_search_take_minimum(struct FrameSearchRecord *, unsigned int);
struct FrameSearchNode *frame_search_find(const unsigned int *, unsigned int);
struct FrameSearchNode *frame_search_find_any(const unsigned int *);
void frame_search_remove_cell(const unsigned int *, unsigned int);
unsigned int frame_search_cell_cost(const int *);
unsigned char frame_search_build_path(struct FrameSearchNode *);
#endif
