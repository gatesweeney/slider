// 'Stepper Controller'
// created by Gates Sweeney
// 2020

// variables
#define plsPin 8
#define plsGnd 9
#define dirPin 10
#define dirGnd 11
#define mf 12
#define mfGnd 13

int SPEED = 0;
int count = 0; //counting ticks taken so far

int pls = 0;
int pos = 0;
int spdIn = 10; // 1 - 100
int spdOut = 0; // counts
int spdDefault = 500; // speed for actions not involving user (constant)
int track = 3511200; // total steps on track (constant)



bool ACTIVE;

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

  pinMode(plsPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(dirGnd, OUTPUT);
  pinMode(plsGnd, OUTPUT);
  pinMode(mf, OUTPUT);
  pinMode(mfGnd, OUTPUT);
  digitalWrite(dirPin, HIGH); // high CC, low CCW
  digitalWrite(dirGnd, LOW);
  digitalWrite(plsGnd, LOW);
  digitalWrite(mf, LOW);
  digitalWrite(mfGnd, LOW);
  Serial.begin(115200);
  speedController();

  ACTIVE = true;

  

// initialize timer1 

  noInterrupts();           // disable all interrupts

  TCCR1A = 0;

  TCCR1B = 0;

  TCNT1 = 0;
  
  OCR1A = 100;              // preload timer 2000000/100 = 20000 --> 10KHz

  TCCR1B |= (1 << WGM12);   // CTC mode

  TCCR1B |= (1 << CS11);    // 8 prescaler 16000000/8 = 2000000

  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt

  interrupts();             // enable all interrupts

}


ISR( TIMER1_COMPA_vect )          // timer overflow interrupt service routine
{

  if (ACTIVE) // check counter
  {  
    if(count > SPEED){          
      digitalWrite(plsPin, digitalRead(plsPin) ^ 1);
      count = 0;
    }
    else {
      count++;
    }
  }
}


int STATE = 0;

void loop()
{
  //if (OCR1A < 100){OCR1A = 100;}
  //if (ACTIVE == false) {digitalWrite(mf, HIGH);}
  //safetySwitch();
  //set steps to zero
  //while (steps < 12800){OCR1A = 12000;}
//    OCR1A = spdDefault;
//    delay(1000);
//    OCR1A = 300;
//    delay(1000);

  if(STATE == 0){
    SPEED = 0;
    STATE++; 
  }
  else if(STATE == 1){
    SPEED = 100;
    STATE++;
  }
  else if(STATE == 2) {
    SPEED = 50; 
    STATE++;
  }
  else {

    STATE = 0;
  }
  
  delay(1000);
}
