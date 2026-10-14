#ifndef SCENE_CATALOG_PAGING_H
#define SCENE_CATALOG_PAGING_H
#include "scene_catalog_content.h"
#include "display_text_fields.h"
#include "display_catalog_presentation.h"
unsigned char scene_catalog_is_basic_row(void);
void scene_catalog_refresh_basic_arrows(void),scene_catalog_refresh_page_arrows(void);
void scene_catalog_previous(void),scene_catalog_next(void),scene_catalog_refresh_quantities(void);
#endif
