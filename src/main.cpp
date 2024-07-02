#include <avr/io.h>

#define RED_LED_PIN 0 // Pin 8
#define BUTTON_LED_PIN 1 // Pin 9
#define SET_BIT(PORT, BIT) ((PORT) |= (1 << (BIT)))
#define CLEAR_BIT(PORT, BIT) ((PORT) &= ~(1 << (BIT)))
#define READ_BIT(PORT, BIT) (((PORT) & (1 << (BIT))) >> (BIT))

bool gLedOn = false;
bool gLastButtonPress = false;
bool gButtonPressed = false;

void setupGPIO(){
  SET_BIT(DDRB, RED_LED_PIN); // setting the red led pin to output
  CLEAR_BIT(DDRB, BUTTON_LED_PIN); // setting button pin to input
  SET_BIT(PORTB, BUTTON_LED_PIN); // activate pull up resistors for button pinnen
}

bool isButtonPressed(){
  return READ_BIT(PINB, BUTTON_LED_PIN) == 1;
}

void setButtonInput(){
  CLEAR_BIT(DDRB, BUTTON_LED_PIN);
}

void setButtonPullUp(){
  SET_BIT(PORTB, BUTTON_LED_PIN);
}

void setLedOn(){
  SET_BIT(PORTB, RED_LED_PIN);
}

void setLedOff(){
  CLEAR_BIT(PORTB, RED_LED_PIN);
}

void setLedOnOrOff(bool on){
  if (on) {
    setLedOn();
  } else {
    setLedOff();
  }
}

void checkButtonPress(){
  gButtonPressed = isButtonPressed();
  if (gButtonPressed && !gLastButtonPress) {
    gLedOn = !gLedOn;
    setLedOnOrOff(gLedOn);
  }
  gLastButtonPress = gButtonPressed;
}

int main(){
  setupGPIO();
  
  while(1){
    checkButtonPress();
  }
  
  return 0;
}