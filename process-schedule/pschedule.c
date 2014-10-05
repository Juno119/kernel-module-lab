#include <linux/module.h>
#include <linux/version.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/wait.h>

static DECLARE_WAIT_QUEUE_HEAD(schedtest_waitq);

static struct {
        int trigger;
} trigger_data;

static int pschedule_proc_show(struct seq_file *m, void *v) {
	trigger_data.trigger = 1;
//	seq_printf(m,"Sleep... (pid=%d, cmd:%s)\n", current->pid, current->comm);
	printk("Sleep... (pid=%d, cmd:%s)\n", current->pid, current->comm);
	wait_event_interruptible(schedtest_waitq, trigger_data.trigger < 1);
	printk("Wake up! (pid=%d, cmd:%s)\n", current->pid, current->comm);
	seq_printf(m,"Wake up! (pid=%d, cmd:%s)\n", current->pid, current->comm);
	return 0;
}

static int pschedule_proc_open(struct inode *inode, struct  file *file) {
	return single_open(file, pschedule_proc_show, NULL);
}

static ssize_t proc_schedtest_write(struct file *file, const char *buffer,
				    size_t count, loff_t *data)
{
	printk("Wake up everybody (pid=%d, cmd:%s)\n",
	       current->pid, current->comm);
	wake_up(&schedtest_waitq);
	trigger_data.trigger = 0;
	return count;
}

static const struct file_operations pschedule_proc_fops = {
	.owner = THIS_MODULE,
	.open = pschedule_proc_open,
	.read = seq_read,
	.write = proc_schedtest_write,
	.llseek = seq_lseek,
	.release = single_release,
};

static int __init schedtest_init(void)
{
	printk("Schedest module init\n");
	proc_create("pschedule_proc", 0, NULL, &pschedule_proc_fops);
	return 0;
}

static void __exit schedtest_exit(void)
{
	printk("Schedtest module removed\n");
	remove_proc_entry("pschedule_proc", NULL);
}

MODULE_LICENSE("GPL");
module_init(schedtest_init);
module_exit(schedtest_exit);
