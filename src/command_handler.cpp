#include "command_handler.h"

void setLedOn(){
    SET_BIT(PORTB, RED_LED);
}

void setLedOff(){
    CLEAR_BIT(PORTB, RED_LED);
}

bool isPowerWithinRange(int power){
    return power >= MIN_VALUE && power <= MAX_VALUE;
}

void setLedOnOrOff(bool on){
    if(on){
        setLedOn();
    } else {
        setLedOff();
    }
}

void handleLedPower(int power){
    if(isPowerWithinRange(power)){
        if(POWER_ON){
            setLedOnOrOff(true);
        } else {
            setLedOnOrOff(false);
        }
    } else {
        uart_putstr("Invalid value, please enter a value between 0-255\n");
    }
}

void handleCommand(char* command){
    if(strlen(command) == 0){
        return;
    }
    int power = -1;
    int res = sscanf(command, "ledpower %d", &power);
    if(res == 1){
        handleLedPower(power);
    }
}