extern void frame_update(void), transition_alpha_tick(void), scene_commit_character_transfer(void);
void scene_vblank_callback(void) {
 frame_update();
 transition_alpha_tick();
 scene_commit_character_transfer();
}
asm(".align 2, 0");
