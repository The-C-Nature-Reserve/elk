#ifndef LINK_H
#define LINK_H

#include "../helper/config_helper.h"
#include "../helper/helper.h"
#include "../lib/argparse.h"

typedef struct link_config_t link_config_t;
struct link_config_t {
    char* name;
    char* location;
};

extern link_config_t link_config[];
extern uint32_t link_config_len;

void link(int argc, char** argv);

#endif
