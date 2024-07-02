#include <avr/io.h>


#define RED_LED_PIN 0 // Binary = 0b00 // Hexadecimal = 0x00 // Pin 8
#define BUTTON_LED_PIN 1 // Binary = 0b01 // Hexadecimal = 0x01 // Pin 9
#define SET_BIT(PORT, BIT) ((PORT) |= (1 << (BIT))) // Sätter en bit till 1 i ett port register / sätter pinnen till output / sätter den "high"
#define CLEAR_BIT(PORT, BIT) ((PORT) &= ~(1 << (BIT))) // Sätter en bit till 0 i ett port register / sätter pinnen till input / sätter den "low"
#define READ_BIT(PORT, BIT) (((PORT) & (1 << (BIT))) >> (BIT)) // Läser av värdet som en bit har i ett port register / läser av värdet på en input pinne / läser är den "low" eller "high"

bool gLedOn = false;
bool gLastButtonPress = false;
bool gButtonPressed = false;

void setupGPIO(){
  SET_BIT(DDRB, RED_LED_PIN); // Sätter led pinnen till output
  CLEAR_BIT(DDRB, BUTTON_LED_PIN); // Sätter button pinnen till input
  SET_BIT(PORTB, BUTTON_LED_PIN); // Aktiverar pull-up resistor för button pinnen
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

void loop() {
  checkButtonPress();
}

int main(){
  setupGPIO();
  
  while(1){
    loop();
  }
  
  return 0;
}