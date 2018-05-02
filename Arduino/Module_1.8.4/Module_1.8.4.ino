/* This code is for the Arduino controlling the Mobile Simulator
 *  You MUST be using Arduino IDE 1.8.4; it will not work on 1.0.6.
 * This script has been through MANY iterations, so there may be some vestigial variables.
 * 
 * There is extensive use of millis() timers, but you should probably know that "widdershins" 
 *  means counter-clockwise.
 *  
 * Make sure you have all of the libraries shown below, all are included in the "libraries"
 *  folder included with this file, but you will need to import them.
 * 
 * Originally written by:
 *  Davis Hunter - 12/14/2017
 *  Davis.Hunter@uah.edu
 *  
 * Adapted by:
 *  Tristan Schuler & Greta Studier - 5/2/18
 *  tkschuler@yahoo.com
 *  gretastudier@yahoo.com
 */

#include <SPI.h>
#include <SD.h>
#include <HX711.h>
#include <Wire.h>
#include <LIDARLite.h>

#define calFac 22220
#define DAT 24                          // Data pin for Load Cell
#define CLK 26                          // Clock pin for Load Cell

char incoming = 'n';
char incoming2 = 'n';
char dir;
char val;
String commandString = "";
String tensionString = "";
String distanceString = "";
bool fS = false;                        // Tension state
bool fRS = false;                       // Tension recording state
bool tS = false;                        // Thrust state
bool eS = false;                        // Emergency state
bool bS = false;                        // Switch for buzzer
bool pS = false;                        // Pulse mode state
bool tN = false;                        // Switch for thrusting
bool dS = false;                        // Delay 
unsigned long pres = 100;
unsigned long sec;
unsigned long milNewP = 1;              // Pressure timer
unsigned long milOldP = 0;
unsigned long milNewT = 1;              // Thrust timer
unsigned long milOldT = 0;
unsigned long milNewF = 1;              // Tension (force) reading timer
unsigned long milOldF = 0;
unsigned long milNewFT = 1;             // Tension recording timer
unsigned long milOldFT = 0;
unsigned long milNewE = 1;              // Low pressure timer
unsigned long milOldE = 0;
unsigned long milNewD = 1;              // Distance reading timer
unsigned long milOldD = 0;
unsigned long milNewDT = 1;             // Distance recording timer
unsigned long milOldDT = 0;
unsigned long pressure;
int thrustTime = 50;                    // Time solenoids reamin open (ms)(50)
int thrustDelay = 400;                  // Time between thrusts (same as ground station)(400)
int tensTime = 50;                      // Time between tension readings
int tensRecTime = 1000;                 // Time between writing tension recordings
int eTime = 500;                        // Buzzer & LED delay for low-pressure
int presTime = 100;                     // Time between measuring pressure
int distTime = 10;                      // Time between distance measurements
int distRecTime = 1000;                 // Time between distance recordings
int slaveSelect = 53;
int dist;
float tens;                             // Tension variable
byte gatePressure = 45;                 // Minimum pressure to signal low pressure

int ind1, ind2, ind3, ind4, ind5, ind6, ind7, ind8, ind9; // , locations
String X, Y, Pitch, Roll, Yaw, X_Vel, Y_Vel, VMAG, angle; // Variables
String readString; //main captured String

HX711 scale(DAT,CLK);
LIDARLite myLidarLite;

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);
  Serial3.begin(9600);

  pinMode(A10, INPUT);                  // Pressure Transducer Pin

  pinMode(25,OUTPUT);                   // LED signals for Thrusters
  pinMode(27,OUTPUT);
  pinMode(29,OUTPUT);
  pinMode(31,OUTPUT);
  pinMode(3,OUTPUT);                    // Thruster outputs
  pinMode(4,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(33,OUTPUT);                   // Emergency LED
  pinMode(35,OUTPUT);                   // Emergency Buzzer
  pinMode(39,OUTPUT);                   // Laser Pointer
  pinMode(48,INPUT);                    // Card Detect for SD
  pinMode(slaveSelect, OUTPUT);         // uSD Slave Select

  digitalWrite(slaveSelect, LOW);       // uSD initialization
  while (!Serial);
  SD.begin(slaveSelect);

  scale.set_scale();                    // Strain gauge initialization
  scale.tare();
  scale.set_scale(calFac);

  myLidarLite.begin(0,true);            // Lidar initialization
  myLidarLite.configure(0);
} 

void loop() {
  if (Serial2.available()) {
    incoming = Serial2.read();
    func(incoming);
}
  if (Serial3.available())  {
    incoming2 = Serial3.read();
    func2(incoming2);
    //char c = Serial3.read();  //gets one byte from serial buffer
    //Serial.println(c);
    //parseInput(c);
  }
  
  timers();
  if (eS)
    lowPressure();
}

void func(char incoming) {              // Interpreting inputs
  switch (incoming) {
    case 'n':                             // Null case
      break;
    case 'x':
      digitalWrite(27, HIGH);
      digitalWrite(29, HIGH);
      digitalWrite(31, HIGH);
      break;
    case 'a':                             // Turn laser on
      digitalWrite(37, HIGH);
      break;
    case 'z':                             // Turn laser off
      digitalWrite(37, LOW);
      break;
    case 'f':                             // Pulse forward
      thrust('f');
      break;
    case 'b':                             // Pulse backward
      thrust('b');
      break;
    case 'r':                             // Pulse right
      thrust('r');
      break;
    case 'l':                             // Pulse left
      thrust('l');
      break;
    case 'c':                             // Pulse clockwise
      thrust('c');
      break;
    case 'w':                             // Pulse widdershins
      thrust('w');
      break;
    case 'g':                             // Enable data collection
      fRS = true;
      break;
    case 'h':                             // Disable data collection
      fRS = false;
      break; 
  }
  storeCommand();
  incoming = 'n';
}

void func2(char incoming2) {              // Interpreting inputs
  //Serial.println(incoming2);
  switch (incoming2) {
      case 'n':                             // Null case
        Serial.println(incoming2);            //print in arduino
        Serial3.println("Do nothing");           //print in Read.py on pi
        break;
      case 'c':                             // Pulse clockwise
        thrust('c');
        Serial.println(incoming2);
        Serial3.println("move clockwise");
        break;
      case 'w':                             // Pulse widdershins
        thrust('w');
        Serial.println(incoming2);
        Serial3.println("move counterclockwise");
        break;
      case 'f':                             // Pulse clockwise
        thrust('f');
        Serial.println(incoming2);
        Serial3.println("move forward");
        break;
      case 'b':                             // Pulse clockwise
        thrust('b');
        Serial.println(incoming2);
        Serial3.println("move backward");
        break;
      case 'r':                             // Pulse clockwise
        thrust('r');
        Serial.println(incoming2);
        Serial3.println("move right");
        break;
      case 'l':                             // Pulse clockwise
        thrust('l');
        Serial.println(incoming2);
        Serial3.println("move left");
        break;
      default:
        Serial3.println("!");
        break;
  }
}


void timers() {
  milNewF = millis();
  milNewFT = millis();
  milNewP = millis();
  milNewD = millis();
  milNewDT = millis();
  milNewT = millis();

  if (tS && milNewT - milOldT >= thrustTime) {
    tS = false;
    off();
  }

  if (milNewF - milOldF >= tensTime && fRS) {
    getTens();
    milOldF = millis();
  }

  if (milNewFT - milOldFT >= tensRecTime && fRS) {
    storeTension();
    milOldFT = millis();
  }

  if (milNewP - milOldP >= presTime && fRS) {
    getPressure();
    milOldP = millis();
  }

  if (milNewD - milOldD >= distTime && fRS) {
    getDistance();
    milOldD = millis();
  }

  if (milNewDT - milOldDT >= distRecTime && fRS) {
    storeDistance();
    milOldDT = millis();
  }
}

void thrust(char dir) {
  switch (dir) {
    case 'f':                           // Pulse forward
      digitalWrite(7, HIGH);
      digitalWrite(8, HIGH);
      digitalWrite(27, HIGH);
      digitalWrite(29, HIGH);
      milOldT = millis();
      
      tS = true;
      break;
    case 'b':                           // Pulse backward
      digitalWrite(3, HIGH);
      digitalWrite(4, HIGH);
      digitalWrite(25, HIGH);
      digitalWrite(31, HIGH);
      milOldT = millis();
      tS = true;
      break;
    case 'r':                           // Pulse right
      digitalWrite(3, HIGH);
      digitalWrite(7, HIGH);
      digitalWrite(25, HIGH);
      digitalWrite(27, HIGH);
      milOldT = millis();
      tS = true;
      break;
    case 'l':                           // Pulse left
      digitalWrite(4, HIGH);
      digitalWrite(8, HIGH);
      digitalWrite(29, HIGH);
      digitalWrite(31, HIGH);
      milOldT = millis();
      tS = true;
      break;
    case 'c':                           // Pulse clockwise
      digitalWrite(4, HIGH);
      digitalWrite(7, HIGH);
      digitalWrite(27, HIGH);
      digitalWrite(31, HIGH);
      milOldT = millis();
      tS = true;
      break;
    case 'w':                           // Pulse widdershins
      digitalWrite(3, HIGH);
      digitalWrite(8, HIGH);
      digitalWrite(25, HIGH);
      digitalWrite(29, HIGH);
      milOldT = millis();
      tS = true;
      break;
    case 's':
      // Null
      break;
  }
}

void off() {
  digitalWrite(3, LOW);                 // Turn off all thrusters
  digitalWrite(4, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(25, LOW);
  digitalWrite(27, LOW);
  digitalWrite(29, LOW);
  digitalWrite(31, LOW);
}

void lowPressure() {                    // Checking for low pressure
  milNewE = millis();
  if (milNewE - milOldE >= eTime) {
    bS = !bS;
    milOldE = milNewE;
    if (bS) {
      digitalWrite(37, HIGH);
      digitalWrite(39, LOW);
    }
    if (!bS) {
      digitalWrite(37, LOW);
      digitalWrite(39, HIGH);
    }
  }
}

void getPressure() {                    // Used for reading pressure
  pressure = analogRead(A10);
  pressure *= 1000000;                  // Converts pressure to psi from kPa
  pressure /= 6894757;
  if (pressure < gatePressure) {
    lowPressure();
    eS = true;
  } else {
    eS  = false;
  }
}

void getTens() {                        // Read tension value from strain gage
  tens = scale.get_units();             // "scale.get_units()" returns a float
  tensionString += millis();
  tensionString += ",";
  tensionString += tens;
  tensionString += ",";
}

void getDistance() {                    // Reads distance from LiDAR
  dist = myLidarLite.distance(true);
  distanceString += millis();
  distanceString += ",";
  distanceString += dist;
  distanceString += ",";
}

void storeCommand() {                   // Record the commands sent to the module
  val = incoming;
  commandString += millis();            // Create string including time and command
  commandString += ",";
  commandString += val;
  File dataFile = SD.open("commands.txt", FILE_WRITE);       // Open/create the file
  dataFile.println(commandString);                           // Write the string
  dataFile.close();                                          // Close the file
  commandString = "";                                        // Clear the string
}

void storeDistance() {                  // Records distance to SD throughout test
  File dataFile = SD.open("distance.txt", FILE_WRITE);       // Open/create the file
  dataFile.println(distanceString);                          // Write the string
  dataFile.close();                                          // Close the file
  distanceString  = "";                                      // Clear the string
}

void storeTension() {                   // Records tension to SD throughout test
  File dataFile = SD.open("tensions.txt", FILE_WRITE);       // Open/create the file
  dataFile.println(tensionString);                           // Write the string
  dataFile.close();                                          // Close the file
  tensionString = "";                                        // Clear the string
}

void parseInput(char c){
    if (c == '^') {
      Serial3.println("No Tags Detected."); 
      Serial.println("No Tags Detected.");
    }
      
  
     if (c == '*') {
      //do stuff

      //readString.remove(0, 1); //THis meesses up very first input. 
      
      Serial3.println();
      Serial3.print("captured String is : "); 
      Serial3.println(readString); //prints string to serial port out

      Serial.println();
      Serial.print("captured String is : "); 
      Serial.println(readString); //prints string to serial port out
      
      ind1 = readString.indexOf(',');  //finds location of first ,
      X = readString.substring(0, ind1);   //captures first data String
      ind2 = readString.indexOf(',', ind1+1 );   //finds location of second ,
      Y = readString.substring(ind1+1, ind2);   //captures second data String
      ind3 = readString.indexOf(',', ind2+1 );
      Pitch = readString.substring(ind2+1, ind3);
      ind4 = readString.indexOf(',', ind3+1 );
      Roll = readString.substring(ind3+1, ind4);
      ind5 = readString.indexOf(',', ind4+1 );
      Yaw = readString.substring(ind4+1, ind5);
      ind6 = readString.indexOf(',', ind5+1 );
      X_Vel = readString.substring(ind5+1, ind6);
      ind7 = readString.indexOf(',', ind6+1 );
      Y_Vel = readString.substring(ind6+1, ind7);
      ind8 = readString.indexOf(',', ind7+1 );
      VMAG = readString.substring(ind7+1, ind8);
      ind9 = readString.indexOf(',', ind8+1 );
      angle = readString.substring(ind8+1); //captures remain part of data after last ,

      //X = 7777;

//Print back to Raspberry Pi

      Serial3.print("X = ");
      Serial3.println(X); 
      Serial3.print("Y = ");
      Serial3.println(Y);
      Serial3.print("Pitch = ");
      Serial3.println(Pitch);
      Serial3.print("Roll = ");
      Serial3.println(Roll);
      Serial3.print("Yaw = ");
      Serial3.println(Yaw);
      Serial3.print("X_Vel = ");
      Serial3.println(X_Vel);
      Serial3.print("Y_Vel = ");
      Serial3.println(Y_Vel);
      Serial3.print("VMAG = ");
      Serial3.println(VMAG);
      Serial3.print("angle = ");
      Serial3.println(angle);
      Serial3.println();

//Print to arduino Serial Port
      Serial.print("X = ");
      Serial.println(X); 
      Serial.print("Y = ");
      Serial.println(Y);
      Serial.print("Pitch = ");
      Serial.println(Pitch);
      Serial.print("Roll = ");
      Serial.println(Roll);
      Serial.print("Yaw = ");
      Serial.println(Yaw);
      Serial.print("X_Vel = ");
      Serial.println(X_Vel);
      Serial.print("Y_Vel = ");
      Serial.println(Y_Vel);
      Serial.print("VMAG = ");
      Serial.println(VMAG);
      Serial.print("angle = ");
      Serial.println(angle);
      Serial.println();

      //for (int i = 0; i < readString.length(); i++)
        //Serial.println(readString[i]);
      
      //readString=""; //clears variable for new input
      readString = "";
      readString;
      X="";
      Y="";
      Pitch="";
      Roll="";
      Yaw="";
      X_Vel="";
      Y_Vel="";
      VMAG="";
      angle="";
    }  
    else {     
      readString += c; //makes the string readString
    }
  } 







