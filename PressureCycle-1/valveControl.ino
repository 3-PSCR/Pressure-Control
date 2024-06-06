void hold(int i) {
  digitalWrite(valV[findPump[i]][0], HIGH); // Vent Output
  digitalWrite(valV[findPump[i]][1], LOW); // Vent Input

  valveState[findPump[i]] = "HOL";
}

void inflate(int i) {
  digitalWrite(valV[findPump[i]][0], LOW); // Connect Output
  digitalWrite(valV[findPump[i]][1], LOW); // Vent Input

  valveState[findPump[i]] = "INF";
}

void deflate(int i) {
  digitalWrite(valV[findPump[i]][0], HIGH); // Vent Output
  digitalWrite(valV[findPump[i]][1], HIGH); // Connect Input

  valveState[findPump[i]] = "DEF";
}

void lockCham(int i, bool pump) {
  digitalWrite(valW[i], LOW);
  if (pump) {
    hold(i);
    analogWrite(chamPump[i], 0);
    PWM[findPump[i]] = 0;
  }
}

// Before opening valve to a chamber, make sure pressure is equalised
void openCham(int i) {
  // Close chambers on same pump
  digitalWrite(valW[i], LOW);
  digitalWrite(valW[otherCham[i][0]], LOW);
  digitalWrite(valW[otherCham[i][1]], LOW);

  while (getPress(pressV[i]) < chamPress[i] - 2) {
    inflate(i);
    analogWrite(chamPump[i], 255);
    PWM[findPump[i]] = 255;
    delay(5);
  }
  hold(i);
  analogWrite(chamPump[i], 0);
  PWM[findPump[i]] = 0;
  
  digitalWrite(valW[i], HIGH);
}