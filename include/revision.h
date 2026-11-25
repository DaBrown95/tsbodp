#ifndef REVISION_H
#define REVISION_H

/* Fixed addresses that the sources use as constants, not as linked symbols.
 * Revision 1 moved IWRAM data by 16 bytes and the save parameter rows by
 * 60 bytes. The build passes TSBO_REVISION; the selection is made here by the
 * preprocessor so each revision compiles from plain constants. */
#ifndef TSBO_REVISION
#error "TSBO_REVISION must be defined by the build"
#endif

#if TSBO_REVISION == 0
#define REVISION_WORD_0300217C 0x0300217c
#define REVISION_WORD_03002180 0x03002180
#define REVISION_FRAME_EMIT_IWRAM 0x03002a20
#define REVISION_FRAME_DRAW_IWRAM 0x03002900
#define REVISION_TILE_ALLOCATOR_IWRAM 0x03007390
#define REVISION_SAVE_TRANSFER_PARAMETERS 0x030074e4
#define REVISION_SAVE_TRANSFER_ROWS 0x08d7074c
#elif TSBO_REVISION == 1
#define REVISION_WORD_0300217C 0x0300216c
#define REVISION_WORD_03002180 0x03002170
#define REVISION_FRAME_EMIT_IWRAM 0x03002a10
#define REVISION_FRAME_DRAW_IWRAM 0x030028f0
#define REVISION_TILE_ALLOCATOR_IWRAM 0x03007380
#define REVISION_SAVE_TRANSFER_PARAMETERS 0x030074d4
#define REVISION_SAVE_TRANSFER_ROWS 0x08d70710
#else
#error "Unsupported TSBO_REVISION"
#endif

#endif
