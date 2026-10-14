#ifndef DISPLAY_MENU_CHOICE_RESTORE_H
#define DISPLAY_MENU_CHOICE_RESTORE_H
#include "display_menu.h"
#include "save_world_view_update.h"
#include "display_scene_setup.h"



struct DisplayMenuChoiceRecord {unsigned short text,unknown02;unsigned char reset,unknown05[3],row,column,entries[5],kinds[5];unsigned int flags;};
struct DisplayMenuChoiceWorld {unsigned int unknown00;int balance;unsigned char unknown08[0xf0-8];struct ConditionActorEntries *list;unsigned char unknownf4[0x440-0xf4];unsigned int kind;};
struct DisplayMenuChoiceSelection {unsigned char unknown00[0x24];unsigned int codes;};
extern struct ConditionActorEntries g_display_menu_restore_extra_entries;
extern void *g_display_menu_notice_owner;
void resource_set_triple(unsigned int,unsigned int,unsigned int);
void display_menu_apply_delta(signed char);
int frame_random_range(int,int);
unsigned int actor_entry_add(struct ConditionActorEntries *,unsigned int,unsigned char,unsigned char);

void condition_finish_display_kind(unsigned int);
unsigned int frame_actor_indicator_kind(unsigned char);
int frame_add_game_value(int);
void condition_select_row(unsigned int);
void display_menu_restore_choice(void);
#endif
