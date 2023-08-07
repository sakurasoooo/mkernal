#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/init_task.h>
#include <linux/syscalls.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/time.h>
#define for_each_process(p) \
	for (p = &init_task ; (p = next_task(p)) != &init_task ; )
#define task_pid_nr(tsk) ((tsk)->pid)

asmlinkage long sys_hello(void){
	int count=0,count1=0,count2=0,count3=0,count4=0;
	struct task_struct *p;
	long int get_time;
	struct timeval tv;
	for_each_process(p){
		if((p->state)==0){
			printk("%s\t[%d]\tRunnable\n",p->comm,task_pid_nr(p));
			count++;
		}
		else if(p->state==-1){
			printk("%s\t[%d]\tBlocked\n",p->comm,task_pid_nr(p));
			count1++;
		}
		else if(p->state ==1){
			printk("%s\t[%d]\tSleeping\n",p->comm,task_pid_nr(p));
			count2++;
		}
		else if((p->state)>1){
			printk("%s\t[%d]\tTerminated\n",p->comm,task_pid_nr(p));
			count3++;
		}
		count4++;
	}
	do_gettimeofday(&tv);
	get_time = tv.tv_sec;
	printk("Total no.of Process = %d\n",count4);
	printk("Total no.of Running(Runnable) process = %d\n",count);
	printk("Total no.of Sleeping(Runnable) process = %d\n",count2);
	printk("Total no.of Blocked process = %d\n",count1);
	printk("Total no.of Terminated process = %d\n",count3);
	printk("Time: %ld\n",get_time);
	return 0;
}