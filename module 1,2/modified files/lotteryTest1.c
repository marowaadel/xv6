#include "types.h"
#include "stat.h"
#include "user.h"
#include "pstat.h"
#include "rand.h"


void spin() {
    unsigned x = 0;
    unsigned y = 0;
    //int pid = getpid();

    while (x < 100000) {
        y = 0;
        while (y < (10000)) {
            y++;
        }
        x++;
    }
}


//void printpinfo(void)
void printpinfo(int pid)
{
	struct pstat pi = {0};
	getpinfo(&pi);
	int i;
    for (i = 0; i < NPROC; i++) {        
	if(pi.tickets[i]==0)
		continue;	
	printf(0, "PID: %d | Ticks: %d | Tickets: %d | Inuse: %d\n", /*pid*/pi.pid[i],pi.ticks[i], pi.tickets[i],pi.inuse[i]);
	
        
    }
    //printf(0, "\n\n");
}

int
main(int argc, char *argv[])
{ 
    	fork();
    	wait();
    	setTickets(10);
    	//printf(0, "Process with PID %d finished!\n", getpid());
	printpinfo(getpid());        
	printf(0, "\n\n");
    	
    	
    	fork();
    	wait();
    	setTickets(20);
    	//printf(0, "Process with PID %d finished!\n", getpid());
	printpinfo(getpid());        
	printf(0, "\n\n");
    	
    	
    	fork();
    	wait();
    	setTickets(30);
    	//printf(0, "Process with PID %d finished!\n", getpid());
	printpinfo(getpid());        
	exit();
		   
    	
}

