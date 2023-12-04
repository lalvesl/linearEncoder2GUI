#include "../binder.h"

void io_fake()
{
    int fake_position = 0;

    for (int i = 0;; i++)
    {
        fake_position++;
        //usleep(1000 * 30);
        if (i % 1000000)
        {
            pthread_mutex_lock(&stopper);
            position = fake_position;
            pthread_mutex_unlock(&stopper);
        }
    }
}