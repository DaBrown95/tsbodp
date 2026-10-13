#ifndef DISPLAY_TRANSIENT_DEFINITION_H
#define DISPLAY_TRANSIENT_DEFINITION_H

#include "display.h"
#include "frame_render.h"
#include "frame_transient_effect.h"

unsigned int display_allocate_tile_bytes(struct DisplayTileResource *, unsigned int,
                                        unsigned int);
unsigned short frame_initialize_transient_definition(unsigned char,
                                                    unsigned char,
                                                    struct FrameSpriteResource *);
unsigned short frame_reload_transient_definition(unsigned char,
                                                unsigned char,
                                                struct FrameSpriteResource *);
unsigned int display_recopy_tile_bytes(struct DisplayTileResource *, unsigned int,
                                      unsigned char, unsigned short);

#endif
