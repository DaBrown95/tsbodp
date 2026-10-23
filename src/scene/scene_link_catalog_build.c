#include "scene_link_catalog.h"

void scene_link_catalog_build(void)
{
    register struct ConditionActorEntry *entry_cursor asm("r4");
    register const struct SceneLinkCatalogDefinition *definitions asm("r10");
    register struct FrameObject **entry_owner_cursor asm("r6");
    unsigned int phase, id, palette;
    int index;

    {
        register struct ConditionActorEntry *entry_seed asm("r9") =
            g_scene_link_catalog_world.context->entries;
        {
            struct FrameObject *object = frame_create_scene_object(57, 10, 0, 1);
            g_scene_link_catalog_owners.first = object;
            object->flags |= 1;
        }
        phase = g_scene_request.unknown_10;
        if (phase == 0) {
            {
                struct FrameObject *object = frame_create_scene_object(93, 236, 9, 1);
                g_scene_link_catalog_owners.details[0] = object;
                object->flags |= 1;
            }
            {
                struct FrameObject *object = frame_create_scene_object(94, 237, 9, 1);
                g_scene_link_catalog_owners.details[1] = object;
                object->flags |= 1;
            }
        } else if (phase == 1 || phase == 3) {
            {
                struct FrameObject *object = frame_create_scene_object(68, 268, 15, 0);
                g_scene_link_catalog_owners.details[1] = object;
                object->flags &= ~1u;
            }
            {
                struct FrameObject *object = frame_create_scene_object(67, 269, 15, 0);
                g_scene_link_catalog_owners.details[0] = object;
                object->flags &= ~1u;
            }
        }
        index = 7;
        definitions = g_scene_link_catalog_definitions;
        {
            register struct FrameObject **owner_base asm("r0") =
                g_display_scene_frame_objects;
            entry_owner_cursor = owner_base + 8;
        }
        palette = 8;
        id = 64;
        entry_cursor = entry_seed + 7;
    }

    {
        register unsigned int clear_mask asm("r9") = ~1u;
        do {
            register unsigned int kind asm("r0") = entry_cursor->kind;
            if (kind != 255) {
                unsigned int subtype = definitions[kind].object_id;
                if (subtype != 317) {
                    struct FrameObject *object = frame_create_scene_object(id, subtype, palette, 1);
                    *entry_owner_cursor = object;
                    frame_set_variant_state(object, 58);
                } else {
                    register struct FrameObject *existing asm("r1") =
                        *entry_owner_cursor;
                    existing->flags &= clear_mask;
                }
            } else {
                struct FrameObject *object = frame_create_scene_object(id, 229, palette, 1);
                *entry_owner_cursor = object;
                object->flags &= clear_mask;
            }
            --entry_owner_cursor;
            --palette;
            --id;
            --entry_cursor;
            --index;
        } while (index >= 0);
    }

    {
        struct FrameObject **caption_owner_cursor;
        index = 4;
        {
            register struct FrameObject **owner_base asm("r0") =
                g_display_scene_frame_objects;
            caption_owner_cursor = owner_base + 13;
        }
        do {
            struct FrameObject *object = frame_create_scene_object(index + 52, index + 229, index + 10, 1);
            *caption_owner_cursor = object;
            frame_set_variant_state(object, 58);
            --caption_owner_cursor;
            --index;
        } while (index >= 0);
    }
}
