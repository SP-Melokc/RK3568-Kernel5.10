#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/melokc_log.h>
#include <linux/module.h>
#include <linux/kthread.h>

static int dp_thread(void *data)
{
	melokc_pr("dp_thread running\n");
	while(!kthread_should_stop()){
		melokc_pr("before schedule...\n");
		set_current_state(TASK_INTERRUPTIBLE);
		schedule_timeout(msecs_to_jiffies(20000));
		dump_stack();
	}
	return 0;
}

static int __init dp_init(void)
{
	struct task_struct *dp;
	melokc_pr("Initialize dump task\n");
	dp = kthread_run(dp_thread,NULL,"dp_thread");
	if(IS_ERR(dp))
		melokc_pr("create dp_thread fail!\n");
	return 0;
}


static void __exit dp_exit(void)
{
	melokc_pr("Exit dump task\n");
}
module_init(dp_init);
module_exit(dp_exit);
MODULE_AUTHOR("Melokc");
MODULE_LICENSE("GPL");
