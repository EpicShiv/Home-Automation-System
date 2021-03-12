/*
 * Title: Home Automation System (Remote and Manual Switch Control)
 * Version 2.0
 * Written by Shiva Teja (B.S.T)
 * GitHub Link: https://github.com/EpicShiv/Home-Automtion-System
 * 
 * BSD 3-Clause License
 * Copyright (c) 2021, SHIVA TEJA
 * All rights reserved.
 */

 /*
  * This code is written assuming the board to be used is ESP-12E or ESP-12F or NodeMCU which is based on ESP8266 controller.  
  * If you are using any other microcontroller other than ESP8266 please change the code carefully as for your requirements.
  * Or else you can also check Git Repo: https://github.com/EpicShiv/Home-Automtion-System  for seperate code for microcontroller and ESP8266 generic module.
  */

// While uploading code define "DEBUG" to "0" and for debugging change it to "1".
#define DEBUG 1
#if DEBUG
  #define DUMPS(s) Serial.print(s)
#else
  #define DUMPS(s)
#endif

// If you are using pull up relay then define 'Relay_Type_Pullup 1' else '#define Relay_Type_Pullup 0'
#define Relay_Type_Pullup 1
#if Relay_Type_Pullup
  #define R_High LOW
  #define R_Low HIGH
#else
  #define R_High HIGH
  #define R_Low LOW
#endif

#define No_Of_Relays 4            // Mention the number of relays used.

int prev_r[No_Of_Relays];         // Initializing an array variable to store previous reading of manual switches.

// Define the GPIO connected with Relays and switches.
const int R[No_Of_Relays] = {A0, 5, 4, 2};      // Relay 1, 2, 3, 4 are connected to the respective GPIO pins of ESP-12F.
const int S[No_Of_Relays] = {13, 12, 14, 16};   // Switch 1, 2, 3, 4 are connected to the respective GPIO pins of ESP-12F.
int State[No_Of_Relays];                        // Initializing the variable state for all relays.

void setup()
{
  for (int i = 0; i < No_Of_Relays; i++)
  {
    pinMode(R[i], OUTPUT);        // Define all pins connected to relays as output pins.
    pinMode(S[i], INPUT_PULLUP);  // Define all pins connected to switches as input pullup pins. (i.e., Virtually connected to a pullup resisitors always high)
    State[i] = R_Low;             // Set the state for all relay.
    digitalWrite(R[i], State[i]); // During Start all Relays should be TURN OFF.
  }
  
  Serial.begin(9600);             // Initializes to start recieve and transmit the serial data.
}

void loop()
{
   if (Serial.available())        // Executes loop if Serial is available.
  {
    remoteSwitch();               // Operates by remote switches. (such as mobile app, IR remote, voice commands and etc.,)
  }
  else                            // Executes loop if Serial is not available.
  {
    manualSwitch();               // Operates by manual switches.
  }
}

// This function changes the state of respective relays. (i.e., If a relay is in ON state then turns it to OFF state and viceversa)
void relayOnOff(int relay)
{
  // Operation is done by switching to specified relay.
  if(relay >= 0 and relay < No_Of_Relays)
  {
    if(State[relay] == 0)
    {
      digitalWrite(R[relay], R_High);                       // Turns on respective relay.
      State[relay] = 1;                                     // Sets the respective relay state to ON.
      DUMPS("\r\n Relay "+ String(relay + 1) +" is ON");    // Useful while debugging.
    }
    else if(State[relay] == 1)
    {
      digitalWrite(R[relay], R_Low);                        // Turns off respective relay.
      State[relay] = 0;                                     // Sets the respective relay state to OFF.
      DUMPS("\r\n Relay "+ String(relay + 1) +" is OFF");   // Useful while debugging.
    }
  }
  delay(100);
}

// This function is used to control relays via manual switches.
void manualSwitch()
{
  // Operation is done by switching to specified relay.
  for (int i = 0; i < No_Of_Relays; i++)                  // Iterates the loop to the number relays.
  {
    if(!digitalRead(S[i]) == prev_r[i])                   // Executes the loop if change in switch state is detected.
    {
      relayOnOff(i);                                      // Turns ON/OFF the relay respective to its state.
      prev_r[i] = digitalRead(S[i]);                      // Assigns switch reading to 'prev_r' to exit from loop.
    }
  }
}

// This function is used to control relays via remote switches. (such as mobile app, IR remote, voice commands and etc.,)
void remoteSwitch()
{
  relayOnOff(int(map(Serial.read(), 'A', 'Z', 0, 25)));
}
