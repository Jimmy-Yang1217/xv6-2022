// Lab Xv6 and Unix utilities
// xargs.c

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

#define MAXN 100


int main(int argc, char *argv[])
{
    // 如果参数个数小于 2
    if (argc < 2) {
        exit(1);
    }
    // 存放子进程 exec 的参数
    char * argvs[MAXARG];
    char buf[MAXN] = {"\0"};
    // 索引
    int j = 0;
    // 略去 xargs ，用来保存命令行参数
    for (int i = 1; i < argc; ++i) {
        argvs[j++] = argv[i];
    }
    while(read(0, buf, MAXN)) {
        // 临时缓冲区存放追加的参数
		char temp[MAXN] = {"\0"};
        // xargs 命令的参数后面再追加参数
        argvs[j] = temp;
        // 内循环获取追加的参数并创建子进程执行命令
        for(int i = 0; i < strlen(buf); ++i) {
            if(buf[i] == '\n') {
                int pid =fork();
                if (pid == 0) {
                    exec(argv[1], argvs);
                }
                wait(0);
            }   else {
                temp[i] = buf[i];
            }
        }
    }
    exit(0);
}
