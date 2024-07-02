#include "serial.h"

void uart_init(){
    UBRR0H = (uint8_t)(UBRR_VAL >> 8);
    UBRR0L = (uint8_t)UBRR_VAL;
    UCSR0C = (3 << UCSZ00);
    UCSR0B = (1 << TXEN0) | (1 << RXEN0);
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

char uart_getchar(){
    while(!(UCSR0A & (1 << RXC0)));
    return UDR0;
}

char* uart_rec_str(){
    static char buffer[RX_BUFFER_SIZE];
    int i = 0;

    while(1){
        char ch = uart_getchar();
        if ((ch == '\n' || ch == '\r') && i == 0){
            continue;
        }
        uart_putchar(ch);
        if(ch == '\n' || ch == '\r'){
            uart_putchar('\n');
            buffer[i] = '\0';
            return buffer;
        } else if(i < RX_BUFFER_SIZE - 1){
            buffer[i++] = ch;
        } else {
            uart_putstr("\nCommand too long, buffer size is 63 bytes\n");
            i = 0;
        }
    }
}
