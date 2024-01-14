#include <digitalWriteFast.h>

const int ICM_Pin = 2;           // Replace with your actual ICM signal pin
const int INJcPin = 3;           // Replace with your actual common injector signal

int NEXTCOIL = 0;

// Enumeration for states
enum EngineState {
  CALIBRATION,
  NORMAL_OPERATION
};

EngineState engineState = CALIBRATION;

// Constants for coil pins
const int COIL_1 = 12;  // Replace with your actual coil 1 pin number
const int COIL_2 = 11;  // Replace with your actual coil 2 pin number
const int COIL_3 = 10;  // Replace with your actual coil 3 pin number
const int COIL_4 = 9;  // Replace with your actual coil 4 pin number

const int INJ_1 = 6;  // Replace with your actual coil 1 pin number
const int INJ_2 = 5;  // Replace with your actual coil 2 pin number
const int INJ_3 = 4;  // Replace with your actual coil 3 pin number
const int INJ_4 = 7;  // Replace with your actual coil 4 pin number

void setup() {
  //Serial.begin(9600);
  pinModeFast(ICM_Pin, INPUT);
  pinModeFast(INJcPin, INPUT);
  
  pinModeFast(INJ_1, INPUT);
  pinModeFast(INJ_2, INPUT);
  pinModeFast(INJ_3, INPUT);
  pinModeFast(INJ_4, INPUT);

  pinModeFast(COIL_1, OUTPUT);
  pinModeFast(COIL_2, OUTPUT);
  pinModeFast(COIL_3, OUTPUT);
  pinModeFast(COIL_4, OUTPUT);
  
  dischargeAllCoils();
  
  attachInterrupt(digitalPinToInterrupt(ICM_Pin), ICM_Interrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(INJcPin), INJ_Interrupt, FALLING);
}

void loop() {
  switch (engineState) {
    case CALIBRATION:
      //Serial.println("Waiting for INJ signal...");
      break;

    case NORMAL_OPERATION:
      // Your normal operation logic goes here
      break;
  }
}

void ICM_Interrupt() {
  int currentState = digitalReadFast(ICM_Pin);

  if (currentState == LOW) {
    //Serial.println("ICM LOW - Discharging all coils");
    dischargeAllCoils();
  } else {
    //Serial.println("ICM HIGH - Firing coil " + String(NEXTCOIL));
    fireCoil(NEXTCOIL);
  }
}

void INJ_Interrupt() {
  int INJ1 = digitalReadFast(INJ_1);
  int INJ2 = digitalReadFast(INJ_2);
  int INJ3 = digitalReadFast(INJ_3);
  int INJ4 = digitalReadFast(INJ_4);

  engineState = NORMAL_OPERATION;
  
  // Add debouncing or delay here if needed

  if (INJ1 == LOW) {
    NEXTCOIL = 3;
    //Serial.println("INJ1 LOW - Setting NEXTCOIL to 3");
  } else if (INJ2 == LOW) {
    NEXTCOIL = 4;
    //Serial.println("INJ2 LOW - Setting NEXTCOIL to 4");
  } else if (INJ3 == LOW) {
    NEXTCOIL = 1;
    //Serial.println("INJ3 LOW - Setting NEXTCOIL to 1");
  } else if (INJ4 == LOW) {
    NEXTCOIL = 2;
    //Serial.println("INJ4 LOW - Setting NEXTCOIL to 2");
  }
}

void fireCoil(int coil) {
  switch (coil) {
    case 1:
      //Serial.println("Firing Coil 1");
      digitalWriteFast(COIL_1, HIGH);
      break;
    case 2:
      //Serial.println("Firing Coil 2");
      digitalWriteFast(COIL_2, HIGH);
      break;
    case 3:
      //Serial.println("Firing Coil 3");
      digitalWriteFast(COIL_3, HIGH);
      break;
    case 4:
      //Serial.println("Firing Coil 4");
      digitalWriteFast(COIL_4, HIGH);
      break;
  }
}

void dischargeAllCoils() {
  //Serial.println("Discharging all coils");
  digitalWriteFast(COIL_1, LOW);
  digitalWriteFast(COIL_2, LOW);
  digitalWriteFast(COIL_3, LOW);
  digitalWriteFast(COIL_4, LOW);
}
