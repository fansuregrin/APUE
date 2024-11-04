#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "mytool.h"

int main() {
    int status;
    pid_t pid;

    printf("main process: %d\n", getpid());
    
    for (int i=0; i<3; ++i) {
        pid = fork();
        if (pid < 0) {
            err_sys("fork error");
        } else if (pid == 0) {
            printf("pgid = %d, pid = %d, ppid = %d\n", getpgrp(), getpid(), getppid());
            exit(0);
        }
        sleep(2);
    }

    while ((pid = waitpid(0, &status, 0)) > 0) {
        printf("child process %d terminated\n", pid);
    }
}