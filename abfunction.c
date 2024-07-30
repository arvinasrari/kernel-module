#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Arvin");

void functionA(void);
void functionB(void);


void functionB(void) {
    pr_info("Inside Function B\n");
    pr_info("%s(): Inside, redirection successful!\n", __func__);
}


void functionA(void) {
    pr_info("Inside Function A\n");
    // _mcount 0xc
}
EXPORT_SYMBOL_GPL(functionA);

static int __init my_module_init(void) {
    pr_info("Module Initialization\n");
    return 0;
}

static void __exit my_module_exit(void) {
    pr_info("Module Exit\n");
}

module_init(my_module_init);
module_exit(my_module_exit);

