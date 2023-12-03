// #include <stdio.h>
// #include <malloc.h>
// #include <pthread.h>

#include <stdio.h>

//necessery for main access and read memory (and registers)
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>


#ifndef types
#define types
#include "types.h"
#endif

#ifndef tools
#define tools 1
#include "tools.c"
#endif
