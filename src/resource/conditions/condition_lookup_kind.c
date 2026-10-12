#include "resource_conditions.h"
unsigned int condition_lookup_kind(unsigned int row,unsigned int column)
{
    unsigned int total=0,index=0;
    unsigned int *ids=g_condition_kind_ids;
    struct ConditionKindRecord *records=g_condition_kind_records;
    for(;index<row;index++)total+=g_condition_definitions[index].count;
    total+=column;
    return ids[records[total].index]-0x12;
}
