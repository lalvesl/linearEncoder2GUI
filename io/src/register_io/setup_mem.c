#include "../binder.h"

i32 mem_fd;
void *gpio_map;

void setup_io(volatile unsigned **gpio)
{
    if ((mem_fd = open("/dev/mem", O_RDWR | O_SYNC)) < 0)
    {
        printf("can't open /dev/mem \n");
        exit(-1);
    }

    gpio_map = mmap(
        NULL,
        BLOCK_SIZE,
        PROT_READ | PROT_WRITE,
        MAP_SHARED,
        mem_fd,
        GPIO_BASE);

    close(mem_fd);

    if (gpio_map == MAP_FAILED)
    {
        printf("mmap error %d\n", gpio_map);
        exit(-1);
    }

    (*gpio) = (volatile unsigned *)gpio_map;
}