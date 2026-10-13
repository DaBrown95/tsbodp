#ifndef RESOURCE_OBJECT_PAYLOAD_H
#define RESOURCE_OBJECT_PAYLOAD_H

struct FrameSceneSavedEffect;

unsigned char *resource_get_object_payload(unsigned int, unsigned int);
struct FrameSceneSavedEffect *frame_create_scene_saved_resource_effect(
    unsigned char, unsigned char);

#endif
