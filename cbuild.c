#include "lib/cbuild.h"

#define FLAGS "-g -Wall -Werror -Og"

module_t modules[] = {
    { .name = "core", .src = "main.c" },
    { .name = "core", .src = "config.c" },
    { .name = "help", .src = "tools/help.c" },
};
uint32_t modules_len = sizeof(modules) / sizeof(*modules);

char* elk[] = { "core", "help", NULL };

int main(int argc, char** argv)
{
    auto_update(argv);
    if (argc == 1) {
        compile(elk, FLAGS);
    } else if (strcmp(argv[1], "clean") == 0) {
        rm("build/*");
        rm("out");
    }
    return 0;
}
