#include <stdio.h>

// necessery for main access and read memory (and registers)
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#include <pthread.h>

#include <malloc.h>

#ifndef enver
#define enver
#include "enver.h"
#endif

#ifndef types
#define types
#include "types.h"
#endif

#ifndef tools
#define tools
#include "tools.c"
#endif

#ifndef global_variables
#define global_variables
#include "global_variables.c"
#endif
