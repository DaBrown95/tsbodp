#ifndef SCENE_MAP_SELECTION_H
#define SCENE_MAP_SELECTION_H

struct FrameObject;
struct FrameObjectList;
struct BackgroundResource;

/* Observed word-coordinate rows. Names and complete table storage are provisional. */
struct SceneMapSelectionPoint { unsigned int x, y; };
/* Only the 26-row accessed prefix is modeled; this is not a complete table bound. */
union SceneMapSelectionPointPrefix {
    struct SceneMapSelectionPoint rows[26];
    unsigned int words[52];
};
struct SceneMapSelectionBounds { unsigned char left, right, top, bottom; };
struct SceneMapSelectionLimits { unsigned int first, last; };
struct SceneMapSelectionPaletteConfig {
    unsigned char resource, bank, count, unknown03;
};
/* Distinct observed byte roles at world-state +42C/+42E; complete ownership unknown. */
struct SceneMapSelectionWorldView {
    unsigned char unknown00[0x42c];
    unsigned char scene, unknown42d, flag;
};
extern const unsigned int g_scene_map_selection_control0, g_scene_map_selection_control1;
extern const unsigned int g_scene_map_selection_control2, g_scene_map_selection_control3;
extern const struct BackgroundResource g_scene_map_selection_background0;
extern const struct BackgroundResource g_scene_map_selection_background1;
extern const struct BackgroundResource g_scene_map_selection_background2;
extern const struct BackgroundResource g_scene_map_selection_background3;
extern const unsigned short g_display_menu_palette_data[];
extern unsigned char g_scene_map_selection_hovered, g_scene_map_selection_mode;
extern unsigned int g_scene_map_selection_origin_x, g_scene_map_selection_palette_block;
extern unsigned int g_scene_map_selection_requested_world;
extern const union SceneMapSelectionPointPrefix g_scene_map_selection_points;
extern const struct SceneMapSelectionBounds g_scene_map_selection_bounds[];
extern const struct SceneMapSelectionLimits g_scene_map_selection_limits[];
extern const struct SceneMapSelectionPoint g_scene_map_selection_world_points[];
extern const struct SceneMapSelectionPaletteConfig g_scene_map_selection_palette_configs[];
extern const unsigned short *const g_scene_map_selection_palettes[];
extern struct FrameObject *g_display_scene_frame_objects[];
extern struct FrameObjectList g_frame_primary_list;

void scene_map_selection_initialize(void), scene_map_selection_step(void);
void scene_map_selection_shutdown(void), scene_map_selection_initialize_objects(void);
unsigned int scene_map_selection_entry_under_cursor(void);
/* Both word inputs are consumed through their low bytes in the original entry. */
void scene_map_selection_select_entry(unsigned int, unsigned int);
/* Explicit original provider: 495C4..49638 (116 bytes), not C coverage. */
unsigned int scene_map_selection_collapse_details(void);

/* Existing provider interfaces, retained at their established original addresses. */
void display_set_mode(unsigned short), display_show_background(unsigned int, unsigned int);
void display_enable_layers(unsigned short);
void display_fill_background(unsigned int, unsigned short);
const unsigned short *display_load_background_dma(unsigned int,
    const struct BackgroundResource *, unsigned short, unsigned short,
    unsigned int, unsigned int);
void display_set_background_scroll_target(unsigned int, int, int, unsigned int);
void transition_run_first(unsigned short, unsigned int);
void transition_run_second(unsigned short, unsigned int);
void display_release_object_list(struct FrameObjectList *);
void display_reset(void), display_scene_clear_object_slots(void);
void frame_set_variant_state(struct FrameObject *, unsigned char);
void display_text_select_font(unsigned int, int, int);
const char *display_scene_lookup_text(unsigned int);
struct FrameObject *display_scene_create_label(unsigned int, const char **);
void display_scene_refresh_item(struct FrameObject *);
void scene_submit_default_request(unsigned int);

#endif
