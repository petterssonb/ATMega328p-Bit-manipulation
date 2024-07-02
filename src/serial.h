#pragma once
#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include "command_handler.h"

#define BAUD 9600
#define UBRR_VAL ((F_CPU / (16UL * BAUD)) - 1)
#define RED_LED 0 // Pin 8
#define SET_BIT(PORT, BIT) ((PORT) |= (1 << (BIT))) // setting bit high / output
#define CLEAR_BIT(PORT, BIT) ((PORT) &= ~(1 << (BIT))) // setting bit low / input
#define READ_BIT(PORT, BIT) (((PORT) & (1 << (BIT))) >> (BIT)) // read value of bit
#define RX_BUFFER_SIZE 64

void uart_init();
void uart_putchar(char c);
void uart_putstr(const char* str);
char uart_getchar();
char* uart_rec_str();