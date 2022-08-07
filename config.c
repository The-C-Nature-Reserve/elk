#include "config.h"

tool_t config_tools[] = {
    { .name = "init", .fn = init },
};

uint32_t config_tools_len = sizeof(config_tools) / sizeof(*config_tools);

char config_default_beaver[]
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

char config_default_main[] = "#include <stdio.h>\n"
                             "#include <stdint.h>\n"
                             "\n"
                             "int main(void)\n"
                             "{\n"
                             "    printf(\"Hello World!\\n\");\n"
                             "    return 0;\n"
                             "}\n";
