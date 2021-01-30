#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "pstat.h"
#include "sysfunc.h"
#include "spinlock.h"
#include "vm.h"

struct public_ptable {
  struct spinlock lock;
  struct proc proc[NPROC];
};

struct public_ptable ptable = {0}; //edited

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

//edited
int 
sys_getyear(void) 
{
return 1975;
} 

int
sys_getReadCount(void)
{
return myproc()->readid;
}

// edited ----------------------------------------------------------------------------
int
sys_setTickets(void)
{
  int n;				// no. of tickets
  if(argint(0, &n) < 0 || n < 1)	// to check if argument is fitched
  {
	myproc()->tickets = 1;		// if not or n < 1 ==> let proc_ticket = 1 (Default) -- myproc() to access current process
	return -1;			// refer to Default no. of tickets
  }
  else
  {
	myproc()->tickets = n;		// if fetched ==> proc_ticket = n
	return 0;			// refer to chosen no. of tickets 
  }  
}

int
sys_getpinfo(void)
{
  acquire(&ptable.lock);
  struct pstat* procstat;
  struct proc* p;
  if(argint(0, (int*)(&procstat)) < 0) {
    return -1;
  }

  for(p = ptable.proc; p != &(ptable.proc[NPROC]); p++) {
    int index = p - ptable.proc;
    if(p->state != UNUSED) {
	procstat->pid[index] = p->pid;
        procstat->ticks[index] = p->ticks;
	procstat->tickets[index] = p->tickets;
	procstat->inuse[index] = p->inuse;
	procstat->goldenTicket[index] = p->goldenTicket;
    }
  }
  release(&ptable.lock);
  return 0;
}

int
sys_mprotect(void){
  int d;
  int n = 0;
  if(argint(0, &d)<0 || argint(1, &n)<0)
    return -1;
  return mprotect((void *)d,n);
}

int
sys_munprotect(void){
  int d;
  int n = 0;
  if(argint(0, &d)<0 || argint(1, &n)<0)
    return -1;
  return munprotect((void *)d,n);
}



