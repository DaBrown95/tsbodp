#include "display_motion.h"

/* Four native size-code rows; only this read view is established here. */
struct DisplayBackgroundMapDimensions {
    unsigned short width, height;
};
extern const struct DisplayBackgroundMapDimensions g_display_background_map_dimensions[4];

/* No incoming caller is established; these are the three observed arguments. */
void display_read_background_dimensions_unrooted_d9d4(unsigned int index,
    unsigned short *width, unsigned short *height)
{
    const struct DisplayBackgroundMapDimensions *dimensions = g_display_background_map_dimensions;
    const unsigned char *system = (const unsigned char *)&g_display_background_system;
    const unsigned char *background = system + index * sizeof(struct BackgroundState);
    *width = dimensions[background[9] >> 6].width;
    *height = dimensions[background[9] >> 6].height;
}
