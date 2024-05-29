#include "definitions.h"
#include <ArduinoJson.h>

bool start = true;
bool setPCh = true;
bool PWMCh = true;
bool stateCh = true;

void setup() {
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);

  // Initialise pressure & valves
  for (int i = 0; i < numCham; i++) {
    pinMode(valW[i], OUTPUT);         // Chamber valves
    pinMode(pressW[i], INPUT);        // Pressure sensors

    pinMode(chamPump[i], OUTPUT);     // Pumps
    analogWrite(chamPump[i], 0);
    PWM[findPump[i]] = 0;

    pinMode(valV[findPump[i]][0], OUTPUT);        // Pre-chamber valve 1
    pinMode(valV[findPump[i]][1], OUTPUT);        // Pre-chamber valve 2

    pinMode(pressV[i], INPUT);                    //Pre-chamber pressure
  }

  for (int i = 0; i < numCham + numSeg; i++) {
    pErr[i] = -getPress(allP[i]);
  }
  Serial.begin(9600);       // Serial
  tic = millis();

}

void loop() {
  // Check for serial, and moce DoF if needed.
  serialCheck();
  dofCheck();

  for (int i = 0; i < numCham; i++) {
    chamPress[i] = getPress(pressW[i]);
    updateStatus(i);
    pressControl(i);

    safetyCheck(i);
  }
  tic = millis();
  jsonConstructor();
}
