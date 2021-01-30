#include "types.h"
#include "stat.h"
#include "user.h"
#include "pstat.h"
#include "rand.h"


void printpinfo(int pid)
{
	struct pstat pi = {0};
	getpinfo(&pi);
	int i;
    for (i = 0; i < NPROC; i++) {        
	if(pi.pid[i] == pid){ //pi.tickets[i]==0 --> continue			
		printf(0, "PID: %d | Ticks: %d | Tickets: %d | Inuse: %d\n", pi.pid[i],pi.ticks[i], pi.tickets[i],pi.inuse[i]);
				
	}
        
    }
    //printf(0, "\n\n");
}


int
main(int argc, char *argv[])
{
  
  
  int nTest=50;
  int j=0;
  while(nTest>j){    
	  printf(0, "\n\n:::: Test %d ::::\n", ++j);
	  int child = fork();
	  
	  if(child==0){//child 1	
		setTickets(10);
		printpinfo(getpid());
		exit();
	  }
	  else if(child>0){//parent 
		wait();// to wait child 1
		child = fork();
		
		if(child==0){//child 2	
		setTickets(20);
		printpinfo(getpid()); 
		exit();
	  	}
	  	wait();// to wait child 2
	  	//now in parent        
		setTickets(30);
		printpinfo(getpid()); 
		//exit();
	  }
	  
  }  
    /*while(nTest>j)
    {     	
    	sleep(100);
    	getpinfo(&pi);
    	printf(0, "\n\n:::: Test %d ::::\n", ++j);
    	for (int i = 0; i < NPROC; i++){
	if (pi.tickets[i]==0)
	continue;
    	printf(0, "PID: %d | Ticks: %d | Tickets: %d | Inuse: %d\n", pi.pid[i],pi.ticks[i], pi.tickets[i],pi.inuse[i]);  	
    	}
    } */
    exit();
    
       
}

