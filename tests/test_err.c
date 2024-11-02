#include <fcntl.h>
#include "mytool.h"

int main() {
    int fd = open("do_no_exist", O_RDONLY);
    if (fd < 0) {
        err_sys("open error");
    }
}