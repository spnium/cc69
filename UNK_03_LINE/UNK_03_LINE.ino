#include <SPI.h>
#include <Adafruit_MCP3008.h> // v1.0.0
Adafruit_MCP3008 adc;
#define NUM_SENSORS 8
int LastError;
int REF[NUM_SENSORS];
uint8_t F_PIN[NUM_SENSORS] = { 7, 6, 5, 4, 3, 2, 1, 0 };
int F[NUM_SENSORS];

///////////////////////////////////////////////////////////////////////////
int MaxValue[NUM_SENSORS] = {43,44,57,44,42,44,89,41};
int MinValue[NUM_SENSORS] = {574,673,763,611,571,591,547,437};
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

void testStart()
{
  TrackCross(120, 0.035, 0.9, 'l');
  TrackCross(140, 0.035, 0.9, 'l');
  TrackCross(140, 0.035, 0.9, 'l');
  TrackCross(140, 0.035, 0.9, 'l');
  TrackCross(140, 0.035, 0.9, 'l');
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

// segStart();
// seg1();
// segEnd();
// segEndOld();

// TrackCross(100, 0.035, 0.3, 'p');
// TrackTime(120, 0.04, 0.3, 2200);
// TrackCross(100, 0.035, 0.3, 'p');

//gjfhg
// segStartR();
// TrackTime(120, 0.035, 0.3, 18000);
// TrackCross(100, 0.035, 0.3, 'p');
//jhfjfj

// segStartR();
TrackCross(110, 0.035, 0.3, 'l');
seg1R();

// segNew();
}

void seg1R()
{
  TrackTime(80, 0.035, 0.3, 200);
  TrackTime(100, 0.035, 0.3, 100);
  TrackTime(250, 0.035, 0.35, 550);

  TrackTime(190, 0.035, 0.3, 400);
  TrackTime(250, 0.035, 0.3, 400);
  TrackTime(150, 0.035, 0.3, 450);

  //bf minor slant

  TrackTime(140, 0.035, 0.3, 600);

  //af minor slant

  TrackTime(190, 0.035, 0.3, 1100);

  //mid oys

  TrackTime(130, 0.035, 0.3, 700);
  TrackTime(110, 0.035, 0.3, 600);

  //af mid oys

  TrackTime(140, 0.035, 0.3, 700);
  TrackTime(200, 0.035, 0.3, 1600);

  //zig-zag
}

void segStartR()
{
  TrackCross(100, 0.035, 0.3, 'l');
  TrackCross(120, 0.035, 0.3, 'l');
  TrackCross(100, 0.035, 0.3, 'l');
  TrackTime(110, 0.04, 0.3, 2200);
  TrackCross(100, 0.035, 0.3, 'l');
  TrackCross(110, 0.035, 0.3, 'l');
  TrackCross(110, 0.035, 0.3, 'l');
}

void loop() {
  MotorStop();
}
