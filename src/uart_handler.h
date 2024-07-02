#pragma once

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define BAUD 9600
#define UBRR_VAL ((F_CPU / (16UL * BAUD)) - 1) 
#define DECIMAL_BASE 10
#define BUFFER_SIZE 32

void uart_init();
void uart_putfloat(float number, int decimalPlaces);
void uart_putchar(char c);
void uart_putstr(const char* str);