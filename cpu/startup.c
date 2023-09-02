#include <stdint.h>
#include "esp8266.h"

typedef struct {
    uint32_t device_id;
    uint32_t chip_size;    // chip size in bytes
    uint32_t block_size;
    uint32_t sector_size;
    uint32_t page_size;
    uint32_t status_mask;
} esp_rom_spiflash_chip_t;

extern esp_rom_spiflash_chip_t* flashchip;

#define printf(...)		ets_printf(__VA_ARGS__)

uint32_t gnBss;
uint32_t gaCntLoop[10] = {
	0x11111111, 
	0x22222222,
	0x33333333,
	0x44444444,
	0x55555555,
	0x66666666,
	0x77777777,
	0x88888888,
	0x99999999,
	0xAAAAAAAA, 
};

#define _COUNTER_STRINGIFY(COUNTER) #COUNTER
#define _SECTION_ATTR_IMPL(SECTION, COUNTER) __attribute__((section(SECTION "." _COUNTER_STRINGIFY(COUNTER))))
#define __NOINIT_ATTR _SECTION_ATTR_IMPL(".noinit", __COUNTER__)

#define IRAM_ATTR _SECTION_ATTR_IMPL(".iram1", __COUNTER__)
#define IFLASH_ATTR _SECTION_ATTR_IMPL(".iflash", __COUNTER__)


#define IFLASH __attribute__((section(".iflash")))

void IFLASH_ATTR flash_func(void);

void flash_func(void)
{
	printf("In IFlash\n");
}

void call_start_cpu(void)
{
	int nLocal;
	printf("Start\n");
	printf("Flash %X, %X, %X, %X, %X\n",
		flashchip->device_id,
		flashchip->chip_size,
		flashchip->block_size,
		flashchip->sector_size,
		flashchip->page_size);
	
	printf("func Addr: %p\n", call_start_cpu);
	printf("bss addr: %p\n", &gnBss);
	printf("data addr: %p\n", gaCntLoop);
	printf("stack Addr: %p\n", &nLocal);
	printf("iF_Func Addr: %p\n", flash_func);

	for(int i=0; i< 3; i++)
	{
		printf("Loop: %d, %X\n", i, gaCntLoop[i]);
	}

//	flash_func();

	while(1);
}

