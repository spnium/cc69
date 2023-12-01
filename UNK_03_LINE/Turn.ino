void TurnLeft() { // เลี้ยวซ้าย
  Motor(-120, 120); delay(90);
  while (1) {
    Motor(-120, 120);
    ReadCalibrate();
    if (F[2] >= 500) {
      // Motor(120, -120); delay(2);
      MotorStop();
      break;
    }
  }
}

void TurnRight() { // เลี้ยวขวา
  Motor(120, -120); delay(90);
  while (1) {
    Motor(120, -120);
    ReadCalibrate();
    if (F[5] >= 500) {
      // Motor(-120, 120); delay(2);
      MotorStop();
      break;
    }
  }
}
