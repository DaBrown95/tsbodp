#include "resource_builders.h"
#include "heap.h"

void resource_prepare(const unsigned char *original)
{
    register const unsigned char *input asm("r4") = original;
    const unsigned char *cursor;
    const unsigned short *header;
    register const unsigned char *base asm("r6");
    const unsigned char *selected;

    heap_clear(g_resource_arena, 0, 8192);
    cursor = input + *(const unsigned short *)input;
    header = (const unsigned short *)cursor;
    {
        register unsigned int base_offset asm("r6") = header[4];
        base = input + base_offset;
    }
    cursor = &g_resource_selected;
    {
        const unsigned char *indices = (const unsigned char *)header + 1;
        unsigned int index = *cursor;
        index = indices[index];
        header += index * 4;
        cursor = input + header[4];
        selected = cursor;
    }
    cursor = resource_copy_arena_header(
        (const struct ResourceArenaHeader *)input, selected);
    g_resource_object_data = (unsigned char *)cursor;
    cursor = resource_build_object_groups(
        base, selected, (unsigned char *)cursor);
    g_resource_word_data = (unsigned char *)cursor;
    cursor = resource_build_word_groups(
        base, selected, (unsigned char *)cursor);
    g_resource_program_data = (unsigned char *)cursor;
    resource_build_program_groups(base, selected, (unsigned char *)cursor);
}
