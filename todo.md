# TODO

This project i feel it's gonna be upgraded for eternity if i don't put some sort of stop to it at some point.
So, at first the goal of the first implementation is to make it a little usable. But probably not useful for the 
real world.
Classic LD_PRELOAD jynxkit clone

# NOTE TO SELF -> Don't just go and copy the source code, dumbass, that's not the POINT!

- hook:
  ->readdir() [to hide from ls, our log of ssh file transfers or stuff]
  ->opendir()
  ->open()
  ->stat()
  ->unlink()

  The following hooks are taken from a jynxkit research, only examples of functions to hook.
  - accept()
  - access()
  - fxstat/fxstat64
  - lxstat/lxstat64
  - open
  - rmdir
  - unlink/unlinkat
  - xstat/xstat64
  - write
  - fopen/fopen64
  - fdopendir/opendir
  - readdir/readdir64

  



- in the bash script for installing make it for, #!/bin/bash 
