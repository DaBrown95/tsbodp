#ifndef DISPLAY_TEXT_SLOTS_H
#define DISPLAY_TEXT_SLOTS_H

struct FrameObject;
/* Six slots are visited by the observed clear loop; callers remain unchecked. */
extern struct FrameObject *g_display_text_slots[];
struct FrameObject *display_create_text_slot(const char **, unsigned int);
void display_clear_text_slots(void);
struct FrameObject *display_allocate_text_object(const char **);

#endif
