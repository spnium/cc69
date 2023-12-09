void TurnLeft() { // เลี้ยวซ้าย
  // MotorStop(); delay(20);
  Motor(-180, 180); delay(40);
  while (1) {
    Motor(-150, 150);
    ReadCalibrate();
    if (F[2] >= 500) {
      Motor(150, -150); delay(2);
      MotorStop();
      break;
    }
  }
}

void TurnRight() { //เลี้ยวขวา
  // MotorStop(); delay(20);
  Motor(180, -180); delay(40);
  while (1) {
    Motor(150, -150);
    ReadCalibrate();
    if (F[5] >= 500) {
      Motor(-150, 150); delay(2);
      MotorStop();
      break;
    }
  }
}

void TurnAround() { // เลี้ยวซ้าย
  Motor(-120, 120); delay(200);
  while (1) {
    Motor(-120, 120);
    ReadCalibrate();
    if (F[2] >= 500) {
      Motor(120, -120); delay(10);
      MotorStop();
      break;
    }
  }
}