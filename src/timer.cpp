#include "timer.h"

void timerStarting(){
  TCCR1A = TIMER_REG_INIT;
  TCCR1B = TIMER_REG_INIT;
  TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10);
  OCR1A = TIMER_COMPARE_VAL;
  TIMSK1 |= TIMER1_COMPA_MATCH_INIT;
}
