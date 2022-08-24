#include "config.h"

// TOOLS
// ----------------------------------------------------------------------------
tool_t config_tools[] = {
    { .name = "init",
        .fn = init,
        .description = "will initialize a project as defined in 'config.c'" },
};

uint32_t config_tools_len = sizeof(config_tools) / sizeof(*config_tools);

// INIT
// ----------------------------------------------------------------------------
static char config_default_beaver[]
    = "#include \"lib/beaver.h\"\n"
      "\n"
      "#define FLAGS \"-g -Wall -Werror -Og\"\n"
      "\n"
      "module_t modules[] = {\n"
      "    { .name = \"main\", .src = \"main.c\" },\n"
      "};\n"
      "uint32_t modules_len = sizeof(modules) / sizeof(*modules);\n"
      "\n"
      "char* program[] = { \"main\", NULL };\n"
      "\n"
      "int main(int argc, char** argv)\n"
      "{\n"
      "    auto_update(argv);\n"
      "    if (argc == 1) {\n"
      "        compile(program, FLAGS);\n"
      "    } else if (strcmp(argv[1], \"clean\") == 0) {\n"
      "        rm(\"build/*\");\n"
      "        rm(\"out\");\n"
      "    }\n"
      "    return 0;\n"
      "}\n";

static char config_default_main[] = "#include <stdio.h>\n"
                             "#include <stdint.h>\n"
                             "\n"
                             "int main(void)\n"
                             "{\n"
                             "    printf(\"Hello World!\\n\");\n"
                             "    return 0;\n"
                             "}\n";

init_config_t init_config[] = {
    { .type = INIT_DIR, .name = "build" },
    { .type = INIT_DIR, .name = "lib" },
    { .type = INIT_CMD,
        .name = "wget "
                "https://raw.githubusercontent.com/The-C-Nature-Reserve/beaver/"
                "main/beaver.h -P lib/" },
    {
        .type = INIT_FILE,
        .name = "beaver.c",
        .content = config_default_beaver,
    },
    {
        .type = INIT_FILE,
        .name = "main.c",
        .content = config_default_main,
    },
    { .type = INIT_CMD, .name = "gcc beaver.c -o beaver" },
};
uint32_t init_config_len = sizeof(init_config) / sizeof(*init_config);
