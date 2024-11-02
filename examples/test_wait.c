#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "mytool.h"

int main() {
    int status;
    pid_t pid;
    
    /*===================================*/
    pid = fork();
    if (pid < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        // child process
        exit(1); // normal termination, exit status = 1
    }
    printf("created subprocess %d\n", pid);
    pid = wait(&status); // wait for a child to die
    if (pid == -1) {
        err_sys("wait error");
    }
    printf("subprocess %d is dead\n", pid);
    pr_exit(status);
    /*===================================*/

    /*===================================*/
    pid = fork();
    if (pid < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        // child process
        abort();  // generate SIGABRT
    }
    printf("created subprocess %d\n", pid);
    pid = wait(&status);
    if (pid == -1) {
        err_sys("wait error");
    }
    printf("subprocess %d is dead\n", pid);
    pr_exit(status);
    /*===================================*/

    /*===================================*/
    pid = fork();
    if (pid < 0) {
        err_sys("fork failed");
    } else if (pid == 0) {
        int t;
        t /= 0;  // generate SIGFPE
    }
    printf("created subprocess %d\n", pid);
    pid = wait(&status);
    if (pid == -1) {
        err_sys("wait error");
    }
    printf("subprocess %d is dead\n", pid);
    pr_exit(status);
    /*===================================*/
}