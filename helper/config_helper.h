#ifndef CONFIG_HELPER_H
#define CONFIG_HELPER_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>

void run_tool(char** argv);

typedef void(*tool_function_t)(char** argv);

typedef struct tool_t tool_t;
struct tool_t {
    char name[64];
    tool_function_t fn;
};

extern tool_t config_tools[];
extern uint32_t config_tools_len;
extern char config_default_beaver[];
extern char config_default_main[];

#endif
