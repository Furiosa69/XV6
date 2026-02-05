#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{

  if(argc < 2){
    fprintf(2,"Usage:Sleep N senconds\n");
    exit(1);
  }

  int n = atoi(argv[1]);

  if(sleep(n)<0){
    fprintf(2,"sleep: error\n");
    exit(1);
  }else{
    fprintf(1,"(nothing happens for a little while)\n");
  }

  exit(0);
}
