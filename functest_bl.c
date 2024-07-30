#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/kallsyms.h>
#include <asm/cacheflush.h>
#include <asm/insn.h>
#include <linux/mm.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Arvin");
MODULE_DESCRIPTION("Modify function call within the kernel.");

extern void linker_func(void); 

static int __init bl_modifier_init(void) {
    pr_info("bl_modifier Initialization\n");

    unsigned long linker_func_addr = (unsigned long)kallsyms_lookup_name("linker_func");
    unsigned long test_function_addr = (unsigned long)kallsyms_lookup_name("test_function");

    if (!linker_func_addr || !test_function_addr) {
        pr_alert("Failed to find one or more functions\n");
        return -1;
    }

    pr_info("Address of linker_func: %px, test_function: %px\n", (void *)linker_func_addr, (void *)test_function_addr);

    unsigned long bl_addr = linker_func_addr + 0xc; // Example offset, adjust as necessary
    pr_info("Address for modification: %px\n", (void *)bl_addr);

    long offset = bl_addr - test_function_addr;
    if (offset < -(1 << 25) || offset >= (1 << 25)) {
        pr_alert("Offset is out of range for a `bl` instruction\n");
        return -1;
    }

    // Assuming AArch64 architecture for instruction encoding
    u32 bl_instruction = aarch64_insn_gen_branch_imm(bl_addr, test_function_addr, AARCH64_INSN_BRANCH_LINK);
    pr_info("New BL instruction: 0x%08x\n", bl_instruction);
    set_memory_rw(PAGE_ALIGN(bl_addr) - PAGE_SIZE, 1);
    *(u32 *)(bl_addr) = bl_instruction;
    set_memory_ro(PAGE_ALIGN(bl_addr) - PAGE_SIZE, 1);

    flush_icache_range(bl_addr, bl_addr + sizeof(bl_instruction));
    pr_info("Instruction at %px modified to branch to test_function.\n", (void *)bl_addr);

    linker_func();
        pr_info("linker_func called\n");


    return 0;
}

static void __exit bl_modifier_exit(void) {
    pr_info("Module unloaded\n");
}

module_init(bl_modifier_init);
module_exit(bl_modifier_exit);
