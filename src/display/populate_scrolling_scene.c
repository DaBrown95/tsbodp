#include "display_scene_catalog_render.h"
#include "display_scene_lifecycle.h"

/* Each low word changes role after the four-object clear loop.
 * The high words hold the actual object and next-slot pointers. */
struct SceneClearObjectWords {
    union { unsigned int flags; unsigned char *eligible; } low;
    struct FrameObject *object;
};
struct SceneClearMaskWords {
    union { int mask; const struct DisplayCatalogItem *catalog; } low;
    struct FrameObject **clear;
};
typedef char scene_clear_object_words_layout[
    (sizeof(struct SceneClearObjectWords)==8 && __alignof__(struct SceneClearObjectWords)==4) ? 1 : -1];
typedef char scene_clear_mask_words_layout[
    (sizeof(struct SceneClearMaskWords)==8 && __alignof__(struct SceneClearMaskWords)==4) ? 1 : -1];
static __inline void scene_increment_count(unsigned char *source)
{
 register unsigned char *count asm("r1") = source;
 register unsigned int value asm("r0") = *count;
 value++;
 *count = value;
}
static __inline unsigned int scene_enabled_count(const unsigned char *source)
{
 register const unsigned char *count asm("r2") = source;
 register unsigned int result asm("r0") = *count;
 return result;
}
void display_scene_stage_0800f034(unsigned int page_word)
{
    register unsigned int incoming_page asm("r0") = page_word;
    unsigned char page = incoming_page;
    unsigned short first = 0;
    register unsigned int visible asm("r6");
    int i;
    register unsigned char *eligible asm("r9");
    const struct DisplayCatalogItem *record;
    struct FrameObject **slots;
    register struct SceneClearObjectWords object_words asm("r0");
    register struct SceneClearMaskWords clear_words asm("r2");
    if (page) first = (unsigned char)(page << 2);
    g_display_scene_byte1 = 0;
    g_display_scene_byte0 = 0;
    visible = 0;
    { register struct FrameObject **base asm("r0") = g_display_scene_frame_objects;
      clear_words.low.mask = ~1;
      { register struct FrameObject **clear_input asm("r3") = base + 6;
        clear_words.clear = clear_input; }
      i = 3;
      do {
        register struct FrameObject **clear asm("r3") = clear_words.clear;
        register struct FrameObject *object asm("r1") = *clear++;
        register unsigned int flags asm("r0");
        clear_words.clear = clear;
        object_words.object = object;
        object = object_words.object;
        flags = object->flags;
        object_words.low.flags = flags;
        object_words.low.flags &= clear_words.low.mask;
        flags = object_words.low.flags;
        object->flags = flags;
      } while (--i >= 0); }
    i = 0;
    { register unsigned int catalog_address asm("r2") =
          (unsigned int)g_display_scene_catalog;
      clear_words.low.catalog = (const struct DisplayCatalogItem *)catalog_address;
      record = clear_words.low.catalog; }
    { register unsigned int eligible_address asm("r0") =
          (unsigned int)&g_display_scene_byte1;
      object_words.low.eligible = (unsigned char *)eligible_address;
      eligible = object_words.low.eligible; }

    for (; i <= 148; ++i) {
        register const struct DisplayCatalogItem *current asm("r1") = record;
        unsigned int id = current->id;
        if (id != 0x13d && current->category == g_display_scene_request_state.scene) {
            ++g_display_scene_byte0;
            if (display_scene_item_enabled(g_display_scene_item_mask, i)) {
                if (visible <= 3 && scene_enabled_count(eligible) >= first) {
                    { register struct FrameObject **base asm("r0") = g_display_scene_frame_objects; register unsigned int address asm("r4") = visible + 6; address *= 4; address += (unsigned int)base; slots = (struct FrameObject **)address; }
                    (*slots)->unknown_0a = id;
                    display_scene_refresh_item(*slots);
                    frame_set_variant_state(*slots, 0x3a);
                    (*slots)->flags |= 1;
                    { register unsigned int next asm("r0") = visible + 1; next = (unsigned char)next; visible = next; }
                }
                scene_increment_count(eligible);
            }
        }
        { register unsigned short stride asm("r2") = sizeof(*record);
          record = (const struct DisplayCatalogItem *)((unsigned int)record + stride); }
    }
    { struct FrameObject **fill_base;
    if (visible > 3 || (int)(visible + first) >= g_display_scene_byte0) goto done;
    fill_base = g_display_scene_frame_objects;
 fill_slot:
        { struct FrameObject **base = fill_base; register unsigned int address asm("r4") = visible + 6; address *= 4; address += (unsigned int)base; slots = (struct FrameObject **)address; }
        (*slots)->unknown_0a = 0xe2;
        display_scene_refresh_item(*slots);
        frame_set_variant_state(*slots, 0x3a);
        (*slots)->flags |= 1;
        { register unsigned int next asm("r0") = visible + 1; next = (unsigned char)next; visible = next; }
    if (visible > 3) goto done;
    { register unsigned short offset asm("r2") = first;
      register unsigned int sum asm("r1") = visible + offset;
      if ((int)sum < g_display_scene_byte0) goto fill_slot; }
 done:;
    }
}
