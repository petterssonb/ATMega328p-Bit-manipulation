#include "adc_handler.h"

void adc_init() {
  ADMUX = (1 << REFS0);
  ADCSRA = (1 << ADEN) | (0 << ADSC) | (0 << ADATE) | (1 << ADIE) | ADC_PRESCALER;
  ADCSRB = 0x00;
}

uint16_t readADC(){
    ADCSRA |= (1 << ADSC);
    while(ADCSRA & (1 << ADSC));

    uint16_t adcValue = ADC;
    return adcValue;
}

void setPrescaler(uint16_t prescaler){
    CLEAR_PRESCALER;

    switch(prescaler){
        case PRESCALER_64:
            SET_PRESCALER_64;
            break;
        case PRESCALER_256:
            SET_PRESCALER_256;
            break;
        case PRESCALER_1024:
            SET_PRESCALER_1024;
            break;
        default:
            break;
    }
}

void setPrescalerBasedOnAdcValue(uint16_t adcValue){
    if(LOWER_THRESHOLD){
        setPrescaler(PRESCALER_1024);
    } else if(MIDDLE_THRESHOLD){
        setPrescaler(PRESCALER_256);
    } else {
        setPrescaler(PRESCALER_64);
    }
}

void handleAdcValueChange(uint16_t adcValue){
    static uint16_t oldAdcValue = 0;
    if(ADC_HAS_CHANGED){
        oldAdcValue = adcValue;
        double voltage = CALCULATE_VOLTAGE;
        setPrescalerBasedOnAdcValue(adcValue);
        handleVoltageChange(voltage, adcValue);
    }
}

void handleVoltageChange(double voltage, uint16_t adcValue){
    if(voltage == 0){
        OCR1A = OCR1A_MAX;
        SET_BIT(PORTD, BLUE_LED_BIT);
        TIMSK1 &= ~OCIE1A_BIT;
    } else {
        TIMSK1 |= OCIE1A_BIT;
        OCR1A = OCR1A_MIN + OCR1A_RANGE * ADC_RANGE / ADC_MAX_VAL;
    }
    printAdcAndVoltage(adcValue, voltage);
}

void printAdcAndVoltage(uint16_t adcValue, double voltage){
    char buffer[PRINT_BUFFER];
    uart_putstr("ADC Value: ");
    itoa(adcValue, buffer, DECIMAL_BASE);
    uart_putstr(buffer);
    uart_putstr(", Voltage: ");
    uart_putfloat(voltage, FLOAT_PRECISION);
    uart_putstr("\n");
}