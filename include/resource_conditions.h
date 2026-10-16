#ifndef RESOURCE_CONDITIONS_H
#define RESOURCE_CONDITIONS_H

/* Partial views of the condition definitions and their serialized state. */
struct ConditionDefinition {
    unsigned char unknown00, group_display_kind, display_kind, count, entry_kinds[1];
};
struct ConditionRow {
    unsigned char display_kinds[5], unknown05, count, unknown07;
    struct ConditionDefinition *columns[6];
};
extern struct ConditionRow g_condition_definitions[];
struct ConditionRowScene { unsigned char scene,mode,unknown02[2]; };
extern struct ConditionRowScene g_condition_row_scenes[];
void condition_select_row(unsigned int);
extern unsigned char g_condition_display_bits[];
struct ConditionKindRecord { unsigned int index,unknown04; };
extern unsigned int g_condition_kind_ids[];
extern struct ConditionKindRecord g_condition_kind_records[];
unsigned int condition_lookup_kind(unsigned int,unsigned int);
/* Raw byte fields are zero-extended into the complete return word. Callers
 * retain explicit low-byte consumption where the original code narrows it. */
unsigned int condition_is_active(unsigned int,unsigned int,unsigned int);
unsigned int condition_is_complete(unsigned int,unsigned int,unsigned int);
unsigned int condition_group_active(unsigned int,unsigned int);
unsigned int condition_group_complete(unsigned int,unsigned int);
unsigned int condition_refresh(unsigned int,unsigned int);
void condition_activate_entry(unsigned int,unsigned int,unsigned int);
void condition_finish_group(unsigned int,unsigned int);
void condition_initialize_prior_rows(unsigned int);
void condition_complete_if_active(unsigned int,unsigned int,unsigned int);
void condition_refresh_thresholds(void *);
void condition_update_actor_context(void *);
void condition_publish_row_displays(unsigned int);
void condition_clear_display_bits(void);
unsigned char condition_notification_active(unsigned int);
#endif
