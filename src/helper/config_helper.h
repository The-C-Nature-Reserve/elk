#ifndef CONFIG_HELPER_H
#define CONFIG_HELPER_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define TYPE_DIR  0
#define TYPE_FILE 1
#define TYPE_CMD  2

typedef struct init_config_t init_config_t;
struct init_config_t
{
    char *name;
    char *content;
    char *(*content_func)();
    uint8_t type;
};

void run_tool(int argc, char** argv);

typedef void(*tool_function_t)(int argc, char** argv);

typedef struct tool_t tool_t;
struct tool_t {
    char name[64];
    tool_function_t fn;
};

extern tool_t config_tools[];
extern uint32_t config_tools_len;
extern char config_default_beaver[];
extern char config_default_main[];
extern init_config_t init_config[];
extern uint32_t init_config_len;

#endif
