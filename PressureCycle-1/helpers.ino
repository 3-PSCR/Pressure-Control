void updateStatus(int i) {
  // Check that the other chamber on the same pump is not being controlled, and that the chamber is not force locked.
  if (setP[0] >= 0) {
    if (chamPress[0] > setP[0] + 10) {
      status[0] = DEF;
    } else if (chamPress[0] > setP[0] + 3) {
      status[0] = CRE;
    } else if (chamPress[0] < setP[0] - 2 && status[0] != INF) {
      status[0] = INF;
      openCham(i);
    } else if (chamPress[0] < setP[0] + 1.2 && chamPress[0] > setP[0] - 0.4 && status[0] != LOK) {
      status[0] = LOK;
      lockCham(i, true);
    } // Else one of the statuses will still be active and should not be updated.
  } else {
    status[0] = LOK;
    lockCham(i, false);
    setP[0] = -1;
  }
}

void safetyCheck(int i) {
  if (chamPress[i] > 100 || chamPress[i] < -10) {
    analogWrite(chamPump[i], 0);
    PWM[findPump[i]] = 0;
    setP[i] = 10;
  }
}