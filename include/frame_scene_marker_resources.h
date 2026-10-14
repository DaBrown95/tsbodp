#ifndef FRAME_SCENE_MARKER_RESOURCES_H
#define FRAME_SCENE_MARKER_RESOURCES_H

struct FrameObject;
/* Word-load access prefixes. The low selector halfword is copied to object
 * id; complete serialized storage and arbitrary root alignment are unknown. */
struct FrameSceneTargetPayload {
    unsigned int selector_word;
    short x, y;
};
struct FrameSpawnPointResourcePayload {
    unsigned int selector_word;
    short x, y;
    unsigned char subtype, direction;
};

struct FrameObject *frame_create_scene_target_resource(
    unsigned char, unsigned char);
void frame_scene_target_resource_step(struct FrameObject *);
struct FrameObject *frame_create_spawn_point_resource(
    unsigned char, unsigned char);
void frame_spawn_point_resource_step(struct FrameObject *);

#endif
