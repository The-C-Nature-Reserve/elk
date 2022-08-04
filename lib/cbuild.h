#ifndef CBUILD_H
#define CBUILD_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

// TODO: windows
#include <unistd.h>

#define GREEN "\033[32m"
#define RED "\033[31m"
#define ORANGE "\033[33m"
#define RESET "\033[39m"

#ifndef COMPILER

#if defined(__clang__)
#define COMPILER "clang"

#elif defined(__GNUG__)
#define COMPILER "g++"

#elif defined(__GNUC__)
#define COMPILER "gcc"

#elif defined(__MSVC_VER__)
#define COMPILER "msvc"

#elif defined(__TINYC__)
#define COMPILER "tcc"

#elif defined(__MINGW32__)
#define COMPILER "mingw"

#elif defined(__MINGW64__)
#define COMPILER "mingw"
#endif

#endif // COMPILER

#ifndef CBUILD_EXTRA_FLAGS_BUFFER_SIZE
#define CBUILD_EXTRA_FLAGS_BUFFER_SIZE 2048
#endif

#define LINKER "ld"

// TODO: check if it exists
#ifndef CBUILD_DIRECTORY
#define CBUILD_DIRECTORY "build/"
#endif

typedef struct module_t module_t;
struct module_t {
    char name[32];
    char module[32];
    char src[256];
    char extra_flags[256];
    char special_flags[256];
};

extern module_t modules[];
extern uint32_t modules_len;

static char cbuild_eflags_[CBUILD_EXTRA_FLAGS_BUFFER_SIZE] = { 0 };
static uint32_t cbuild_eflags_len_ = 0;

static inline bool cbuild_should_recomp_(char* file, char* dep)
{
    if (access(file, F_OK) != 0) {
        return 1;
    }
    struct stat file_stat;
    struct stat dep_stat;

    stat(file, &file_stat);
    stat(dep, &dep_stat);

    if (dep_stat.st_mtime >= file_stat.st_mtime) {
        return 1;
    }
    return 0;
}

static inline void cbuild_eflags_add_(char* flags)
{
    uint32_t len = strlen(flags) + 1;
    if (cbuild_eflags_len_ + len >= sizeof(cbuild_eflags_)) {
        char errmsg[] = "Error: extra flags buffer too small!\n"
                        "to resolve this add\n"
                        "'#define CBUILD_EXTRA_FLAGS_BUFFER_SIZE %lu'\n"
                        "just before '#inlcude \"cbuild.h\"'\n";
        fprintf(stderr, errmsg, sizeof(cbuild_eflags_) << 1);
        exit(1);
    }
    cbuild_eflags_[cbuild_eflags_len_++] = ' ';
    len--;
    memcpy(cbuild_eflags_ + cbuild_eflags_len_, flags, len);
    cbuild_eflags_len_ += len;
    cbuild_eflags_[cbuild_eflags_len_] = 0;
}

static inline int cbuild_bcmd_(
    char** cmd, uint32_t* len, uint32_t* size, char* s, bool space)
{
    if (*cmd == NULL) {
        *size = 1024;
        *len = 0;
        *cmd = malloc(*size);
        if (*cmd == NULL) {
            return -1;
        }
        **cmd = 0;
    }
    uint32_t sl = strlen(s);
    if (*len + sl + space >= *size) {
        *size = (*size << 1) + sl;
        *cmd = realloc(*cmd, *size);
        if (*cmd == NULL) {
            return -1;
        }
    }
    if (space) {
        (*cmd)[*len] = ' ';
        *len += 1;
    }
    memcpy(*cmd + *len, s, sl);
    *len += sl;
    (*cmd)[*len] = 0;
    return 0;
}

static inline void cbuild_call_or_panic_(char* cmd)
{
    printf(GREEN "[running]" RESET " %s\n", cmd);
    int r = system(cmd);
    if (r != 0) {
        fprintf(stderr, RED "CBUILD PANIC!" RESET ": '%s'\n", cmd);
        exit(1);
    }
}

static inline void cbuild_call_or_warn_(char* cmd)
{
    printf(GREEN "[running]" RESET " %s\n", cmd);
    int r = system(cmd);
    if (r != 0) {
        fprintf(stderr, ORANGE "CBUILD WARN!" RESET ": '%s'\n", cmd);
    }
}

static inline void auto_update(char** argv)
{
    if (!cbuild_should_recomp_("cbuild", "cbuild.c")) {
        return;
    }

    char* cmd = NULL;
    uint32_t len = 0;
    uint32_t size = 0;

    cbuild_bcmd_(&cmd, &len, &size, COMPILER " -o cbuild cbuild.c &&", 0);
    for (; *argv; argv++) {
        cbuild_bcmd_(&cmd, &len, &size, *argv, 1);
    }

    cbuild_call_or_panic_(cmd);
    free(cmd);
    exit(0);
}

static inline void rm(char* p)
{
    char* cmd = NULL;
    uint32_t len = 0;
    uint32_t size = 0;

    cbuild_bcmd_(&cmd, &len, &size, "rm", 0);
    cbuild_bcmd_(&cmd, &len, &size, p, 1);
    cbuild_call_or_warn_(cmd);
    free(cmd);
}

static inline void cbuild_clean_dir_(char* p)
{
    char* cmd = NULL;
    uint32_t cmd_len = 0;
    uint32_t cmd_size = 0;
    cbuild_bcmd_(&cmd, &cmd_len, &cmd_size, "rm", 0);
    cbuild_bcmd_(&cmd, &cmd_len, &cmd_size, p, 1);
    cbuild_bcmd_(&cmd, &cmd_len, &cmd_size, "*", 0);
    cbuild_call_or_panic_(cmd);
    free(cmd);
}

static inline char* cbuild_file_from_path_(char* p)
{
    char* src = rindex(p, '/');
    if (src == NULL) {
        return p;
    } else {
        return ++src;
    }
}

static inline void cbuild_compile_module_(char* name, char* flags)
{
    // check if recompile needed
    module_t* mi;
    {
        bool recomp_needed = 0;
        char mod_name[strlen(name) + strlen(CBUILD_DIRECTORY) + 3];
        strcpy(mod_name, CBUILD_DIRECTORY);
        strcat(mod_name, name);
        strcat(mod_name, ".o");
        for (mi = modules; mi != modules + modules_len; ++mi) {
            if (strcmp(mi->name, name) != 0) {
                continue;
            }
            if (*mi->module != 0) {
                cbuild_compile_module_(mi->module, flags);
                continue;
            }
            cbuild_eflags_add_(mi->extra_flags);
            if (!recomp_needed && cbuild_should_recomp_(mod_name, mi->src)) {
                recomp_needed = 1;
            }
        }
        if (!recomp_needed) {
            return;
        }
    }

    char* cmd = NULL;
    uint32_t cmd_len = 0;
    uint32_t cmd_size = 0;
    for (mi = modules; mi != modules + modules_len; ++mi) {
        if (strcmp(mi->name, name) != 0) {
            continue;
        }
        if (*mi->module != 0) {
            continue;
        }
        cbuild_bcmd_(&cmd, &cmd_len, &cmd_size, COMPILER " -c -o", 0);
        cbuild_bcmd_(&cmd, &cmd_len, &cmd_size, CBUILD_DIRECTORY "inter/", 1);

        cbuild_bcmd_(
            &cmd, &cmd_len, &cmd_size, cbuild_file_from_path_(mi->src), 0);

        cbuild_bcmd_(&cmd, &cmd_len, &cmd_size, ".o", 0);
        if (*mi->special_flags == 0) {
            cbuild_bcmd_(&cmd, &cmd_len, &cmd_size, flags, 1);
        } else {
            cbuild_bcmd_(&cmd, &cmd_len, &cmd_size, mi->special_flags, 1);
        }
        cbuild_bcmd_(&cmd, &cmd_len, &cmd_size, mi->extra_flags, 1);
        cbuild_bcmd_(&cmd, &cmd_len, &cmd_size, mi->src, 1);
        cbuild_call_or_panic_(cmd);

        // reset cmd
        {
            *cmd = 0;
            cmd_len = 0;
        }
    }

    cbuild_bcmd_(&cmd, &cmd_len, &cmd_size, LINKER " -relocatable -o", 0);
    cbuild_bcmd_(&cmd, &cmd_len, &cmd_size, CBUILD_DIRECTORY, 1);
    cbuild_bcmd_(&cmd, &cmd_len, &cmd_size, name, 0);
    cbuild_bcmd_(&cmd, &cmd_len, &cmd_size, ".o", 0);
    for (mi = modules; mi != modules + modules_len; ++mi) {
        if (strcmp(mi->name, name) != 0) {
            continue;
        }
        cbuild_bcmd_(&cmd, &cmd_len, &cmd_size, CBUILD_DIRECTORY "inter/", 1);
        // cbuild_bcmd_(&cmd, &cmd_len, &cmd_size, mi->src, 0);
        cbuild_bcmd_(
            &cmd, &cmd_len, &cmd_size, cbuild_file_from_path_(mi->src), 0);
        cbuild_bcmd_(&cmd, &cmd_len, &cmd_size, ".o", 0);
    }
    cbuild_call_or_panic_(cmd);
    free(cmd);
    cbuild_clean_dir_(CBUILD_DIRECTORY "inter/");
}

static inline void compile(char** prog, char* flags)
{
    char* cmd = NULL;
    uint32_t len = 0;
    uint32_t size = 0;

    char** pi;
    for (pi = prog; *pi; ++pi) {
        cbuild_compile_module_(*pi, flags);
    }

    cbuild_bcmd_(&cmd, &len, &size, COMPILER " -o out", 0);
    cbuild_bcmd_(&cmd, &len, &size, flags, 1);
    cbuild_bcmd_(&cmd, &len, &size, cbuild_eflags_, 1);
    for (pi = prog; *pi; ++pi) {
        cbuild_bcmd_(&cmd, &len, &size, CBUILD_DIRECTORY, 1);
        cbuild_bcmd_(&cmd, &len, &size, *pi, 0);
        cbuild_bcmd_(&cmd, &len, &size, ".o", 0);
    }
    cbuild_call_or_panic_(cmd);
    free(cmd);
}

#endif
