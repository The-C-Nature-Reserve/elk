#include "lib/beaver.h"

#define FLAGS "-g -Wall -Werror"
#define FAST_FLAGS "-Ofast -march=native"


module_t modules[] = {
    { .name = "core", .src = "main.c" },
    { .name = "core", .src = "config.c" },
    { .name = "config_helper", .src = "helper/config_helper.c" },
    { .name = "helper", .src = "helper/helper.c", .extra_flags = "-lcurl" },

    { .name = "smap", .src = "lib/smap.c" },

    { .name = "argparse", .src = "lib/argparse.c" },
    { .name = "argparse", .module = "smap" },

    // Tools
    { .name = "init", .src = "tools/init.c" },
    { .name = "init", .module = "argparse" },

};
uint32_t modules_len = sizeof(modules) / sizeof(*modules);

char* elk[] = { "core", "helper", "init", "config_helper", NULL };

int main(int argc, char** argv)
{
    auto_update(argv);
    rm(" -rf test/*");

    if (argc == 1) {
        compile(elk, FLAGS);
    } else if (strcmp(argv[1], "clean") == 0) {
        call_or_warn("rm $(find build/ -type f)");
        rm("out");
    } else if (strcmp(argv[1], "install") == 0) {
        // TODO: windows
        call_or_panic("cp out /usr/bin/elk");
    } else if (strcmp(argv[1], "uninstall") == 0) {
        // TODO: windows
        call_or_panic("rm /usr/bin/elk");
    } else if (strcmp(argv[1], "fast") == 0) {
        compile(elk, FAST_FLAGS);
    } else if (strcmp(argv[1], "hard-clean") == 0) {
        rm("-rf build/");
        rm("out");
    } else {
        fprintf(stderr, "Err: unknown option: '%s'", argv[1]);
    }
    return 0;
}
