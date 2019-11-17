#include <linux/init.h>
#include <linux/module.h>

int init_module_fun(void){
	printk(KERN_ALERT "Inside the %s function!\n",__FUNCTION__);
	return 0;
}

void exit_module_fun(void){
	printk(KERN_ALERT "Inside the %s function!\n",__FUNCTION__);
}

module_init(init_module_fun);
module_exit(exit_module_fun);
