#include "config_helper.h"

void run_tool(int argc, char** argv)
{
    tool_t* iter;
    for (iter = config_tools; iter != config_tools + config_tools_len; ++iter) {
        if (strcmp(*argv, iter->name) == 0) {
            iter->fn(argc - 1, argv + 1);
            return;
        }
    }
}
