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
    
    for (int i = 0; i < init_config_len; ++i)
    {
        switch (init_config[i].type)
        {
            case TYPE_DIR:
            {
                make_directory(init_config[i].name);
                break;
            }

            case TYPE_FILE:
            {
                FILE *f = fopen(init_config[i].name, "w");

                if (!f)
                {
                    // TODO: Error
                }

                if (init_config[i].content_func == NULL)
                {
                    fputs(init_config[i].content, f);
                }

                else
                {
                    char* str = init_config[i].content_func();
                    fputs(str, f);
                    free(str);
                }

                fclose(f);
                break;
            }

            case TYPE_CMD:
            {
                run_command(init_config[i].name);
                break;
            }
        }
    }
}
