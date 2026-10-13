#ifndef SCENE_REQUEST_H
#define SCENE_REQUEST_H

/* Overlapping scene/menu access view; the two tail words are transition state. */
struct SceneRequest {
    unsigned int unknown_00, mode, scene, parameter, unknown_10, unknown_14;
};
extern struct SceneRequest g_scene_request;

#endif
