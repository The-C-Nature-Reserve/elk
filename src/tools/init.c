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

    init_config_t* i;
    for (i = init_config; i < init_config + init_config_len; ++i) {
        switch (i->type) {

        case TYPE_DIR: {
            make_directory(i->name);
            break;
        }

        case TYPE_FILE: {
            FILE* f = fopen(i->name, "w");

            PANIC_IF(f == NULL, "could not open file: %s: %s",
                i->name, strerror(errno));

            if (i->content_func == NULL) {
                PANIC_IF(*i->content == 0,
                    "no content provided for file: %s", i->name);
                fputs(i->content, f);
            } else {
                char* str = i->content_func();
                PANIC_IF(str == NULL, "function provided for file: %s failed",
                    i->name);
                fputs(str, f);
                free(str);
            }
            fclose(f);
            break;
        }

        case TYPE_CMD: {
            run_command(i->name);
            break;
        }
        }
    }
}
