#define BCM2708_PERI_BASE 0x3F000000 // for raspberries more simple then raspberryPi2 use 0x20000000
#define GPIO_BASE (BCM2708_PERI_BASE + 0x200000) /* GPIO controller */

#define A_CHANEL 16
#define B_CHANEL 26

#define PAGE_SIZE (4 * 1024)
#define BLOCK_SIZE (4 * 1024)

