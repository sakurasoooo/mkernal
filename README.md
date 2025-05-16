## Linux Kernel Modules for Process Information

This repository contains Linux kernel modules designed to provide custom system calls for retrieving information about running processes.

### Project Overview

This project demonstrates how to create and insert custom system calls into the Linux kernel. It includes two main kernel modules:

1.  **Process Tree Lister (`dqyps.cpp`)**: This module implements a system call (ID 223) that traverses the entire process tree starting from the `init` process and collects information (Process ID and depth in the tree) for each process. This information is then made available to user-space applications.
2.  **Process State Reporter (`hello.c`)**: This module implements a system call (`sys_hello`) that iterates through all running processes, logs their current state (e.g., Runnable, Sleeping, Blocked, Terminated), and provides a count for each state. It also displays the total number of processes and the current system time.

A user-space test application (`test.cpp`) is provided to demonstrate how to invoke the custom system call implemented in `dqyps.cpp` and display the retrieved process tree.

### Files in the Repository

  * **`dqyps.cpp`**: Source code for the kernel module that implements a system call to list the process tree. It includes logic to modify the system call table and traverse process structures.
  * **`hello.c`**: Source code for the kernel module that implements a system call to report the state of all processes.
  * **`test.cpp`**: A C++ user-space program to test the system call provided by `dqyps.cpp`. It calls the system call and prints the process tree structure.
  * **`makefile`**: A makefile currently configured to build the `hello.o` kernel module from `hello.c`.

### Functionality

#### Process Tree (`dqyps.cpp` and `test.cpp`)

  * The `dqyps.cpp` module registers a new system call (number 223).
  * When this system call is invoked, it populates an array of `process` structures, where each structure holds a `pid` (process ID) and `depth` (its level in the process hierarchy).
  * The `test.cpp` application calls this system call and then iterates through the received array to print the process tree in a hierarchical format.

#### Process State Summary (`hello.c`)

  * The `hello.c` module registers a `sys_hello` system call.
  * When invoked, this system call iterates through all tasks in the system.
  * It prints the name, PID, and state of each process to the kernel log (viewable with `dmesg`).
  * It also prints a summary count of processes in different states (Runnable, Sleeping, Blocked, Terminated) and the current time.

### Building and Usage

**Prerequisites:**

  * Linux Kernel Headers: You will need the kernel headers corresponding to your running kernel to build these modules. These can typically be installed via your distribution's package manager (e.g., `linux-headers-$(uname -r)` on Debian/Ubuntu based systems).
  * A C/C++ compiler (like GCC/G++) and `make`.

**Building the `hello` module:**

The provided `makefile` is set up to build `hello.o`.

```bash
make
```

This will produce `hello.o`.

**Building the `dqyps` module and `test` application:**

You will need to adapt the `makefile` or use manual compilation commands for `dqyps.cpp` and `test.cpp`.

  * **To compile `dqyps.cpp` (example command, might need adjustments for your kernel version):**

    ```bash
    # Ensure you have the necessary kernel build tools and headers
    # The makefile syntax for kernel modules is specific.
    # You would typically add 'obj-m += dqyps.o' to a makefile and run make.
    # For a standalone command (less common for kernel modules):
    # gcc -D__KERNEL__ -DMODULE -I/lib/modules/$(uname -r)/build/include -c dqyps.cpp -o dqyps.o
    ```

    It's recommended to create a proper Kbuild makefile for this.

  * **To compile `test.cpp`:**

    ```bash
    g++ test.cpp -o test
    ```

**Loading and Unloading Kernel Modules:**

  * Load a module:
    ```bash
    sudo insmod <module_name>.ko # (e.g., sudo insmod hello.ko or sudo insmod dqyps.ko)
    ```
  * Unload a module:
    ```bash
    sudo rmmod <module_name>
    ```
  * View kernel messages (to see output from `printk`):
    ```bash
    dmesg
    ```

**Running the `test` application:**

After compiling `test.cpp` to `test` and loading the `dqyps.ko` module:

```bash
./test
```

This will print the process tree.

### Notes

  * Modifying the system call table and working with kernel modules requires root privileges and can destabilize your system if not done correctly. Proceed with caution.
  * The hardcoded system call table address (`0xc15b3000` in `dqyps.cpp`) is highly system-specific and will likely not work on different kernel versions or configurations. Modern approaches to adding system calls are generally preferred over direct modification of the table for security and portability reasons.
  * The code mentions "lihuan" in comments, possibly indicating the original author.
