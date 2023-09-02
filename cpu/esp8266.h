#pragma once

#include "esp8266_rom.h"


#define _COUNTER_STRINGIFY(COUNTER) #COUNTER
#define _SECTION_ATTR_IMPL(SECTION, COUNTER) __attribute__((section(SECTION "." _COUNTER_STRINGIFY(COUNTER))))
#define __NOINIT_ATTR _SECTION_ATTR_IMPL(".noinit", __COUNTER__)

#define IRAM_ATTR _SECTION_ATTR_IMPL(".iram1", __COUNTER__)
#define IFLASH_ATTR _SECTION_ATTR_IMPL(".iflash", __COUNTER__)

