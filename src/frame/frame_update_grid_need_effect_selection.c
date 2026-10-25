#include "frame_grid_math.h"
#include "frame_need_effect_placement.h"
#include "resource_scene_selector.h"
#include "save_world_scene_selection.h"
#include "frame_grid_selection.h"

/* Provisional selector access view; the wider owner remains shared. */
struct GridNeedSelectionState {
 struct FrameNeedEffectState *next;
 unsigned int unknown04,kind,request;
 unsigned char unknown10[68];
 struct FrameObject *object;
 unsigned char unknown58[116];
 int right,top,left,bottom;
 unsigned char blocked;
};

union GridNeedSelectionCell {
 unsigned int word;
 struct { unsigned int x:8,y:8,unknown:16; } axes;
};

extern const struct FramePoint g_grid_selection_x_offsets[];
extern const struct FramePoint g_grid_selection_y_offsets[];
extern const unsigned char g_grid_selection_kind_height[];

void frame_update_grid_need_effect_selection(struct FrameObject *object)
{
  struct GridNeedSelectionState *state = 0;
  struct GridNeedSelectionState *next;
  unsigned int allowed;
  unsigned int y_offsets_address;
  unsigned int world_allowed = frame_world_in_idle_exclusion_set(g_frame_world_id);
  const struct FramePoint *x_offsets;
  if (((struct FrameActorObject *) object)->state != 16)
  {
    g_grid_selected_need_effect_object = 0;
    resource_scene_selector_release_player(g_frame_scene_active_actor);
    return;
  }
  {
    struct FramePoint position;
    struct FrameActorPackedCell cell;
    position.x = (short) (object->position.x >> 16);
    position.y = (short) (object->position.y >> 16);
    if (!frame_grid_point_to_cell(g_frame_registration, &position, &cell))
    {
      return;
    }
    allowed = 0;
    if (frame_grid_occupancy(g_frame_registration, (const int *) (&cell)) & 2)
    {
      state = (void *) g_frame_need_effect_active_list.first;
      y_offsets_address = (unsigned int) g_grid_selection_y_offsets;
      while (state)
      {
        unsigned int kind;
        x_offsets = g_grid_selection_x_offsets;
        next = (void *) state->next;
        if (frame_need_effect_contains_candidate((struct FrameNeedEffectState *) state, &cell) != 1)
        {
          goto next;
        }
        if (state->blocked)
        {
          goto next;
        }
        if (state->object->flags & 2)
        {
          goto next;
        }
        kind = state->kind;
        if ((!world_allowed) && ((((((unsigned int) (kind - 76)) <= 2) || (kind == 68)) || (kind == 70)) || (kind == 72)))
        {
          goto next;
        }
        if (state->request && ((g_frame_world_id == 28) || (g_frame_world_id == 26)))
        {
          goto next;
        }
        if ((kind == 117) && (!save_world_scene_in_selected_row(g_frame_world_id, 1)))
        {
          goto next;
        }
        if (((unsigned int) (kind - 146)) <= 1)
        {
          allowed = 1;
          break;
        }
        {
          union GridNeedSelectionCell neighbor;
          struct FramePoint point;
          struct FramePoint lb;
          struct FramePoint rt;
          unsigned int address = ((struct FrameActorObject *) object)->direction * 8;
          address += (unsigned int) x_offsets;
          neighbor.axes.x = (unsigned char) ((*((unsigned char *) (&cell))) + (*((int *) address)));
          address = ((struct FrameActorObject *) object)->direction * 8;
          address += y_offsets_address;
          neighbor.axes.y = (unsigned char) ((*(((unsigned char *) (&cell)) + 1)) + (*((int *) address)));
          // BUG: A broken registration invariant can leave point unset after the
          // provider's unchecked inner projection, even though it returns 1.
          if (!frame_grid_cell_to_point(g_frame_registration, (const int *) (&neighbor), &point))
          {
            allowed = 0;
            break;
          }
          resource_project_point(g_frame_registration, &point, &point);
          lb.x = state->left - ((struct FrameMapRegistration *) g_frame_registration)->cell_size;
          lb.y = state->bottom;
          rt.x = state->right + ((struct FrameMapRegistration *) g_frame_registration)->cell_size;
          rt.y = state->top;
          if ((((point.x >= lb.x) && (point.y <= lb.y)) && (point.x <= rt.x)) && (point.y >= rt.y))
          {
            allowed = 1;
            break;
          }
          lb.x = state->left;
          lb.y = state->bottom + ((struct FrameMapRegistration *) g_frame_registration)->cell_size;
          rt.x = state->right;
          rt.y = state->top - ((struct FrameMapRegistration *) g_frame_registration)->cell_size;
          if ((((point.x >= lb.x) && (point.y <= lb.y)) && (point.x <= rt.x)) && (point.y >= rt.y))
          {
            allowed = 1;
            break;
          }
        }
        next:
        state = next;

      }

    }
    if ((allowed == 1) && state)
    {
      struct FramePoint center;
      struct FramePoint point;
      g_grid_selected_need_effect_object = state->object;
      center.x = (state->left + state->right) / 2;
      center.y = (state->bottom + state->top) / 2;
      // BUG: point is unset if center projection fails, but its coordinates are still used.
      frame_grid_coordinates_to_point(g_frame_registration, &center, &point);
      point.y -= g_grid_selection_kind_height[state->kind];
      resource_scene_selector_activate_player(g_frame_scene_active_actor, point.x, point.y, object->display_layer);
    }
    else
    {
      g_grid_selected_need_effect_object = 0;
      resource_scene_selector_release_player(g_frame_scene_active_actor);
    }
  }
}
asm(".align 2,0");
