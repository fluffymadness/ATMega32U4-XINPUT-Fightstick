#include "LUFAConfig.h"
#include <LUFA.h>
#include "XInputPad.h"
#define BOUNCE_WITH_PROMPT_DETECTION
#include "Bounce2.h"

#define MILLIDEBOUNCE 1 //Debounce time in milliseconds
#define pinSWITCH 20
#define pinMODELED 21

byte buttonStatus[16];
#define BUTTONUP 0
#define BUTTONDOWN 1
#define BUTTONLEFT 2
#define BUTTONRIGHT 3
#define BUTTONA 4
#define BUTTONB 5
#define BUTTONX 6
#define BUTTONY 7
#define BUTTONLB 8
#define BUTTONRB 9
#define BUTTONLT 10
#define BUTTONRT 11
#define BUTTONSTART 12
#define BUTTONSELECT 13
#define BUTTONHOME 14
#define BUTTONMODE 15

Bounce joystickUP = Bounce();
Bounce joystickDOWN = Bounce();
Bounce joystickLEFT = Bounce();
Bounce joystickRIGHT = Bounce();
Bounce buttonA = Bounce();
Bounce buttonB = Bounce();
Bounce buttonX = Bounce();
Bounce buttonY = Bounce();
Bounce buttonLB = Bounce();
Bounce buttonRB = Bounce();
Bounce buttonLT = Bounce();
Bounce buttonRT = Bounce();
Bounce buttonSTART = Bounce();
Bounce buttonSELECT = Bounce();
Bounce buttonHOME = Bounce();
Bounce buttonMODE = Bounce();

typedef enum {
  ANALOG_MODE,
  DIGITAL,
} State_t;
State_t state = DIGITAL;


void setup() {
  setupPins();
  setupHardware();
  GlobalInterruptEnable();
}

void setupPins(){
    joystickUP.attach(0,INPUT_PULLUP);
    joystickDOWN.attach(1,INPUT_PULLUP);
    joystickLEFT.attach(2,INPUT_PULLUP);
    joystickRIGHT.attach(3,INPUT_PULLUP);
    buttonA.attach(4,INPUT_PULLUP);
    buttonB.attach(5,INPUT_PULLUP);;
    buttonX.attach(6,INPUT_PULLUP);
    buttonY.attach(7,INPUT_PULLUP);
    buttonLB.attach(9,INPUT_PULLUP);
    buttonRB.attach(8,INPUT_PULLUP);
    buttonLT.attach(14,INPUT_PULLUP);
    buttonRT.attach(10,INPUT_PULLUP);
    buttonSTART.attach(15,INPUT_PULLUP);
    buttonSELECT.attach(16,INPUT_PULLUP);
    buttonHOME.attach(18,INPUT_PULLUP);

    joystickUP.interval(MILLIDEBOUNCE);
    joystickDOWN.interval(MILLIDEBOUNCE);
    joystickLEFT.interval(MILLIDEBOUNCE);
    joystickRIGHT.interval(MILLIDEBOUNCE);
    buttonA.interval(MILLIDEBOUNCE);
    buttonB.interval(MILLIDEBOUNCE);
    buttonX.interval(MILLIDEBOUNCE);
    buttonY.interval(MILLIDEBOUNCE);
    buttonLB.interval(MILLIDEBOUNCE);
    buttonRB.interval(MILLIDEBOUNCE);
    buttonLT.interval(MILLIDEBOUNCE);
    buttonRT.interval(MILLIDEBOUNCE);
    buttonSTART.interval(MILLIDEBOUNCE);
    buttonSELECT.interval(MILLIDEBOUNCE);
    buttonHOME.interval(MILLIDEBOUNCE);
  
    pinMode(pinMODELED, OUTPUT);  
    //Set the LED to low to make sure it is off
    digitalWrite(pinMODELED, LOW);
}
void loop() {
    updateButtonStatus();  
    processDirections();
    processButtons();
    xbox_send_pad_state();
    xbox_reset_pad_status();
}

void updateButtonStatus()
{
  //IF THERE IS A CHANGE IN STATE FROM HIGH to LOW Buttonstatus gets updated, or else BUTTONSTATUS stays the same as before...the mask always is set with OR, so if button status changes to zero, mask wont change. to counter this, the whole struct where button states are saved is set with memset to zero after everything
  if (joystickUP.update()) {buttonStatus[BUTTONUP] = joystickUP.fell();}
  if (joystickDOWN.update()) {buttonStatus[BUTTONDOWN] = joystickDOWN.fell();}
  if (joystickLEFT.update()) {buttonStatus[BUTTONLEFT] = joystickLEFT.fell();}
  if (joystickRIGHT.update()) {buttonStatus[BUTTONRIGHT] = joystickRIGHT.fell();}
  if (buttonA.update()) {buttonStatus[BUTTONA] = buttonA.fell();}
  if (buttonB.update()) {buttonStatus[BUTTONB] = buttonB.fell();}
  if (buttonX.update()) {buttonStatus[BUTTONX] = buttonX.fell();}
  if (buttonY.update()) {buttonStatus[BUTTONY] = buttonY.fell();}
  if (buttonLB.update()) {buttonStatus[BUTTONLB] = buttonLB.fell();}
  if (buttonRB.update()) {buttonStatus[BUTTONRB] = buttonRB.fell();}
  if (buttonLT.update()) {buttonStatus[BUTTONLT] = buttonLT.fell();}
  if (buttonRT.update()) {buttonStatus[BUTTONRT] = buttonRT.fell();}
  if (buttonSTART.update()) {buttonStatus[BUTTONSTART] = buttonSTART.fell();}
  if (buttonSELECT.update()) {buttonStatus[BUTTONSELECT] = buttonSELECT.fell();}
  if (buttonHOME.update()) {buttonStatus[BUTTONHOME] = buttonHOME.fell();}
}
void processDirections()
{
  switch (state)
  {
    case DIGITAL:
      if(buttonStatus[BUTTONUP]) {gamepad_state.digital_buttons_1 |= DPAD_UP_MASK_ON ;}
      if(buttonStatus[BUTTONDOWN] && !buttonStatus[BUTTONUP]) {gamepad_state.digital_buttons_1 |= DPAD_DOWN_MASK_ON ;}
      if(buttonStatus[BUTTONLEFT] && !buttonStatus[BUTTONRIGHT]) {gamepad_state.digital_buttons_1 |= DPAD_LEFT_MASK_ON ;}
      if(buttonStatus[BUTTONRIGHT] && !buttonStatus[BUTTONLEFT]) {gamepad_state.digital_buttons_1 |= DPAD_RIGHT_MASK_ON ;}
    break;

    case ANALOG_MODE:
      fakeLeftAnalog(buttonStatus[BUTTONUP], buttonStatus[BUTTONDOWN], buttonStatus[BUTTONLEFT], buttonStatus[BUTTONRIGHT]);
    break;
  }
}
void processButtons(){
  if (buttonStatus[BUTTONA]) {gamepad_state.digital_buttons_2 |= A_MASK_ON;}
  if (buttonStatus[BUTTONB]) {gamepad_state.digital_buttons_2 |= B_MASK_ON;}
  if (buttonStatus[BUTTONX]) {gamepad_state.digital_buttons_2 |= X_MASK_ON;}
  if (buttonStatus[BUTTONY]) {gamepad_state.digital_buttons_2 |= Y_MASK_ON;}
  if (buttonStatus[BUTTONLB]) {gamepad_state.digital_buttons_2 |= LB_MASK_ON;}
  if (buttonStatus[BUTTONRB]) {gamepad_state.digital_buttons_2 |= RB_MASK_ON;}
  if (buttonStatus[BUTTONLT]) {gamepad_state.lt = 0xFF;}
  if (buttonStatus[BUTTONRT]) {gamepad_state.rt = 0xFF;}
  if (buttonStatus[BUTTONSTART]&&buttonStatus[BUTTONSELECT]){
    switch (state)
    {
    case DIGITAL:
      state = ANALOG_MODE;
    break;
    case ANALOG_MODE:
      state = DIGITAL;
    break;
    }
  }
  else if (buttonStatus[BUTTONSTART]){gamepad_state.digital_buttons_1 |= START_MASK_ON;}
  else if (buttonStatus[BUTTONSELECT]){gamepad_state.digital_buttons_1 |= BACK_MASK_ON;}
  if (buttonStatus[BUTTONHOME]){gamepad_state.digital_buttons_1 |= L3_MASK_ON;}
}


void fakeLeftAnalog(uint8_t dpadUP, uint8_t dpadDOWN, uint8_t dpadLEFT, uint8_t dpadRIGHT){
  if (dpadUP) 
  {
    gamepad_state.l_y = 32767;
  }
  //DPAD Down
  if (dpadDOWN && !dpadUP) {
    gamepad_state.l_y = -32768;
  }
  if (dpadLEFT && !dpadRIGHT){
    gamepad_state.l_x = -32768;
  }
  //DPAD Right
  if (dpadRIGHT && !dpadLEFT){
    gamepad_state.l_x = 32767;
  }
}
