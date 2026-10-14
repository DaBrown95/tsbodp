#include "resource_timed_scene_selector.h"
#include "resource_scene_selector.h"

struct FrameObject *resource_create_timed_scene_selector(unsigned char group,
        unsigned char entry)
{
    struct ResourceSceneSelector *object =
        (void *)resource_create_scene_selector(group, entry);
    struct ResourceTimedSelectorHours *payload =
        (void *)resource_get_object_payload(group, entry);

    object->first_hour = payload->first_hour;
    object->second_hour = payload->second_hour;
    return (struct FrameObject *)object;
}
