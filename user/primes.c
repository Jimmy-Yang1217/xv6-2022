#include "kernel/types.h"
#include "user.h"


int main() {
    int p1[2],i;
    int ret1 = pipe(p1); /*正常创建后，p[1]为管道写入端，p[0]为管道读出端*/ 
    if(ret1<0){
        printf("Pipe error\n");
        ret1++;
        exit(-1);
    }
    for(i=2;i<=35;i++){
        write(p1[1],&i,sizeof(i));
    }
    int null = 0;
    write(p1[1],&null,sizeof(null));
    while(1){
        int p2[2],prime,num;
        int ret2 = pipe(p2); /*正常创建后，p[1]为管道写入端，p[0]为管道读出端*/ 
        if(ret2<0){
            printf("Pipe error\n");
            ret2++;
            exit(-1);
        }
        read(p1[0],&prime,sizeof(prime));
        printf("prime %d\n",prime);
        if(read(p1[0],&num,sizeof(num))&&num){
            int pid =fork();
            if(pid<0){
                printf("fork error\n");
                exit(-1);
            }
            else if (pid==0)
            {
                close(p1[0]);
                close(p1[1]);
                p1[0]=p2[0];
                p1[1]=p2[1];
                continue;
            }
            else if (pid>0)
            {
                do{
                    if(num%prime!=0)
                        write(p2[1],&num,sizeof(num));
                }while(read(p1[0],&num,sizeof(num))&&num);
                write(p2[1],&null,sizeof(null));
            }
        }
        close(p1[0]);
        close(p1[1]);
        close(p2[0]);
        close(p2[1]);
        break;
    }
    wait(0);
    exit(0);
}