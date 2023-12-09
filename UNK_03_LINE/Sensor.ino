void OK() {
  while (1) {
    if (analogRead(A7) < 500) {
      break;
    }
  }
  Beep(100);
}

void swOK() {
  while (1) {
    if (analogRead(A6) < 500) {
      break;
    }
  }
  Beep(100);
}

int OK_PUSH() {
  if (analogRead(A6) > 500)return 0;
  else {
    return 1;
  }
}

void Beep(int delayb) {
  digitalWrite(8, 1);
  delay(delayb);
  digitalWrite(8, 0);
  delay(10);
}

uint8_t sck = 13;
uint8_t miso = 12;
uint8_t mosi = 11;
uint8_t ssf = 10;

void ReadSensor() {
  for (int _sensor = 0; _sensor < NUM_SENSORS; _sensor++) {
    adc.begin(sck, mosi, miso, ssf);
    F[_sensor] = adc.readADC(F_PIN[_sensor]);
  }
}

void ReadCalibrate() { //ค่าที่ Calibrate แล้ว
  ReadSensor();
  for (int i = 0; i < NUM_SENSORS; i++) {
    unsigned int calmin, calmax;
    long x = 0;
    calmax = MinValue[i];
    calmin = MaxValue[i];
    x = map(F[i], calmin, calmax, 0, 1000);
    if (x < 0) x = 0;
    if (x > 1000) x = 1000;
    F[i] = x;
  }
}

void CalibrateSensor(int pauseTime, int samples) {
  for (int i = 0; i < NUM_SENSORS; i++) {
    MinValue[i] = 1023;
    MaxValue[i] = 0;
  }
  for (int startSamp = 0; startSamp <= samples; startSamp++) {
    ReadSensor();
    for (int i = 0; i < NUM_SENSORS; i++) {
      MinValue[i] = (F[i] <= MinValue[i] ? F[i] : MinValue[i]);
      MaxValue[i] = (F[i] >= MaxValue[i] ? F[i] : MaxValue[i]);
    }
    delay(pauseTime);
  }
}

void ShowCalibrate() { // Calibrate ค่าแสง
  Serial.println("Press OK to Start Calibrate Sensor");
  swOK();
  Serial.println("Calibrating...");
  Beep(100);
  CalibrateSensor(20, 250);
  Beep(100);
  Serial.println("Finish");
  Serial.println("  ");
  Serial.print("int MinValue[NUM_SENSORS] = {");
  for (int i = 0; i < NUM_SENSORS; i++) {
    Serial.print(MinValue[i]);
    if (i < NUM_SENSORS - 1) Serial.print(",");
    else Serial.println("};");
  }

  Serial.print("int MaxValue[NUM_SENSORS] = {");
  for (int i = 0; i < NUM_SENSORS; i++) {
    Serial.print(MaxValue[i]);
    if (i < NUM_SENSORS - 1) Serial.print(",");
    else Serial.println("};");
  }
  while(1);
}


void SerialF() {
  while (1) {
    ReadSensor();
    for (int _serialF = 0; _serialF < NUM_SENSORS; _serialF++) {
      Serial.print(F[_serialF]);
      Serial.print("\t");
    }
    Serial.println("");
    delay(50);
    if (OK_PUSH() == 1) {
      Beep(100);
      break;
    }
  }
}

void SerialFCalibrate() {
  while (1) {
    ReadCalibrate();
    for (int _serialF = 0; _serialF < NUM_SENSORS; _serialF++) {
      Serial.print(F[_serialF]);
      Serial.print("\t");
    }
    Serial.println("");
    delay(50);
    if (OK_PUSH() == 1) {
      Beep(100);
      break;
    }
  }
}

void AutoRef(){
  for (int i=0; i<NUM_SENSORS; i++){
    REF[i] = (MinValue[i] + MaxValue[i]) /2;
  }
}