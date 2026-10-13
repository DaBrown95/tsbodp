#include "frame_scene_player.h"

short frame_scene_actor_world_slot(const struct FrameSceneWorldContext *data)
{
 return data->column % 7;
}
