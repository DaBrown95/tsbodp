#ifndef VIEW_CONFIGURATION_H
#define VIEW_CONFIGURATION_H

struct FramePoint;
struct TransitionViewObject;
/* Two-word access view at the observed per-view configuration root.
 * Array capacity and the original declaration remain unknown. */
struct ResourceViewDimensions { int x,y; };
extern struct ResourceViewDimensions g_resource_view_dimensions[];
void transition_configure_view(struct TransitionViewObject *,struct FramePoint,unsigned char);

#endif
