/* This is the code to be uploaded to the 
    Arbotix Robot Controller to turn the brake
    on the tether and turn it back.
   
-->To run/upload the code, you MUST use Arduino IDE Version 1.0.6 <--

-->You must also have the Bioloid and AX12 libraries (included with this script) <--
   
  -Sending 'b' turns the brake ~90deg
  -Sending 'r' turns the brake in reverse until 's' is sent
  -Sending 's' stops the break from turning
  
  Here are the possible values to set for servo speeds
     - 0-1023 CCW
     - 1024-2047 CW
     
  Originally written by:
  Davis Hunter - 12/14/2017
  Davis.Hunter@uah.edu
*/

#include <ax12.h>
#include <BioloidController.h>

bool turn = false;
int count = 0;
char input = 'n';

void setup() {
  Serial.begin(9600);
}

void loop() {
  if(Serial.available()) {
    input = Serial.read();
  }
    switch (input) {
      case 'b':
        brake();
        break;
      case 'r':
        reverse();
        break;
      case 's':
        //halt();
        ax12SetRegister2(1, AX_GOAL_SPEED_L, 0);
        break;
      case 'n':
        //null
        break;
      input = 'n';
  }
}

void brake() {
  count++;
  ax12SetRegister2(1, AX_GOAL_SPEED_L, 1088);
  delay(2000);
  input = 's';
}

void halt() {
  ax12SetRegister2(1, AX_GOAL_SPEED_L, 0);
}

void reverse() {
  ax12SetRegister2(1, AX_GOAL_SPEED_L, 63);
}

