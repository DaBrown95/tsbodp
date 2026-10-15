#include "scene_startup.h"

unsigned char scene_audio_for_period(unsigned int period) {
 unsigned char sequence=0;
 switch(period) {
 case 0:sequence=g_scene_period_audio[g_scene_id].sequences[0];break;
 case 1:sequence=g_scene_period_audio[g_scene_id].sequences[1];break;
 case 2:sequence=g_scene_period_audio[g_scene_id].sequences[2];break;
 case 3:sequence=g_scene_period_audio[g_scene_id].sequences[3];break;
 }
 return sequence;
}
asm(".align 2,0");
