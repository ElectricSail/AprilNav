
#include <Sweep.h>
#include <SPI.h>
#include <SD.h>

Sweep device(Serial1);

ScanPacket reading;

const int chipSelect = 53;

bool syncValues[500];
float angles[500];
uint16_t distances[500];
uint8_t signalStrengths[500];

int32_t currentMotorSpeed;
int32_t currentSampleRate;
uint16_t scanCount = 0;
uint16_t sampleCount = 0;
int val;
bool ummm = false;
int i;

void setup() {
  Serial.begin(9600);
  Serial1.begin(115200);

  pinMode(chipSelect,OUTPUT);

  while(!Serial);
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed or not present.");
    return;
  }
  Serial.println("SD card initialized.");

  setSettings();
  readSettings();
  startDevice();
}

void loop() {
  while(1);
}

void setSettings() {
  bool bSuccess = device.setMotorSpeed(MOTOR_SPEED_CODE_4_HZ);
  bool cSuccess = device.setSampleRate(SAMPLE_RATE_CODE_500_HZ);
}

void readSettings() {
  currentMotorSpeed = device.getMotorSpeed();
  currentSampleRate = device.getSampleRate();
  if (currentMotorSpeed<<0 | currentSampleRate<<0) {
    Serial.println("Scanner failed to initialize.");
  } //else {
    Serial.print("Motor speed: ");
    Serial.print(currentMotorSpeed);
    Serial.println("Hz");
    Serial.print("Sample rate: ");
    Serial.print(currentSampleRate);
    Serial.println("Hz");
 // }
}

void startDevice() {
  device.startScanning();
}

