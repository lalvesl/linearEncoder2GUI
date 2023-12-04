#include "../binder.h"

#include <math.h>

void reverse(char *str, int len)
{
    int i = 0, j = len - 1, temp;
    while (i < j)
    {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}

int intToStr(int x, char str[], int d)
{
    int i = 0;
    while (x)
    {
        str[i++] = (x % 10) + '0';
        x = x / 10;
    }
    while (i < d)
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
        return -1;
    }

    char data[DATA_BLOCK_SIZE];

    for (int i = 0;; i++)
    {

        intToStr(position, data, DATA_BLOCK_SIZE);
        fseek(f, 0, SEEK_SET);
        fwrite(data, DATA_BLOCK_SIZE, 1, f);
        usleep(1000 * 20);
    }

    fclose(f);
}
