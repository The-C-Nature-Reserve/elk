#ifndef INIT_H
#define INIT_H

#include <stdio.h>
#include <stdlib.h>

//#include "../helper/config_helper.h"
#include "../helper/helper.h"
#include "../lib/argparse.h"

#define TYPE_DIR ((uint8_t)0)
#define TYPE_FILE ((uint8_t)1)
#define TYPE_CMD ((uint8_t)2)

typedef struct init_config_t init_config_t;
struct init_config_t {
    char* name;
    char* content;
    char* (*content_func)();
    uint8_t type;
};

extern init_config_t init_config[];
extern uint32_t init_config_len;

void init(int argc, char** argv);

#endif
