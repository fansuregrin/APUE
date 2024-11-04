#include <sys/types.h>
#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "mytool.h"

int main() {
    pid_t pid;
    pid = fork();
    if (pid < 0) {
        err_sys("fork error");
    } else if (pid > 0) {
        exit(0);
    }

    // child process
    pid_t sid;
    // 调用进程不能是进程组的组长
    sid = setsid();
    if (sid < 0) {
        err_sys("setsid error");
    }
    assert(sid == getpid());
    pr_proc_ids("new session");
}