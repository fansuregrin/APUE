#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <sys/types.h>
#include <signal.h>
#include <errno.h>
#include <stdio.h>
#include "mytool.h"

typedef struct {
    int signo;
    const char * sigstr;
} sig_info;

static const sig_info const sig_list[] = {
    SIGHUP,     "SIGHUP",
    SIGINT,     "SIGINT",
    SIGQUIT,    "SIGQUIT",
    SIGILL,     "SIGILL",
    SIGTRAP,    "SIGTRAP",
    SIGABRT,    "SIGABRT",
    SIGFPE,     "SIGFPE",
    SIGKILL,    "SIGKILL",
    SIGSEGV,    "SIGSEGV",
    SIGPIPE,    "SIGPIPE",
    SIGALRM,    "SIGALRM",
    SIGTERM,    "SIGTERM",
    SIGUSR1,    "SIGUSR1",   
    SIGUSR2,    "SIGUSR2"    
};

static void pr_mask(const char *msg) {
    sigset_t sigset;
    int saved_errno = errno;
    if (sigprocmask(0, NULL, &sigset) < 0) {
        err_ret("sigprocmask error");
    } else {
        printf("%s", msg);
        for (int i = 0; i < sizeof(sig_list) / sizeof(sig_info); ++i) {
            if (sigismember(&sigset, sig_list[i].signo) == 1) {
                printf(" %s", sig_list[i].sigstr);
            }
        }
        printf("\n");
    }
    errno = saved_errno;
}

void sig_usr1(int signo) {
    printf("SIGUSR1 received\n");
}

void sig_usr2(int signo) {
    printf("SIGUSR2 received\n");
}

int main() {
    sigset_t sigset;
    if (sigemptyset(&sigset) < 0) {
        err_sys("sigemptyset error");
    }

    if (sigaddset(&sigset, SIGUSR1) < 0) {
        err_sys("sigaddset error");
    }

    if (sigprocmask(SIG_BLOCK, &sigset, NULL) < 0) {
        err_sys("sigprocmask error");
    }

    pr_mask("signal mask: ");

    if (signal(SIGUSR1, sig_usr1) == SIG_ERR) {
        err_sys("signal error");
    }
    if (signal(SIGUSR2, sig_usr2) == SIG_ERR) {
        err_sys("signal error");
    }

    raise(SIGUSR1);
    raise(SIGUSR2);

    sigdelset(&sigset, SIGUSR1);
    sigaddset(&sigset, SIGUSR2);
    sigprocmask(SIG_SETMASK, &sigset, NULL);
    // sigprocmask(SIG_UNBLOCK, &sigset, NULL);
    // sigprocmask(SIG_BLOCK, &sigset, NULL);
    pr_mask("signal mask: ");

    raise(SIGUSR1);
    raise(SIGUSR2);
}