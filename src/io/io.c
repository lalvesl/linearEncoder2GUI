#include "../binder.h"
#include "setup_mem.c"

volatile unsigned *gpio;

void io()
{
    int g, rep;

    setup_io(gpio);

    int _position = 0;
    int stateA = GET_STATE(A_CHANEL);
    int stateB = GET_STATE(B_CHANEL);
    for (int i = 0;; i++)
    {

        if (stateA != GET_STATE(A_CHANEL))
        {
            stateA = INV_STATE(stateA);
            stateB = GET_STATE(B_CHANEL);
            if (stateA != stateB)
                _position--;
            else
                _position++;
        }
        if (i % 1000000)
        {
            pthread_mutex_lock(&stopper);
            position = _position;
            pthread_mutex_unlock(&stopper);
        }
    }
}
