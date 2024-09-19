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

`ldd /bin/ls output here'




