#include "kernel/types.h"
#include "kernel/pinfo.h"
#include "user/user.h"

#define MAXPROCS 64

static char *states[] = {
  "UNUSED", "USED", "SLEEPING", "RUNNABLE", "RUNNING", "ZOMBIE"
};

// print s, then spaces until w characters have been written
static void
pad(char *s, int w)
{
  int len = strlen(s);
  printf("%s", s);
  for(int i = len; i < w; i++)
    printf(" ");
}

// print integer v, then spaces until w characters have been written
static void
padint(int v, int w)
{
  char buf[16];
  int i = 0, neg = 0;

  if(v < 0){
    neg = 1;
    v = -v;
  }
  char tmp[16];
  int t = 0;
  do {
    tmp[t++] = '0' + (v % 10);
    v /= 10;
  } while(v > 0);
  if(neg)
    buf[i++] = '-';
  while(t > 0)
    buf[i++] = tmp[--t];
  buf[i] = 0;
  pad(buf, w);
}

int
main(int argc, char *argv[])
{
  struct pinfo info[MAXPROCS];
  int n = getprocs(info, MAXPROCS);

  if(n < 0){
    printf("ps: getprocs failed\n");
    exit(1);
  }

  pad("PID", 6);
  pad("PPID", 6);
  pad("STATE", 11);
  pad("SIZE", 8);
  printf("NAME\n");

  for(int i = 0; i < n; i++){
    char *s = "UNKNOWN";
    if(info[i].state >= 0 && info[i].state < 6)
      s = states[info[i].state];
    padint(info[i].pid, 6);
    padint(info[i].ppid, 6);
    pad(s, 11);
    padint((int)info[i].sz, 8);
    printf("%s\n", info[i].name);
  }
  exit(0);
}
