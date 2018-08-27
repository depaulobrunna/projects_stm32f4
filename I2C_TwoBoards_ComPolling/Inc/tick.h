#ifndef __TICK_H__
#define __TICK_H__

#include <stdint.h>

uint32_t tick_set_timer(uint32_t ticks_per_sec);
uint32_t tick_get_tick(void);

uint32_t tick_set_miliseconds(uint32_t time);
uint32_t tick_set_seconds(uint32_t time);
#endif
