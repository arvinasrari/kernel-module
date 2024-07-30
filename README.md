
# Kernel Module Projects

This repository contains several kernel modules that demonstrate various aspects of kernel programming. These modules are created by Arvin Asrari.

## Modules

1. `function_redirection.c`: A sample module to check if the function redirection works correctly.
2. `bl_modifier.c`: A kernel module to modify the `bl` instruction in ARM64 architecture for a specific function.
3. `memory_after.c`: A module to print the memory contents of a specified function.
4. `crash.c`: A module to trigger a kernel panic by causing a fault.
5. `functest_bl.c`: A module to test function modification.
6. `debug_before.c`: A module to debug before modification.
7. `debug_after.c`: A module to debug after modification.
8. `abfunction.c`: A module defining functions for testing redirection.
9. `abcfunction.c`: Another module defining functions for testing redirection.

## Scripts

- `run.sh`: A script to push kernel modules to a device and run them.

## Requirements

- Linux kernel development environment
- ARM64 architecture (for `bl_modifier.c`)
- Root privileges

## Usage

### Step 1: Clone this repository
```bash
git clone https://github.com/arvinasrari/kernel-module-projects.git
cd kernel-module-projects
```

### Step 2: Build the kernel modules
```bash
make
```

### Step 3: Insert and test the modules

1. **Function Redirection**:
    ```bash
    sudo insmod function_redirection.ko
    dmesg | grep "Inside function redirection"
    sudo rmmod function_redirection
    ```

2. **BL Modifier**:
    ```bash
    sudo insmod bl_modifier.ko
    dmesg | grep "ARVIN_DEBUG"
    sudo rmmod bl_modifier
    ```

3. **Memory After**:
    ```bash
    sudo insmod memory_after.ko
    dmesg | grep "Memory contents"
    sudo rmmod memory_after
    ```

4. **Trigger Crash**:
    ```bash
    sudo insmod crash.ko
    ```

    *Note: The `crash` module will trigger a kernel panic. Ensure you have saved all your work and are prepared for a system reboot.*

### Step 4: Use the run script
```bash
chmod +x run.sh
./run.sh
```

## Note

- Ensure you have the necessary permissions to insert and remove kernel modules on your system.
- Adjust the `Makefile` if you are using a non-standard kernel build directory.

## License

This project is licensed under the GPL License.

## Author

- Arvin Asrari
