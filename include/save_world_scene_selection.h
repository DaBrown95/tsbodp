#ifndef SAVE_WORLD_SCENE_SELECTION_H
#define SAVE_WORLD_SCENE_SELECTION_H

/* The low byte of option selects base-scene or scene-variant membership. */
unsigned char save_world_scene_in_selected_row(unsigned int scene,
                                               unsigned int option);

#endif
