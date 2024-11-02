#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "mytool.h"

static void _err(int errno_, int flag, const char *fmt, va_list args);

void err_sys(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    _err(errno, 1, fmt, args);
    va_end(args);
    exit(EXIT_FAILURE);
}

static void 
_err(int errno_, int flag, const char *fmt, va_list args) {
    char buf[BUF_SIZE];
    int pos = 0, len = BUF_SIZE - 1;
    memset(buf, 0, BUF_SIZE);
    int ret = vsnprintf(buf, len, fmt, args);
    if (ret != -1) {
        pos += (ret < len ? ret : len-1);
    }
    if (pos < BUF_SIZE-1 && flag) {
        len = BUF_SIZE - 1 - pos;
        ret = snprintf(buf + pos, len, ": %s", strerror(errno_));
        if (ret != -1) {
            pos += (ret < len ? ret : len-1);
        }
    }
    strcat(buf + pos, "\n");
    fputs(buf, stderr);
    fflush(NULL);
}