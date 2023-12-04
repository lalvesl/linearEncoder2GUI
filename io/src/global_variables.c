#include "binder.h"

i32 position = 0;

pthread_mutex_t stopper;

char *pathIO = "./mem/io";
