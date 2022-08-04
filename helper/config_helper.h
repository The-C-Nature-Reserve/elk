#ifndef CONFIG_HELPER_H
#define CONFIG_HELPER_H

typedef void(*tool_function_t)(char** argv);

typedef struct tool_t tool_t;
struct tool_t {
    char name[64];
    tool_function_t fn;
};

#endif
