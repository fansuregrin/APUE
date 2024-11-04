#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include "mytool.h"

void pr_proc_ids() {
#if defined _GNU_SOURCE
    printf("pid = %d, ppid = %d, pgid = %d, sid = %d\n",
        getpid(), getppid(), getpgrp(), getsid(0));
#else
    printf("pid = %d, ppid = %d, pgid = %d\n",
        getpid(), getppid(), getpgrp());
#endif
}