#include "kernel/types.h"
#include "user.h"

int main(int argc,char* argv[]){
    printf("%s\n,%s\n,%s\n,%s\n,%d\n,%d\n",argv[0],argv[1],argv[2],argv[3],sizeof(*argv),argc);

    if(argc != 2){
        printf("Sleep needs one argument!\n"); //检查参数数量是否正确
        exit(-1);
    }
    int ticks = atoi(argv[1]); //将字符串参数转为整数
    sleep(ticks);              //使用系统调用sleep
    printf("(nothing happens for a little while)\n");
    exit(0); //确保进程退出
}