#include "save_game_serialization.h"

void save_stream_serialize_game_state(void)
{
    struct SaveStreamGameStateView *world;
    unsigned char *selection;
    frame_write_save_value(&g_save_serialized_marker, 1);
    world = &g_save_world_view;
    frame_write_save_value(&world->unknown00, 4);
    frame_write_save_value(&world->clock, 6);
    frame_write_save_value(&world->unknown04, 3);
    save_stream_write_world_record((struct SaveStreamWorldRecord *)world->unknown10);
    save_world_write_region_1fecc(world->unknowndc);
    selection = g_save_selection_prefix;
    frame_write_save_value(selection, 1);
    frame_write_save_value(selection + 1, 2);
    frame_write_save_value(selection + 3, 2);
    save_stream_write_bits(&world->bit747, 1);
    save_stream_write_bits((const unsigned char *)&g_save_world_rows[selection[42]].unknown00, 1);
    save_stream_write_bits(&world->bit749, 1);
    frame_write_save_value(&world->byte741, 1);
    frame_write_save_value(&world->byte742, 1);
    frame_write_save_value(&world->byte746, 1);
    frame_write_save_value(&world->short744, 2);
    frame_write_save_value(&world->byte726, 1);
    frame_write_save_value(&world->byte72e, 1);
    frame_write_save_value(&g_save_world_event, 1);
    save_world_write_module_29d18();
    save_stream_write_nibble_state();
    save_stream_write_world_fields();
    save_stream_write_auxiliary_fields();
    save_stream_write_flag_words();
    frame_write_save_value(&world->byte740, 1);
}
asm(".align 2, 0");
