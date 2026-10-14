#ifndef FRAME_SPEED_EXIT_RESOURCE_H
#define FRAME_SPEED_EXIT_RESOURCE_H
struct FrameObject;
/* Read-only observed prefix; the first four bytes are not interpreted here. */
struct __attribute__((packed,aligned(2))) FrameSpeedExitResourcePayload {unsigned char unknown00[4];short x,y;unsigned char direction;};
struct FrameObject *frame_create_speed_exit_resource(unsigned char,unsigned char);
void condition_refresh_scene(unsigned int);
#endif
