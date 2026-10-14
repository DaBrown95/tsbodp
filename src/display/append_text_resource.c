#include "display_text_helpers.h"
#include "display_text_resource.h"
char *display_append_text_resource(char *buffer, unsigned int id)
{
    char *cursor = buffer;
    while (*cursor)
        cursor++;
    if (!display_text_load_string(id, cursor, 1024)) {
        while (*cursor)
            cursor++;
        return cursor;
    }
    return 0;
}
asm(".align 2,0");
