#include "tick.h"
#include "stm32f4xx.h"                  // Device header


void SysTick_Handler(void);

static volatile uint32_t tick;

uint32_t tick_set_timer(uint32_t ticks_per_sec)
{
    return SysTick_Config(SystemCoreClock/ticks_per_sec);
}

uint32_t tick_get_tick(void)
{
    return tick;
}

uint32_t tick_set_miliseconds(uint32_t time)
{
    return time;
}

uint32_t tick_set_seconds(uint32_t time)
{
    return (1000 * tick_set_miliseconds(time));
}

void SysTick_Handler(void)
{
	tick++;
}
