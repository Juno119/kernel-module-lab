#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/proc_fs.h>
#include <linux/interrupt.h>
#include <asm/uaccess.h>
#include <linux/seq_file.h>

MODULE_LICENSE("Dual BSD/GPL");

struct timer_list timer1;

int i;

void timer1_routine(unsigned long data)
{
	printk(KERN_ALERT"Inside Timer Routine count-> %d data passed %ld\n",i++,data);
	mod_timer(&timer1, jiffies + HZ); /* restarting timer */
}


static int timer_module_init(void)
{
	init_timer(&timer1);

	timer1.function = timer1_routine;
	timer1.data = 1;
	timer1.expires = jiffies + HZ; /* 1 second */
	add_timer(&timer1); /* Starting the timer */

	printk(KERN_ALERT"Timer Module loaded\n");
	return 0;
}

static void timer_module_exit(void)
{
	del_timer_sync(&timer1); /* Deleting the timer */

	printk(KERN_ALERT "Timer module unloaded \n");
}

module_init(timer_module_init);
module_exit(timer_module_exit);
