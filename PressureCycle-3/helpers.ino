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
  }
}