#include <Adafruit_MCP3008.h>

// https://github.com/DBSStore/DBS_Lib

#define NUM_SENSORS 8  //จำนวนเซนเซอร์
int F[NUM_SENSORS];
int REF[NUM_SENSORS];
int LastError;
int x = 0;

Adafruit_MCP3008 adc;

// int MinValue[NUM_SENSORS] = {27,33,46,44,35,32,33,27};
// int MaxValue[NUM_SENSORS] = {259,281,340,374,294,291,299,256};

int MinValue[NUM_SENSORS] = {46,46,56,58,47,48,48,42};
int MaxValue[NUM_SENSORS] = {322,319,363,404,325,329,338,308};

void setup() {
  Serial.begin(9600);
  PHONG_begin();

  digitalWrite(8,HIGH);
  delay(100);
  digitalWrite(8,LOW);
  delay(100);
  digitalWrite(8,HIGH);
  delay(100);
  digitalWrite(8,LOW);
  delay(100);
  Serial.println("ready");
  OK();
  Serial.println("OK");
  AutoRef();
  delay(500);
  // SerialF();
  // SerialCalibrate();
  // ShowCalibrate();

  // Motor(100, -100);
  // delay(1000);
  // MotorStop();

  // TrackTime(baseSpeed, Kp(ปรับขึ้นทีละ 0.01), Kd(ปรับขึ้นทีละ 0.1), delay(milli second))
  // r = right
  // l = left
  // p = pass
  // s = stop

//100 0.05 0.5 TrackTime(100, 0.06, 1.89, 9000);
// TrackCross(100, 0.05, 0.5, 's');
// TrackCross(80, 0.05, 0.5, 'l');
  seg();
  // TrackCross(80, 0.03, 4.2, 'r');
//// TrackCross(80, 0.05, 1.9, 'r');
}

void seg() {

  // TrackCross(80, 0.04, 0.4, 'l');
  // TrackCross(80, 0.04, 0.4, 'l');
  // TrackCross(80, 0.04, 0.4, 'l');
  // TrackCross(80, 0.04, 0.4, 'l');
  TrackCross(80, 0.04, 0.4, 'r');
  TrackCross(80, 0.04, 0.4, 'r');
  TrackCross(80, 0.04, 0.4, 'r');

  TrackTime(100, 0.04, 0.4, 200);
  TrackTime(200, 0.04, 0.4, 280);
  TrackTime(120, 0.04, 0.4, 420);
  TrackTime(200, 0.04, 0.4, 400);
  TrackTime(100, 0.04, 0.4, 200);
  TrackTime(120, 0.04, 0.4, 1000);
  TrackTime(140, 0.04, 0.4, 1800);
  TrackTime(120, 0.04, 0.4, 1000);
  TrackTime(140, 0.04, 0.4, 1500);

  //zz
  TrackTime(80, 0.04, 0.4, 1000);
  //zz

  TrackTime(140, 0.04, 0.4, 1500);
  TrackTime(120, 0.04, 0.4, 2700);
  TrackTime(100, 0.04, 0.4, 800);
  TrackTime(120, 0.04, 0.4, 1600);

  TrackCross(80, 0.04, 0.4, 'r');
  TrackCross(80, 0.04, 0.4, 'r');
  TrackCross(80, 0.04, 0.4, 'r');
  TrackCross(80, 0.04, 0.4, 'r');
  TrackCross(80, 0.04, 0.4, 'r');
  TrackCross(80, 0.04, 0.4, 'r');
  TrackCross(80, 0.04, 0.4, 'r');
  TrackTime(100, 0.04, 0.4, 100);
  TrackTime(200, 0.04, 0.4, 280);

  // while (1) {
  //   PID(80, 0.04, 0.4);
  //   ReadCalibrate();
  //   if (F[2] > 200 && F[5] > 200) {
  //     break;
  //   }
  // }
  // Motor(-60, 60);
  // delay(20);
  // ReadCalibrate();
  // while (F[0] < 200) {
  //   Motor(-60, 60);
  //   ReadCalibrate();
  // }
}

void loop() {
  MotorStop();
  // Serial.println(analogRead(A1));
  // Motor(40, 0);
}
