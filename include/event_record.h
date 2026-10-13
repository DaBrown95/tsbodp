/* Eight-byte payload ABI and twelve-byte record inferred from callers/callee.
 * Kind selects the fields read; the byte view keeps the parameter representation. */
struct EventPayload {
 unsigned char bytes[8];
} __attribute__((aligned(4)));
union EventData {
 unsigned int word;
 unsigned int words[2];
 unsigned short halfwords[4];
 unsigned char bytes[8];
};
struct EventRecord {
 unsigned char kind, sequence;
 unsigned short reserved;
 union EventData payload;
};
extern unsigned char g_event_sequence;
extern struct EventRecord g_event_record;
extern struct EventPayload g_event_vector_a, g_event_vector_b, g_event_vector_c;
extern unsigned int g_game_flags;
extern void transition_record_event(unsigned int, struct EventPayload);
extern void *memory_fill(void *, int, unsigned int);
extern void *memory_copy(void *, const void *, unsigned int);
/* The slot is interpreted as a signed byte and returned as a full word. */
extern int event_get_link_slot(void);
