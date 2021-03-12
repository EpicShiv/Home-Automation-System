# Home Automation System
Code has been provided for both standalone ESP8266 based wifi module (i.e., ESP-12E or ESP-12F or NodeMCU) for all operatios to be done single handedly and also seperate code for your chosen microcontroller to connect with ESP8266 based wifi module.

#### Note:
If you are using any other microcontroller with ESP8266 generic module then you have to upload the code written for them seperately (where actual/main code goes into microcontroller and code for wifi connection goes into ESP8266 generic module.
 
This code is the copy of first version (v1.0) with a few modifications to increase program efficiency and decrease size of program memory to be used.

In this version you can use as many relays and switches as possible by simply changing "x" in "#define No_Of_Relays x" to  number of relays you want to use.

You can debug the code by changing "#define DEBUG 0" to "1", and dont forget to restore it to "0" while uploading the code to the microcontroller.

#### Note:
Unfortunately here we have a limitation of adding relays only upto 26 to control via a remote switch, which is more than enough for a simple/regular home automation system project.

If you are looking for more advanced code relating to Home automation please checkout the repository link given below, which includes different versions depending on various installed transducers and modules.

## Author
Shiva Teja ([@EpicShiv](https://github.com/EpicShiv))

Github link: https://github.com/EpicShiv/Home-Automation-System