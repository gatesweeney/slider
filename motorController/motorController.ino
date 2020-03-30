// 'Stepper Controller'
// created by Gates Sweeney
// 2020

//Libraries
#include <DueTimer.h>

// x pins
#define plsPinX 8
#define plsGndX 9
#define dirPinX 10
#define dirGndX 11
#define mfX 12
#define mfGndX 13
// y pins
#define plsPinY 1
#define plsGndY 1
#define dirPinY 1
#define dirGndY 1
#define mfY 1
#define mfGndY 1

// isr variable
int SPEEDX = 0;
int COUNTX = 0; //counting ticks taken so far
int SPEEDY = 0;
int COUNTY = 0; //counting ticks taken so far

// other variables
int plsX = 0;
int plsY = 0;
int posX = 0;
int posY = 0;
int spdIn = 10; // 1 - 100
int spdOut = 0; // counts
int spdDefault = 500; // speed for actions not involving user (constant)
int track = 3511200; // total steps on track (constant)

bool ACTIVEX;
bool ACTIVEY;

void speedController() //linear model
{
  // spdIn = 10;
  spdOut = 1;
}


// safety limiter
// TODO position switches that trip when the carrage slides too far right or left
// also used to "zero" the slider on init 
//void safetySwitch(){if ((steps > 351120) or (steps < 0)){ACTIVE = false;}}

//setup

void setup()
{
  //motor status
  ACTIVEX = true;
  ACTIVEY = false;
  // initialize X motor
  Timer.getAvailable().attachInterrupt(motorControllerX).setFrequency(84000000).start();

  // initialize Y motor
  Timer.getAvailable().attachInterrupt(motorControllerY).setFrequency(84000000).start();

  //get initial speed
  speedController();

}


void motorControllerX()          // timer overflow interrupt service routine
{

  if (ACTIVEX) // check counter
  {  
    if(COUNTX > SPEEDX){          
      digitalWrite(plsPinX, digitalRead(plsPinX) ^ 1);
      COUNTX = 0;
      if (digitalRead(dirPinX) == LOW) {posX --;} else {posX ++;}
    }
    else {
      COUNTX++;
    }
  }
}

void motorControllerY()          // timer overflow interrupt service routine
{

  if (ACTIVEY) // check counter
  {  
    if(COUNTY > SPEEDX){          
      digitalWrite(plsPinY, digitalRead(plsPinY) ^ 1);
      COUNTY = 0;
      if (digitalRead(dirPinY) == LOW) {posY --;} else {posY ++;}
    }
    else {
      COUNTY++;
    }
  }
}

void loop()
{

}


void pinSetup() {
  //x motor
  pinMode(plsPinX, OUTPUT);
  pinMode(dirPinX, OUTPUT);
  pinMode(dirGndX, OUTPUT);
  pinMode(plsGndX, OUTPUT);
  pinMode(mfX, OUTPUT);
  pinMode(mfGndX, OUTPUT);
  digitalWrite(dirPinX, HIGH); // high CC, low CCW
  digitalWrite(dirGndX, LOW);
  digitalWrite(plsGndX, LOW);
  digitalWrite(mfX, LOW);
  digitalWrite(mfGndX, LOW);

  // y motor
  pinMode(plsPinY, OUTPUT);
  pinMode(dirPinY, OUTPUT);
  pinMode(dirGndY, OUTPUT);
  pinMode(plsGndY, OUTPUT);
  pinMode(mfY, OUTPUT);
  pinMode(mfGndY, OUTPUT);
  digitalWrite(dirPinY, HIGH); // high CC, low CCW
  digitalWrite(dirGndY, LOW);
  digitalWrite(plsGndY, LOW);
  digitalWrite(mfY, LOW);
  digitalWrite(mfGndY, LOW);
  Serial.begin(115200);

}
