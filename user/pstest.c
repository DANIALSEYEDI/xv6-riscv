#include "kernel/types.h"
#include "kernel/pinfo.h"
#include "user/user.h"

static char *states[] = {
  "UNUSED", "USED", "SLEEPING", "RUNNABLE", "RUNNING", "ZOMBIE"
};

static void
show(int max)
{
  struct pinfo info[64];
  int n = getprocs(info, max);

  printf("getprocs(max=%d) returned %d\n", max, n);
  for(int i = 0; i < n; i++){
    char *s = "UNKNOWN";
    if(info[i].state >= 0 && info[i].state < 6)
      s = states[info[i].state];
    printf("  pid=%d ppid=%d state=%s name=%s\n",
           info[i].pid, info[i].ppid, s, info[i].name);
  }
}

int
main(void)
{
  int mypid = getpid();
  printf("parent pid = %d\n", mypid);

  for(int i = 0; i < 3; i++){
    int pid = fork();
    if(pid < 0){
      printf("fork failed\n");
      exit(1);
    }
    if(pid == 0){
      if(i % 2 == 0)
        pause(200);                    // sleeping child
      else
        for(volatile int k = 0; k < 100000000; k++)
          ;                            // busy child
      exit(0);
    }
    printf("created child pid=%d (%s)\n", pid, i % 2 == 0 ? "sleeping" : "busy");
  }

  pause(50);   // let the children start

  printf("--- max = 64 (more than process count) ---\n");
  show(64);

  printf("--- max = 2 (less than process count) ---\n");
  show(2);

  printf("--- max = 0 (invalid) ---\n");
  show(0);

  for(int i = 0; i < 3; i++)
    wait(0);

  exit(0);
}
