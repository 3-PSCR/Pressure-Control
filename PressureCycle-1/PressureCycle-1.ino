#include "definitions.h"
#include <ArduinoJson.h>

bool geoffrey = false;
int pressSeq[8] = {80, 0, 50, 30, 80, 0, 20, 0};
int curr = 0;

void setup() {
  Serial.begin(9600);       // Serial
  delay(5000);
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

  setP[0] = pressSeq[curr];
  tic = millis();
}

void loop() {
  delay(50);
  if (geoffrey == false) {
    chamPress[0] = getPress(pressW[0]);
    updateStatus(0);
    pressControl(0);

    tic = millis();

    if (status[0] == LOK) {
      geoffrey = true;
    }
  }

  if (geoffrey && millis() - tic >= 1000) {
    setP[0] = pressSeq[++curr];
    geoffrey = false;
  }

  safetyCheck(0);

  Serial.print(setP[0]);
  Serial.print(", ");
  Serial.print(millis());
  Serial.print(", ");
  Serial.print(status[0]);
  Serial.print(", ");
  Serial.println(chamPress[0]);
}
