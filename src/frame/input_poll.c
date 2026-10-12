#include "input.h"
void input_poll(void)
{
    int i;
    if (g_input_disabled[0]) {
        input_clear();
        return;
    }
    if (g_input_config.player_count > 1) {
        for (i = 0; i < 4; i++) {
            g_input_previous[i] = g_input_current[i];
            g_input_current[i] = g_input_link_received[i];
            g_input_pressed[i] = (g_input_previous[i] ^ g_input_current[i]) & g_input_current[i];
            g_input_released[i] = (g_input_current[i] ^ g_input_previous[i]) & g_input_previous[i];
        }
        g_input_local_previous[g_input_config.local_player] = g_input_local_current[g_input_config.local_player];
        g_input_local_current[g_input_config.local_player] = *(volatile InputU16 *)0x04000130 ^ 0x3ff;
        g_input_local_pressed[g_input_config.local_player] = (g_input_local_current[g_input_config.local_player] ^ g_input_local_previous[g_input_config.local_player]) & g_input_local_current[g_input_config.local_player];
        g_input_local_released[g_input_config.local_player] = g_input_local_previous[g_input_config.local_player] & (g_input_local_current[g_input_config.local_player] ^ g_input_local_previous[g_input_config.local_player]);
    } else {
        g_input_previous[0] = g_input_current[0];
        g_input_current[0] = *(volatile InputU16 *)0x04000130 ^ 0x3ff;
        g_input_pressed[0] = (g_input_current[0] ^ g_input_previous[0]) & g_input_current[0];
        g_input_released[0] = (g_input_current[0] ^ g_input_previous[0]) & g_input_previous[0];
        g_input_local_previous[0] = g_input_local_current[0];
        g_input_local_current[0] = g_input_current[0];
        g_input_local_pressed[0] = (g_input_current[0] ^ g_input_local_previous[0]) & g_input_current[0];
        g_input_local_released[0] = (g_input_current[0] ^ g_input_local_previous[0]) & g_input_local_previous[0];
    }
    if (!(g_input_current[g_input_config.local_player] & 0x3ff))
        g_input_idle_frames++;
    else
        g_input_idle_frames = 0;
}
