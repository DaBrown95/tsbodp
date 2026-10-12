#include "display.h"
/* Resource count/header and eight-byte records follow the selected DMA source. */
struct SceneCharacterTransferRecord {
 const void *source;
 unsigned short bytes, duration;
};
struct SceneCharacterTransferResource {
 unsigned char count, unknown_01[3];
 struct SceneCharacterTransferRecord records[1];
};
struct SceneCharacterTransfer {
 unsigned char flags, unknown_01, frame, elapsed;
 struct BackgroundState *background;
 struct SceneCharacterTransferResource *resource;
};
extern struct SceneCharacterTransfer g_scene_character_transfer;

struct SceneCharacterBase { unsigned int unknown_low : 2, character_base : 2, unknown_high : 28; };
