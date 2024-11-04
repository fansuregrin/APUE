#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <sys/types.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "mytool.h"

// handle SIGHUP
static void sig_hup(int signo) {
    printf("SIGHUP received, pid = %d\n", getpid());
}

// handle SIGCONT
static void sig_cont(int signo) {
    printf("SIGCONT received, pid = %d\n", getpid());
}

int main() {
    char c;
    pid_t pid;
    pr_proc_ids("parent");
    
    pid = fork();
    if (pid < 0) {
        err_sys("fork error");
    } else if (pid > 0) {
        sleep(5);  // sleep to let child process stop itself
    } else {
        // child process
        pr_proc_ids("child");
        signal(SIGHUP, sig_hup);
        signal(SIGCONT, sig_cont);
        kill(getpid(), SIGTSTP);
        pr_proc_ids("child");
        if (read(STDIN_FILENO, &c, sizeof(c)) != 1) {
            printf("read error %d on controlling TTY\n", errno);
        }
    }
    exit(0);
}