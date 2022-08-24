#ifndef INIT_H
#define INIT_H

#include <stdio.h>
#include <stdlib.h>

//#include "../helper/config_helper.h"
#include "../helper/helper.h"
#include "../lib/argparse.h"

typedef enum {
    INIT_DIR,
    INIT_FILE,
    INIT_CMD,
} init_config_type_t;

typedef struct init_config_t init_config_t;
struct init_config_t {
    char* name;
    char* content;
    char* (*content_func)();
    init_config_type_t type;
};

extern init_config_t init_config[];
extern uint32_t init_config_len;

void init(int argc, char** argv);

#endif
