#pragma once
#include <stdint.h>

#define JOY_BUTTON_START 0x0080
#define JOY_BUTTON_A     0x0040
#define JOY_BUTTON_B     0x0010
#define JOY_BUTTON_C     0x0020
#define JOY_BUTTON_UP    0x0001
#define JOY_BUTTON_DOWN  0x0002
#define JOY_BUTTON_LEFT  0x0004
#define JOY_BUTTON_RIGHT 0x0008

extern uint16_t joypad1;

int mdJoyButtonSelected( uint16_t button );