#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int 
main(int argc,char *argv[])
{
  if(argc<1){
    fprintf(2,"Usage:Pingpong\n");
    exit(1);
  }
  
  int fd[2];
  pipe(fd);

  if(fork()==0){
    close(fd[0]);
    int child_pid = getpid();
    write(fd[1],&child_pid,sizeof(child_pid));
    close(fd[1]);
    exit(0);
  }else{
    close(fd[1]);
    int child_pid;
    read(fd[0],&child_pid,sizeof(child_pid));
    int parant_pid = getpid();
    printf("%d: received ping\n",child_pid);
    printf("%d: received pong\n",parant_pid);
    close(fd[0]);
  }
  exit(0);
}
