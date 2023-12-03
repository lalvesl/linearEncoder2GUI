//
//  How to access GPIO registers from C-code on the Raspberry-Pi
//  Example program
//  15-January-2012
//  Dom and Gert
//  Revised: 15-Feb-2013

// Access from ARM Running Linux

#include "binder.h"

#define BCM2708_PERI_BASE 0x3F000000
#define GPIO_BASE (BCM2708_PERI_BASE + 0x200000) /* GPIO controller */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <math.h>

#define PAGE_SIZE (4 * 1024)
#define BLOCK_SIZE (4 * 1024)

int mem_fd;
void *gpio_map;

// I/O access
volatile unsigned *gpio;

// GPIO setup macros. Always use INP_GPIO(x) before using OUT_GPIO(x) or SET_GPIO_ALT(x,y)
#define INP_GPIO(g) *(gpio + ((g) / 10)) &= ~(7 << (((g) % 10) * 3))
#define OUT_GPIO(g) *(gpio + ((g) / 10)) |= (1 << (((g) % 10) * 3))
#define SET_GPIO_ALT(g, a) *(gpio + (((g) / 10))) |= (((a) <= 3 ? (a) + 4 : (a) == 4 ? 3  \
                                                                                     : 2) \
                                                      << (((g) % 10) * 3))

#define GPIO_SET *(gpio + 7)  // sets   bits which are 1 ignores bits which are 0
#define GPIO_CLR *(gpio + 10) // clears bits which are 1 ignores bits which are 0

#define GET_GPIO(g) (*(gpio + 13) & (1 << g)) // 0 if LOW, (1<<g) if HIGH
#define GET_STATE(g) (((GET_GPIO(g)) == 0) ? (0) : (1))
#define INV_STATE(v) (((v) == 0) ? (1) : (0))

#define GPIO_PULL *(gpio + 37)     // Pull up/pull down
#define GPIO_PULLCLK0 *(gpio + 38) // Pull up/pull down clock

// Reverses a string 'str' of length 'len'
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

// Converts a given integer x to string str[].
// d is the number of digits required in the output.
// If d is more than the number of digits in x,
// then 0s are added at the beginning.
int intToStr(int x, char str[], int d)
{
  int i = 0;
  while (x)
  {
    str[i++] = (x % 10) + '0';
    x = x / 10;
  }

  // If number of digits required is more, then
  // add 0s at the beginning
  while (i < d)
    str[i++] = '0';

  reverse(str, i);
  str[i] = '\0';
  return i;
}

// Converts a floating-point/double number to a string.
void ftoa(float n, char *res, int afterpoint)
{
  // Extract integer part
  int ipart = (int)n;

  // Extract floating part
  float fpart = n - (float)ipart;

  // convert integer part to string
  int i = intToStr(ipart, res, 0);

  // check for display option after point
  if (afterpoint != 0)
  {
    res[i] = '.'; // add dot

    // Get the value of fraction part upto given no.
    // of points after dot. The third parameter
    // is needed to handle cases like 233.007
    fpart = fpart * pow(10, afterpoint);

    intToStr((int)fpart, res + i + 1, afterpoint);
  }
}

void setup_io()
{
  /* open /dev/mem */
  if ((mem_fd = open("/dev/mem", O_RDWR | O_SYNC)) < 0)
  {
    printf("can't open /dev/mem \n");
    exit(-1);
  }

  /* mmap GPIO */
  gpio_map = mmap(
      NULL,                   // Any adddress in our space will do
      BLOCK_SIZE,             // Map length
      PROT_READ | PROT_WRITE, // Enable reading & writting to mapped memory
      MAP_SHARED,             // Shared with other processes
      mem_fd,                 // File to map
      GPIO_BASE               // Offset to GPIO peripheral
  );

  close(mem_fd); // No need to keep mem_fd open after mmap

  if (gpio_map == MAP_FAILED)
  {
    printf("mmap error %d\n", gpio_map); // errno also set!
    exit(-1);
  }

  // Always use volatile pointer!
  gpio = (volatile unsigned *)gpio_map;

} // setup_io

void printButton(int g)
{
  if (GET_GPIO(g)) // !=0 <-> bit is 1 <- port is HIGH=3.3V
    printf("Button pressed!\n");
  else // port is LOW=0V
    printf("Button released!\n");
}

#define A_CHANEL 16
#define B_CHANEL 26

int main(int argc, char **argv)
{
  int g, rep;

  setup_io();

  char *location = "./mem/io";
  FILE *f = fopen(location, "wb");

  if (f == NULL)
  {
    printf("//Opening failed...%s\n", location);
    return -1;
  }

  int count = 0;
  int stateA = GET_STATE(A_CHANEL);
  int stateB = GET_STATE(B_CHANEL);
  for (int i = 0;; i++)
  {

    if (stateA != GET_STATE(A_CHANEL))
    {
      stateA = INV_STATE(stateA);
      stateB = GET_STATE(B_CHANEL);
      if (stateA != stateB)
        count--;
      else
        count++;
    }

    char data[100];
    if (i % 10000 == 0)
    {
      ftoa(count, data, 3);
      fseek(f, 0, SEEK_SET);
      fwrite(data, 100, 1, f);
      fprintf(f, "%f", (float)((count * 10)) / 1000);
      // printf("%f\n", (float)((count * 10)) / 1000);
    }
  }

  fclose(f);
  return 0;
}

// for i in $(ps -aux  | grep "sudo \./io" | awk '{print $2}');do sudo renice -n -15 -p $i;done && ps -al  | grep "sudo \./io"
