#ifndef HELPER_H
#define HELPER_H

#include <curl/curl.h>
#include <curl/easy.h>
#include <stdarg.h>
#include <stdio.h>

#define INFO(...)                                                              \
    do {                                                                       \
        fprintf(stdout, "\033[34m[info] \033[39m");                            \
        fprintf(stdout, __VA_ARGS__);                                          \
        fprintf(stdout, "\n");                                                 \
    } while (0);

// TODO: windows
// linux for mkdir
#include <sys/stat.h>

#include "../config.h"
#include "config_helper.h"

void download_file(char* path, char* url);
int make_directory(char* path);
void logging(char* s);

#endif
