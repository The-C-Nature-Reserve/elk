#include "link.h"

void link(int argc, char** argv)
{
    // parse flags
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
            printf("link help page\n");
            exit(0);
        }
    }

    link_config_t* i;
    for (i = link_config; i != link_config + link_config_len; ++i) {
        printf("%s %s\n", i->name, i->location);
    }
}
