#include "kernel/types.h"
#include "user.h"

#include "stddef.h"

int main(int args,char*argv[]){
    /* 子进程读管道，父进程写管道 */
    char buf1[10]="ping";
    char buf2[10]="pong";
    int p[2];
    int ret = pipe(p); /*正常创建后，p[1]为管道写入端，p[0]为管道读出端*/ 
    if(ret<0){
        printf("Pipe error\n");
        ret++;
        exit(-1);
    }
    int pid = fork();
    if(pid<0){
        printf("fork error\n");
        exit(-1);
    }
    else if (pid > 0) { 
        /* 父进程 */
        char dad[10];
        write(p[1],buf1,sizeof(buf1));
        close(p[1]); // 写入完成，关闭写端
        wait(0);

        read(p[0],dad,sizeof(dad));
        if(strcmp(dad,"pong")==0){
            printf("%d: received %s\n",getpid(),dad);
        }
        close(p[0]);
        exit(0);
    } else if (pid==0) { 
        /* 子进程 */
        char child[10];
        read(p[0],child,sizeof(child));
        if(strcmp(child,"ping")==0){
            printf("%d: received %s\n",getpid(),child);
        }
        close(p[0]); // 读取完成，关闭读端
        write(p[1],buf2,sizeof(buf2));
        close(p[1]);
    }
    exit(0);
}