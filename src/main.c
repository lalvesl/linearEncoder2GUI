#include "binder.h"
#include "io/io.c"
#include "fs_stream/fs_stream.c"

int main()
{
    void *funcs[] = {&fs_stream, &io};

    u8 funcsSize = ((sizeof funcs) / (sizeof(void *)));
    pthread_t *threads = (pthread_t *)calloc((sizeof(pthread_t)), funcsSize);

    if (pthread_mutex_init(&stopper, NULL) != 0)
    {
        printf("Shared memory err\n");
        exit(-1);
    }

    for (u8 i = 0; i < funcsSize; i++)
    {
        pthread_create(&threads[i], NULL, funcs[i], NULL);
    }

    for (u8 i = 0; i < funcsSize; i++)
    {
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&stopper);
    sleep(i32MAX);
}