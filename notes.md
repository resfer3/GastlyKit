# Linux dynamic linker
Statically linked binaries are compiled together with all dependencies needed for execution. (Not the case)
Dynamically linked binaries use shared libraries located on the operating system. These libraries will be resolved, loaded, and linked at runtime. The linux component that is in charge of this operation is the dynamic linker,
 also known as ld.so or ld-linux.so.*

That's why one linux rootkit works in every distro or flavor of linux.

### Checking the binaries of ls

The ldd command allows us to inspect an ELF's dependencies and shared libraries.
If we execute the command, it clearly says that the ld binary uses libselinux, libc, and libpcre2

In the first line there's a file(which is not a file) called virtual shared object.
And on the last line is the ld.so
- linux-vdso.so.1 -> It's a virtual shared object that doesn't have any physical file on the disk; it's a part 
of the kernel that's exported into every program's address space when it's loaded. It's main purpose is to make more efficient to call system calls. Lookup the manual pages for vdso for more detail [here](https://man7.org/linux/man-pages/man7/vdso.7.html).
-  
`code copy`

```
linux-vdso.so.1 (0x00007ffd0b9b8000)`
libselinux.so.1 => /lib/x86_64-linux-gnu/libselinux.so.1 (0x000077cded9df000)
libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x000077cded600000)
libpcre2-8.so.0 => /lib/x86_64-linux-gnu/libpcre2-8.so.0 (0x000077cded945000)
/lib64/ld-linux-x86-64.so.2 (0x000077cdeda45000)`
```

Next, we run strace ls and check the libraries that get loaded into memory upon execution.


```
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libselinux.so.1", O_RDONLY|O_CLOEXEC) = 3
```

We can see that libselinux.so.1 and libc get executed. But also, earlier, ld.so.preload gets executed.

### LD_PRELOAD
LD_PRELOAD holds a list of user-specified, ELF-shared objects and it enables users to load these shared objects into
a process's address space before any other shared library and prior to the execution of the program itself.
We can write to the /etc/ld.so.preload or utilize the LD_PRELOAD environment variable.

Why it's more beneficial to use the LD_PRELOAD environment variable, instead of accessing the file /etc/ld.so.preload?
1 - You don't have to be root to put the library in through LD_PRELOAD
2 - Libraries defined by LD_PRELOAD are loaded prior to those in /etc/ld.so.preload

Now, if you have root access, you should put it in /etc/ld.so.preload.
We will be trying it from a root perspective.



