// Copyright (c) 2022 Cesanta
// All rights reserved

#pragma once

#include <stdarg.h>

#define GPIO			0x60000300
#define uart0			0x60000000
#define uart1			0x60000f00
#define frc1			0x60000600
#define rtc_sys_info	0x60001100
#define SLC0			0x60000B00
#define I2S0			0x60000e00
#define SPI1			0x60000100
#define SPI0			0x60000200

typedef uint8_t			bool;
typedef void (*int_handler_t)(void *arg);
typedef void os_timer_func_t(void *timer_arg);

typedef struct _os_timer_t {
	struct _os_timer_t *timer_next;
	void               *timer_handle;
	uint32_t             timer_expire;
	uint32_t             timer_period;
	os_timer_func_t    *timer_func;
	bool               timer_repeat_flag;
	void               *timer_arg;
} os_timer_t;


int uart_tx_one_char(char nCh);
void ets_install_uart_printf(void);
void ets_update_cpu_frequency(uint32_t ticks_per_us);

int ets_printf(const char *fmt, ...);
int ets_putc(int c);
int ets_io_vprintf(int (*putc)(int), const char* fmt, va_list ap);

int_handler_t ets_isr_attach(uint32_t int_num, int_handler_t handler, void *arg);
void ets_isr_mask(uint32_t ints);
void ets_isr_unmask(uint32_t ints);
void ets_intr_lock();
void ets_intr_unlock();

void ets_delay_us(uint32_t us);
void ets_timer_done(os_timer_t *ptimer);

int md5_vector(uint32_t num_elem, const uint8_t *addr[], const uint32_t *len, uint8_t *mac);
