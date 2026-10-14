#include "audio_game_activity.h"
void audio_game_parameter_activity_notice(int kind,int parameter) {
 switch(kind) {
 case 2:case 6:g_audio_game_activity_notice.flags|=2;break;
 case 3:g_audio_game_activity_notice.parameter=parameter;g_audio_game_activity_notice.flags|=4;break;
 case 5:break;
 }
}
asm(".align 2,0");
