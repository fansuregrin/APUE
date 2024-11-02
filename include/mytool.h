#ifndef MY_TOOL_H
#define MY_TOOL_H

#define BUF_SIZE 1024

/**
 * @brief 打印因系统调用出错而产生的消息，然后终止。
 */
void err_sys(const char *fmt, ...);

/**
 * @brief 打印进程的退出状态
 */
void pr_exit(int status);

#endif // MY_TOOL_H