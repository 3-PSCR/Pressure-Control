float getPress(char SENS) {
  rawPressure = analogRead(SENS);
  volt = rawPressure * (5.0 / 1023.0);

  // Get index of SENS in error aray
  static float plus;
  for (int i = 0; i < numCham + numSeg; i++) {
    if (allP[i] == SENS) {
      plus = pErr[i];
      break;
    }
  }

  return ((volt - 0.5) * 100.0) + plus;
}

void pressControl(int i) {
  switch (status[i]) {
    case DEF:
      // Fast deflation
      deflate(i);
      digitalWrite(valW[i], HIGH);
      analogWrite(chamPump[i], 150);
      PWM[findPump[i]] = 150;
      PWMCh = true;
      break;
    
    case CRE:
      // Creep deflation
      analogWrite(chamPump[i], 100);
      PWM[findPump[i]] = 100;
      PWMCh = true;

      digitalWrite(valW[i], LOW);
      delay(5);
      deflate(i);

      delay(20);

      hold(i);
      delay(5);
      digitalWrite(valW[i], HIGH);
      
      delay(10);
      break;
    
    case INF:
      // Inflate
      inflate(i);
      digitalWrite(valW[i], HIGH);
      inflateW(i);   // Updates PWM[i]
      analogWrite(chamPump[i], PWM[findPump[i]]);
      break;

    // case LOK: Do nothing.
  }
}

void inflateW(int i) {
  static int localW;

  if (setP[i] <= 28) {
    // Constant for low values
    localW = 72;
  } else {
    // Exponential
    localW = (1.5122 * exp(0.0844 * (setP[i] - 48.39)) + 62) + 20;
  }

  // Apply Integral term
  pError = setP[i] - chamPress[i];
  iPressure[i] = iPressure[i] + pError;
  localW = localW + kI * iPressure[i];

  PWM[findPump[i]] = max(min(localW, 255), 0);
  PWMCh = true;
}