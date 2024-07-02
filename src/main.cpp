#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "uart_handler.h"
#include "adc_handler.h"
#include "timer.h"

#define BLUE_LED_PIN 3
#define SET_BIT(PORT, BIT) ((PORT) |= (1 << (BIT)))
#define CLEAR_BIT(PORT, BIT) ((PORT) &= ~(1 << (BIT)))
#define RX_BUFFER_SIZE 64
#define FREQUENCY = F_CPU / (2 * N * (1 + OCR1A))
#define SWITCH_BIT(PORT, BIT) ((PORT) ^= (1 << (BIT)))

volatile uint16_t gDelay = 1000;
volatile uint16_t gPreviousMillis = 0;

void initializeLed(){
    SET_BIT(DDRD, BLUE_LED_PIN);
}

void ledOff(){
    CLEAR_BIT(PORTD, BLUE_LED_PIN);
}

ISR(ADC_vect){
    uint16_t adcValue = ADC;
    handleAdcValueChange(adcValue);
    ADCSRA |= (1 << ADSC);
}

ISR(TIMER1_COMPA_vect){
    SWITCH_BIT(PORTD, BLUE_LED_PIN);
    ADCSRA |= (1 << ADSC);
}

int main(){
    uart_init();
    adc_init();
    timerStarting();
    initializeLed();
    sei();
    ADCSRA |= (1 << ADSC); 
    while(1){}

    return 0;
}