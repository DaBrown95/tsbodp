#ifndef SCENE_PALETTE_H
#define SCENE_PALETTE_H

/* Four pointer slots in each observed 16-byte scene palette record. */
struct ScenePeriodPalette { void *sources[4]; };
extern const struct ScenePeriodPalette g_scene_period_palettes[];
void *scene_palette_source(void);

#endif
