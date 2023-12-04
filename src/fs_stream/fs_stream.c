#include "../binder.h"

#include <math.h>

void reverse(char *str, i32 b_size)
{
    u32 i = 0, j = b_size - 1, temp;
    while (i < j)
    {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}

int intToStr(u32 number, char str[], u32 b_size)
{
    i32 i = 0;
    while (number)
    {
        str[i++] = (number % 10) + '0';
        number = number / 10;
    }
    while (i < (b_size - 1))
        str[i++] = '0';

    reverse(str, i);
    str[i] = '\0';
    return i;
}

#define DATA_BLOCK_SIZE 20

void fs_stream()
{
    char *location = "./mem/io";
    FILE *f = fopen(location, "wb");

    if (f == NULL)
    {
        printf("//Opening failed...%s\n", location);
        exit(-1);
    }

    char data[DATA_BLOCK_SIZE];

    for (u8 i = 0;; i++)
    {

        intToStr(position, data, DATA_BLOCK_SIZE);
        fseek(f, 0, SEEK_SET);
        fwrite(data, DATA_BLOCK_SIZE, 1, f);
        usleep(1000 * 20);
    }

    fclose(f);
}
