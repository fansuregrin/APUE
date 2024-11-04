#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include "mytool.h"

void pr_proc_ids(const char *prompt) {
#if defined _GNU_SOURCE
    printf("%s: pid = %d, ppid = %d, pgid = %d, sid = %d\n",
        prompt, getpid(), getppid(), getpgrp(), getsid(0));
#else
    printf("%s: pid = %d, ppid = %d, pgid = %d\n",
        prompt, getpid(), getppid(), getpgrp());
#endif
}