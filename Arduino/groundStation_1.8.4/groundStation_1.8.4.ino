/* This code is for the Arduino on the ground controlling the Mobile Simulator
 *  You MUST be using Arduino IDE 1.8.4; it will not work on 1.0.6.
 * This script has been through MANY iterations, so there may be some vestigial variables.
 * 
 * There is extensive use of millis() timers, but other than that it should be fairly simple.
 * 
 * Originally written by:
 *  Davis Hunter - 12/14/2017
 *  Davis.Hunter@uah.edu
 */

bool turnStateNew = false;               // Switch states
bool turnStateOld = false;
bool pulseState = true;
bool pulseState_NEW = true;
bool laserStateNew = false;
bool laserStateOld = false;
bool recordStateNew = false;
bool recordStateOld = false;
bool thrustState = false;
bool pSwitch = true;
bool var = false;

unsigned long milNewC = 1;
unsigned long milOldC = 0;
unsigned long milNewP = 1;
unsigned long milOldP = 0;

int thrustDelay = 200;
int pDelay = 10;
int thrustGap = 50;

int xRaw;                                  // Variables used for the control stick
int yRaw;
int zRaw;
int xVal;
int yVal;
int zVal;
int xValO;
int yValO;
int zValO;
int Port42;
int Port44;
int Port46;
int Port48;
int Port50;
int Port52;
bool butn;
bool butnO;

char incXbee;                              // Logic variables
char cas;

void setup() {
  Serial.begin(9600);                      // Just for Serial Monitor
  Serial1.begin(9600);                     // Radio to Arbotix
  Serial2.begin(9600);                     // Radio to module

  pinMode(29,OUTPUT);                      // Laser state indicator         (RED)
  pinMode(27,OUTPUT);                      // Recording state indicator     (GRN)
  pinMode(25,OUTPUT);                      // Pulse state indicator         (YLO)
  pinMode(23,OUTPUT);                      // Brake reverse Indicator       (WHT)

  pinMode(A15,INPUT);                      // X-axis
  pinMode(A14,INPUT);                      // Y-axis
  pinMode(A13,INPUT_PULLUP);               // Button
  pinMode(A12,INPUT);                      // Z-axis

                                                 // These are the new controller ports
  pinMode(42,INPUT_PULLUP);                      // r
  pinMode(44,INPUT_PULLUP);                      // w
  pinMode(46,INPUT_PULLUP);                      // b
  pinMode(48,INPUT_PULLUP);                      // l 
  pinMode(50,INPUT_PULLUP);                      // c
  pinMode(52,INPUT_PULLUP);                      // f
  
                                           // The following labels are:   (LED/WIRE)
  pinMode(22,INPUT_PULLUP);                // Reposition brake switch     (PRP/WHT)
  pinMode(24,INPUT_PULLUP);                // Recording data switch       (BLU/BLU)
  pinMode(26,INPUT_PULLUP);                // Laser switch                (GRN/RED)
  pinMode(28,INPUT_PULLUP);                // Pulse mode switch           (YLO/YLO)

  turnStateNew = digitalRead(22);
  laserStateNew = digitalRead(28);
  recordStateNew = digitalRead(24);

  //stickPulse_NEW();
}

void loop() {
  states();
  if (pulseState) {
    stickPulse_NEW();
  } else {
    stickConst_NEW();
  }

  if (Serial2.available()) {
    incXbee = Serial2.read();
    Serial.println(incXbee);
  }
}

void states() {                            // This is used for general refreshing of switches and possible states
  turnStateOld = turnStateNew;
  turnStateNew = digitalRead(22);
  recordStateOld = recordStateNew;
  recordStateNew = digitalRead(24);
  laserStateOld = laserStateNew;
  laserStateNew = digitalRead(26); 
  pulseState = digitalRead(28);
  Port42 = digitalRead(42);
  Port44 = digitalRead(44);
  Port46 = digitalRead(46);
  Port48 = digitalRead(48);
  Port50 = digitalRead(50);
  Port52 = digitalRead(52);
  
  
  ///////////////////////////////////////////////
   if (Port42==0) {                        // Port 42 on Arduino, for remote control  
     Serial.println("Left Brown");               //Left Brown
   } 
     if (Port44==0) {                        // Port 44 on Arduino, for remote control 
     Serial.println("CW Yellow");                  //CW Yellow
     }
     if (Port46==0) {                        // Port 46 on Arduino, for remote control 
     Serial.println("Forward Blue");              //Forward Blue
     }
     if (Port48==0) {                        // Port 48 on Arduino, for remote control 
     Serial.println("Right Red");            //Right Red                 
   }
     if (Port50==0) {                        // Port 50 on Arduino, for remote control 
     Serial.println("CCW Green");                    //CCW Green
   } 
     if (Port52==0) {                        // Port 52 on Arduino, for remote control 
     Serial.println("Back Black");                      //Back Black
   } 
  ////////////////////////////////////////////////
   
    
    if (pulseState) {                        // Used to differentiate between constant/single pulse modes
    digitalWrite(25,HIGH);                 // Tied to the yellow LED on the breadboard, and the yellow switch
  } else {
    digitalWrite(25,LOW);
  }

  if (turnStateOld != turnStateNew) {      // Used to turn the tether brake backward
    if (turnStateNew) {
      Serial1.print('r');
      delay(2);
      digitalWrite(23,HIGH);
    } else {
      Serial1.print('s');
      delay(2);
      digitalWrite(23,LOW);
    }
  }

  if (laserStateNew != laserStateOld) {   // Used to turn the laser on/off (but NOT CURRENTLY IN USE)
    if (laserStateNew) {
      Serial2.print('a');
      delay(2);
      digitalWrite(29,HIGH);
    } else {
      Serial2.print('z');
      delay(2);
      digitalWrite(29,LOW);
    }
  }

  if (recordStateNew != recordStateOld) {  // Used to turn on/off data recording
    if (recordStateNew) {                  // Tied to the green LED on the breadboard & the blue switch
      Serial2.print('g');
      delay(2);
      digitalWrite(27,HIGH);
    } else {
      Serial2.print('h');
      delay(2);
      digitalWrite(27,LOW);
    }
  }
}


void readStick() {                         // Used to read the current input from the control stick
  xRaw = analogRead(A15); 
  yRaw = analogRead(A14);
  zRaw = analogRead(A12);
  butnO = butn;
  butn = digitalRead(A13);                 // Button default HIGH
  
  /* Neutral Zones:
   *  X: 250 - 800
   *  Y: 250 - 800
   *  Z: 15 - 400
   */

  if (!butn && butnO != butn)
    Serial1.print('b');
  
  if (xRaw < 250) {                        // Set xVal = -1 for left tilt
    xVal = -1;
  } else if (xRaw > 800) {                 // Set xVal = 1 for right tilt
    xVal = 1;
  } else {
    xVal = 0;                              // Set xVal = 0 for no tilt
  }

  if (yRaw < 250) {                        // Set yVal = 1 for up tilt
    yVal = 1;
  } else if (yRaw > 800) {                 // Set xVal = -1 for down tilt
    yVal = -1;
  } else {
    yVal = 0;                              // Set xVal = 0 for no tilt
  }

  if (zRaw < 15) {                         // Set zVal = 1 for clockwise
    zVal = -1;    
  } else if (zRaw > 300) {                 // Set zVal = -1 for widdershins
    zVal = 1;
  } else {   
    zVal = 0;                              // Set zVal = 0 for no rotation
  }
}


void stickPulse() {                        // Thrusting with single pulses
  readStick();                             // The stick has to go back to the neutral position before sending another pulse command
  milNewP = millis();

  if (xVal == 0 && yVal == 0 && zVal == 0)
    pSwitch = true;
  
  if (milNewP - milOldP >= pDelay && pSwitch) {
    milOldP = milNewP;
    if (xVal == 1) {
      Serial2.print('r');
      delay(1);
      pSwitch = false;
    } else if (xVal == -1) {
      Serial2.print('l');
      delay(1);
      pSwitch = false;
    } else if (yVal == 1) {
      Serial2.print('f');
      delay(1);
      pSwitch = false;
    } else if (yVal == -1) {
      Serial2.print('b');
      delay(1);
      pSwitch = false;
    } else if (zVal == 1) {
      Serial2.print('c');
      delay(1);
      pSwitch = false;
    } else if (zVal == -1) {
      Serial2.print('w');
      delay(1);
      pSwitch = false;
    }
  }
}



void stickPulse_NEW() {                        // Thrusting with single pulses
  //readStick();                             // The stick has to go back to the neutral position before sending another pulse command
  milNewP = millis();

  if (Port42 == 1 && Port44 == 1 && Port46 == 1 && Port48 == 1 && Port50 == 1 && Port52 == 1){
    pSwitch = true;}
  
  if (milNewP - milOldP >= pDelay && pSwitch) {
    milOldP = milNewP;
    if (Port42 == 0) {
      Serial2.print('r');
      delay(1);
      pSwitch = false;
    } else if (Port44 == 0) {
      Serial2.print('w');
      delay(1);
      pSwitch = false;
    } else if (Port46 == 0) {
      Serial2.print('b');
      delay(1);
      pSwitch = false;
    } else if (Port48 == 0) {
      Serial2.print('l');
      delay(1);
      pSwitch = false;
    } else if (Port50 == 0) {
      Serial2.print('c');
      delay(1);
      pSwitch = false;
    } else if (Port52 == 0) {
      Serial2.print('f');
      delay(1);
      pSwitch = false;
    }
  }
}

void stickConst() {                      // Thrusting with constant pulses
  readStick();
  milNewC = millis();

  if (milNewC - milOldC >= thrustDelay) {
    if (xVal == 1) {
      Serial2.print('r');
      delay(1);
    } else if (xVal == -1) {
      Serial2.print('l');
      delay(1);
    } else if (yVal == 1) {
      Serial2.print('f');
      delay(1);
    } else if (yVal == -1) {
      Serial2.print('b');
      delay(1);
    } else if (zVal == 1) {
      Serial2.print('c');
      delay(1);
    } else if (zVal == -1) {
      Serial2.print('w');
      delay(1);
    }
    milOldC = milNewC;
  }
}

void stickConst_NEW() {                      // Thrusting with constant pulses
  readStick();
  milNewC = millis();

  if (milNewC - milOldC >= thrustDelay) {
    if (Port42 == 0) {
      Serial2.print('r');
      delay(1);
    } else if (Port44 == 0) {
      Serial2.print('w');
      delay(1);
    } else if (Port46 == 0) {
      Serial2.print('b');
      delay(1);
    } else if (Port48 == 0) {
      Serial2.print('l');
      delay(1);
    } else if(Port50 == 0) {
      Serial2.print('c');
      delay(1);
    } else if (Port52 == 0) {
      Serial2.print('f');
      delay(1);
    }
    milOldC = milNewC;
  }
}
