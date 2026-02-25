#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

__attribute__((noreturn))
void sieve(int pleft[2]) 
{
  int prime;
  if(read(pleft[0],&prime,sizeof(prime))==0){
    close(pleft[0]);
    exit(0);
  }
  printf("prime %d\n",prime);

  int pright[2];
  pipe(pright);

  if(fork()==0){
    close(pright[1]);
    close(pleft[0]);
    sieve(pright);
  }else{
    close(pright[0]);
    int num;
    while(read(pleft[0],&num,sizeof(num))>0){
      if(num%prime!=0){
        write(pright[1],&num,sizeof(num));
      }
    }
    close(pleft[0]);
    close(pright[1]);
    wait(0);
    exit(0);
  }
}
int 
main(int argc, char *argv[])
{
  int init_pipe[2];
  pipe(init_pipe);

  if(fork()==0){
    close(init_pipe[1]);
    sieve(init_pipe);
  }else{
    close(init_pipe[0]);
    for(int i=2;i<=35;i++){
      write(init_pipe[1],&i,sizeof(i));
    }
    close(init_pipe[1]);
    wait(0);
    exit(0);
  }
}
