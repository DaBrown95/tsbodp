#ifndef RESOURCE_TIMED_SCENE_SELECTOR_H
#define RESOURCE_TIMED_SCENE_SELECTOR_H

struct FrameObject;

/* Byte-only tail access view, distinct from the parent's earlier payload fields. */
struct __attribute__((packed, aligned(1))) ResourceTimedSelectorHours {
    unsigned char unknown00[13], first_hour, second_hour;
};

struct FrameObject *resource_create_timed_scene_selector(unsigned char, unsigned char);

#endif
