#pragma once
#include <stdint.h>

void keyboard_init();
char keyboard_get_char();       // blocking
int keyboard_available();       // non-blocking