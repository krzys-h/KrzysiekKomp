#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "common/types.h"

void serial_init();
void serial_printchar(char c);
void serial_print(const char* s);
char serial_readchar();
int serial_read(char* buf);

#ifdef __cplusplus
}
#endif
