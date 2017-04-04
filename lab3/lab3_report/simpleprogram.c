#include <stdio.h>
#include "testsyscall.h"

int main(void){

     char buffer0 = (char*) malloc (9000);
     char buffer1 = (char*) malloc (3000);
     char buffer2 = (char*) malloc (2000);
     char buffer3 = (char*) malloc (1000);

     printk("amount free %d",syscall(__NR_get_slob_amt_free));
     printk("amount claimed %d",syscall(__NR_get_slob_amt_claimed));
     return 0;
}
