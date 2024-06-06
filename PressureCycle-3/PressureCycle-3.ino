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

  setP[1] = pressSeq[curr];
  setP[4] = pressSeq[curr];
  setP[7] = pressSeq[curr];

  for (int i = 0; i < numCham + numSeg; i++) {
    pErr[i] = -getPress(allP[i]);
  }
  tic = millis();

}

void loop() {
  if (geoffrey == false) {

    for (int i = 0; i < numCham; i++) {
      chamPress[i] = getPress(pressW[i]);
      updateStatus(i);
      pressControl(i);

      safetyCheck(i);
    }
    tic = millis();

    if (status[1] == LOK && status[4] == LOK && status[7] == LOK) {
      geoffrey = true;
    }
  }

  if (geoffrey && millis() - tic >= 1000 && curr < 7) {
    setP[1] = pressSeq[++curr];
    setP[4] = pressSeq[curr];
    setP[7] = pressSeq[curr];
    geoffrey = false;
  }

  // Serial.print(setP[1]);
  // Serial.print(", ");
  // Serial.print(setP[4]);
  // Serial.print(", ");
  // Serial.print(setP[7]);
  // Serial.print(", ");
  Serial.print(millis());
  Serial.print(", ");
  // Serial.print(status[1]);
  // Serial.print(", ");
  // Serial.print(status[4]);
  // Serial.print(", ");
  // Serial.print(status[7]);
  // Serial.print(", ");
  Serial.print(chamPress[1]);
  Serial.print(", ");
  Serial.print(chamPress[4]);
  Serial.print(", ");
  Serial.println(chamPress[7]);
}
