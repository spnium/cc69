// void TurnLeft() { // เลี้ยวซ้าย
//   Motor(-100, 100); delay(10);
//   while (1) {
//     Motor(-100, 100);
//     ReadCalibrate();
//     if (F[1] >= 200) {
//       Motor(120, -120); delay(40);
//       MotorStop();
//       break;
//     }
//   }
// }

// void TurnRight() { // เลี้ยวขวา
//   Motor(120, -120); delay(20);
//   while (1) {
//     Motor(120, -120);
//     ReadCalibrate();
//     if (F[6] >= 200) {
//       Motor(-120, 120); delay(40);
//       MotorStop();
//       break;
//     }
//   }
// }


void TurnLeft() {
  Motor(-60, 60);
  delay(20);
  ReadCalibrate();
  while (F[0] < 200) {
    Motor(-60, 60);
    ReadCalibrate();
  }
}

void TurnRight() {
  Motor(60, -60);
  delay(20);
  ReadCalibrate();
  while (F[7] < 200) {
    Motor(60, -60);
    ReadCalibrate();
  }
}