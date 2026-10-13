#include "save_world_pending_notices.h"
#include "resource_conditions.h"
#include "display_catalog_text.h"
#include "display_text_fields.h"
#include "frame_actor_scene.h"

void save_world_show_pending_column(unsigned int row, unsigned int column)
{
    display_text_copy_field_one(display_scene_lookup_text(
        condition_lookup_kind(row, column) + 6025));
    g_actor_scene_result_id.id = 299;
    frame_activate_actor_scene_request();
}
