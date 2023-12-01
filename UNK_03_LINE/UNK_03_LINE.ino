#include <SPI.h>
#include <Adafruit_MCP3008.h> // v1.0.0
Adafruit_MCP3008 adc;
#define NUM_SENSORS 8
int LastError;
int REF[NUM_SENSORS];
uint8_t F_PIN[NUM_SENSORS] = { 7, 6, 5, 4, 3, 2, 1, 0 };
int F[NUM_SENSORS];

///////////////////////////////////////////////////////////////////////////
int MaxValue[NUM_SENSORS] = {47,55,64,50,46,49,53,45};
int MinValue[NUM_SENSORS] = {720,821,851,792,761,793,752,625};
///////////////////////////////////////////////////////////////////////////

void segStart()
{
  TrackCross(120, 0.035, 0.9, 'p');
  TrackCross(140, 0.035, 0.9, 'l');
  TrackCross(140, 0.035, 0.9, 'l');
  TrackCross(140, 0.035, 0.9, 'l');
}

void segEnd()
{
  // TrackCross(120, 0.025, 0.9, 'l');
  // TrackCross(140, 0.025, 0.9, 'l');
  // TrackCross(140, 0.025, 0.9, 'l');
  // TrackCross(140, 0.025, 0.9, 'p');
  TrackCross(120, 0.035, 0.9, 'r');
  TrackCross(140, 0.035, 0.9, 'r');
  TrackCross(140, 0.035, 0.9, 'r');
  TrackTime(120, 0.035, 0.9, 2400);
  TrackCross(100, 0.035, 0.9, 'p');
}

void segEndOld()
{
  TrackCross(120, 0.025, 0.9, 'l');
  TrackCross(140, 0.025, 0.9, 'l');
  TrackCross(140, 0.025, 0.9, 'l');
  TrackCross(200, 0.025, 0.9, 'p');
  // TrackCross(120, 0.035, 0.9, 'r');
  // TrackCross(140, 0.035, 0.9, 'r');
  // TrackCross(140, 0.035, 0.9, 'r');
  // TrackTime(120, 0.035, 0.9, 2400);
  // TrackCross(100, 0.035, 0.9, 'p');
}

void seg1() {
  // TrackCross(60, 0.025, 0.9, 's');

  // TrackTime(65, 0.025, 0.9, 800);
  
  // TrackTime(200, 0.025, 0.9, 400);

  // TrackTime(100, 0.025, 0.9, 700);

  // TrackTime(200, 0.025, 0.9, 350);



  // TrackTime(80, 0.025, 0.9, 2700);

  // TrackTime(120, 0.025, 0.9, 500);

  // TrackTime(120, 0.025, 0.9, 500);
  


  // TrackTime(75, 0.025, 0.9, 1300);

  // TrackTime(120, 0.025, 0.9, 1400);

  // TrackTime(120, 0.025, 0.9, 1400);

  // TrackTime(65, 0.025, 0.9, 2400);

  // TrackTime(120, 0.025, 0.9, 3000);

  // TrackTime(80, 0.025, 0.9, 1000);

  // TrackTime(120, 0.025, 0.9, 3000);

  // TrackTime(140, 0.025, 0.9, 900);

  // TrackTime(100, 0.025, 0.9, 900);

  // TrackCross(80, 0.025, 0.9, 's');

  TrackTime(80, 0.06, 0.9, 200);
  TrackTime(240, 0.06, 0.9, 500);
  TrackTime(120, 0.06, 0.9, 200);
  TrackTime(220, 0.06, 0.9, 700);
  TrackTime(100, 0.06, 0.9, 400);
  TrackTime(140, 0.06, 0.9, 2500);
  TrackTime(140, 0.06, 0.9, 800);
  // TrackTime(200, 0.06, 0.9, 2100);
  TrackTime(200, 0.06, 0.9, 1800);
  TrackTime(100, 0.07, 0.9, 1600);
 //after zig-zag
  TrackTime(220, 0.06, 0.9, 1000);
  TrackTime(160, 0.06, 0.9, 600);
  TrackTime(180, 0.06, 0.9, 400);
  TrackTime(120, 0.06, 0.9, 1500);
  TrackTime(200, 0.06, 0.9, 700);

  TrackTime(160, 0.06, 0.9, 1200);

  TrackTime(200, 0.06, 0.9, 1250);


}

void seg2() {
  TrackCross(120, 0.07, 0.9, 'l');

  TrackCross(120, 0.07, 0.9, 'l');
  
  // TrackCross(70, 0.03, 0.9, 's');

  // delay(20);

  // TrackCross(70, 0.03, 0.9, 's');

  TrackCross(120, 0.07, 0.9, 'l');

  TrackCross(120, 0.07, 0.9, 'l');

  TrackCross(120, 0.03, 0.9, 'l');

  // TrackCross(70, 0.03, 0.9, 'r');

  // TrackCross(70, 0.03, 0.9, 'r');
}


void thank()
{
  TrackCross(90,0.06, 1.6, 'l');
  TrackCross(90,0.06, 1.6, 'l');
  TrackCross(90,0.06, 1.6, 'l');
  TrackTime(90, 0.2, 2.5, 77500);
  TrackTime(90, 0.2, 2.5, 77500);
  TrackCross(90,0.06, 1.5, 'l');
  TrackCross(90,0.06, 1.5, 'l');
  TrackCross(90,0.06, 1.5, 'l');
  TrackTime(90, 0.15, 1.5, 2500);
  TrackCross(90,0.06, 1.5, 'l');
  TrackCross(90,0.06, 1.5, 'l');

}

void segNew()
{
  TrackTime(80, 0.06, 0.9, 200);
  TrackTime(240, 0.06, 0.9, 500);
  TrackTime(180, 0.06, 0.9, 800);
  // TrackTime(220, 0.06, 0.9, 700);
}

void setup()
{
  Serial.begin(9600);
  // analogReadResolution(10);
  for (int i = 2; i <= 8; i++) {
    pinMode(i, OUTPUT);
  }
  Beep(20);
  // delay(100);
  // Beep(100);


  swOK();
  delay(500);
  //SerialFCalibrate();
    //  SerialF();
        // ShowCalibrate();
  /////1750//////

  // TrackCross(60, 0.03, 0.9, 's');

  // TrackTime(100, 0.04, 0.9, 800);
  
  // TrackTime(200, 0.03, 0.9, 500);

  // TrackTime(80, 0.04, 0.9, 800);

  // TrackTime(200, 0.03, 0.9, 500);

  // TrackTime(80, 0.04, 0.9, 800);

  // TrackTime(120, 0.04, 0.9, 800);

  // TrackTime(120, 0.04, 0.9, 2000);

  // TrackTime(80, 0.04, 0.9, 800);

  // TrackTime(120, 0.04, 0.9, 2000);

  // TrackTime(180, 0.04, 0.9, 2000);

//2

  // TrackTime(65, 0.03, 0.9, 800);
  
  // TrackTime(200, 0.03, 0.9, 400);

  // TrackTime(80, 0.03, 0.9, 800);

  // TrackTime(200, 0.03, 0.9, 350);

  // //TrackTime(65, 0.03, 0.9, 900);

  // TrackTime(80, 0.03, 0.9, 2700);

  // TrackTime(120, 0.03, 0.9, 500);

  // TrackTime(80, 0.03, 0.9, 700);
  
  // TrackTime(60, 0.9 , 0.2, 2000);

  // TrackTime(80, 0.03, 0.9, 1500);

  // TrackTime(120, 0.03, 0.9, 1900);

  // TrackTime(65, 0.04, 0.9, 2200);
//2

segStart();
seg1();
// segEnd();
segEndOld();
// TrackCross(120, 0.035, 0.9, 'p');
//   TrackCross(140, 0.035, 0.9, 'l');
//   TrackCross(140, 0.035, 0.9, 'l');
//   TrackCross(140, 0.035, 0.9, 'l');
// TrackTime(120, 0.035, 0.9, 2500);
// TrackCross(100, 0.035, 0.9, 's');
// segNew();

    //  thank();

// seg2();

// TrackCross(120, 0.085, 0.9, 'r');
// TrackCross(120, 0.085, 0.9, 'l');
// TrackCross(120, 0.085, 0.9, 'r');
}

void loop() {
  //TrackTime(80, 0.03 , 0.9, 300);
  MotorStop();
}
