#include <POP32.h>

const int numSensors = 8;
int sensors[numSensors] = {A1, A8, A0, A3, A4, A7, A5, A6};
int sensorVals[numSensors] = {0, 0, 0, 0, 0, 0, 0, 0};

// const int threshold[numSensors] = {1524, 1157, 1693, 1550, 1109, 1561, 1309, 1554};
// const int threshold[numSensors] = {1644, 1386, 1766, 1598, 1138, 1570, 1365, 1505};
// const int threshold[numSensors] = {1406, 1227, 1609, 1537, 1014, 1530, 1240, 1524};
const int threshold[numSensors] = {700, 700, 700, 700, 700, 700, 700, 700};

int sensorFLL = threshold[2];//2678//1610 //เซ็นเซอร์หน้าซ้าย
int sensorFL  = threshold[0];//2555//2054 //เซ็นเซอร์ตรงกลาง
int sensorFR  = threshold[1];//1833//2122//1838 //เซ็นเซอร์ตรงกลาง
int sensorFRR = threshold[3];//2456//2116 //เซ็นเซอร์หน้าขวา
int sensorBLL = threshold[4];//2222//750 //เซ็นเซอร์หน้าซ้าย
int sensorBL  = threshold[6];//2345//622 //เซ็นเซอร์ตรงกลาง
int sensorBR  = threshold[7];//2765//724 //เซ็นเซอร์ตรงกลาง
int sensorBRR = threshold[5];//2654//796 //เซ็นเซอร์หน้าขวา

///////////////////////////////////////////////////////////////////////////
#define MaxSpeedL  70  //ล้อซ้ายความเร็วเดินหน้าเช็คเร็ว
#define MaxSpeedR  70  //ล้อขวาความเร็วเดินหน้าเช็คเร็ว
#define LowSpeedL  20  //ล้อซ้ายความเร็วเดินหน้าเช็คช้า
#define LowSpeedR  20  //ล้อขวาความเร็วเดินหน้าเช็คช้า

///////////////////////////////////////////////////////////////////////////
#define B_MaxSpeedL  30  //ล้อซ้ายความเร็วถอยหลังเช็ค
#define B_MaxSpeedR  30  //ล้อขวาความเร็วถอยหลังเช็ค

///////////////////////////////////////////////////////////////////////////
#define Speed_stage  60   //สปีดการกลับเข้าเส้น ค่าต้องมากกว่า set_to_stage
#define set_to_stage  20 //สปีดการกลับเข้าเส้น 8่ายิ่งน้อยยิ่งกลับตัวแรง

//////////////////////////////////////////////////////////////////////////
#define turn1  180        //หน่วงเวลาในการเลี้ยวซ้าย  ****ใส่เป็นเวลา****** //L
#define turn2  198//200//182//220//245//185//275        //หน่วงเวลาในการเลี้ยวขวา  ****ใส่เป็นเวลา****** //R
#define turnB  235        //หน่วงเวลาในการกลับหลังหัน  ****ใส่เป็นเวลา****** //R
#define Delay  80        //หน่วงเวลาเถอยหลัง ก่อนเลี้ยว ***ใส่เป็นเวลา****

#define FL A1
#define FR A8
#define FLL A0
#define FRR A3
#define BL A5
#define BR A6
#define BLL A4
#define BRR A7

//black > white

///////////////////////////////////////////////////////////////////////////
// long CH[9] = {0, 180, 380, 580, 950, 1100, 1200, 1400};//จับเส้น ใช่กับ FC
long CH[10] = {0, 200, 400, 600, 950, 1100, 1200, 1400, 543, 180};
//จับเส้นระยะการเคลื่อนทีแต่ละช่อง {0,1ช่อง,2ช่อง,3ช่อง,4ช่อง,5ช่อง,6ช่อง,7ช่อง} //หาค่าก่อนใช้งาน

///////////////////////////////////////////////////////////////////////////
long CH1[10] = {0, 280, 470, 695, 950, 1100, 1200, 1400, 680, 420}; //ไม่จับเส็น ใช่กับ T และ FT
//ไม่จับเส็นระยะการเคลื่อนทีแต่ละช่อง {0,1ช่อง,2ช่อง,3ช่อง,4ช่อง,5ช่อง,6ช่อง,7ช่อง} //หาค่าก่อนใช้งาน

///////////////////////////////////////////////////////////////////////////
long CH2[9] = {0, 150, 430, 580, 800, 1100, 1200, 1400}; //จับเส็น ใช่กับ FS
//จับเส็นระยะการเคลื่อนทีแต่ละช่อง {0,1ช่อง,2ช่อง,3ช่อง,4ช่อง,5ช่อง,6ช่อง,7ช่อง} //หาค่าก่อนใช้งาน

///////////////////////////////////////////////////////////////////////////

//FC(ช่อง);วิ่งเช็คดำเช็คข้าง เช่น อยากเดิน 3 ช่องให้ใส่ 3 ได้เลย ไม่นับแผ่นตัวเอง
//FT(ช่อง); วิ่งหน่วงเวลาเช็คข้าง เช่น อยากเดิน 3 ช่องให้ใส่ 3 ได้เลย ไม่นับแผ่นตัวเอง
//T(ช่อง);วิ่งหน่วงเวลา เช่น อยากเดิน 3 ช่องให้ใส่ 3 ได้เลย ไม่นับแผ่นตัวเอง
//BC1();ถอยหลังจากเส้นสีดำ
//BC2();ถอยหลังจากพื้นสีเขียว
//L1();หันขวา
//R1();หันขวา
//RT();กลับหลังหัน
//FS(ช่อง);วิ่งเช็คเขียวเช็คข้าง เช่น อยากเดิน 2 ช่องให้ใส่ 2 ได้เลย ไม่นับแผ่นตัวเอง
//SD1();ทั้งลูกถอยหลัง
//SD2();ทั้งลูกถอยหลังใช้กับ BC2
//TT(40,40,1500); วิ่งข้ามตะเกียบ (ความเร็วล้อซ้าย,ความเร็วล้อขวา,เวลา)
//AO();delay(); หยุดมอเตอร์ หยุดนานหีือเร็วให้ใส่เลขในวงเล็บ
void setup() {
  Serial.begin(9600);
  servo(1, 92);
  waitSW_OK();
  // motor(__MTR_ALL, 20);
  // calibrate();while (1);
  // printSensor(); 
  // releaseCube(); while (1) {}
  // while (analogRead(FL) > 300 || analogRead(FR) > 300) {
  //   motor(__MTR_ALL, 40);
  // }
  motor(__MTR_ALL, 40); delay(180);AO();
  FC(8);
  R1();
  FC(2);
  R1();
  FC(1);
  R1();
  RC(0);
  FC(1);
  L1();
  RC(0);
  FT(CH1[9]);

  releaseCube();
  delay(500);
  RC(1);

  FT(CH1[1]);
  L1();
  RC(0);
  FT(CH1[2]);
  L1();
  FC(2);
  RC(3);
  L1();
  motor(__MTR_ALL, 60); delay(180);AO();delay(200);
  releaseCube();

  RC(3);
  delay(200);
  R1();
  FT(460);
  R1();
  RC(0);
  TT(40,40,1200);
  FC(0);
  
  L1();
  FC(9);
  L1();
  motor(__MTR_ALL, 60); delay(200);AO();delay(200);
  releaseCube();
  motor(__MTR_ALL, -60); delay(220);AO();delay(200);
  RC(0);
  L1();
  RC(0);
  FT(CH1[8]);
  motor(__MTR_ALL, -40); delay(160);AO();delay(200);
  releaseCube();
  delay(500);

  //n
  motor(12, -70);motor(34, -50); delay(240);AO();delay(200);
  L1();
  motor(12, -50);motor(34, -70); delay(185);AO();delay(200);
  FC(0);
  RC(0);
  FC(1);
  L1();
  FT(CH1[1]);
  R1();
  FC(0);
  TT(-40,-40,1200);
  RC(0);
}
///////////////////////////////////////////////////////////////////////////
void loop() {
  // char s[10];
  // sprintf(s, "%ld", analogRead(FL));
  // oled.text(0,0,s);
  // // oled.text(0, 0, "analogRead(A1)");
  // oled.show();
  // delay(500);
  // waitSW_OK();
  // beep();
  // FC(3);
  // R1();
  // BC1();
  // FC(2);
  // R1();
  // BC1();
  // FC(1);
  // R1();
  // BC1();
  // FC(1);
  // L1();
  // BC1();
  // FS(2);
  // SD1();
}

///////////////////////////////////////////////////////////////////////////
void FC (int TIME) { // เดินหน้าเจอเส้น
  long cur = millis();
  while (millis() - cur <= CH[TIME]) {
    if (analogRead(FLL) < sensorFLL  && analogRead(FRR) < sensorFRR) {
      motor(12, MaxSpeedL);   //ล้อซ้ายความเร็วเดินหน้าเช็คเร็ว
      motor(34, MaxSpeedR);   //ล้อขวาความเร็วเดินหน้าเช็คเร็ว
    }
    else if (analogRead(FLL) < sensorFLL && analogRead(FRR) > sensorFRR) {
      AO();
      motor(12, set_to_stage);
      motor(34, Speed_stage);
      delay(50);
      AO();
    }
    else if (analogRead(FLL) > sensorFLL && analogRead(FRR) < sensorFRR) {
      AO();
      motor(12, Speed_stage);
      motor(34, set_to_stage);
      delay(50);
      AO();
    }
  }
  AO();
  delay(10);
  while (analogRead(FL) < sensorFL  || analogRead(FR) < sensorFR) {

    // if (analogRead(FL) > sensorFL || analogRead(FR) > sensorFR || analogRead(FLL) > sensorFLL  || analogRead(FRR) > sensorFRR)
    // {
    //   AO();
    //   break;
    // }
    if (analogRead(FL) < sensorFL  && analogRead(FR) < sensorFR) {
      motor(12, LowSpeedL );  //ล้อซ้ายความเร็วเดินหน้าเช็คช้า
      motor(34, LowSpeedR );  //ล้อขวาความเร็วเดินหน้าเช็คช้า
    }
    else if (analogRead(FL) < sensorFL && analogRead(FR) > sensorFR) {
      motor(12, 50 );
      motor(34, -40 );
    }
    else if (analogRead(FL) > sensorFL && analogRead(FR) < sensorFR) {
      motor(12, -40 );
      motor(34, 50 );
    }
    else {
      break;
    }
    // else if (analogRead(FL) < sensorFL && analogRead(FR) > sensorFR ) {
    //   // motor(12, set_to_stage );
    //   // motor(34, Speed_stage );
    //   motor(12, 55 );
    //   motor(34, -50 );
    // }
    // else if (analogRead(FL) > sensorFL && analogRead(FR) < sensorFR ) {
    //   // motor(12, Speed_stage );
    //   // motor(34, set_to_stage );
    //   motor(12, -50 );
    //   motor(34, 55 );
    // }
  }
  AO();
  // set1();
  while (analogRead(FLL) < sensorFLL) {
    motor(12, 45);
    motor(34, -45);
  }
  AO();
  while (analogRead(FRR) < sensorFRR) {
    motor(12, -45);
    motor(34, 45);
  }
  AO();
  delay(Delay);
  motor(12, -80);
  motor(34, -80);
  delay(Delay);
  AO();
  delay(200);
}

void set1() {
  /////// ปรับแก้ตัวค้านหน้า
  while (analogRead(FLL)  < sensorFLL) {
    // motor(12, 40);
    // motor(34, -45);
    motor(12, -45);
    motor(34, 40);
  }
  AO();

  while (analogRead(FRR) < sensorFRR) {
    // motor(12, -45);
    // motor(34, 40);
    motor(12, 40);
    motor(34, -45);
  }
  AO();
}

void RC (int TIME) {
  long cur = millis();
  while (millis() - cur <= CH[TIME]) {
    if (analogRead(BLL) < sensorBLL  && analogRead(BRR) < sensorBRR) {
      motor(12, -MaxSpeedL);   //ล้อซ้ายความเร็วเดินหน้าเช็คเร็ว
      motor(34, -MaxSpeedR);   //ล้อขวาความเร็วเดินหน้าเช็คเร็ว
    }
    else if (analogRead(BLL) < sensorBLL && analogRead(BRR) > sensorBRR) {
      AO();
      motor(12, -set_to_stage);
      motor(34, -Speed_stage);
      delay(5);
      AO();
    }
    else if (analogRead(BLL) > sensorBLL && analogRead(BRR) < sensorBRR) {
      AO();
      motor(12, -Speed_stage);
      motor(34, -set_to_stage);
      delay(5);
      AO();
    }
  }
  AO();
  delay(10);
  while (analogRead(BL) < sensorBL || analog(BR) < sensorBR) {
    if (analogRead(BL) < sensorBL  && analogRead(BR) < sensorBR) {
      motor(12, -LowSpeedL );  //ล้อซ้ายความเร็วเดินหน้าเช็คช้า
      motor(34, -LowSpeedR );  //ล้อขวาความเร็วเดินหน้าเช็คช้า
    }
    else if (analogRead(BL) < sensorBL && analogRead(BR) > sensorBR) {
      motor(12, -40 );
      motor(34, 50 );
    }
    else if (analogRead(BL) > sensorBL && analogRead(BR) < sensorBR) {
      motor(12, 50 );
      motor(34, -40 );
    }
    else {
      break;
    }
  }
  AO();
  while (analogRead(BLL) < sensorBLL) {
    motor(12, -45);
    motor(34, 45);
  }
  AO();
  while (analogRead(BRR) < sensorBRR) {
    motor(12, 45);
    motor(34, -45);
  }
  AO();
  delay(Delay);
  motor(12, 80);
  motor(34, 80);
  delay(Delay);
  AO();
  delay(200);
}

void RT (int TIME) {
  long cur = millis();
  while (millis() - cur <= CH[TIME]) {
    if (analogRead(BLL) < sensorBLL  && analogRead(BRR) < sensorBRR) {
      motor(12, -MaxSpeedL);   //ล้อซ้ายความเร็วเดินหน้าเช็คเร็ว
      motor(34, -MaxSpeedR);   //ล้อขวาความเร็วเดินหน้าเช็คเร็ว
    }
    else if (analogRead(BLL) < sensorBLL && analogRead(BRR) > sensorBRR) {
      AO();
      motor(12, -set_to_stage);
      motor(34, -Speed_stage);
      delay(50);
      AO();
    }
    else if (analogRead(BLL) > sensorBLL && analogRead(BRR) < sensorBRR) {
      AO();
      motor(12, -Speed_stage);
      motor(34, -set_to_stage);
      delay(50);
      AO();
    }
  }
  AO();
  delay(Delay);
  delay(200);
}

///////////////////////////////////////////////////////////////////////////
void FT (int TIME) {
  long cur = millis();
  while (millis() - cur <= TIME) {
    if (analogRead(A0) < sensorFLL  && analogRead(A3) < sensorFRR) {
      motor(12, MaxSpeedL);   //ล้อซ้ายความเร็วเดินหน้าเช็คเร็ว
      motor(34, MaxSpeedR);   //ล้อขวาความเร็วเดินหน้าเช็คเร็ว
    }
    else if (analogRead(A0) < sensorFLL && analogRead(A3) > sensorFRR) {
      motor(12, set_to_stage);
      motor(34, Speed_stage);
    }
    else if (analogRead(A0) > sensorFLL && analogRead(A3) < sensorFRR) {
      motor(12, Speed_stage);
      motor(34, set_to_stage);
    }
  }
  AO();
  delay(Delay);
  AO();
  delay(200);
}

///////////////////////////////////////////////////////////////////////////
void T (int TIME) {
  long cur = millis();
  while (millis() - cur <= CH1[TIME]) {
    motor(12, MaxSpeedL);   //ล้อซ้ายความเร็วเดินหน้าเช็คเร็ว
    motor(34, MaxSpeedR);   //ล้อขวาความเร็วเดินหน้าเช็คเร็ว
  }
  AO();
}

///////////////////////////////////////////////////////////////////////////
void BC1() {
  while (analogRead(A5) < sensorBL  || analogRead(A6) < sensorBR) {
    motor(12, -B_MaxSpeedL);
    motor(34, -B_MaxSpeedR);
  }
  //ปรับตัวด้านหนัง
  while (analogRead(A4) < sensorBLL) {
    motor(12, -40);
    motor(34, 45);
  }
  while (analogRead(A7) < sensorBRR) {
    motor(12, 45);
    motor(34, -40);
  }
  AO();
  delay(100);
  AO();
  motor(12, 50);
  motor(34, 50);
  delay(Delay);
  AO();
}


///////////////////////////////////////////////////////////////////////////
void BC2() {
  while (analogRead(A5) < sensorBL  || analogRead(A6) < sensorBR) {
    motor(12, -B_MaxSpeedL);
    motor(34, -B_MaxSpeedR);
  }
  //ปรับตัวด้านหนัง
  while (analogRead(A4) < sensorBLL) {
    motor(12, -40);
    motor(34, 45);
  }
  while (analogRead(A7) < sensorBRR) {
    motor(12, 45);
    motor(34, -40);
  }
  AO();
  delay(100);
  AO();
  motor(12, 50);
  motor(34, 50);
  delay(Delay + 85);
  AO();
}

///////////////////////////////////////////////////////////////////////////
void L1() {
  motor(12, -100);
  motor(34, 100);
  delay(turn1);
  AO();
  delay(Delay);
  AO();
  delay(200);
}
void R1() {
  AO();
  motor(12, 100);
  motor(34, -100);
  delay(turn2);
  AO();
  delay(Delay);
  AO();
  delay(200);
}
void R1(int delayTime) {
  AO();
  motor(12, 100);
  motor(34, -100);
  delay(delayTime);
  AO();
  delay(Delay);
  AO();
  delay(200);
}
void RT() {
  motor(12, 90);
  motor(34, -90);
  delay(turnB);
  AO();
  delay(Delay + 50);
  AO();
}


///////////////////////////////////////////////////////////////////////////
void SD2() {
  AO();
  servo(1, 92); //เข้า
  delay(100);
  servo(1, 25), ///ออก
        delay(500);
  servo(1, 92); //เข้า
  motor(12, -60); //ถอยหลังจากทิ้ง
  motor(34, -60); //ถอยหลังจากทิ้ง
  delay(120);//เวลา
  AO();
}
void SD1() {
  AO();
  servo(1, 92); //เข้า
  delay(100);
  servo(1, 25), ///ออก
        delay(500);
  servo(1, 92); //เข้า
  motor(12, -80); //ถอยหลังจากทิ้ง
  motor(34, -80); //ถอยหลังจากทิ้ง
  delay(140);//เวลา
  AO();
}
void FS (int TIME) { // เดินหน้าเจอเส้น
  long cur = millis();
  while (millis() - cur <= CH2[TIME]) {
    if (analogRead(A0) < sensorFLL  && analogRead(A3) < sensorFRR) {
      motor(12, MaxSpeedL);   //ล้อซ้ายความเร็วเดินหน้าเช็คเร็ว
      motor(34, MaxSpeedR);   //ล้อขวาความเร็วเดินหน้าเช็คเร็ว
    }
    else if (analogRead(A0) < sensorFLL && analogRead(A3) > sensorFRR) {
      motor(12, set_to_stage);
      motor(34, Speed_stage);
    }
    else if (analogRead(A0) > sensorFLL && analogRead(A3) < sensorFRR) {
      motor(12, Speed_stage);
      motor(34, set_to_stage);
    }
  }
  AO();
  delay(10);
  while (analogRead(A1) < sensorFL  || analogRead(A8) < sensorFR) {
    if (analogRead(A0) < sensorFLL  && analogRead(A3) < sensorFRR) {
      motor(12, LowSpeedL );  //ล้อซ้ายความเร็วเดินหน้าเช็คช้า
      motor(34, LowSpeedR );  //ล้อขวาความเร็วเดินหน้าเช็คช้า
    }
    else if (analogRead(A0) < sensorFLL && analogRead(A3) > sensorFRR ) {
      motor(12, set_to_stage );
      motor(34, Speed_stage );
    }
    else if (analogRead(A0) > sensorFLL && analogRead(A3) < sensorFRR ) {
      motor(12, Speed_stage );
      motor(34, set_to_stage );
    }
  }
  AO();
  set1();
  AO();
}

///////////////////////////////////////////////////////////////////////////
void TT (int SpeedL, int SpeedR, int TIME) {
  long cur = millis();
  while (millis() - cur <= TIME) {
    motor(12, SpeedL);   //ล้อซ้ายความเร็วเดินหน้าเช็คเร็ว
    motor(34, SpeedR);   //ล้อขวาความเร็วเดินหน้าเช็คเร็ว
  }
  AO();
}

void readSensors() {
  for (int i = 0; i < numSensors; i++) {
    sensorVals[i] = analogRead(sensors[i]);
  }
}

void calibrate() {
  Serial.println("Press OK to start calibrate");
  waitSW_OK();
  Serial.println("Calibrating");

  int minVal[numSensors];
  int maxVal[numSensors];
  int sensorThreshold[numSensors];
  
  for (int i = 0; i < numSensors; i++) {
    minVal[i] = 3000;
    maxVal[i] = 0;
  }

  for (int i = 0; i < 500; i++) {
    readSensors();
    for (int i = 0; i < numSensors; i++) {
      if (sensorVals[i] <= minVal[i]) {
        minVal[i] = sensorVals[i];
      }

      if (sensorVals[i] >= maxVal[i]) {
        maxVal[i] = sensorVals[i];
      }
    }
    Serial.println(i);
    delay(20);
  }

  for (int i = 0; i < numSensors; i++) {
    sensorThreshold[i] = (int)((maxVal[i] + minVal[i]) / 2);
  }

  char sensorPinStrings[numSensors] = {'1', '8', '0', '3', '4', '7', '5', '6'};

  Serial.print("const int threshold[numSensors] = {");
  for (int i = 0; i < numSensors; i++) {
    // Serial.print("A");
    // Serial.print(sensorPinStrings[i]);
    // Serial.print(" : ");
    Serial.print(sensorThreshold[i]);
    if (i != 7) Serial.print(", ");
  }
  Serial.print("};");
}

void printSensor() {
  while (1) {
    readSensors();
    for (int i = 0; i < numSensors; i++) {
      Serial.print(sensorVals[i]);
      Serial.print(" ");
    }
    Serial.println("");
    delay(500);
  }
}

void releaseCube() {
  for (int i = 92; i > 10; i--) {
    servo(1, i);
  }
  delay(500);
  servo(1, 92);
}