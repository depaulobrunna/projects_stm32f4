#ifndef __DEBUG_H__
#define __DEBUG_H__

#include "stdio.h"
#include "string.h"
#include "stdarg.h"

#define DEBUG

void debug_init(void);
void debug_print(char *format, ...);
void debug_print_bytes(const char *format, ...);

#ifdef DEBUG
#define PRINTS(...)	debug_print(__VA_ARGS__)
#else
#define PRINTS(...)
#endif

#endif
