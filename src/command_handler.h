#pragma once
#include <stdbool.h>
#include "serial.h"

#define MAX_VALUE 255
#define MIN_VALUE 0
#define TURN_OFF_VALUE 127
#define POWER_ON power > TURN_OFF_VALUE

void setLedOnOrOff(bool on);
void setLedOn();
void setLedOff();
bool isPowerWithinRange(int power);
void handleLedPower(int power);
void handleCommand(char* command);