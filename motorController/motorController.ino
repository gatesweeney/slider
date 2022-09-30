// 'Stepper Controller'
// created by Gates Sweeney
// 2020

//Libraries
#include <DueTimer.h>
#include <Encoder.h>

// x pins
#define plsPinX 23
#define plsGndX 25
#define dirPinX 27
#define dirGndX 29
#define mfX 31
#define mfGndX 33
// y pins
#define plsPinY 1
#define plsGndY 1
#define dirPinY 1
#define dirGndY 1
#define mfY 1
#define mfGndY 1

// other variables
int plsX = 0;
int plsY = 0;
int posX = 0;
int posY = 0;
int spdIn = 10; // 1 - 100
int spdOut = 0; // counts
int spdDefault = 100000; // speed for actions not involving user (constant)
int track = 3511200; // total steps on track (constant)

// isr variable
int SPEEDX = spdDefault;
int COUNTX = 0; //counting ticks taken so far
int SPEEDY = 0;
int COUNTY = 0; //counting ticks taken so far

Encoder myEnc(2,4);

volatile boolean ACTIVEX;
volatile boolean ACTIVEY;

void speedController() //linear model
  {
    SPEEDX = spdIn + 10;
  }


// safety limiter
// TODO position switches that trip when the carrage slides too far right or left
// also used to "zero" the slider on init 
//void safetySwitch(){if ((steps > 351120) or (steps < 0)){ACTIVE = false;}}

//setup

void setup()
{
  delay(1000); // just chill for a sec so the motor doesn't start prematurely
  pinSetup();
  //motor status
  ACTIVEX = true;
  ACTIVEY = false;
  
  // initialize X motor
  Timer3.attachInterrupt(motorControllerX).start(10);

  // initialize Y motor
  Timer4.attachInterrupt(motorControllerY).start(10);

  //get initial speed
  speedController();

}

// encoder
long oldPosition  = -999;
void spdWheel() {
  long newPosition = myEnc.read();
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
  }
  if (newPosition < 0) {newPosition = 0; oldPosition = 0;} else if (newPosition > 1000) {newPosition = 1000; oldPosition = 1000;}
  spdIn = newPosition;
}


void motorControllerX()          // timer overflow interrupt service routine
{

  if (ACTIVEX) // check counter
  {  
    if(COUNTX > SPEEDX){          
      digitalWrite(plsPinX, HIGH);
      COUNTX = 0;
      digitalWrite(plsPinX, LOW );
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
    if(COUNTY > SPEEDY){          
      digitalWrite(plsPinY, digitalRead(plsPinY) ^ 1);
      COUNTY = 0;
    }
    else {
      COUNTY++;
    }
  }
}

void loop()
{
  spdWheel();
  speedController();
  
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
  Serial.begin(9600);

}
