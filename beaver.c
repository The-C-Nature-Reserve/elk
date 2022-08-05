#include "lib/beaver.h"
#define FLAGS "-g -Wall -Werror -Og"

module_t modules[] = {
    { .name = "core", .src = "main.c" },
    { .name = "core", .src = "config.c" },
    { .name = "config_helper", .src = "helper/config_helper.c" },
    { .name = "helper", .src = "helper/helper.c", .extra_flags = "-lcurl" },

    // Tools
    { .name = "init", .src = "tools/init.c" },
};
uint32_t modules_len = sizeof(modules) / sizeof(*modules);

char* elk[] = { "core", "helper", "init", "config_helper", NULL };

int main(int argc, char** argv)
{
    auto_update(argv);
    if (argc == 1) {
        compile(elk, FLAGS);
    } else if (strcmp(argv[1], "clean") == 0) {
        rm("build/*");
        rm("out");
        rm("-rf test/*");
    }
    return 0;
}