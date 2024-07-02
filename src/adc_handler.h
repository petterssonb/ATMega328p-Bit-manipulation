#pragma once

#define ADC_CHANNEL 0 // ADC channel for A0
#define ADC_REF_VOLTAGE 5.0
#define ADC_MAX_VAL 1023.0
#define ADC_PRESCALER ((1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0)) // Prescaler to 128 so it is 125kHz
#define N 64
#define SET_BIT(PORT, BIT) ((PORT) |= (1 << (BIT)))
#define BLUE_LED_PIN 3

#define PRESCALER_64 64
#define PRESCALER_256 256
#define PRESCALER_1024 1024

#define SET_PRESCALER_64 (TCCR1B |= (1 << CS11) | (1 << CS10))
#define SET_PRESCALER_256 (TCCR1B |= (1 << CS12))
#define SET_PRESCALER_1024 (TCCR1B |= (1 << CS12) | (1 << CS10))
#define CLEAR_PRESCALER (TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10)))
#define LOWER_THRESHOLD (adcValue < ADC_MAX_VAL / 3)
#define MIDDLE_THRESHOLD (adcValue < 2 * ADC_MAX_VAL / 3)
#define ADC_HAS_CHANGED (adcValue != oldAdcValue)
#define CALCULATE_VOLTAGE (adcValue * (ADC_REF_VOLTAGE / ADC_MAX_VAL))
#define OCR1A_MAX 0xFFFF
#define BLUE_LED_BIT (1 << BLUE_LED_PIN)
#define OCIE1A_BIT (1 << OCIE1A)
#define OCR1A_MIN (F_CPU / (2 * N * 10) - 1)
#define OCR1A_RANGE (OCR1A_MAX - OCR1A_MIN)
#define ADC_RANGE (ADC_MAX_VAL - adcValue)
#define PRINT_BUFFER 32
#define DECIMAL_BASE 10
#define FLOAT_PRECISION 2


#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart_handler.h"

void adc_init();
uint16_t readADC();
void setPrescalerBasedOnAdcValue(uint16_t adcValue);
void handleAdcValueChange(uint16_t adcValue);
void handleVoltageChange(double voltage, uint16_t adcValue);
void printAdcAndVoltage(uint16_t adcValue, double voltage);