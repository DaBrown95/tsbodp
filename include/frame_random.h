#ifndef FRAME_RANDOM_H
#define FRAME_RANDOM_H

/* Observed IWRAM storage, rather than a complete generator/context format.
 * The first word stores the address of the 625-word allocation. */
extern unsigned int g_frame_random_buffer_address;
extern unsigned int *g_frame_random_next;
extern int g_frame_random_remaining;
extern unsigned int *g_frame_random_secondary_next;
extern int g_frame_random_secondary_remaining;
extern unsigned int g_frame_random_seed_refresh_count;
extern unsigned int g_frame_random_seed;
extern unsigned char g_frame_random_last_byte;

void frame_initialize_random_buffer(void);
void frame_refresh_random_seed(void);
void frame_set_random_seed(unsigned int);
void frame_seed_random_words(unsigned int);
unsigned int frame_random_refill(void);
unsigned int frame_next_random_word(void);
int frame_random_range(int, int);
unsigned int frame_next_random_secondary_word(void);
int frame_random_secondary_range(int, int);

#endif
