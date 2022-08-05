#ifndef HELPER_H
#define HELPER_H

#include <curl/curl.h>
#include <curl/easy.h>
#include <stdio.h>


// TODO: windows
// linux for mkdir
#include <sys/stat.h>

#include "config_helper.h"
#include "../config.h"

void download_file(char* path, char* url);
int make_directory(char* path);
void logging(char* s);

#endif
