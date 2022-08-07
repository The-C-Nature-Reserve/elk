#include "init.h"

void init(int argc, char** argv)
{
    // check for flags
    {
        bool help = 0;
        argflag_t flags[] = {
            { .name = "help", .has_arg = 0, .target = &help },
            { .name = "h", .has_arg = 0, .target = &help },
        };
        uint32_t flags_len = sizeof(flags) / sizeof(*flags);

        argparse(flags, flags_len, argc, argv, NULL, NULL);

        if (help) {
            // TODO: print help
            printf("init help page\n");
            exit(0);
        }
    }

    int err = make_directory("lib");

    if (err != 0) {
        // TODO: error
    }

    download_file("lib/beaver.h", BEAVER_URL);

    FILE* fh;

    // main.c
    {
        INFO("making 'main.c'");
        fh = fopen("main.c", "w");
        // TODO panic
        fprintf(fh, "%s", config_default_main);
        fclose(fh);
    }

    // beaver.c
    {
        INFO("making 'beaver.c'");
        fh = fopen("beaver.c", "w");
        fprintf(fh, "%s", config_default_beaver);
        fclose(fh);

        INFO("compiling 'beaver.c'");
        system(COMPILER " -o beaver beaver.c");
    }
}
