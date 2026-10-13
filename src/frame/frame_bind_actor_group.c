#include "frame_actor_group.h"

void frame_bind_actor_group(struct FrameObject *base, const void *data)
{
    struct FrameActorObject *object = (struct FrameActorObject *)base;
    const unsigned char *definition = data;
    struct FrameSpriteVariant **variants;
    unsigned int palette;
    register int animation asm("r1");
    register const unsigned char *palette_map asm("r0");

    frame_set_part_variants(base, 0, g_actor_group_part0_tables[definition[0]],
                            object->oam.palette);
    frame_set_part_variants(base, 1,
                            g_actor_group_part1_tables[definition[0]][definition[2]],
                            object->oam.palette);
    variants = g_actor_group_part2_tables[definition[0]];
    palette_map = g_actor_group_part2_palette;
    animation = ((struct FrameActorGroupAnimationView *)object)->animation;
    palette = *(const unsigned char *)((unsigned int)animation +
                                      (unsigned int)palette_map);
    if (palette == 254)
        palette = ((const struct FrameActorGroupGameView *)&g_resource_game_state)->palette;
    {
        register unsigned int offset asm("r0") = (unsigned int)animation * 4;
        if (*(struct FrameSpriteVariant **)(offset + (unsigned int)variants))
            frame_set_part_variants(base, 2, variants, palette);
        else
            frame_clear_part_variants(base, 2);
    }
}

asm(".align 2, 0");
