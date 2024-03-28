// #define PWMA 5
// #define AIN1 2
// #define AIN2 3

// #define PWMB 6
// #define BIN1 4
// #define BIN2 7

#define PWMA 5
#define AIN1 3
#define AIN2 2 

#define PWMB 6
#define BIN1 7
#define BIN2 4

int maxspeed = 255;

void Motor1(int speedmotor1) {  // Control Motor 1
  bool dir1 = (speedmotor1 >= 0 ? true : false);
  speedmotor1 = abs(speedmotor1);
  if (speedmotor1 > maxspeed) {
    speedmotor1 = maxspeed;
  }
  digitalWrite(AIN1, dir1);
  digitalWrite(AIN2, !dir1);
  analogWrite(PWMA, speedmotor1);
}

void Motor2(int speedmotor2) {  // Control Motor 2
  bool dir2 = (speedmotor2 >= 0 ? true : false);
  speedmotor2 = abs(speedmotor2);
  if (speedmotor2 > maxspeed) {
    speedmotor2 = maxspeed;
  }
  digitalWrite(BIN1, dir2);
  digitalWrite(BIN2, !dir2);
  analogWrite(PWMB, speedmotor2);
}

void Motor(int LeftSpd, int RightSpd) {
  Motor1(LeftSpd);
  Motor2(RightSpd);
}

void MotorStop() {
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);
  delay(10);
  // Motor(-200, -200);
  // delay(20);
  // Motor(0, 0);
}

void powerStop(int speed) {
  Motor(-speed, -speed);
  delay(60);
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);
  delay(10);
}
