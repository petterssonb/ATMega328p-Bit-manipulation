#include "serial.h"
#include "command_handler.h"

int main(){

    uart_init();
    SET_BIT(DDRB, RED_LED);
    while(1){
      uart_putstr("Enter ledpower (0-255): ");
      char* command = uart_rec_str();
      handleCommand(command);
    }

  return 0;
}