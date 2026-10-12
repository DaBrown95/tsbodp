extern void frame_update(void), frame_publish_map_scroll(void), scene_commit_character_transfer(void);
void scene_vblank_callback(void) {
 frame_update();
 frame_publish_map_scroll();
 scene_commit_character_transfer();
}
asm(".align 2, 0");
