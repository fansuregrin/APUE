#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include "mytool.h"

static void sig_quit(int signo);

int main() {
    sigset_t new_mask, old_mask, pending_mask;

    if (signal(SIGQUIT, sig_quit) == SIG_ERR) {
        err_sys("can't catch SIGQUIT");
    }

    sigemptyset(&new_mask);
    sigaddset(&new_mask, SIGQUIT);
    if (sigprocmask(SIG_BLOCK, &new_mask, &old_mask) < 0) {
        err_sys("SIG_BLOCK error");
    }

    sleep(5); // SIGQUIT 在此处是未决的

    if (sigpending(&pending_mask) < 0) {
        err_sys("sigpending error");
    }
    if (sigismember(&pending_mask, SIGQUIT) == 1) {
        printf("SIGQUIT pending\n");
    }

    if (sigprocmask(SIG_SETMASK, &old_mask, NULL) < 0) {
        err_sys("SIG_SETMASK error");
    }
    printf("SIGQUIT unblocked\n");

    sleep(5); // SIGQUIT 在此处会终止进程，并 core dumped
    exit(0);
}

static void sig_quit(int signo) {
    printf("caught SIGQUIT\n");
    if (signal(SIGQUIT, SIG_DFL) == SIG_ERR) {
        err_sys("can't reset SIGQUIT");
    }
}