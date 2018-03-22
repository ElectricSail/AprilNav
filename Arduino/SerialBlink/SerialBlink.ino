
int led = 13;
String readString; //main captured String 
//String angle; //data String
String fuel;
String speed1;
String altidude;

int ind1; // , locations
int ind2;
int ind3;
int ind4;
int ind5;
int ind6;
int ind7;
int ind8;
int ind9;

String X, Y, Pitch, Roll, Yaw, X_Vel, Y_Vel, VMAG, angle;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  Serial.begin(57600);
  pinMode(led, OUTPUT);
  Serial.println("Serial Test");  
}

// the loop routine runs over and over again forever:
void loop() {
  /*
  if (Serial.available()) {
    if (Serial.read() == '1'){
      digitalWrite(led, HIGH);
      Serial.write("Good Job!\n");
    }
    else{
      digitalWrite(led, LOW);
      Serial.write("FAIL!\n");
    }
    */
    
    
    //Expect a string like 1.1234,2.454,-2.765*
    
//expect a string like 90,low,15.6,125*
  //or 130,hi,7.2,389*
  
  
  //Variable input X,Y,PITCH,ROLL,YAW,X_VEL,Y_VEL,VMAG,Angle*
  //Variable input X,Y,PITCH,ROLL,YAW,X_VEL,Y_VEL,VMAG,Angle*

  if (Serial.available())  {
    char c = Serial.read();  //gets one byte from serial buffer
    if (c == '*') {
      //do stuff
      
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
      angle = readString.substring(ind8); //captures remain part of data after last ,

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
      
      readString=""; //clears variable for new input
      angle="";
      fuel="";
      speed1="";
      altidude="";
    }  
    else {     
      readString += c; //makes the string readString
    }
  }
}
