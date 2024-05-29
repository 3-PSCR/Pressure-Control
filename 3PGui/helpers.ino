void serialCheck() {
  if (Serial.available()) {
    char bob[30];
    Serial.readString().toCharArray(bob, sizeof(bob));
    char* token = strtok(bob, ",");
    int size = 0;

    while (token != NULL) {
      if (size < numCham) {
        setP[size] = atoi(token);
        setPCh = true;
        size++;
      } else {DoF = atoi(token);}
      token = strtok(NULL, ",");
    };
  };
}

void dofCheck() {
  if (DoF != 0) {
    switch (DoF) {
      case 1:
        digitalWrite(dirPin, LOW);
        for (int i = 0; i < stepsPerRevolution; i++) {
          digitalWrite(stepPin, HIGH);
          delayMicroseconds(500);
          digitalWrite(stepPin, LOW);
          delayMicroseconds(500);
        };
        break;
      case 2:
        digitalWrite(dirPin, HIGH);
        for (int i = 0; i < stepsPerRevolution; i++) {
          digitalWrite(stepPin, HIGH);
          delayMicroseconds(500);
          digitalWrite(stepPin, LOW);
          delayMicroseconds(500);
        };
        break;
      case 3:
        digitalWrite(dirPin, LOW);
        for (int i = 0; i < 5*stepsPerRevolution; i++) {
          digitalWrite(stepPin, HIGH);
          delayMicroseconds(500);
          digitalWrite(stepPin, LOW);
          delayMicroseconds(500);
        };
        break;
      case 4:
        digitalWrite(dirPin, HIGH);
        for (int i = 0; i < 5*stepsPerRevolution; i++) {
          digitalWrite(stepPin, HIGH);
          delayMicroseconds(500);
          digitalWrite(stepPin, LOW);
          delayMicroseconds(500);
        };
        break;
    }
  } 
  DoF = 0;
}

void jsonConstructor() {
  JsonDocument doc;
  
  if (start) {
    doc["numSeg"] = numSeg;
    doc["numCham"] = numCham;
    start = false;
  }

  doc["boardTime"] = millis();

  if (setPCh) {
    JsonArray PArr = doc.createNestedArray("setP");
    for (int i = 0; i < numCham; ++i) {
      PArr.add(setP[i]);
    }
    setPCh = false;
  }

  if (PWMCh || stateCh) {
    JsonArray PWMArr = doc.createNestedArray("PWM");
    JsonArray ValveArr = doc.createNestedArray("valveState");
    for (int i = 0; i < numSeg; ++i) {
      PWMArr.add(PWM[i]);
      ValveArr.add(valveState[i]);
    }
    PWMCh = false;
    stateCh = false;
  }

  JsonArray PressArr = doc.createNestedArray("chamPress");
  JsonArray StatusArr = doc.createNestedArray("status");

  for (int i = 0; i < numCham; ++i) {
    // if (setPCh) {PArr.add(setP[i]);}
    PressArr.add(round(chamPress[i]*10)/10);
    StatusArr.add(status[i]);
  }

  serializeJson(doc, Serial);
  Serial.println();
}

void updateStatus(int i) {
  // Check that the other chamber on the same pump is not being controlled, and that the chamber is not force locked.
  if (status[otherCham[i][0]] == LOK && status[otherCham[i][1]] == LOK && setP[i] >= 0) {
    if (chamPress[i] > setP[i] + 10) {
      status[i] = DEF;
    } else if (chamPress[i] > setP[i] + 3) {
      status[i] = CRE;
    } else if (chamPress[i] < setP[i] - 2 && status[i] != INF) {
      status[i] = INF;
      openCham(i);
    } else if (chamPress[i] < setP[i] + 1.2 && chamPress[i] > setP[i] - 0.4 && status[i] != LOK) {
      status[i] = LOK;
      lockCham(i, true);
    } // Else one of the statuses will still be active and should not be updated.
  } else {
    status[i] = LOK;
    lockCham(i, false);
  }
}

void safetyCheck(int i) {
  if (chamPress[i] > 100 || chamPress[i] < -10) {
    analogWrite(chamPump[i], 0);
    PWM[findPump[i]] = 0;
    setP[i] = 10;
    PWMCh = true;
    setPCh = true;
  }
}