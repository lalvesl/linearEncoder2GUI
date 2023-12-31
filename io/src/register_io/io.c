#include "../binder.h"
#include "setup_mem.c"
#include "cpu_afinity.c"

volatile unsigned *gpio;

void io()
{
    i32 g, rep;

    setup_io(&gpio);
    setCPU(2);

    i32 _position = 0;
    i32 stateA = GET_STATE(A_CHANEL);
    i32 stateB = GET_STATE(B_CHANEL);
    i32 stateZ = GET_STATE(Z_CHANEL);
    for (int i = 0;; i++)
    {

        if (stateA != GET_STATE(A_CHANEL))
        {
            usleep(25);
            stateA = INV_STATE(stateA);
            stateB = GET_STATE(B_CHANEL);
            if (stateA != stateB)
                _position++;
            else
                _position--;
        }
        if (stateZ != GET_STATE(Z_CHANEL))
        {
            usleep(25);
            if ((_position % PULSES_TO_Z_CHANGE) > (PULSES_TO_Z_CHANGE / 2))
                _position = (((int)(_position / PULSES_TO_Z_CHANGE)) * PULSES_TO_Z_CHANGE) + PULSES_TO_Z_CHANGE;
            else
                _position = (((int)(_position / PULSES_TO_Z_CHANGE)) * PULSES_TO_Z_CHANGE);
        }
        if (i % 100000)
        {
            pthread_mutex_lock(&stopper);
            position = _position;
            pthread_mutex_unlock(&stopper);
        }
    }
}
