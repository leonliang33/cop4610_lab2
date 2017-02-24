#include<linux/linkage.h>
#include<linux/sched.h>
/* Leon Liang */
/* COP 4610 Lab 1, Spring 2017*/
struct task_struct *me;
struct task_struct *t;
asmlinkage long sys_cajigas_liang_pinales()
{
	
	for_each_process(me){
		t=me;
		char *stateName;
		do {
			int stateNum = t->state;
			if(stateNum == 0){
				stateName = "INTERRUPTIBLE";
			}else if(stateNum == 1){
				stateName = "RUNNING";			
			}else{
				stateName = "WAITING";			
			}
			printk("PID: %d Name: %s Parent PID: %d state %s\n",t->pid,t->comm,t->parent->pid,stateName);
		}while_each_thread(me, t);
	}
	return 0;

}

