#ifndef _PINFO_H_
#define _PINFO_H_

struct pinfo {
  int pid;
  int ppid;
  int state;
  uint64 sz;
  char name[16];
};

#endif
