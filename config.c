#include "config.h"

static tool_t tools[] = {
    { .name = "help", .fn = help },
};

tool_t* config_tools()
{
    return tools;
}


