#include "kernel/types.h"
#include "user/user.h"

int
main(void)
{
  for(int i = 0; i < 3; i++){
    if(fork() == 0){
      for(volatile int k = 0; k < 2000000000; k++)
        ;
      printf("child %d (pid %d) done\n", i, getpid());
      exit(0);
    }
  }
  for(int i = 0; i < 3; i++)
    wait(0);
  exit(0);
}
