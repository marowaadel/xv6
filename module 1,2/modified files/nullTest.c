#include "types.h"
#include "stat.h"
#include "user.h"

int main(void) 
{  
  printf(1,"=================================\n");
  printf(1,"Trying to derefrence NULL pointer\n");
  printf(1,"Watch this,I'll trap now\n");
  int *p = 0;
  printf(1,"This statement will not be printed --> Null Pointer = %p\n",*p);
    exit();
}

/*main(int argc, char *argv[])
{
  
  printf(1,"Trying to derefrence NULL pointer\n");
  printf(1,"Watch this,I'll trap now\n");
  int *p = 0;
  printf(1,"This statement will not be printed --> Null Pointer = %p\n",*p);*/
