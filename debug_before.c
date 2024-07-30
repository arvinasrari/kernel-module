#include <linux/module.h>
#include <linux/init.h>
#include <linux/kallsyms.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Arvin");
#define INSTRUCTION_COUNT 20 // Number of instructions to print

static int __init print_instructions_init(void) {
    
    unsigned int *instructions;
    int i;

    unsigned long address = (unsigned long)kallsyms_lookup_name("functionA");

    if (!address) {
        pr_alert("functionA not found\n");
        return -ENOENT;
    }

    instructions = (unsigned int *)address;

    pr_info("Instructions at functionA:\n");
    for (i = 0; i < INSTRUCTION_COUNT; i++) {
        pr_info("%p: %08x\n", instructions + i, *(instructions + i));
    }

    return 0; 
}

static void __exit print_instructions_exit(void) {
    pr_info("Module unloaded\n");
}

module_init(print_instructions_init);
module_exit(print_instructions_exit);

