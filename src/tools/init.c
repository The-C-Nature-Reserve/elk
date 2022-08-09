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

    uint32_t i;
    for (i = 0; i < init_config_len; ++i) {
        switch (init_config[i].type) {

        case TYPE_DIR: {
            make_directory(init_config[i].name);
            break;
        }

        case TYPE_FILE: {
            FILE* f = fopen(init_config[i].name, "w");

            PANIC_IF(f == NULL, "could not open file: %s: %s",
                init_config[i].name, strerror(errno));

            if (init_config[i].content_func == NULL) {
                PANIC_IF(*init_config[i].content == 0,
                    "no content provided for file: %s", init_config[i].name);
                fputs(init_config[i].content, f);
            } else {
                char* str = init_config[i].content_func();
                PANIC_IF(str == NULL, "function provided for file: %s failed",
                    init_config[i].name);
                fputs(str, f);
                free(str);
            }
            fclose(f);
            break;
        }

        case TYPE_CMD: {
            run_command(init_config[i].name);
            break;
        }
        }
    }
}
