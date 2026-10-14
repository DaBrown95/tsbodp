#include "scene_text_bank.h"
void scene_text_bank_change_selection(void)
{
    struct SceneRequest *request = &g_scene_request;
    unsigned int previous = request->parameter;
    input_step_local_vertical_pressed(&request->parameter, 0, 5, 1,
                                       g_input_config.local_player);
    scene_text_bank_redraw_row(previous);
    scene_text_bank_redraw_row(request->parameter);
    {
        unsigned int bank = request->parameter;
        display_load_background_dma(3, g_scene_text_bank_backgrounds[bank],
                                    1, 1, 0, 0);
    }
}
asm(".align 2,0");
