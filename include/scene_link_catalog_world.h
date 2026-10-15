#ifndef SCENE_LINK_CATALOG_WORLD_H
#define SCENE_LINK_CATALOG_WORLD_H
/* Same observed owner, shared without importing the scene catalog graph. */
struct SceneLinkCatalogContext;
struct SceneLinkCatalogWorld {
    unsigned int unknown00, value;
    unsigned char unknown08[232];
    struct SceneLinkCatalogContext *context;
    unsigned char unknownf4[772];
    unsigned char *policies;
    unsigned char unknown3fc[835], requested_kind;
};
extern struct SceneLinkCatalogWorld g_scene_link_catalog_world;
#endif
