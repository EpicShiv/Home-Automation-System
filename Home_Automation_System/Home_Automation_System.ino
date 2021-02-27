/*
 * Title: Home Automation System (Remote and Manual Switch Control)
 * Version 1.0
 * Written by Shiva Teja (B.S.T)
 * GitHub Link: https://github.com/bst415/Home-Automtion-System
 * 
 * BSD 3-Clause License
 * Copyright (c) 2021, SHIVA TEJA
 * All rights reserved.
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

int a, b, c, d, e, f, g, h;

// Define the GPIO connected with Relays and switches.
#define R1 2          // Relay 1 connected to digital pin D2.
#define R2 3          // Relay 2 connected to digital pin D3.
#define R3 4          // Relay 3 connected to digital pin D4.
#define R4 5          // Relay 4 connected to digital pin D5.

#define S1 8          // Switch 1 connected to digital pin D8.
#define S2 9          // Switch 2 connected to digital pin D9.
#define S3 10         // Switch 3 connected to digital pin D10.
#define S4 11         // Switch 4 connected to digital pin D11.

int R1_State = 1;     // Define integer to remember the state for relay 1.
int R2_State = 1;     // Define integer to remember the state for relay 2.
int R3_State = 1;     // Define integer to remember the state for relay 3.
int R4_State = 1;     // Define integer to remember the state for relay 4.

void setup()
{
  // Define R1, R2, R3, R4 as an output pins.
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(R3, OUTPUT);
  pinMode(R4, OUTPUT);

  // Define S1, S2, S3, S4 as input pullup pins. (i.e., Virtually connected to a pullup resisitors always high)
  pinMode(S1, INPUT_PULLUP);
  pinMode(S2, INPUT_PULLUP);
  pinMode(S3, INPUT_PULLUP);
  pinMode(S4, INPUT_PULLUP);

  //During Starting all Relays should be TURN OFF.
  digitalWrite(R1, R1_State);
  digitalWrite(R2, R2_State);
  digitalWrite(R3, R3_State);
  digitalWrite(R4, R4_State);
  
  Serial.begin(9600);         // Initializes to start recieve and transmit the serial data.

}

void loop()
{
   if (Serial.available())    // Executes loop if Serial is available.
  {
    remoteSwitch();           // Operates by remote switches. (such as mobile app, IR remote, voice commands and etc.,)
  }
  else                        // Executes loop if Serial is not available.
  {
    manualSwitch();           // Operates by manual switches.
  }
}

// This function changes the state of respective relays. (i.e., If a relay is in ON state then turns it to OFF state and viceversa)
void relayOnOff(int relay)
{
  // Operation is done by switching to specified relay.
  switch(relay)
  {
    case 1:
    if(!R1_State)
    {
      digitalWrite(R1, R_High);          // Turns on relay 1.
      R1_State = 1;                   // Sets or changes the relay 1 state to ON.
      DUMPS("\r\n Relay 1 is ON");    // Useful while debugging.
    }
    else
    {
      digitalWrite(R1, R_Low);         // Turns off relay 1.
      R1_State = 0;                   // Sets the relay 1 state to OFF.
      DUMPS("\r\n Relay 1 is OFF");   // Useful while debugging.
    }
    delay(100);
    break;
    case 2:
    if(R2_State == 0)
    {
      digitalWrite(R2, R_High);          // Turns on relay 2.
      R2_State = 1;                   // Sets or changes the relay 2 state to ON.
      DUMPS("\r\n Relay 2 is ON");    // Useful while debugging.
    }
    else
    {
      digitalWrite(R2, R_Low);          // Turns on relay 2.
      R2_State = 0;                    // Sets or changes the relay 2 state to OFF.
      DUMPS("\r\n Relay 2 is OFF");    // Useful while debugging.
    }
    delay(100);
    break;
    case 3:
    if(R3_State == 0)
    {
      digitalWrite(R3, R_High);          // Turns on relay 3.
      R3_State = 1;                   // Sets or changes the relay 3 state to ON.
      DUMPS("\r\n Relay 3 is ON");    // Useful while debugging.
    }
    else
    {
      digitalWrite(R3, R_Low);         // Turns on relay 3.
      R3_State = 0;                   // Sets or changes the relay 3 state to OFF.
      DUMPS("\r\n Relay 3 is OFF");   // Useful while debugging.
    }
    delay(100);
    break;
    case 4:
    if(R4_State == 0)
    {
      digitalWrite(R4, R_High);          // Turns on relay 4.
      R4_State = 1;                   // Sets or changes the relay 4 state to ON.
      DUMPS("\r\n Relay 4 is ON");    // Useful while debugging.
    }
    else
    {
      digitalWrite(R4, R_Low);         // Turns off relay 4.
      R4_State = 0;                   // Sets or changes the relay 4 state to OFF.
      DUMPS("\r\n Relay 4 is OFF");   // Useful while debugging.
    }
    delay(100);
    break;
    default : break;
  }
}

// This function is used to control relays via manual switches.
void manualSwitch()
{
  // Operation is done by switching to specified relay.
  a = digitalRead(S1);          // Stores the Switch 1 input in variiable 'a'.
  while(!a == b)                // Executes the loop if change in switch 1 state is detected.
  {
    relayOnOff(1);              // Turns ON/OFF the relay respective to its state.
    b = a;                      // assigns previous input to 'b' to exit from loop.
  }
  c = digitalRead(S2);
  while(!c == d)
  {
    relayOnOff(2);
    d = c;
  }
  e = digitalRead(S3);
  while(!e == f)
  {
    relayOnOff(3);
    f = e;
  }
  g = digitalRead(S4);
  while(!g == h)
  {
    relayOnOff(4);
    h = g;
  }
}

// This function is used to control relays via Remote switches. (such as mobile app, IR remote, voice commands and etc.,)
void remoteSwitch()
{
  switch (Serial.read())
  {
    case 'A':
    relayOnOff(1);
    break;
    case 'B':
    relayOnOff(2);
    break;
    case 'C':
    relayOnOff(3);
    break;
    case 'D':
    relayOnOff(4);
    break;
    default:
    break;
   }
}
