#ifndef HEAP_H
#define HEAP_H
/* Physical links stay valid; allocated blocks encode their arena in next_free. */
struct HeapBlock {
    struct HeapBlock *next, *previous, *next_free, *previous_free;
};
struct HeapArena {
    struct HeapBlock *first, *free;
    unsigned int bytes;
    unsigned char *end;
};
extern struct HeapArena g_heap_arenas[];
extern unsigned int g_heap_arena_count;
extern const unsigned int g_heap_span_begin, g_heap_span_end;
extern unsigned int heap_block_bytes(struct HeapBlock *, unsigned int);
extern void heap_link_physical(struct HeapBlock *, struct HeapBlock *);
extern void heap_link_free(struct HeapBlock *, struct HeapBlock *);
extern void heap_prepend_free(struct HeapBlock *, unsigned int);
extern void heap_unlink_physical(struct HeapBlock *, unsigned int);
extern void heap_unlink_free(struct HeapBlock *, unsigned int);
extern void heap_merge_previous(struct HeapBlock *, unsigned int);
extern void heap_merge_next(struct HeapBlock *, unsigned int);
extern void *heap_allocate(unsigned int);
extern void *heap_allocate_zeroed(unsigned int);
extern void heap_free(void *);
extern void heap_initialize_arena(unsigned int, void *, void *);
extern void *heap_clear(void *, int, unsigned int);
extern void *heap_copy(void *, const void *, unsigned int);
extern void *heap_move(void *, const void *, unsigned int);
extern void *heap_resize_in_place(void *, unsigned int);
extern void heap_initialize(void);
#endif
