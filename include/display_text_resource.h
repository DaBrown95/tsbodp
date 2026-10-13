#ifndef DISPLAY_TEXT_RESOURCE_H
#define DISPLAY_TEXT_RESOURCE_H
/* Paired edges: values below 256 are bytes, others select node value - 256. */
struct DisplayTextCodeNode {
    unsigned short zero, one;
};
extern const unsigned char *g_display_text_resource;
extern const unsigned int *g_display_text_offsets;
extern const struct DisplayTextCodeNode *g_display_text_nodes;
extern int display_text_set_resource(const void *);
extern int display_text_load_string(unsigned int, char *, unsigned int);
#endif
