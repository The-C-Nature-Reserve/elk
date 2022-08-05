#include "config_helper.h"

void run_tool(char** argv)
{
    tool_t* iter;
    for(iter = config_tools; iter != config_tools + config_tools_len; ++iter) {
        if(strcmp(*argv, iter->name) == 0) {
            iter->fn(argv + 1);
            return;
        }
    }
}
