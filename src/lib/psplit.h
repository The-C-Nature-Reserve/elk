#ifndef PSPLIT_H
#define PSPLIT_H

#include <sys/wait.h>
#include <unistd.h>

static inline void psplit(void (*fn)(void*), void* arg)
{
    if (fork() == 0) {
        fn(arg);
        _exit(0);
    }
}

static inline void psplit_wait()
{
    wait(NULL);
}

#endif
