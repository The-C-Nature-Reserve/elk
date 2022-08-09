#ifndef HELPER_H
#define HELPER_H

#include <curl/curl.h>
#include <curl/easy.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include <errno.h>
#include <stdarg.h>
#include <string.h>

#define PANIC(...)                                                             \
    do {                                                                       \
        fprintf(stderr, "\033[31melk PANIC!: \033[39m");                       \
        fprintf(stderr, __VA_ARGS__);                                          \
        fprintf(stderr, "\n");                                                 \
        exit(1);                                                               \
    } while (0);

#define PANIC_IF(b, ...)                                                       \
    do {                                                                       \
        if (b) {                                                               \
            PANIC(__VA_ARGS__);                                                \
        }                                                                      \
    } while (0);

#define INFO(...)                                                              \
    do {                                                                       \
        fprintf(stdout, "\033[34m[info] \033[39m");                            \
        fprintf(stdout, __VA_ARGS__);                                          \
        fprintf(stdout, "\n");                                                 \
    } while (0);

// TODO: windows
// linux for mkdir
#include <sys/stat.h>

#include "config_helper.h"

void download_file(char* path, char* url);
int make_directory(char* path);
int run_command(char* cmd);

void logging(char* s);

#endif
