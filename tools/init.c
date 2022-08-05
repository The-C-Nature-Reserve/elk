#include "init.h"

void init(char** argv)
{
    int err = make_directory("lib");

    if(err != 0) {
        // TODO: error
    }

    download_file("lib/beaver.h", BEAVER_URL);

    FILE* fh;
    {
        fh = fopen("main.c", "w");
        // TODO panic
        fprintf(fh, "%s", config_default_main);
        fclose(fh);
    }

    {
        fh = fopen("beaver.c", "w");
        fprintf(fh, "%s", config_default_beaver);
        fclose(fh);
        // TODO: compile
    }
}
