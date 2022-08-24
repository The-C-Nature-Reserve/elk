#include "config_helper.h"

static void print_help(FILE* stream)
{
    fprintf(stream, "Available tools are: \n");
    tool_t* iter;
    for (iter = config_tools; iter != config_tools + config_tools_len; ++iter) {
        fprintf(stream, "\t%s\t\t%s\n", iter->name, iter->description);
    }
}

void run_tool(int argc, char** argv)
{
    if (*argv == NULL) {
        print_help(stdout);
        return;
    }

    tool_t* iter;
    for (iter = config_tools; iter != config_tools + config_tools_len; ++iter) {
        if (strcmp(*argv, iter->name) == 0) {
            iter->fn(argc - 1, argv + 1);
            return;
        }
    }
    // TODO: find a way to keep this consitent with PANIC!
    fprintf(stderr, "\033[31melk PANIC!: \033[39m");
    fprintf(stderr, "could not find tool '%s'\n", *argv);
    print_help(stderr);
}
