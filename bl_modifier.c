#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/kallsyms.h>
#include <asm/cacheflush.h>
#include <asm/insn.h>
#include <linux/mm.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Arvin");
MODULE_DESCRIPTION("Modify __do_kernel_fault bl");


static int __init bl_modifier(void) {
    pr_info("bl_modifier Initialization\n"); 


    // Finding the memory address of the kernel page fault handler & the custom function in the kernel. 
    unsigned long __do_kernel_fault_function_addr = (unsigned long)kallsyms_lookup_name("__do_kernel_fault.part.6");
    unsigned long linker_func_addr = (unsigned long)kallsyms_lookup_name("linker_func");

    //printk("[ARVIN_DEBUG] checkpoint 1\n");
    //return 0;


    
    // check if these functions exist 
    
    if (!__do_kernel_fault_function_addr || !linker_func_addr) {
        pr_alert("Failed to find one or more functions\n");
        return -1;
    }

    pr_info("Address of __do_kernel_fault: %px\n", (void *)__do_kernel_fault_function_addr);
    pr_info("Address of bl_modifier: %px\n", (void *)linker_func_addr);

    //printk("[ARVIN_DEBUG] checkpoint 2\n");
    //return 0;


    // Add 0x28 (hexadecimal) to the address of the kernel fault handler to reach the bl _mcount.
    unsigned long bl_addr = __do_kernel_fault_function_addr + 0x30;

    long offset = bl_addr - linker_func_addr; 


    pr_info("Fixed offset for BL instruction: %ld (0x%lx)\n", offset, offset);

    //printk("[ARVIN_DEBUG] checkpoint 3\n");
    //return 0;

    //check if offset is not out of the range for bl 
    if (offset < -(1 << 25) || offset >= (1 << 25)) {
        pr_alert("Offset is out of range for a `bl` instruction\n");
        return -1;
    }




    // Encode the `bl` instruction with the offset
    u32 bl_instruction = aarch64_insn_gen_branch_imm(bl_addr, linker_func_addr, AARCH64_INSN_BRANCH_LINK);

    pr_info("New BL instruction: 0x%08x\n", bl_instruction);

    //printk("[ARVIN_DEBUG] checkpoint 4 \n");
    //return 0;


    // Make the page writable
    //set_memory_rw(PAGE_ALIGN(bl_addr) - PAGE_SIZE, 1);
    //set_memory_rw(PAGE_ALIGN(bl_addr), 1);

    // Patch the `bl` instruction
    *(u32 *)(bl_addr) = bl_instruction;
    printk("[ARVIN_DEBUG] the `bl` instruction patched  \n");
    //return 0;
    // Flush the instruction cache
    flush_icache_range(bl_addr, bl_addr + sizeof(bl_instruction));

    // Revert the page to read-only
    //set_memory_ro(PAGE_ALIGN(bl_addr) - PAGE_SIZE, 1);


    return 0; 
}


static void __exit bl_modifier_exit(void) {
    pr_info("Module unloaded\n");
}


module_init(bl_modifier);
module_exit(bl_modifier_exit);



/*
//arvin2
	//static int __init linker_func(void) __attribute__((unused));
	//static void (*hook_ptr)(void);
	static int __init linker_func(void) {
    pr_emerg("inside linker_func");
	//unsigned long addr = kallsyms_lookup_name("function_redirection");
	
	unsigned long hook_addr = (unsigned long)kallsyms_lookup_name("hook_dest");
	    hook_ptr = (void (*)(void)) hook_addr;
    
    printk("Address of hook_dest: %px\n", (void *)hook_addr);
    
    // Call the function through the function pointer
    hook_ptr();
	//unsigned long addr = kallsyms_lookup_name("hook_dest");
    //void (*func_ptr)(void);
	
	//printk("Address hook_dest %px\n", (void *)addr);
*/
/*
    if (addr == 0) {
        pr_alert("hook_dest not found\n");
        return -ENOENT;
    }

    func_ptr = (void (*)(void)) addr;

    func_ptr();
*/
/*
    return 0;
}
*/