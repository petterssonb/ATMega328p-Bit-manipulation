#include "uart_handler.h"

void uart_init(){
    UBRR0H = (uint8_t)(UBRR_VAL >> 8); // Setting UBRR0H to MSB of UBRR_VAL
    UBRR0L = (uint8_t)UBRR_VAL; // Setting UBRR0L to LSB of UBRR_VAL

    UCSR0C = (3 << UCSZ00); // Setting frame format for UART to 8-bits

    // Activate sending for UART = TXEN0
    // Activate receiving for UART = RXEN0
    UCSR0B = (1 << TXEN0) | (1 << RXEN0); 
}

void uart_putfloat(float number, int decimalPlaces){
    char buffer[BUFFER_SIZE];

    int integer_part = (int)number;
    itoa(integer_part, buffer, DECIMAL_BASE);

    int length = 0;
    while(buffer[length] != '\0'){
        length++;
    }

    buffer[length] = '.';
    length++;

    float fractional_part = number - integer_part;
    for(int i = 0; i < decimalPlaces; i++){
        fractional_part *= DECIMAL_BASE;
    }

    integer_part = (int)(fractional_part + 0.5);
    itoa(integer_part, buffer + length, DECIMAL_BASE);

    uart_putstr(buffer);
}

void uart_putchar(char c){
    while(!(UCSR0A & (1 << UDRE0)));

    UDR0 = c;
}

void uart_putstr(const char* str){
    while(*str){
        uart_putchar(*str++);
    }
}