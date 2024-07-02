#pragma once

#include <avr/io.h>
#include <avr/interrupt.h>

#define TIMER_REG_INIT 0
#define TIMER1_COMPA_MATCH_INIT 0x02
#define TIMER_COMPARE_VAL 25000
#define SET_BIT(PORT, BIT) ((PORT) |= (1 << (BIT)))
#define CLEAR_BIT(PORT, BIT) ((PORT) &= ~(1 << (BIT)))

void timerStarting();